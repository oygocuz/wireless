/*******************************************************************************************************
 * i2c.c                    I2C bus support                                                            *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         TexasInstruments CC1110                                                    *
 * Author:                  MJB                                                                        *
 * Last Update:             06 April 2011                                                              *
 ******************************************************************************************************/
 
// Includes

#include "board.h"
#include "TLV320AIC3104.h"

volatile UINT16 junk;

#define  CLK_WIDTH          \
  junk++

#define SHORT_DELAY   \
  asm("NOP");         \
  asm("NOP");         \
  asm("NOP");         \
  asm("NOP")         

// Create a pseudo I2C bus using P0_3 (SCL) and P0_4 (SDA)

void I2Cwrite(char page_addr, char reg_addr, char data)
{
unsigned char i, mask;

  P2 |= 0x10;                   // Debug - Set P2_4 (TP1)

// Generate a START condition  
  
  I2C_Px_DIR |= I2C_SDA;        // allow Master to control the SDA pin
  
  I2C_PORT |= I2C_SDA;          // set SDA high 
  I2C_PORT |= I2C_SCL;          // set SCL high (JIC - the SCL pin should be high by default)
    
  I2C_PORT &= ~I2C_SDA;         // set SDA low
  CLK_WIDTH;                    // Delay
  CLK_WIDTH;                    // Delay
  I2C_PORT &= ~I2C_SCL;         // set SCL low
  
// Send the 7 bit Slave Address, followed by a 0. Address is sent MSB first.
  
  mask = 0x40;
  for (i = 0; i < 7; i++) {
    if ((CODEC_I2C_ADDR & mask) > 0)
      I2C_PORT |= I2C_SDA;      // set SDA high
    else
      I2C_PORT &= ~I2C_SDA;     // set SDA low
    SHORT_DELAY;                // Delay
    I2C_PORT |= I2C_SCL;        // set SCL high
    CLK_WIDTH;                  // Delay
    I2C_PORT &= ~I2C_SCL;       // set SCL low
    mask = mask >> 1;
  }
  
  I2C_PORT &= ~I2C_SDA;         // set SDA low
  SHORT_DELAY;                  // Delay
  I2C_PORT |= I2C_SCL;          // set SCL high
  CLK_WIDTH;                    // Delay
  I2C_PORT &= ~I2C_SCL;         // set SCL low
   
  CLK_WIDTH;
  
  I2C_Px_DIR &= ~I2C_SDA;       // allow Slave to control the SDA pin (Acknowledge)
  
  CLK_WIDTH;                    // Delay
  
// Toggle SCL  
  
  I2C_PORT |= I2C_SCL;          // set SCL high
  CLK_WIDTH;                    // Delay
  I2C_PORT &= ~I2C_SCL;         // set SCL low
  
// Send the Register Address (8 bits, MSB first)
  
  I2C_Px_DIR |= I2C_SDA;        // allow Master to control the SDA pin
  mask = 0x80;
  
  CLK_WIDTH;                    // Delay
  
  for (i = 0; i < 8; i++) {
    if ((reg_addr & mask) > 0)
      I2C_PORT |= I2C_SDA;      // set SDA high
    else
      I2C_PORT &= ~I2C_SDA;     // set SDA low
    SHORT_DELAY;                // Delay
    I2C_PORT |= I2C_SCL;        // set SCL high
    CLK_WIDTH;                  // Delay
    I2C_PORT &= ~I2C_SCL;       // set SCL low
    mask = mask >> 1;
  }
 
  CLK_WIDTH;
  
  I2C_Px_DIR &= ~I2C_SDA;       // allow Slave to control the SDA pin (Acknowledge)
  
  CLK_WIDTH;                    // Delay
  
// Toggle SCL  
  
  I2C_PORT |= I2C_SCL;          // set SCL high
  CLK_WIDTH;                    // Delay
  I2C_PORT &= ~I2C_SCL;         // set SCL low
  
// Send data (8 bits, MSB first)
  
  I2C_Px_DIR |= I2C_SDA;        // allow Master to control the SDA pin
  mask = 0x80;
  
  CLK_WIDTH;                    // Delay
  
  for (i = 0; i < 8; i++) {
    if ((data & mask) > 0)
      I2C_PORT |= I2C_SDA;      // set SDA high
    else
      I2C_PORT &= ~I2C_SDA;     // set SDA low
    SHORT_DELAY;                // Delay
    I2C_PORT |= I2C_SCL;        // set SCL high
    CLK_WIDTH;                  // Delay
    I2C_PORT &= ~I2C_SCL;       // set SCL low
    mask = mask >> 1;
  }
 
  CLK_WIDTH;
  
  I2C_Px_DIR &= ~I2C_SDA;       // allow Slave to control the SDA pin (Acknowledge)
  
  CLK_WIDTH;                    // Delay
  
// Toggle SCL  
  
  I2C_PORT |= I2C_SCL;          // set SCL high
  CLK_WIDTH;                    // Delay
  I2C_PORT &= ~I2C_SCL;         // set SCL low
  
// Generate a STOP condition

  I2C_Px_DIR |= I2C_SDA;        // allow Master to control the SDA pin
  
  CLK_WIDTH;                    // Delay
  
  I2C_PORT &= ~I2C_SDA;         // set SDA low
  CLK_WIDTH;                    // Delay
  I2C_PORT |= I2C_SCL;          // set SCL high
  CLK_WIDTH;                    // Delay
  I2C_PORT |= I2C_SDA;          // set SDA high

  P2 &= ~0x10;                  // Debug - Reset P2_4 (TP1)
  
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


