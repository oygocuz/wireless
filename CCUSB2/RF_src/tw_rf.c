/*******************************************************************************************************
 *                                                                                                     *
 *        **********                                                                                   *
 *       ************                                                                                  *
 *      ***        ***                                                                                 *
 *      ***   +++   ***                                                                                *
 *      ***   + +   ***     Radio functions                                                            *
 *      ***   +                                                                                        *
 *      ***   + +   ***                                                                                *
 *      ***   +++   ***     rs_rf.c                                                                    *
 *      ***        ***                                                                                 *
 *       ************                                                                                  *
 *        **********                                                                                   *
 *                                                                                                     *
 *******************************************************************************************************
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Chipcon CC2510                                                             *
 * Author:                  TBR, KHO, ESY                                                              *
 *******************************************************************************************************
 * Revision history:        See end of file                                                            *
 ******************************************************************************************************/

//-------------------------------------------------------------------------------------------------------
// Includes

#include "twoway.h"
#include "stdlib.h"         // Note: 'stdlib' defines abs as 'int abs(int)'

//-------------------------------------------------------------------------------------------------------
// Global variables

volatile UINT8 __xdata rxPacketStatus;

RX_SLAVE_STRUCT __xdata SLVrxData;      // RX packet buffer for data from Master to Slave

INT16 __xdata rssi;
INT16 __xdata rssisum = 0;
INT16 __xdata rssiavg = 0;
UINT8 __xdata rssipkts = 0;
UINT8 __xdata rssivalid = 0;            // rssiavg valid when non zero; will remain zero untill 32 packets have been received

UINT8 oops = 0;   // Debug

//-------------------------------------------------------------------------------------------------------
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
  frequency /= 24;                  // <- This is valid only for CC2511 (@24 MHz)
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
/* Deviation = 128.906250 */
/* Base frequency = 901.999878 */
/* Carrier frequency = 905.998901 */
/* Channel number = 20 */
/* Carrier frequency = 905.998901 */
/* Modulated = true */
/* Modulation format = GFSK */
/* Manchester enable = false */
/* Sync word qualifier mode = 30/32 sync word bits detected */
/* Preamble count = 4 */
/* Channel spacing = 199.951172 */
/* Carrier frequency = 905.998901 */
/* Data rate = 249.756 */
/* RX filter BW = 600.000000 */
/* Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word */
/* CRC enable = true */
/* Packet length = 255 */
/* Device address = 0 */
/* Address config = No address check */
/* PA ramping = false */
/* TX power = 0 */
/* RF settings SoC */





void rfConfigRadio() {

  
  ////////////////////////// from rfstudio7, 902, 250
  PKTCTRL0   = 0x05; // packet automation control 
/*CHANNR     = 0x14; // channel number */
FSCTRL1    = 0x0C; // frequency synthesizer control 
//FREQ2      = 0x25; // frequency control word, high byte 
//FREQ1      = 0x95; // frequency control word, middle byte 
//FREQ0      = 0x55; // frequency control word, low byte 
MDMCFG4    = 0x1D; // modem configuration 
//MDMCFG3    = 0x55; // modem configuration 
MDMCFG2    = 0x13; // modem configuration 
MDMCFG1    = 0x23; // modem configuration 
MDMCFG0    = 0x11; // modem configuration 
DEVIATN    = 0x63; // modem deviation setting 
MCSM0      = 0x18; // main radio control state machine configuration 
//FOCCFG     = 0x1D; // frequency offset compensation configuration 
//BSCFG      = 0x1C; // bit synchronization configuration 
//AGCCTRL2   = 0xC7; // agc control 
AGCCTRL1   = 0x00; // agc control 
AGCCTRL0   = 0xB0; // agc control 
FREND1     = 0xB6; // front end rx configuration 
//FSCAL3     = 0xEA; // frequency synthesizer calibration 
FSCAL2     = 0x2A; // frequency synthesizer calibration 
//FSCAL1     = 0x00; // frequency synthesizer calibration 
FSCAL0     = 0x1F; // frequency synthesizer calibration 
//TEST1      = 0x31; // various test settings 
//TEST0      = 0x09; // various test settings 
PA_TABLE0  = 0x8E; // pa power setting 0 
//IOCFG0     = 0x06; // radio test signal configuration (p1_5) 
/*LQI        = 0x7F; // demodulator estimate for link quality */
/*VCO_VC_DAC = 0xA4; // current setting from pll calibration module */
  ///////////////////////////////////////////////////////
// Set base Frequency
  
  SetRadioFrequency(BASE_FREQUENCY_IN_KHZ);
  
  PKTCTRL1 = 0x00;          // No address check. Do not append status bytes.
  PKTCTRL0 = 0x44;          // Fixed length. Use CRC. Enable whitening
  PKTLEN = RX_PAYLOAD_LEN + PHY_FIELD_LEN;            

  // Filter BW, data rate.
  MDMCFG4 = 0x0E;           // Data Rate = 500 kbps
  MDMCFG3 = 0x55;           // Rx filter bandwidth = 750 kHz

  // IF frequency
  FSCTRL1 = 0x10;           // IF Frequency: 406.25 kHz
  FSCTRL0 = 0x00;

  // Modulation format, detection level
  MDMCFG2 = 0x73;           // 30/32 bits sync word detection. MSK modulation.
  MDMCFG1 = 0x43;           // 8 byte preamble. No FEC.
  MDMCFG0 = 0x55;           // Channel spacing: 250 kHz

  // Deviation setting
  DEVIATN = 0x00;

  // Calibration synth
  MCSM2 = 0x07;
  MCSM1 = 0x30;             // RXOFF_MOODE: Idle; TXOFF_MODE: Idle
  MCSM0 = 0x04;             // Manual Calibration using SCAL

  // Frequency offset compensation configuration
  FOCCFG = 0x1D;

  // Bit synchronization
  BSCFG = 0x1C;

  // AGC settings (from SmartRF04)
  AGCCTRL2 = 0xC7;
  AGCCTRL1 = 0x40;
  AGCCTRL0 = 0xB2;

  // Front end settings (from SmartRF04)
  FREND1 = 0x56;
  FREND0 = 0x10;

  // Synth calibration
  FSCAL3 = 0xEA;
  FSCAL2 = 0x0A;
  FSCAL1 = 0x00;
  FSCAL0 = 0x11;
  
  // Test registers (from SmartRF Studio)
  TEST2 = 0x88;
  TEST1 = 0x31;
  TEST0 = 0x09;

  // Output power

  PA_TABLE0 = 0xFF;         // Output power: +1 dBm

  SIDLE();
  while (MARCSTATE != MARCSTATE_IDLE);    // Wait for state
 
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

  txStatus = TX_IDLE;
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
//      if ((P1 & GDO0MSK) > 0)           // If SYNC has been detected (GDO0 is high)
      if ((PKTSTATUS & 0x08))
        syncdetected = 1;
//      if ((syncdetected == 1) &&  ((P1 & GDO0MSK) == 0)) {
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
