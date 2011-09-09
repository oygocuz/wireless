/*******************************************************************************************************
 * tw_rf.c                  Radio Initilization, Packet Send Routines                                  *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         TexasInstruments CC1110                                                    *
 * Author:                  MJB                                                                        *
 * Last Update:             06 April 2011                                                              *
 ******************************************************************************************************/

// Includes

#include "board.h"

// Global variables

#define GDO0MSK 0x20        // GDO0 appears on bit 5 of P1

volatile UINT8 __xdata rxPacketStatus;
BOOL dmaDone;

TX_MASTER_STRUCT __xdata MAStxData;     // TX packet buffer for data from Master to Slave

// Local variables

char  __xdata marcstate;

UINT8 __xdata syncdetected;

////////////////////////////////////////////////////////////////////////////////
/// @brief	Configures the Radio
///
////////////////////////////////////////////////////////////////////////////////

void rfConfigRadio() {

  PKTCTRL1 = 0x04;          // No address check. Append status bytes.
  PKTCTRL0 = 0x45;          // Variable packet length. Use CRC. Enable whitening
  PKTLEN = 0xFF;            // Maximum packet length (255 bytes)

// Base Frequency = 902.5 MHz
 
  FREQ2 = 0x22;
  FREQ1 = 0xB6;
  FREQ0 = 0x27;

#ifdef BAUD300MSK

  // Filter BW, data rate.
  MDMCFG4 = 0x1D;           // Data Rate = 300 kbps
  MDMCFG3 = 0x7A;           // Rx filter bandwidth = 650 kHz

  // IF frequency
  FSCTRL1 = 0x10;           // IF Frequency: 406.25 kHz
  FSCTRL0 = 0x00;

  // Modulation format, detection level
  MDMCFG2 = 0x73;           // 30/32 bits sync word detection. MSK modulation.
  MDMCFG1 = 0x23;           // 4 bytes preamble. No FEC.
  MDMCFG0 = 0x3B;           // Channel spacing: 250 kHz

  // Deviation setting
  DEVIATN = 0x00;

#endif

#ifdef BAUD500MSK

  // Filter BW, data rate.
  MDMCFG4 = 0x0E;           // Data Rate = 500 kbps
  MDMCFG3 = 0x3B;           // Rx filter bandwidth = 812.5 kHz

  // IF frequency
  FSCTRL1 = 0x10;           // IF Frequency: 406.25 kHz
  FSCTRL0 = 0x00;

  // Modulation format, detection level
  MDMCFG2 = 0x73;           // 30/32 bits sync word detection. MSK modulation.
  MDMCFG1 = 0x43;           // 8 byte preamble. No FEC.
  MDMCFG0 = 0x3B;           // Channel spacing: 250 kHz

  // Deviation setting
  DEVIATN = 0x00;

#endif

#ifdef BAUD300GFSK

  // Filter BW, data rate.
  MDMCFG4 = 0x1D;           // Data Rate = 300 kbps
  MDMCFG3 = 0x7A;           // Rx filter bandwidth = 650 kHz

  // IF frequency
  FSCTRL1 = 0x12;           // IF Frequency: 457.03 kHz
  FSCTRL0 = 0x00;

  // Modulation format, detection level
  MDMCFG2 = 0x13;           // 30/32 bits sync word detection. GFSK modulation.
  MDMCFG1 = 0x23;           // 4 byte preamble. No FEC.
  MDMCFG0 = 0x3B;           // Channel spacing: 250 kHz

  // Deviation setting
  DEVIATN = 0x65;           // 165 kHz

#endif

#ifdef BAUD300_2FSK

  // Filter BW, data rate.
  MDMCFG4 = 0x1D;           // Data Rate = 300 kbps
  MDMCFG3 = 0x7A;           // Rx filter bandwidth = 650 kHz

  // IF frequency
  FSCTRL1 = 0x12;           // IF Frequency: 457.03 kHz
  FSCTRL0 = 0x00;

  // Modulation format, detection level
  MDMCFG2 = 0x03;           // 30/32 bits sync word detection. 2-FSK modulation.
  MDMCFG1 = 0x23;           // 4 byte preamble. No FEC.
  MDMCFG0 = 0x3B;           // Channel spacing: 250 kHz

  // Deviation setting
  DEVIATN = 0x65;           // 165 kHz

#endif

  // Calibration synth
  MCSM2 = 0x07;
  MCSM1 = 0x30;             // RXOFF_MOODE: Idle; TXOFF_MODE: Idle
  MCSM0 = 0x08;             // Manual FS calibration

  // Frequency offset compensation configuration
  FOCCFG = 0x1D;

  // Bit synchronization
  BSCFG = 0x1C;

  // AGC settings (from SmartRF04)
  AGCCTRL2 = 0xC7;
  AGCCTRL1 = 0x40;
  AGCCTRL0 = 0xB2;

  // Front end settings (from SmartRF04)
  FREND1 = 0xB6;
  FREND0 = 0x10;

  // Synth calibration
  FSCAL3 = 0xEA;
  FSCAL2 = 0x2A;
  FSCAL1 = 0x00;
  FSCAL0 = 0x1F;

  // Output power

  PA_TABLE0 = 0xC0;         // Output power: +10 dBm

  // Calibrate the frequency synth.
  
  SIDLE();
  SCAL();
  while(MARCSTATE != 0x01);   // Wait for calibration to complete
  
  FSCAL3 &= ~0x30;            // Disable charge pump calibration 
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
  RFIF = 0;                               // Clear RF interrupt flag
  RFIM = 0;                               // Clear RF interrupt enable mask
  INT_SETFLAG(INUM_RF,INT_CLR);           // Clear RF interrupt flag in main interrupt register
  INT_ENABLE(INUM_RF,INT_ON);             // Enable RF interrupts
  rfConfigRadio();                        // Initialize the radio
  IOCFG0 = 0x06;                          // Set GDO0 to Sync Word Status

  dmaToRadio(TX_PAYLOAD_LEN + 1, (WORD) &MAStxData);                    // Configure the DMA channel for TX
  DMA_ABORT_CHANNEL(DMA_TX);                                            // Make sure the DMA channel is disarmed.

  INT_ENABLE(INUM_DMA, INT_ON);                                         // Enable DMA interrupts
  return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief	Transmit the packet that is already in the txData TX buffer
///
/// Arms the TX DMA channel, Starts a TX timeout timer, starts TX mode,
/// waits for the timer to expire, forces the CC2510 to idle if it is still
/// in TX mode when the timer expires.
///
/// The packet to transmit must be in the TX buffer txData before calling this function.
///
/// The timeout should be such that the packet is completely transmitted when
/// the timer expires and TX operates normaly.
///
/// How to calculate timeout:
/// Timeout in milliseconds >= Margin + Calibration time + Total packet length in bytes  * 8 / RF baud rate in kilobits pr second
///
/// The total packet length must include preamble, syncword, header, user data and CRC.
/// Calibration time may be included for simplicity even if calibration is not actually performed.
///
/// @param[in]  none
///
/// @return
///         Returns TRUE is the transmission is successful and FALSE if the transceiver was in TX at timeout
////////////////////////////////////////////////////////////////////////////////

BOOL rfSendPacket(UINT8 timeout, UINT8 multiplier) {
  RFTXRXIF = 0;                                 // clear flag as this serves as a trigger for the DMA
  DMA_ARM_CHANNEL(DMA_TX);

  STX();
  macsetT3TimeoutAndWait(timeout, multiplier);  // wait for normal TX operation to complete
  if(MARCSTATE == MARCSTATE_TX) {
    SIDLE();
    DMA_ABORT_CHANNEL(DMA_TX);                  // Abort the TX DMA channel
    return FALSE;
  }
  if(MARCSTATE != MARCSTATE_IDLE) {
    SIDLE();
    DMA_ABORT_CHANNEL(DMA_TX);                  // Abort the TX DMA channel
    return FALSE;
  }
  return TRUE;
}

/***********************************************************************************
  Copyright 2011 Texas Instruments Incorporated. All rights reserved.

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
