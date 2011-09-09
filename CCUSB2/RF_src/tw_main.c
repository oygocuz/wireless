/*
 *******************************************************************************************************
 * tw_main.c                For use with "CODEC EVM REV B" cards                                       *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Chipcon CC2510                                                             *
 * Author:                  MJB                                                                        *
 * Last Update:             03 June 2009                                                               *
 ******************************************************************************************************/

//-------------------------------------------------------------------------------------------------------
// Includes
#include "twoway.h"
#include "codec_TLV320AIC26.h"
#include "intrinsics.h"

//-------------------------------------------------------------------------------------------------------

// Global variables
UINT16 __xdata audiocontrol1; 
UINT16 __xdata adcgainctrl; 

volatile BYTE __xdata rxStatus = 0;
volatile BYTE __xdata txStatus = 0;

// External variables

extern const UINT8 HoppingChannels[TOTAL_NUM_CHANNELS];

#ifdef SLAVE
UINT8   __xdata activeIn = 0;               // Audio In (to Codec) active buffer (0 | 1)
UINT16  __xdata audioIn[2][AF_BUF_SIZE];    // Audio In (to Codec) data buffer
#else
UINT8   __xdata activeOut = 0;              // Audio Out (from Codec) active buffer (0 | 1)
UINT16  __xdata audioOut[2][AF_BUF_SIZE];   // Audio Out (from Codec) data buffer
UINT16  __xdata crap[2][AF_BUF_SIZE];
#endif

// Note: The concept of 'In' and 'Out' is rather confusing, as is the concept of 'RX' and 'TX'. Here, 'RX' and 'TX"
// refer to the RF transceiver, NOT to the I2S RX and TX functions.
//
// The AudioIn buffer conatins audio samples to be sent to the Codec that were received (RX) from the Slave (if Master) or from the Master (if Slave).
// The AudioOut buffer conatins audio samples obtained from the Codec that will be sent (TX) to the Slave (if Master) or to the Master (if Slave).

BOOL   waitingforbeacon = TRUE;
UINT8  i, j;
UINT8  first_byte;
UINT8  lostpkts = 0;
UINT16 packets = 0;
UINT8  optionstatus = 0xC0;           // The option bits (P0_6 and P0_7) are 'pulled high' by default (i.e., low true)
UINT16 __xdata audionull = 0x1300;    // I2S data for muted audio
UINT8  __xdata t2cnta, t2cntb;

UINT8 __xdata frametime;              // T2 (frametimer) count when DMA switches from using buffer B to using Buffer A
UINT16 __xdata atstart;

extern __xdata INT16 rssiavg;
extern __xdata UINT8 rssivalid;

////////////////////////////////////////////////////////////////////////////////
/// @brief	Application main function.
////////////////////////////////////////////////////////////////////////////////
void main(void) {

  // Initializations
  SET_MAIN_CLOCK_SOURCE(CRYSTAL);
  SET_MAIN_CLOCK_SPEED(MHZ_24);
  CLKCON = (CLKCON & 0xC7);

  init_peripherals();
  
  initCodec();        // Initilize the Codec
  
  INT_SETFLAG(INUM_DMA, INT_CLR);         // clear the DMA interrupt flag
  I2SCFG0 |= 0x01;                        // Enable the I2S interface

  DMA_SET_ADDR_DESC0(&DmaDesc0);          // Set up DMA configuration table for channel 0
  DMA_SET_ADDR_DESC1234(&DmaDesc1_4[0]);  // Set up DMA configuration table for channels 1 - 4
  dmaMemtoMem(AF_BUF_SIZE);               // Set up DMA Channel 0 for memmory to memory data transfers
  initRf();                               // Set radio base frequency and reserve DMA channels 1 and 2 for RX/TX buffers
  dmaAudio();                             // Set up DMA channels 3 and 4 for the Audio In/Out buffers
  DMAIRQ = 0;
#ifdef SLAVE 
  DMA_ARM_CHANNEL(3);                     // Arm DMA channels 2 (CODEC Rx)
#else
  DMA_ARM_CHANNEL(4);                     // Arm DMA channels 3 (CODEC Tx)
#endif

  macTimer3Init();

  INT_ENABLE(INUM_T1, INT_ON);            // Enable Timer 1 interrupts
  INT_ENABLE(INUM_DMA, INT_ON);           // Enable DMA interrupts
  INT_GLOBAL_ENABLE(INT_ON);              // Enable Global interrupts

#ifdef MASTER

// Master Code
   
  MAStxData.macPayloadLen = TX_PAYLOAD_LEN;
  MAStxData.macField = MAC_ADDR;
  MAStxData.statusField = 0x00;
  
//  setChannel(10);                       // set frequency to 2402 + 10*.25 = 2404.5 MHz
//  SCAL();                               // Start PLL calibration at new channel
//  while (MARCSTATE != 0x01);            // Wait for calibration to complete

  while (1)  {        // main program loop
//    setChannel(HoppingChannels[ActiveChIdx]);     // SetChannel will set the MARCSTATE to IDLE
//    ActiveChIdx++;
//    if (ActiveChIdx == TOTAL_NUM_CHANNELS)
//      ActiveChIdx = 0;
//    SCAL();           // Start PLL calibration at new channel

    if ((P0 & 0x40) != optionstatus) {                  // if the 'SEL AUX IN' option bit has changed state
      if ((P0 & 0x40) == 0) {                           // SEL AUX IN has changed state to true
        audiocontrol1 |= 0x1000;                        // CODEC ADC Input: 'Single-ended AUX'
        writeCodecRegister(AUDIO_CONTROL_1, audiocontrol1); 
        adcgainctrl &= 0x0001;                          // Set ADC gain to 0 dB
        writeCodecRegister(ADC_GAIN_CONTROL, adcgainctrl);      
        optionstatus &= ~0x40;
      }
      else {                                            // SEL AUX IN has changed state to false
        audiocontrol1 &= ~0x1000;                       // CODEC ADC Input: 'Single-ended MICIN'
        writeCodecRegister(AUDIO_CONTROL_1, audiocontrol1);    
        adcgainctrl |= 0x3400;                          // Set ADC gain to 26 dB
        writeCodecRegister(ADC_GAIN_CONTROL, adcgainctrl);      
        optionstatus |= 0x40;
      }
    }
     
    if ((P0 & 0x80) != optionstatus) {          // if the 'ENA AGC' option bit has changed state
      if ((P0 & 0x80) == 0) {                   // ENA AGC has changed state to true
        adcgainctrl |= 0x0001;                  // Enable the AGC
        writeCodecRegister(ADC_GAIN_CONTROL, adcgainctrl);      
        optionstatus &= ~0x80;
      }
      else {                                    // SEL AUX IN has changed state to false
        adcgainctrl &= ~0x0001;                 // Disable the AGC
        writeCodecRegister(ADC_GAIN_CONTROL, adcgainctrl);      
        optionstatus |= 0x80;
      }    
    }
    
// Now wait for the "audio frame ready" signal
    
    while (audioFrameReady == FALSE);     // Wait until an audioframe is ready to be transmitted
        
    audioFrameReady = FALSE;              // Reset the flag

// Move data from the CODEC (audioOut) buffer to the TX buffer using DMA Channel 0

    SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut[activeOut]);
    SET_WORD(DmaDesc0.DESTADDRH, DmaDesc0.DESTADDRL, MAStxData.payload);
    DmaDesc0.SRCINC = SRCINC_1;             // Increment Source address 
    DMAARM |= DMA_CHANNEL_0;
    DMAREQ |= DMA_CHANNEL_0;                // Enable memory-to-memory transfer using DMA channel 0
    while ((DMAARM & DMA_CHANNEL_0) > 0);   // Wait for transfer to complete

//    while (MARCSTATE != 0x01);            // Wait for calibration to complete

    T2CT = FRAME_TIMEOUT_DEFAULT;         // Reset the Frame Timer just prior to enabling the TX

#ifdef CC2590 
    P2 |= 0x10;             // set P2_4 (T/R)
    rfSendPacket(MASTER_TX_TIMEOUT_WO_CALIB);
    P2 &= ~0x10;            // reset P2_4 (T/R)
#else
    rfSendPacket(MASTER_TX_TIMEOUT_WO_CALIB);
#endif

  }   // end of 'while (1)' loop

#else

// Slave Code

// Initilize Timer 2 (Frame Timer)

  T2CT = 0;         // Stop the timer
  T2PR = 6;         // Timer Prescale Multipler
  T2CTL = 0x01;     // Set Tick period to 128 * T2PR clock cycles (128*6/26.0 = 29.538 usec)
                    // Interrupts Disabled
//  setChannel(10);                       // set frequency to 2402 + 10*.25 = 2404.5 MHz
//  SCAL();                               // Start PLL calibration at new channel
//  while (MARCSTATE != 0x01);            // Wait for calibration to complete
  
#ifdef CC2590
  P2 |= 0x08;       // Enable High Gain Mode
#endif
  
  while (1)  {                              // main program loop
    if (waitingforbeacon) {
      LED_GREEN_REG &= ~LED_GREEN;          // Extinguish the Green (paired) LED
      LED_YELLOW_REG |= LED_YELLOW;         // Light the Yellow LED (Waiting for Beacon)
//      setChannel(HoppingChannels[0]);       // Listen on channel[0] for the beacon
//      SCAL();                               // Start PLL calibration at new channel
//      while (MARCSTATE != MARCSTATE_IDLE);  // Wait for calibration to complete

      while (1) {                           // Stay in this loop until the Beacon is heard
        ListenforMaster(&SLVrxData, LISTEN_FOR_BEACON_TIMEOUT, DMA_RX, RX_PAYLOAD_LEN);
        if (rxPacketStatus == PKT_OK)
          break;
      }   // end of 'while (1)' loop

      LED_YELLOW_REG &= ~LED_YELLOW;        // Extinguish the Yellow LED (Waiting for Beacon)
      LED_GREEN_REG |= LED_GREEN;           // Light the Green ('Paired') LED
      lostpkts = 0;
//      ActiveChIdx = 1;                      // set up next channel
      waitingforbeacon = FALSE;             // Exit 'waitingforbeacon' mode
      T2CT = FRAME_TIMEOUT_DEFAULT;         // Reset the Frame Timer
    }     // end of 'waitingforbeacon' if

    else {                                // We are 'Paired'

// Listen for packet from Master

//      if ((frametime > 0xD0) && (frametime < 0xEE))     // if in the so called 'bad zone' ...
//        I2SCLKF1 -= 1;                                  // speed up the I2S bit clock

//      if ((frametime > 0x10) && (frametime < 0x5F))     // if in the so called 'good zone' ...
//        I2SCLKF1 = 0x59;                                // reset the bit clock frequency to 256 kbps

#ifdef CC2590
      if (rssivalid > 0) {
        if (rssiavg < 30) 
          P2 &= ~0x08;                          // Enable Low Gain Mode
        if (rssiavg > 65)
          P2 |= 0x08;                           // Enable High Gain Mode
      }
#endif
      
//      while (MARCSTATE != MARCSTATE_IDLE);      // Wait for calibration to complete (Machine State = Idle)

      while (T2CT > LISTENFORMASTER);           // Wait until it's time to listen for the Master

      rfReceivePacket(&SLVrxData, SLAVE_RX_SYNC_TIMEOUT, DMA_RX, RX_PAYLOAD_LEN, 0);

      if (rxPacketStatus == TIMEOUT_ERROR)
        while (T2CT > END_OF_FRAME);            // let the frame timer run down to the end of a frame

      T2CT = FRAME_TIMEOUT_DEFAULT;       // Reset the Frame Timer
    }     // end of waitingforbeacon 'else' loop

    SIDLE();          // Force the Receiver into the Idle state

// Set the next channel and initiate calibration
//    setChannel(HoppingChannels[ActiveChIdx]);     // SetChannel will force the MARCSTATE to IDLE
//    ActiveChIdx++;
//    if (ActiveChIdx == TOTAL_NUM_CHANNELS)
//      ActiveChIdx = 0;
//    SCAL();                         // Start PLL calibration at new channel

    if (rxPacketStatus == TIMEOUT_ERROR) {
      LED_RED_REG |= LED_RED;       // light the Red (Paket Lost) LED

// fill the audioIn buffer with 'nulls', so as to mute the audio

      SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, &audionull);
      SET_WORD(DmaDesc0.DESTADDRH, DmaDesc0.DESTADDRL, audioIn[activeIn]);
      DmaDesc0.SRCINC = SRCINC_0;                 // Do not increment Source address 
      DMAARM |= DMA_CHANNEL_0;
      DMAREQ |= DMA_CHANNEL_0;                    // Enable memory-to-memory transfer using DMA channel 0
      while ((DMAARM & DMA_CHANNEL_0) > 0);       // Wait for transfer to complete
      
      lostpkts++;
      if (lostpkts > 4) {           // if 4 consecutive packets have been lost
        lostpkts = 0;
        waitingforbeacon = TRUE;    // enter 'waiting for beacon' (resync) mode
      }
    }
    else {                          // A packet was received
      LED_RED_REG &= ~LED_RED;      // extinguish the Red (Paket Lost) LED
      lostpkts = 0;

      if (rxPacketStatus == PKT_OK) {                       // if a packet was sucessfully received ...
        t2cnta = T2CT;
        
// Transfer audio data from the receive buffer to the audioIn buffer using DMA        
        
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, SLVrxData.payload);
        SET_WORD(DmaDesc0.DESTADDRH, DmaDesc0.DESTADDRL, audioIn[activeIn]);
        DmaDesc0.SRCINC = SRCINC_1;                 // Increment Source address 
        DMAARM |= DMA_CHANNEL_0;
        DMAREQ |= DMA_CHANNEL_0;                    // Enable memory-to-memory transfer using DMA channel 0
        while ((DMAARM & DMA_CHANNEL_0) > 0);       // Wait for transfer to complete
      }
      else {
// fill the audioIn buffer with 'nulls', so as to mute the audio

        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, &audionull);
        SET_WORD(DmaDesc0.DESTADDRH, DmaDesc0.DESTADDRL, audioIn[activeIn]);
        DmaDesc0.SRCINC = SRCINC_0;                 // Do not increment Source address 
        DMAARM |= DMA_CHANNEL_0;
        DMAREQ |= DMA_CHANNEL_0;                    // Enable memory-to-memory transfer using DMA channel 0
        while ((DMAARM & DMA_CHANNEL_0) > 0);       // Wait for transfer to complete
      }
    }     // end of TIMEOUT_ERROR 'else' (i.e., packet received)
  }       // end of 'while (1)' (main program) loop

#endif
}



