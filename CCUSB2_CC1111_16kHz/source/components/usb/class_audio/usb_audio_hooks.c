/***********************************************************************************

    Filename:	usb_audio_hooks.c

    Contains the necessary hook functions for various USB request processing
    that is featured from the USB firmware library. Some
    functions are empty.

***********************************************************************************/

//Stolen and modified from usb_hid_hooks

/***********************************************************************************
* INCLUDES
*/
//#include "simple_hid.h"
#include "hal_int.h"

#include "usb_firmware_library_headers.h"
#include "usb_class_requests.h"
#include "twoway.h"

/***********************************************************************************
* GLOBAL DATA
*/

extern int __xdata SINE_TABLE[48];
extern volatile UINT8 __xdata activeOut;              // Audio Out active buffer (0 | 1)
extern struct AUDIO_OUT_STRUCT audioOut;

// Local Data

uint8 oldEndpoint;
int8  null = 0;
uint8 failed_to_send = 0;
uint8 whichbuffer = 0;

// ****************************************************************************************
// All Hooks and functions required by the USB library.
// ****************************************************************************************

// **************** Process USB class requests with OUT data phase ************************
void usbcrHookProcessOut(void)
{
    // Process USB class requests with OUT data phase, or stall endpoint 0 when unsupported
    switch (usbSetupHeader.request) {
    case AUD_REQ_SET_CUR :    usbcrSetCur(); break;
    default:            usbfwData.ep0Status = EP_STALL; break;
    }
}


// **************** Process USB class requests with IN data phase *************************
void usbcrHookProcessIn(void)
{
    // Process USB class requests with IN data phase, or stall endpoint 0 when unsupported
    switch (usbSetupHeader.request) {
    case AUD_REQ_GET_CUR :    usbcrGetCur(); break;
    case AUD_REQ_GET_MIN :    usbcrGetMin(); break;
    case AUD_REQ_GET_MAX :    usbcrGetMax(); break;
    case AUD_REQ_GET_RES :    usbcrGetRes(); break;
    default:            usbfwData.ep0Status = EP_STALL; break;
    }
}


// ********************************  Unsupported USB hooks ********************************
void usbvrHookProcessOut(void) { usbfwData.ep0Status = EP_STALL; }
void usbvrHookProcessIn(void) { usbfwData.ep0Status = EP_STALL; }

// ************************  unsupported/unhandled standard requests **********************
void usbsrHookSetDescriptor(void) { usbfwData.ep0Status = EP_STALL; }
void usbsrHookSynchFrame(void) { usbfwData.ep0Status = EP_STALL; }
void usbsrHookClearFeature(void) { usbfwData.ep0Status = EP_STALL; }
void usbsrHookSetFeature(void) { usbfwData.ep0Status = EP_STALL; }
void usbsrHookModifyGetStatus(uint8 recipient, uint8 index, uint16 __xdata *pStatus) { }


// ************************ USB standard request event processing *************************
void usbsrHookProcessEvent(uint8 event, uint8 index)
{
    // Process relevant events, one at a time.
    switch (event) {
    case USBSR_EVENT_CONFIGURATION_CHANGING : //(the device configuration is about to change)
        break;
    case USBSR_EVENT_CONFIGURATION_CHANGED :// (the device configuration has changed)
        break;
    case USBSR_EVENT_INTERFACE_CHANGING ://(the alternate setting of the given interface is about to change)
        break;
    case USBSR_EVENT_INTERFACE_CHANGED : //(the alternate setting of the given interface has changed)
        break;
    case USBSR_EVENT_REMOTE_WAKEUP_ENABLED ://(remote wakeup has been enabled by the host)
        break;
    case USBSR_EVENT_REMOTE_WAKEUP_DISABLED ://(remote wakeup has been disabled by the host)
        break;
    case USBSR_EVENT_EPIN_STALL_CLEARED ://(the given IN endpoint's stall condition has been cleared the host)
        break;
    case USBSR_EVENT_EPIN_STALL_SET ://(the given IN endpoint has been stalled by the host)
        break;
    case USBSR_EVENT_EPOUT_STALL_CLEARED ://(the given OUT endpoint's stall condition has been cleared the host)
        break;
    case USBSR_EVENT_EPOUT_STALL_SET ://(the given OUT endpoint has been stalled by the PC)
        break;
    }
}


// ************************ USB interrupt event processing ********************************
void usbirqHookProcessEvents(void)
{
  
// Handle events that require immediate processing here

  P0 |= 0x04;             // Set P0_2 (P4 pin 6)
  
  if (usbirqData.eventMask & USBIRQ_EVENT_START_OF_FRAME) {
    oldEndpoint = USBINDEX;
    if (failed_to_send != 0) {
      
// Transfer nulls into the USB audio buffer using DMA        
        
      SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, &null);
      DmaDesc0.SRCINC = SRCINC_0;                 // The source address is constant
      DMAARM |= DMA_CHANNEL_0;
      DMAREQ |= DMA_CHANNEL_0;                    // Enable memory-to-memory transfer using DMA channel 0
      while ((DMAARM & DMA_CHANNEL_0) > 0);       // Wait for transfer to complete
    }
     
    failed_to_send = 1;                           // This flag should be cleard by a subsequent EP4IN interrupt  
    usbirqData.eventMask &= ~USBIRQ_EVENT_START_OF_FRAME;
    USBCSIL |= USBCSIL_INPKT_RDY;
    USBINDEX = oldEndpoint;
  }
  
  if (usbirqData.eventMask & USBIRQ_EVENT_EP4IN) {
    oldEndpoint = USBINDEX;
    USBINDEX = 4;                               // Change to endpoint 4
    
// Transfer audio data from the audioIn buffer to the USB audio buffer using DMA        
    
//    SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, SINE_TABLE);
     
    switch (whichbuffer) {
    case 0:
      if (activeOut == 0)
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.A.fifoA);
      else
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.B.fifoA);
      break;
    case 1:
      if (activeOut == 0)
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.A.fifoB);
      else
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.B.fifoB);
      break;
    case 2:
      if (activeOut == 0)
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.A.fifoC);
      else
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.B.fifoC);
      break;
    case 3:
      if (activeOut == 0)
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.A.fifoD);
      else
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.B.fifoD);
      break;
    case 4:
      if (activeOut == 0)
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.A.fifoE);
      else
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.B.fifoE);
      break;
    case 5:
      if (activeOut == 0)
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.A.fifoF);
      else
        SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, audioOut.B.fifoF);
      break;
    }
 
//    SET_WORD(DmaDesc0.SRCADDRH, DmaDesc0.SRCADDRL, SINE_TABLE);
  
    DmaDesc0.SRCINC = SRCINC_1;                 // The incrment the source address
    
    DMAARM |= DMA_CHANNEL_0;
    DMAREQ |= DMA_CHANNEL_0;                    // Enable memory-to-memory transfer using DMA channel 0
    while ((DMAARM & DMA_CHANNEL_0) > 0);       // Wait for transfer to complete
    
    whichbuffer++;
    if (whichbuffer > 5) {
      activeOut++;
      activeOut &= 0x01;
      whichbuffer = 0;
    }

    usbirqData.eventMask &= ~USBIRQ_EVENT_EP4IN;
    USBCSIL |= USBCSIL_INPKT_RDY;
    USBINDEX = oldEndpoint;
    failed_to_send = 0;
  }
}


/*
+------------------------------------------------------------------------------
|  Copyright 2004-2007 Texas Instruments Incorporated. All rights reserved.
|
|  IMPORTANT: Your use of this Software is limited to those specific rights
|  granted under the terms of a software license agreement between the user who
|  downloaded the software, his/her employer (which must be your employer) and
|  Texas Instruments Incorporated (the "License"). You may not use this Software
|  unless you agree to abide by the terms of the License. The License limits
|  your use, and you acknowledge, that the Software may not be modified, copied
|  or distributed unless embedded on a Texas Instruments microcontroller or used
|  solely and exclusively in conjunction with a Texas Instruments radio
|  frequency transceiver, which is integrated into your product. Other than for
|  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
|  works of, modify, distribute, perform, display or sell this Software and/or
|  its documentation for any purpose.
|
|  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
|  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
|  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
|  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
|  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
|  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
|  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING
|  BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
|  CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
|  SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
|  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
|
|  Should you have any questions regarding your right to use this Software,
|  contact Texas Instruments Incorporated at www.TI.com.
|
+------------------------------------------------------------------------------
*/





