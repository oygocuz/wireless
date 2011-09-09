/*******************************************************************************************************
 * codec_TLV320AIC26.h  Global definitions for the TLV320AIC26 CODEC                                   *
 * Compiler:                IAR 8051 compiler for CC1110                                               *
 * Target platform:         Chipcon CC1110                                                             *
 * Author:                  MJB                                                                        *
 * Last Update:             29 May 2009                                                                *
 ******************************************************************************************************/

#ifndef CODEC_TLV320AIC26_H
#define CODEC_TLV320AIC26_H

#define RESET_CONTROL           1, 0x04       // Reset Control - Page 1 Register 04H
#define AUDIO_CONTROL_1         2, 0x00       // Audio Control 1 - Page 2 Register 00H
#define ADC_GAIN_CONTROL        2, 0x01       // Codec ADC Gain Control - Page 2 Register 01H
#define DAC_GAIN_CONTROL        2, 0x02       // Codec ADC Gain Control - Page 2 Register 02H
#define SIDETONE_CONTROL        2, 0x03       // Codec Sidetone Control - Page 2 Register 03H
#define AUDIO_CONTROL_2         2, 0x04       // Audio Control 2 - Page 2 Register 04H
#define POWER_CONTROL           2, 0x05       // Codec Power Control - Page 2 Register 05H
#define AUDIO_CONTROL_3         2, 0x06       // Audio Control 3 - Page 2 Register 06H
#define PLL_PROGRAMMABILITY_1   2, 0x1B       // PLL Programmability - Page 2 Register 1BH
#define PLL_PROGRAMMABILITY_2   2, 0x1C       // PLL Programmability - Page 2 Register 1CH
#define AUDIO_CONTROL_4         2, 0x1D       // Audio Control 4 - Page 2 Register 1DH
#define AUDIO_CONTROL_5         2, 0x1E       // Audio Control 5 - Page 2 Register 1EH

#endif  // CODEC_TLV320AIC26_H

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



