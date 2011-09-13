/***********************************************************************************

    Filename:		usb_class_request.c

    Description:	USB class request handler (audio class).

***********************************************************************************/
//Stolen from HID class requests, and modified for audio

/***********************************************************************************
* INCLUDES
*/
#include "usb_class_requests.h"
#include "usb_audio_controls.h"
#include "usb_framework.h"

int16 const volMin = VOL_MIN*256;
int16 const volMax = VOL_MAX*256;
int16 const volRes = VOL_RES*256;

/***********************************************************************************
* @fn          usbcrSetCur
*
* @brief       Implements support for the audio class request SET_CUR.
*
* @return      none
*/
void usbcrSetCur(void)
{
    // Received setup header?
    if (usbfwData.ep0Status == EP_IDLE) {

        // Sanity check the incoming setup header:
        // Asking for mute control?
           if ((HI_UINT16(usbSetupHeader.value) == MUTE_CONTROL) &&
              (usbSetupHeader.index == 0x0200) &&
              (usbSetupHeader.length == sizeof(MUTE_CNTRL))) {  
            // Prepare to receive the data
            usbfwData.ep0Status = EP_RX;
            usbSetupData.pBuffer = (uint8 *) &audioData.muteControl;
            usbSetupData.bytesLeft = usbSetupHeader.length;
            return;
        //Asking for volume control?            
          } else if ((HI_UINT16(usbSetupHeader.value) == VOLUME_CONTROL) &&
            (usbSetupHeader.index == 0x0200) &&
            (usbSetupHeader.length == sizeof(VOLUME_CNTRL))) {    
            // Prepare to receive the data
            usbfwData.ep0Status = EP_RX;
            usbSetupData.pBuffer = (uint8 *) &audioData.volumeControl;
            usbSetupData.bytesLeft = usbSetupHeader.length;
            return;
          } else {
            // Unsupported: Stall the request
            usbfwData.ep0Status = EP_STALL;
            return;
        }

    // Received data?
    } else if (usbfwData.ep0Status == EP_RX) {

        // The USB firmware library will return here after the data has been
        // received. This USB example only implements one-way RF link protocol
        // (i.e. keyboard device -> USB device), but can optionally be extended
        // by transmitting the received LED status (now stored in
        // hidData.keyboardOutReport.ledStatus) back to keyboard for it to
        // update itself.

    }

} // usbcrSetCur


/***********************************************************************************
* @fn          usbcrGetCur
*
* @brief       Implements support for the audio class request GET_CUR.
*
* @return      none
*/
void usbcrGetCur(void)
{
    // Received setup header?
    if (usbfwData.ep0Status == EP_IDLE) {

        // Asking for mute control?
        if ((HI_UINT16(usbSetupHeader.value) == MUTE_CONTROL) &&
                (usbSetupHeader.index == 0x0200) &&
                (usbSetupHeader.length == sizeof(MUTE_CNTRL))) {
            // Prepare to send the data
            usbfwData.ep0Status = EP_TX;
            usbSetupData.pBuffer = (uint8 *) &audioData.muteControl;
            usbSetupData.bytesLeft = usbSetupHeader.length;
            return;
        // Asking for volume control?
        } else if ((HI_UINT16(usbSetupHeader.value) == VOLUME_CONTROL) &&
                    (usbSetupHeader.index == 0x0200) &&
                    (usbSetupHeader.length == sizeof(VOLUME_CNTRL))) {
         // Prepare to send the data
            usbfwData.ep0Status = EP_TX;
            usbSetupData.pBuffer = (uint8 *) &audioData.volumeControl;
            usbSetupData.bytesLeft = usbSetupHeader.length;
            return;

        } else {

            // Unsupported: Stall the request
            usbfwData.ep0Status = EP_STALL;
            return;
        }

    // Data transmitted?
    } else if (usbfwData.ep0Status == EP_TX) {

        // The USB firmware library will return here after the         // report has been transmitted, but there is nothing for us to do here.
    }

} // usbcrGetCur

/***********************************************************************************
* @fn          usbcrGetMin
*
* @brief       Implements support for the audio class request GET_MIN.
*
* @return      none
*/
void usbcrGetMin(void)
{
     if (usbfwData.ep0Status == EP_IDLE) {


        // Asking for volume control?
         if ((HI_UINT16(usbSetupHeader.value) == VOLUME_CONTROL) &&
                    (usbSetupHeader.index == 0x0200) &&
                    (usbSetupHeader.length == sizeof(VOLUME_CNTRL))) {
            // Prepare to send the data
            usbfwData.ep0Status = EP_TX;
            usbSetupData.pBuffer = (uint8 *) &volMin;
            usbSetupData.bytesLeft = usbSetupHeader.length;
            return;

        } else {

            // Unsupported: Stall the request
            usbfwData.ep0Status = EP_STALL;
            return;
        }

    // Data transmitted?
    } else if (usbfwData.ep0Status == EP_TX) {

        // The USB firmware library will return here after the         // report has been transmitted, but there is nothing for us to do here.
    }
}

/***********************************************************************************
* @fn          usbcrGetMax
*
* @brief       Implements support for the audio class request GET_MAX.
*
* @return      none
*/
void usbcrGetMax(void)
{
    if (usbfwData.ep0Status == EP_IDLE) {


        // Asking for volume control?
        if ((HI_UINT16(usbSetupHeader.value) == VOLUME_CONTROL) &&
                    (usbSetupHeader.index == 0x0200) &&
                    (usbSetupHeader.length == sizeof(VOLUME_CNTRL))) {
            // Prepare to send the data
            usbfwData.ep0Status = EP_TX;
            usbSetupData.pBuffer = (uint8 *) &volMax;
            usbSetupData.bytesLeft = usbSetupHeader.length;
            return;

        } else {

            // Unsupported: Stall the request
            usbfwData.ep0Status = EP_STALL;
            return;
        }

    // Data transmitted?
    } else if (usbfwData.ep0Status == EP_TX) {

        // The USB firmware library will return here after the         // report has been transmitted, but there is nothing for us to do here.
    }
}

/***********************************************************************************
* @fn          usbcrGetRes
*
* @brief       Implements support for the audio class request GET_RES.
*
* @return      none
*/
void usbcrGetRes(void)
{
    // Received setup header?
    if (usbfwData.ep0Status == EP_IDLE) {

        // Asking for volume control?
        if ((HI_UINT16(usbSetupHeader.value) == VOLUME_CONTROL) &&
                    (usbSetupHeader.index == 0x0200) &&
                    (usbSetupHeader.length == sizeof(VOLUME_CNTRL))) {
            // Prepare to send the data
            usbfwData.ep0Status = EP_TX;
            usbSetupData.pBuffer = (uint8 *) &volRes;
            usbSetupData.bytesLeft = usbSetupHeader.length;
            return;

        } else {

            // Unsupported: Stall the request
            usbfwData.ep0Status = EP_STALL;
            return;
        }

    // Data transmitted?
    } else if (usbfwData.ep0Status == EP_TX) {

        // The USB firmware library will return here after the         // report has been transmitted, but there is nothing for us to do here.
    }

} // usbcrGetRes
