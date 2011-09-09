/*
 *******************************************************************************************************
 * tw_mac.c           I     Timer 3 ("MAC") Routines                                                   *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Texas Instruments Cc1110/CC2510                                            *
 * Author:                  MJB                                                                        *
 * Last Update:             06 April 2011                                                              *
 *******************************************************************************************************
*/

//-------------------------------------------------------------------------------------------------------
// Global variables

#include "board.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief	Set the T3 timeout and start timer. Counts down twice before returns
////////////////////////////////////////////////////////////////////////////////
void macsetT3TimeoutAndWait(UINT8 timeout, UINT8 multiplier) {

  TIMIF &= ~T3OVFIF;            // Clear RX_TIMEOUT_TIMER_FLAG

  for ( int i = 1; i <= multiplier; i++) {
    T3CC0 = timeout;            // Set timeout period
    TIMER3_RUN(TRUE);           // Start timer

    while(!(TIMIF & T3OVFIF));  // Wait for timeout

    TIMIF &= ~T3OVFIF;          // Clear RX_TIMEOUT_TIMER_FLAG
    TIMER3_RUN(FALSE);          // Stop timer
  }
}


////////////////////////////////////////////////////////////////////////////////
/// @brief	Set next channel after RX/TX completes
////////////////////////////////////////////////////////////////////////////////

void setChannel (UINT8 ch) {
  
  // Only change channel when radio state is IDLE, i.e. not in RX or TX
  // Include a "safety" check to escape from dead locks?

  while(MARCSTATE != 0x01)
    if (MARCSTATE == 0x11 || MARCSTATE == 0x16 || MARCSTATE == 0x0D) 
      SIDLE();
  
  CHANNR = ch;
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

