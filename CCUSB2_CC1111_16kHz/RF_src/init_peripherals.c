/*
 *******************************************************************************************************
 * init_peripherals.c       For use with "CC1111 and CC2511 USB Dongle" cards                          *
 *                                                                                                     *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         CC1111 and CC2511                                                          *
 * Author:                  MJB                                                                        *
 * Last Update:             17 May 2010                                                                *
 ******************************************************************************************************/

// Includes
#include "twoway.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief	Initialize hardware peripherals, including P0, P1, P2,
///             
///
////////////////////////////////////////////////////////////////////////////////

void init_peripherals(void) {

  // Port 0
  // P0_0  I/O DO   Test Point - P4 pin 8
  // P0_1  I/O DO   Test Point - P4 pin 7
  // P0_2  I/O DO   Test Point - P4 pin 6
  // P0_3  I/O DO   Test Point - P4 pin 5
  // P0_4  I/O DO   Test Point - P4 pin 4
  // P0_5  I/O DO   Test Point - P4 pin 3

  P0SEL = 0x00;
  P0DIR |= 0x3F;      
  P0 = 0x00;        

  // Port 1
  // P1_0  I/O DO   USB Enable/Disable
  // P1_1  I/O DO   LED
  // P1_2  I/O DI   Push Button
  // P1_3  I/O DO   Test Point - P4 pin 10
  // P1_4  I/O DI   Unknown   
  // P1_5  PIO xx   GDO0 
  // P1_6  PIO xx   GDO1  
  // P1_7  PIO xx   GDO2   

  P1SEL = 0x00;
  P1DIR |= 0x0B;
  P1 |= 0x01;
  
  // Port 2
  // P2_0  I/O DO   Test Point - P4 pin 1
  // P2_1  I/O DI   DD/Debug (JP3 pin 4)
  // P2_2  I/O DI   DC/Debug (JP3 pin 3)
  
  P2SEL = 0x00;
  P2DIR = 0x01;                
  P2 = 0x00;

// Timer 1 Setup
//
// Timer 1 is used in modulo mode to generate an interrupt every 250 milliseconds

  // T1CTL.DIV (b3:2)  - 11b Prescaler divider set to 128 (clock frequency = 24/128 = 187.5 kHz or 5.333 usec per tic)
  // T1CTL.MODE (B1:0) - 10b Modulo Mode
  T1CTL = 0x0E; 
  
  // T1CCTL0.IM   (b6) - 1b Enable interrupt request
  // T1CCTL0.MODE (b2) - 0b Capture Mode
  // T1CCTL0.CAP  (b1:0) - 00b No capture
  T1CCTL0 = 0x40;
  
  // Set Timer Terminal Count to 46875 (0xB71B)
  T1CC0L = 0x1B;
  T1CC0H = 0xB7;

// Timer 3 Setup
//
// Timer 3 is used in the ListenforMaster subroutine
  
  T3CCTL0 = 0;
  T3CCTL1 = 0;
  T3CTL = 0xE5;               // tick frequency = 128/24.000 = 5.333 usec
                              // interrupt on overflow disabled
                              // Clear the counter and set mode to Down (count from T3CCO to 0)  
  
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

