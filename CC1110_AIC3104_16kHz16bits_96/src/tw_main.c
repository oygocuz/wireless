/*
 *******************************************************************************************************
 * tw_main.c                For use with "CC110_AIC3104" cards                                         *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Texas Instruments CC1110                                                   *
 * Author:                  MJB                                                                        *
 * Last Update:             06 April 2011                                                              *
 *******************************************************************************************************
*/

//-------------------------------------------------------------------------------------------------------
// Includes
#include "board.h"
#include "TLV320AIC3104.h"

//-------------------------------------------------------------------------------------------------------

// Global variables

const char channel[3][4] = {{ 0, 20,  4, 16},     // Band 1; f = 902.5 MHz, 907.5 MHz, 903.5 MHz, 906.5 MHz
                            {74, 98, 78, 94},     // Band 2; f = 921.0 MHz, 927.0 MHz, 922.0 MHz, 926.0 MHz
                            { 8, 82, 12, 90}};    // Band 3; f = 904.5 MHz, 923.0 MHz, 905.5 MHz, 925.0 MHz


#define MHZ_26          0x00

// Active table index variables 

UINT8 __xdata ActiveChIdx, band;


UINT8   __xdata activeOut = 0;              // Audio Out (from Codec) active buffer (0 | 1)
UINT16  __xdata audioOut[2][AF_BUF_SIZE];   // Audio Out (from Codec) data buffer

// Note: The concept of 'In' and 'Out' is rather confusing, as is the concept of 'RX' and 'TX'. Here, 'RX' and 'TX"
// refer to the RF transceiver, NOT to the I2S RX and TX functions.
//
// The AudioIn buffer conatins audio samples to be sent to the Codec that were received (RX) from the Slave (if Master) or from the Master (if Slave).
// The AudioOut buffer conatins audio samples obtained from the Codec that will be sent (TX) to the Slave (if Master) or to the Master (if Slave).

UINT8  i, j;
UINT8  agc_option_status = 0x04;      // The option bits (P0_6 and P0_7) are 'pulled high' by default (i.e., low true)
UINT8  aux_option_status = 0x08; 

////////////////////////////////////////////////////////////////////////////////
/// @brief	Application main function.
////////////////////////////////////////////////////////////////////////////////
void main(void) {

  // Initializations
  SET_MAIN_CLOCK_SOURCE(CRYSTAL);
  SET_MAIN_CLOCK_SPEED(MHZ_26);
  CLKCON = (CLKCON & 0xC7);

  init_peripherals();
  
  P0 &= ~0x40;                            // Pulse the Codec Reset line (high to low, low to high)
  P0 |= 0x40;
  
  init_codec();                           // Initilize the Codec
  
  INT_SETFLAG(INUM_DMA, INT_CLR);         // clear the DMA interrupt flag
  I2SCFG0 |= 0x01;                        // Enable the I2S interface

  DMA_SET_ADDR_DESC0(&DmaDesc0);          // Set up DMA configuration table for channel 0
  DMA_SET_ADDR_DESC1234(&DmaDesc1_4[0]);  // Set up DMA configuration table for channels 1 - 4
  dmaMemtoMem(AF_BUF_SIZE);               // Set up DMA Channel 0 for memmory to memory data transfers
  initRf();                               // Set radio base frequency and reserve DMA channels 1 and 2 for RX/TX buffers
  dmaAudio();                             // Set up DMA channels 3 and 4 for the Audio In/Out buffers
  DMAIRQ = 0;
  DMA_ARM_CHANNEL(4);                     // Arm DMA channel 4

  macTimer3Init();

  INT_ENABLE(INUM_T1, INT_ON);            // Enable Timer 1 interrupts
  INT_ENABLE(INUM_DMA, INT_ON);           // Enable DMA interrupts
  INT_GLOBAL_ENABLE(INT_ON);              // Enable Global interrupts

  MAStxData.macPayloadLen = TX_PAYLOAD_LEN;
  MAStxData.macField = MAC_ADDR;

  while (1)  {        // main program loop
    setChannel(channel[band][ActiveChIdx]);             // SetChannel will set the MARCSTATE to IDLE
    ActiveChIdx = (ActiveChIdx + 1) & 0x03;
    
    SCAL();           // Start PLL calibration at new channel

    if ((P1 & 0x08) != aux_option_status) {             // if the 'SEL AUX IN' option bit has changed state
      if ((P1 & 0x08) == 0) {                           // SEL AUX IN has changed state to true
        I2Cwrite(MIC1LP_LEFTADC, 0xFC);                 // Disconnect MIC1LP/M from the Left ADC, Leave Left DAC enabled
        I2Cwrite(MIC2L_MIC2R_LEFTADC, 0x2F);            // Connect AUX In (MIC2L) to Left ADC
        I2Cwrite(LEFT_ADC_PGA_GAIN, 0x00);              // Set PGA gain to 0 dB
        aux_option_status &= ~0x08;
      }
      else {                                            // SEL AUX IN has changed state to false
        I2Cwrite(MIC2L_MIC2R_LEFTADC, 0xFF);            // Disconnect AUX In (MIC2L) from Left ADC
        I2Cwrite(MIC1LP_LEFTADC, 0x84);                 // Connect the internal microphone to the Left ADC using differential inputs (gain = 0 dB); Power Up the Left ADC
        I2Cwrite(LEFT_ADC_PGA_GAIN, 0x3C);              // Enable PGA and set gain to 30 dB
        aux_option_status |= 0x08;
      }
    }
     
    if ((P1 & 0x04) != agc_option_status) {             // if the 'ENA AGC' option bit has changed state
      if ((P1 & 0x04) == 0) {                           // ENA AGC has changed state to true
        I2Cwrite(LEFT_AGC_CNTRL_A, 0x90);               // Left AGC Control Register A - Enable, set target level to -8 dB
        I2Cwrite(LEFT_AGC_CNTRL_B, 0xC8);               // Left AGC Control Register B - Set maximum gain to  to 50 dB
        I2Cwrite(LEFT_AGC_CNTRL_C, 0x00);               // Left AGC Control Register C - Disable Silence Detection
        agc_option_status &= ~0x04;
      }
      else {                                            // SEL AUX IN has changed state to false
        I2Cwrite(LEFT_AGC_CNTRL_A, 0x10);               // Left AGC Control Register A - Disable
        agc_option_status |= 0x04;
      }    
    }
    
// Check the band selection bits

    band = 2;                             // if the switch is not in position 1 or 2, in must be in position 3
    
    if ((P1 & 0x10) == 0)                 // check if switch is in position 1
      band = 0;
    
    else if ((P0 & 0x04) == 0)            // check if switch is in position 2
      band = 1;
    
// Now wait for the "audio frame ready" signal

    while (audioFrameReady == FALSE);     // Wait until an audioframe is ready to be transmitted
    
    audioFrameReady = FALSE;              // Reset the flag

// Move data from the CODEC (audioOut) buffer to the TX buffer using DMA Channel 0

    SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut[activeOut]);
    SET_WORD(DmaDesc0.DESTADDRH, DmaDesc0.DESTADDRL, MAStxData.payload);
    DmaDesc0.SRCINC = SRCINC_1;           // Increment Source address 
    DMAARM |= DMA_CHANNEL_0;
    DMAREQ |= DMA_CHANNEL_0;              // Enable memory-to-memory transfer using DMA channel 0
    while ((DMAARM & DMA_CHANNEL_0) > 0); // Wait for transfer to complete

    while (MARCSTATE != 0x01);            // Wait for calibration to complete
   
    P2 |= 0x08;                   // Debug - Set P2_3 (TP2)
    rfSendPacket(MASTER_TX_TIMEOUT_WO_CALIB);
    P2 &= ~0x08;                  // Debug - Reset P2_3 (TP2)
  
  }   // end of 'while (1)' loop
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

