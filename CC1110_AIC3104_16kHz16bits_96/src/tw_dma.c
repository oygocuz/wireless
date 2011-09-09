/*
 *******************************************************************************************************
 * tw_dma.c                 DMA functions                                                              *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Texas Instruments CC1110/CC2510                                            *
 * Author:                  TBR, KHO, ESY, MJB                                                         *
 * Last Update:            06 April 2011                                                               *
 *******************************************************************************************************
*/

// Includes

#include "board.h"

//The following two #defines were lifted from "hal_CC2510.h' (Feb 2008)

#define DMATRIG_ADC_I2S_RX DMATRIG_ADC_CH6      // I2S word/byte received
#define DMATRIG_ADC_I2S_TX DMATRIG_ADC_CH7      // I2S word/byte transmitted

// Global variables

DMA_DESC __xdata DmaDesc0;
DMA_DESC __xdata DmaDesc1_4[4];
extern UINT8 __xdata frametime;

////////////////////////////////////////////////////////////////////////////////
/// @brief	Interrupt routine for DMA generated interrupts.
///
/// This interrupt routine is run each time the DMA generates an interrupt.
/// According to the interrupt flag of the DMA channel, the corresponding
/// callBackFunction is called. The interrupt flags are cleared.
////////////////////////////////////////////////////////////////////////////////

#pragma vector=DMA_VECTOR
__interrupt void dma_IRQ (void){
  INT_GLOBAL_ENABLE(INT_OFF);       // Stop all other interrupts
  DMAIF = 0;                        // Clear the main CPU interrupt flag

  INT_SETFLAG(INUM_DMA, INT_CLR);   // Clear the DMA IRQ flag
  
  if (DMAIRQ & DMA_CHANNEL_4) {     // DMA Channel 4 is used to transfer audio data from the CODEC (I2SRX) to the audioOut buffer
    DMAIRQ &= ~DMA_CHANNEL_4;
    activeOut ^= 0x01;              // Switch Buffers
    if (activeOut == 0)
      SET_WORD(DmaDesc1_4[3].DESTADDRH, DmaDesc1_4[3].DESTADDRL, audioOut[1]);
    else 
      SET_WORD(DmaDesc1_4[3].DESTADDRH, DmaDesc1_4[3].DESTADDRL, audioOut[0]);
    audioFrameReady = TRUE;
    DMA_ARM_CHANNEL(4);
  }

  INT_GLOBAL_ENABLE(INT_ON);        // Re-enable interrupts
}

////////////////////////////////////////////////////////////////////////////////
/// @brief	This function configures DMA transfer to the radio from a TX buffer.
///
///
/// @param[in]  length
///             The length (bytes) of packet to move from TX buffer
///
/// @param[in]  srcAddr
///             The start address in __xdata space into which the data to be transferred.
///
/// Uses DMA Channel 2
///
////////////////////////////////////////////////////////////////////////////////

void dmaToRadio(WORD length, WORD srcAddr){
   SET_WORD(DmaDesc1_4[1].SRCADDRH, DmaDesc1_4[1].SRCADDRL, srcAddr);   // TX buffer address
   SET_WORD(DmaDesc1_4[1].DESTADDRH, DmaDesc1_4[1].DESTADDRL, &X_RFD);  // Set RFD register as destination
   SET_WORD(DmaDesc1_4[1].LENH, DmaDesc1_4[1].LENL, length);            // Set the length of the transfer (bytes)
   DmaDesc1_4[1].VLEN      = VLEN_USE_LEN;                              // Use the length field
   DmaDesc1_4[1].PRIORITY  = PRI_LOW;
   DmaDesc1_4[1].M8        = M8_USE_8_BITS;       // Transferring all 8 bits in each byte.
   DmaDesc1_4[1].IRQMASK   = IRQMASK_DISABLE;     // No interrupt on DMA completion.
   DmaDesc1_4[1].DESTINC   = DESTINC_0;           // The destination address is constant
   DmaDesc1_4[1].SRCINC    = SRCINC_1;            // The address for data fetch is inremented by 1 byte
                                                  // after each transfer.
   DmaDesc1_4[1].TRIG      = DMATRIG_RADIO;       // DMA is started by writing the radio
   DmaDesc1_4[1].TMODE     = TMODE_SINGLE;        // Byte for byte is transferred.
   DmaDesc1_4[1].WORDSIZE  = WORDSIZE_BYTE;       // One byte is transferred each time.

   return;
}

////////////////////////////////////////////////////////////////////////////////
/// This function configures DMA transfer from the AudioOut buffer to the CODEC (DMA Channel 3)
/// And from the CODEC to the AudioIn buffer (DMA Channel 4)
////////////////////////////////////////////////////////////////////////////////

void dmaAudio(void){

// Setup DMA descriptor for Audio from CODEC using DMA Channel 4
// Audio from the CODEC goes into the 'audioOut' buffer to be transmitted
  
  SET_WORD(DmaDesc1_4[3].SRCADDRH, DmaDesc1_4[3].SRCADDRL, &I2SDATL);
  SET_WORD(DmaDesc1_4[3].DESTADDRH, DmaDesc1_4[3].DESTADDRL, audioOut[0]);
  DmaDesc1_4[3].VLEN       = VLEN_FIXED;
  DmaDesc1_4[3].LENH       = 0;
  DmaDesc1_4[3].LENL       = AF_BUF_SIZE;
  DmaDesc1_4[3].WORDSIZE   = WORDSIZE_WORD;
  DmaDesc1_4[3].TMODE      = TMODE_SINGLE;
  DmaDesc1_4[3].TRIG       = DMATRIG_ADC_I2S_RX;  
  DmaDesc1_4[3].SRCINC     = SRCINC_0;
  DmaDesc1_4[3].DESTINC    = DESTINC_1;
  DmaDesc1_4[3].IRQMASK    = IRQMASK_ENABLE;
  DmaDesc1_4[3].M8         = M8_USE_8_BITS;
  DmaDesc1_4[3].PRIORITY   = PRI_LOW;

  return;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief	This function configures DMA transfer a block of data
///             from 'srcAddr' to 'dstAddr'
///
/// @param[in]  length - the number of words to be transferred
///
/// Uses DMA Channel 0
///
////////////////////////////////////////////////////////////////////////////////

void dmaMemtoMem(UINT8 length){
  
  DmaDesc0.VLEN       = VLEN_FIXED;
  DmaDesc0.LENH       = 0;
  DmaDesc0.LENL       = length;
  DmaDesc0.WORDSIZE   = WORDSIZE_WORD;
  DmaDesc0.TMODE      = TMODE_BLOCK;
  DmaDesc0.TRIG       = DMATRIG_NONE;       // Triggered by setting DMAREQ
  DmaDesc0.DESTINC    = DESTINC_1;          // Increment destination address
  DmaDesc0.IRQMASK    = IRQMASK_DISABLE;
  DmaDesc0.PRIORITY   = PRI_LOW;
  
  return;
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




