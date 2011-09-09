/*******************************************************************************************************
 * tw_dma.c                 DMA functions                                                              *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Chipcon CC1110/CC2510                                                             *
 * Author:                  TBR, KHO, ESY, MJB                                                         *
 * Last Update:             02 June 2009                                                               *
 ******************************************************************************************************/

//-------------------------------------------------------------------------------------------------------

// Includes

#include "twoway.h"

// external variables

extern UINT8  __xdata audioIn[2*ADC_SAMPLES];     // Audio in from remote microphone (96 samples, 192 bytes)
extern UINT8  __xdata USB_fifo_all[4*96];         // Audio data in USB format (48 samples, repeated)         

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

  INT_GLOBAL_ENABLE(INT_ON);        // Re-enable interrupts
}

////////////////////////////////////////////////////////////////////////////////
/// @brief	This function configures DMA transfer from the radio to an RX buffer.
///
/// @param[in]  dstAddr
///             The start address in __xdata space to where the data is to be stored
///             length
///             Nunber of data bytes to be transferred
///
/// Uses DMA Channel 1
///
////////////////////////////////////////////////////////////////////////////////

void dmaFromRadio(WORD length, WORD dstAddr){
  SET_WORD(DmaDesc1_4[0].SRCADDRH, DmaDesc1_4[0].SRCADDRL, &X_RFD);     // Set RFD register as source
  SET_WORD(DmaDesc1_4[0].DESTADDRH, DmaDesc1_4[0].DESTADDRL, dstAddr);  // RX buffer address
  SET_WORD(DmaDesc1_4[0].LENH, DmaDesc1_4[0].LENL, length);             // Set the length of the transfer (bytes)
  DmaDesc1_4[0].VLEN       = VLEN_USE_LEN;                              // Use the length field
  DmaDesc1_4[0].PRIORITY   = PRI_GUARANTEED;
  DmaDesc1_4[0].M8         = M8_USE_8_BITS;
  DmaDesc1_4[0].IRQMASK    = IRQMASK_ENABLE;      // Raise IRCON.DMAIF upon DMA completion.
  DmaDesc1_4[0].DESTINC    = DESTINC_1;           // The increment the destination address
  DmaDesc1_4[0].SRCINC     = SRCINC_0;            // The source address is constant
  DmaDesc1_4[0].TRIG       = DMATRIG_RADIO;       // DMA is started by the radio receiver.
  DmaDesc1_4[0].TMODE      = TMODE_SINGLE;        // One byte is transferred at each DMA trigger.
  DmaDesc1_4[0].WORDSIZE   = WORDSIZE_BYTE;       // Byte transfer.

  return;
}


////////////////////////////////////////////////////////////////////////////////
/// @brief	This function configures DMA transfer to the audioIn buffer
///
/// Sets the audioIn buffer as the destination. The source address is NOT set, nor is 'SRCINC' field. 
/// These parameters must be set prior to the DMA request
///
/// Uses DMA Channel 3
///
////////////////////////////////////////////////////////////////////////////////

void dmaToAudioIn(){
   SET_WORD(DmaDesc1_4[2].DESTADDRH, DmaDesc1_4[2].DESTADDRL, audioIn);     // Set the audioIn buffer as the destination
   DmaDesc1_4[2].LENL = 192;                       // Set the length of the transfer (bytes)                                 
   DmaDesc1_4[2].LENH = 0;
   DmaDesc1_4[2].VLEN      = VLEN_FIXED;
   DmaDesc1_4[2].PRIORITY  = PRI_LOW;
   DmaDesc1_4[2].M8        = M8_USE_8_BITS;       // Transferring all 8 bits in each byte.
   DmaDesc1_4[2].IRQMASK   = IRQMASK_DISABLE;     // No interrupt on DMA completion.
   DmaDesc1_4[2].DESTINC   = DESTINC_1;           // Increment the destination address by 1 
   DmaDesc1_4[2].TRIG      = DMATRIG_NONE;        // Triggered by setting DMAREQ
   DmaDesc1_4[2].TMODE     = TMODE_BLOCK;
   DmaDesc1_4[2].WORDSIZE  = WORDSIZE_BYTE;       // One byte is transferred each time.

   return;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief	This function configures DMA transfer to the active audioOut buffer
///
/// Sets the USB_fifo_all buffer as the source. The detination address is NOT set, 
/// this parameter must be set prior to the DMA request
///
/// Uses DMA Channel 4
///
////////////////////////////////////////////////////////////////////////////////

void dmaToAudioOut(){
   SET_WORD(DmaDesc1_4[3].SRCADDRH, DmaDesc1_4[3].SRCADDRL, USB_fifo_all);    // Set the USB_fifo_all as the source
   SET_WORD(DmaDesc1_4[3].LENH, DmaDesc1_4[3].LENL, 192);                     // Set the length of the transfer (bytes)                                 
   DmaDesc1_4[3].VLEN      = VLEN_FIXED;
   DmaDesc1_4[3].PRIORITY  = PRI_LOW;
   DmaDesc1_4[3].M8        = M8_USE_8_BITS;       // Transferring all 8 bits in each byte.
   DmaDesc1_4[3].IRQMASK   = IRQMASK_DISABLE;     // No interrupt on DMA completion.
   DmaDesc1_4[3].SRCINC   =  SRCINC_1;            // Increment the source address
   DmaDesc1_4[3].DESTINC   = DESTINC_1;           // Increment the destination address 
   DmaDesc1_4[3].TRIG      = DMATRIG_NONE;        // Triggered by setting DMAREQ
   DmaDesc1_4[3].TMODE     = TMODE_BLOCK;
   DmaDesc1_4[3].WORDSIZE  = WORDSIZE_BYTE;       // One byte is transferred each time.

   return;
}



///////////////////////////////////////////////////////////////////////////////
/// @brief	This function configures DMA to transfer data into the USB fifo
///             
/// The source address is NOT set, nor is 'SRCINC' field 
/// These parameters must be set prior to the DMA request
///
/// Uses DMA Channel 0
///
////////////////////////////////////////////////////////////////////////////////

void dmaToUSBfifo(){
  
  SET_WORD(DmaDesc0.DESTADDRH, DmaDesc0.DESTADDRL, &USBF4);
  DmaDesc0.DESTINC = DESTINC_0;             // The destination address is constant
  DmaDesc0.VLEN     = VLEN_FIXED;
  DmaDesc0.LENH     = 0;
  DmaDesc0.LENL     = 96;
  DmaDesc0.WORDSIZE = WORDSIZE_BYTE;
  DmaDesc0.TMODE    = TMODE_BLOCK;
  DmaDesc0.TRIG     = DMATRIG_NONE;         // Triggered by setting DMAREQ
                                               
  DmaDesc0.IRQMASK    = IRQMASK_DISABLE;
  DmaDesc0.PRIORITY   = PRI_LOW;
  
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




