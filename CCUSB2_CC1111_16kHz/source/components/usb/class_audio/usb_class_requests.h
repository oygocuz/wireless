/***********************************************************************************

    Filename:     usb_class_request.h

    Description:  Handle USB class requests for audio class.

***********************************************************************************/

//Stole the usb_class_request files for HID and modified them.

#ifndef USB_CLASS_REQUEST
#define USB_CLASS_REQUEST

//Audio-specific Request Codes

#define AUD_REQ_UNDEFINED    0x00
#define AUD_REQ_SET_CUR      0x01
#define AUD_REQ_GET_CUR      0x81
#define AUD_REQ_SET_MIN      0x02
#define AUD_REQ_GET_MIN      0x82
#define AUD_REQ_SET_MAX      0x03
#define AUD_REQ_GET_MAX      0x83
#define AUD_REQ_SET_RES      0x04
#define AUD_REQ_GET_RES      0x84
#define AUD_REQ_SET_MEM      0x05
#define AUD_REQ_GET_MEM      0x85
#define AUD_REQ_GET_STAT     0xFF

//Feature Unit Control Selectors

#define FU_CONTROL_UNDEFINED      0x00
#define MUTE_CONTROL              0x01
#define VOLUME_CONTROL            0x02
#define BASS_CONTROL              0x03
#define MID_CONTROL               0x04
#define TREBLE_CONTROL            0x05
#define GRAPHIC_EQUALIZER_CONTROL 0x06
#define AUTOMATIC_GAIN_CONTROL    0x07
#define DELAY_CONTROL             0x08
#define BASS_BOOST_CONTROL        0x09
#define LOUDNESS_CONTROL          0x0A


// HID Interface indices (as used in USB descriptor) for class request parsing
//#define KEYBOARD_INDEX          0
//#define MOUSE_INDEX             1

// Constants specifying HID Class requests (bRequest)
//#define GET_REPORT              0x01
//#define GET_IDLE                0x02
//#define GET_PROTOCOL            0x03
//#define SET_REPORT              0x09
//#define SET_IDLE                0x0A
//#define SET_PROTOCOL            0x0B

// Report types for use with the GET_/SET_REPORT request
//#define HID_REP_TYPE_INPUT      1
//#define HID_REP_TYPE_OUTPUT     2
//#define HID_REP_TYPE_FEATURE    3

// Idle rate constants used for GET_/SET_IDLE request
//#define HID_IDLE_INDEFINITE     0x0000
//#define HID_IDLE_NOT_SET        0x00FF      // Used as dummy init value

// Protocol constants for use with GET_/SET_PROTOCOL request
//#define HID_PROTOCOL_BOOT       0
//#define HID_PROTOCOL_REPORT     1


// Function prototypes
void usbcrSetCur(void);
void usbcrGetCur(void);
void usbcrGetMin(void);
void usbcrGetMax(void);
void usbcrGetRes(void);
//void usbcrSetReport(void);
//void usbcrSetProtocol(void);
//void usbcrSetIdle(void);
//void usbcrGetReport(void);
//void usbcrGetProtocol(void);
//void usbcrGetIdle(void);

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
#endif