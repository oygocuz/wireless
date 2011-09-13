/***********************************************************************************

  Filename:	usb_audio.c

  Description:	Application support for the audio class

***********************************************************************************/

/***********************************************************************************
* INCLUDES
*/
#include "hal_int.h"
#include "hal_mcu.h"
#include "twoway.h"

#include "usb_firmware_library_headers.h"   //need to have audio version
#include "usb_audio_controls.h"
#include "usb_class_requests.h"             //need to have audio version


/***********************************************************************************
* GLOBAL DATA
*/

int __xdata SINE_TABLE[48] = {
0x0,
0x0,
0x1E54,
0x1E54,
0x3A97,
0x3A97,
0x52DD,
0x52DD,
0x657C,
0x657c,
0x7131,
0x7131,
0x7530,
0x7530,
0x7131,
0x7131,
0x657C,
0x657C,
0x52DD,
0x52DD,
0x3A97,
0x3A97,
0x1E54,
0x1E54,
0x0,
0x0,
0xE1AC,
0xE1AC,
0xC569,
0xC569,
0xAD23,
0xAD23,
0x9A84,
0x9A84,
0x8ECF,
0x8ECF,
0x8AD1,
0x8AD1,
0x8ECF,
0x8ECF,
0x9A84,
0x9A84,
0xAD23,
0xAD23,
0xC568,
0xC568,
0xE1AC,
0xE1AC,
};  

/** brief Initializes the \ref module_usb_firmware_library_config module
*
* This function should be called first.
*/
void usbAudioInit(void)
{
//uint8 oldEndpoint;
    // Init USB library
    usbfwInit();

    // Initialize the USB interrupt handler with bit mask containing all processed USBIRQ events
    usbirqInit(0xFFFF);

    // Enable pullup on D+
    HAL_USB_PULLUP_ENABLE();

    // Enable global interrupts
    halIntOn();
 
} // usbAudioInit

/// @}



void usbAudioProcessEvents(void)
{
uint8 oldEndpoint;
uint8 i;

  // Handle USB reset

  if (USBIRQ_GET_EVENT_MASK() & USBIRQ_EVENT_RESET) {
    USBIRQ_CLEAR_EVENTS(0xFFFF);
    usbfwResetHandler();
    USBPOW = USBPOW_SUSPEND_EN | USBPOW_ISO_WAIT_SOF;
    //USBPOW = USBPOW_SUSPEND_EN;  //for now
  }

// Handle USB packets on EP0

  if (USBIRQ_GET_EVENT_MASK() & USBIRQ_EVENT_SETUP) {
    USBIRQ_CLEAR_EVENTS(USBIRQ_EVENT_SETUP);
    usbfwSetupHandler();
  }

// Handle USB suspend

  if (USBIRQ_GET_EVENT_MASK() & USBIRQ_EVENT_SUSPEND) {
    USBIRQ_CLEAR_EVENTS(USBIRQ_EVENT_SUSPEND);  // Clear USB suspend interrupt
    usbsuspEnter();                             // Calling this function will take the chip into PM1 until a USB resume is deteceted.
    USBIRQ_CLEAR_EVENTS(USBIRQ_EVENT_RESUME);   // Clear USB resume interrupt.
  }
  
// Code to monitor USBCSIL to see if we underran and need to fill up again.
// There is no interrupt when an underrun occurs.

  oldEndpoint = USBFW_GET_SELECTED_ENDPOINT();
  USBFW_SELECT_ENDPOINT(4);
  if (USBCSIL & USBCSIL_UNDERRUN) {
    for (i = 0; i < 96; i++) {
      USBF4 = 0;
    }
    USBCSIL |= USBCSIL_INPKT_RDY;
    USBCSIL &= ~(USBCSIL_UNDERRUN);
  }
  USBFW_SELECT_ENDPOINT(oldEndpoint);
  
  return;
}





/*
+------------------------------------------------------------------------------
|  Copyright 2004-2009 Texas Instruments Incorporated. All rights reserved.
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





