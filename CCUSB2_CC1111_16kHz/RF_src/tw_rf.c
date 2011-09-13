/*******************************************************************************************************
 * tw_rf.c                  For use with "CC1111 USB Dongle" cards                                     *
 *                                                                                                     *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Texas Instruments CC1111                                                   *
 * Author:                  MJB                                                                        *
 * Last Update:             18 April 2011                                                              *
 ******************************************************************************************************/

// Includes

#include "twoway.h"
#include "stdlib.h"         // Note: 'stdlib' defines abs as 'int abs(int)'

// Global variables

volatile UINT8 __xdata rxPacketStatus;

RX_SLAVE_STRUCT __xdata SLVrxData;      // RX packet buffer for data from Master to Slave

INT16 __xdata rssi;
INT16 __xdata rssisum = 0;
INT16 __xdata rssiavg = 0;
UINT8 __xdata rssipkts = 0;
UINT8 __xdata rssivalid = 0;            // rssiavg valid when non zero; will remain zero untill 32 packets have been received

// Local variables

char  __xdata marcstate;
UINT8 __xdata syncdetected;

////////////////////////////////////////////////////////////////////////////////
/// @brief	Sets the radio's base frequency
///
/// Updates the FREQx radio registers for the given frequency.
///
/// @param[in]  frequency
///             Radio frequency in kHz
////////////////////////////////////////////////////////////////////////////////

void SetRadioFrequency(UINT32 frequency) {
  frequency = (frequency << 10);
  frequency /= 1000;
  frequency = (frequency << 6);
  frequency /= 24;                  // <- This is valid only for the CC1111 and CC2511 (48 MHz crystal)
  FREQ0 = (BYTE) frequency;
  frequency >>= 8;
  FREQ1 = (BYTE) frequency;
  frequency >>= 8;
  FREQ2 = (BYTE) frequency;
  
  return;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief	Configures the Radio Registers
///
////////////////////////////////////////////////////////////////////////////////



void rfConfigRadio() {

// Set base Frequency
  
  SetRadioFrequency(BASE_FREQUENCY_IN_KHZ);
  
  PKTCTRL1 = 0x00;          // No address check. Do not append status bytes.
//  PKTCTRL0 = 0x44;          // Fixed length. Use CRC. Enable whitening
  PKTCTRL0 = 0x45;          // Variable length packet. Use CRC. Enable whitening
//  PKTLEN = RX_PAYLOAD_LEN + PHY_FIELD_LEN; 
  PKTLEN = 0xFF;  

  // Filter BW, data rate.
  MDMCFG4 = 0x1D;           // Data Rate = 300 kbps
  MDMCFG3 = 0x9A;           // Rx filter bandwidth = 600 kHz

  // IF frequency
  FSCTRL1 = 0x0C;           // IF Frquency = 406.25 kHz
  FSCTRL0 = 0x00;
    
  // Modulation format, detection level
  MDMCFG2 = 0x13;           // 30/32 bits sync word detection. GFSK modulation.
  MDMCFG1 = 0x23;           // 4 byte preamble. No FEC.
  MDMCFG0 = 0x55;           // Channel spacing: 250 kHz

  // Deviation setting
  DEVIATN = 0x66;           // 165 kHz

  // Calibration synth
  MCSM2 = 0x07;
  MCSM1 = 0x30;             // RXOFF_MOODE: Idle; TXOFF_MODE: Idle
  MCSM0 = 0x08;             // Manual Calibration using SCAL

  // Frequency offset compensation configuration
  FOCCFG = 0x1D;

  // Bit synchronization
  BSCFG = 0x1C;

  // AGC settings (from SmartRF04)
  AGCCTRL2 = 0xC7;
  AGCCTRL1 = 0x00;
  AGCCTRL0 = 0xB0;

  // Front end settings (from SmartRF04)
  FREND1 = 0xB6;
  FREND0 = 0x10;

  // Synth calibration
  FSCAL3 = 0xEA;
  FSCAL2 = 0x2A;
  FSCAL1 = 0x00;
  FSCAL0 = 0x1F;
  
  // Test registers (from SmartRF Studio)
  TEST2 = 0x88;
  TEST1 = 0x31;
  TEST0 = 0x09;

  // Output power

  PA_TABLE0 = 0xC0;         // Output power: +10 dBm

  SIDLE();
  while (MARCSTATE != MARCSTATE_IDLE);    // Wait for state to become Idle
 
  return;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief	This function initializes the resources necessary for sending
///             and receiving packets
///
/// Two DMA channels are requested from the DMA administrator and set up to transfer
/// data to and from the necessary RX or TX buffers.
/// The radio is configured to transmit at a defined frequency and to
/// automatically calculate and insert a CRC value when in transmit and to
/// check the CRC value in receive.
///
/// @param[in]  frequency
///             The radio base frequency (channel 0) in kHz
///
/// @return
///             Returns TRUE is the configuration is successful and FALSE otherwise
////////////////////////////////////////////////////////////////////////////////
BOOL initRf() {

  rxStatus = RX_IDLE;

  RFIF = 0;                               // Clear RF interrupt flag
  RFIM = 0;                               // Clear RF interrupt enable mask
  INT_SETFLAG(INUM_RF,INT_CLR);           // Clear RF interrupt flag in main interrupt register
  rfConfigRadio();                        // Initialize the radio
  IOCFG0 = 0x06;                          // Set GDO0 to Sync Word Status

  dmaFromRadio(RX_PAYLOAD_LEN + 1, (WORD) &SLVrxData);                  // Configure the DMA channel for RX
  DMA_ABORT_CHANNEL(DMA_RX);                                            // Make sure the DMA channel is disarmed.

  return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief	Listen for Master
///
/// Returns one of the following in rxStatus:
///
///             TIMEOUT_ERROR:  If SYNC was not detected within the timeout period
///             PKT_ERROR:      If either address or length of received packet was incorrect
///             CRC_ERROR:      CRC error in incomming audio data frame
///             PKT_OK:         Received packet is OK
///
/// Unlike 'rfReceivePacket', this routine will return immediately if a packet is received before the 'timeout' period
//
/// @param[in]  rxData
///             Pointer to the received data
///
////////////////////////////////////////////////////////////////////////////////

void ListenforMaster(RX_SLAVE_STRUCT __xdata * rxData, UINT8 timeout, UINT8 t3_multiplier, BYTE dmaNumber, UINT8 packetlen) {

  P0 |= 0x20;       // Set P0_4 (P4 pin 3)
  SIDLE();                                                // Force Idle state
  rxStatus = RX_WAIT;                                     // Set rxStatus, will be updated if SFD detected
  RFIM = 0x00;                                            // Disable all RF interrupts
  RFIF = 0x00;                                            // Clear all RF interrupts
  INT_SETFLAG(INUM_RF, INT_CLR);                          // Clearing main RF interrupt flags in S1CON[1:0]
  INT_SETFLAG(INUM_DMA, INT_CLR);

  RFTXRXIF = 0x00;

  if ((DMAARM & DMA_CHANNEL_1) != 0x00)                   // If DMA Channel 1 is busy ...
    DMA_ABORT_CHANNEL(dmaNumber);                         // Abort DMA channel
  DMA_ARM_CHANNEL(dmaNumber);                             // Arm DMA channel

  syncdetected = 0;

  SRX();                                // Strobe RX

  for ( int i = 1; i <= t3_multiplier; i++) {
    TIMER3_RUN(FALSE);                  // Stop Timer
    T3CC0 = timeout;                    // Set timeout period
    TIMER3_RUN(TRUE);                   // Start timer

    while (T3CNT > 0) {                 // loop until T3 reaches 0
      if ((PKTSTATUS & 0x08))
        syncdetected = 1;
      if ((syncdetected == 1) &&  (MARCSTATE == MARCSTATE_IDLE)) {  

// Packet received. Check address field and CRC error

        if (rxData->macPayloadLen != packetlen)
          rxPacketStatus = PKT_ERROR;             // Return Packet error
        else if ((PKTSTATUS & CRC_OK_MASK) == 0)  // Check for CRC Error
          rxPacketStatus = CRC_ERROR;             // Return CRC error
        else
          rxPacketStatus = PKT_OK;

        TIMER3_RUN(FALSE);                // Stop timer
        P0 &= ~0x20;       // Reset P0_4 (P4 pin 3)
        return;
      }         // end of 'sfdDetected' if
    }           // end of 'while' loop - if reached, T3CNT has reached 0
  }             // end of 'for' loop - if reached, SYNC was not detected within timeout period

  rxPacketStatus = TIMEOUT_ERROR;
  P0 &= ~0x20;       // Reset P0_4 (P4 pin 3)
  
  return;
}

/***********************************************************************************
  Copyright 2009 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
***********************************************************************************/

