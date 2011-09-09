/*
 *******************************************************************************************************
 * init_peripherals.c       For use with "Microphone with TLV320AIC3104 Codec Rev A" cards             *
 * I2S format - 16 bit uncompressed                                                                    *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         TexasInstruments CC1110                                                    *
 * Author:                  MJB                                                                        *
 * Last Update:             06 April 2011                                                              *
 *******************************************************************************************************
*/

// Includes
#include "board.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief	Initialize hardware peripherals, including P0, P1, P2,
///             Timers 1 and 4, and USART 0 (SPI)
///
////////////////////////////////////////////////////////////////////////////////

void init_peripherals(void) {

// The I2S bus uses Alternate location 1 (WS on P0_0, CK on P0-1, RX on P1-7. TX is not used)   
  
  // Port 0
  // P0_0  PIO xx   I2S LR CLK
  // P0_1  PIO xx   I2S BCLK 
  // P0_2  I/O DI   Band Switch position 2 (Middle)
  // P0_3  I/O DO   I2C SCL 
  // P0_4  I/O DO   I2C SDA
  // P0_5  I/O DI   Band Switch position 3 (Up)
  // P0_6  I/O DO   Codec Reset 
  // P0_7  ADC xx   ADC 7 (Battery Voltage)

  P0SEL = 0x03;     // set bits 0 and 1 to 'peripheral function' mode (I2S bus)
  P0DIR = 0x58;     // set bits 3, 4, and 7 for DO
  ADCCFG = 0x80;    // set bit 7 for ADC mode
  P0 = 0x58;        // Hold the Codec in the Reset state; Set SCL and SDA high        

// Leave P0INP at reset value (0x00) so that bits 2 and 5 are in 'Pull-up / pull-down' mode
// Leave P2INP at reset value (0x00) so that bit 5 is set 0 (Port 0 'Pull-up / pull-down' select set to 'Pull-up')
  
  // Port 1
  // P1_0  I/O DO   Blue LED (Heartbeat)
  // P1_1  I/O DO   Green LED (Power On / Low Battery)
  // P1_2  I/O DI   Enable AGC Jumper
  // P1_3  I/O DI   Enable AUX Input Jumper
  // P1_4  I/O DI   Band Switch position 3 (Down) 
  // P1_5  I/O DO   GDO0 (JP3 pin 1)
  // P1_6  I/O DO   GDO1 (JP3 pin 2)
  // P1_7  PIO xx   I2S RX

  P1SEL = 0x80;     // set bit 7 to 'peripheral function' mode (I2S bus)
  P1DIR = 0x63;     // set bits 0, 1, 5, and 6 for DO
  P1 = 0x00;
  
// Leave P1INP at reset value (0x00) so that bits 2, 3, and 4 are in 'Pull-up / pull-down' mode
// Leave P2INP at reset value (0x00) so that bit 6 is set 0 (Port 1 'Pull-up / pull-down' select set to 'Pull-up')  
  
  // Port 2
  // P2_0  PIO DO   Codec MCLK / T4CH0 
  // Note: Timer 4 I/O location must be set to 'Alternate 2'
  // P2_1  I/O DO   DD/Debug (JP4 pin 4)
  // P2_2  I/O DO   DC/Debug (JP4 pin 3)
  // P2_3  I/O DO   Test Point TP2       
  // P2_4  I/O DO   Test Point TP1
  
  P2SEL = 0x01;
  P2DIR = 0x1F;              
  P2 = 0x00;

  PERCFG = 0x10;        // Timer 4: Use Alternate 2 location (P2_0)
                        // I2S: Use Alternate 1 location
  
// I2S Setup  

  I2SCFG0 = 0x0E;     // Bit 7: 0 - TX Interrupts disabled
                      // Bit 6: 0 - RX Interrupts disabled
                      // Bit 5: 0 - ulaw expansion disabled
                      // Bit 4: 0 - ulaw compression disabled
                      // Bit 3: 1 - TX mono mode enabled
                      // Bit 2: 1 - RX mono mode enabled
                      // Bit 1: 1 - mode set to Master
                      // Bit 0: 0 - I2S interface disabled
  I2SCFG1 = 0x78;     // Bits 7:4: 0x07 - WORDSIZE = 16 bits
                      // Bit 0 - IOLOC = 0 (Alternate 1)

// Refer to Table 48 of CC1110 document  
  
  I2SCLKF2 = 0x06;    // NUM = 1625    
  I2SCLKF1 = 0x59;    
  
#ifdef SR8KHZ  
  I2SCLKF0 = 0x20;    // DENOM = 32; CLKDIV = 50.78125; Fsclk = 256 kHz
#endif  

#ifdef SR12KHZ  
  I2SCLKF0 = 0x30;    // DENOM = 32; CLKDIV = 33.85417; Fsclk = 384 kHz
#endif  
  
#ifdef SR16KHZ  
  I2SCLKF0 = 0x40;    // DENOM = 64; CLKDIV = 25.390625; Fsclk = 512 kHz
#endif    
 
#ifdef SR24KHZ  
  I2SCLKF0 = 0x60;    // DENOM = 96; CLKDIV = 16.92708; Fsclk = 768 kHz
#endif      
  
  
// Timer 1 Setup
//
// Timer 1 is used in modulo mode to generate an interrupt every 250 milliseconds

  // T1CTL.DIV (b3:2)  - 11b Prescaler divider set to 128 (clock frequency = 26/128 = 203.125 kHz)
  // T1CTL.MODE (B1:0) - 10b Modulo Mode
  T1CTL = 0x0E; 
  
  // T1CCTL0.IM   (b6) - 1b Enable interrupt request
  // T1CCTL0.MODE (b2) - 0b Capture Mode
  // T1CCTL0.CAP  (b1:0) - 00b No capture
  T1CCTL0 = 0x40;
  
  // Set Timer Terminal Count to 50781 (0xC65D)
  T1CC0L = 0x5D;
  T1CC0H = 0xC6;
  
// Timer 4 Setup
//
// Timer 4 is used to generate the CODEC MCLK (13.000 MHz) 
  
  T4CTL   = 0x06;     // Tick frequency/1, modulo mode; Clear the 'Start' bit
  T4CCTL0 = 0x14;     // Compare mode, toggle output on compare
  T4CC0   = 0x00;     // Set timeout period

// ADC Setup

  ADCCON1 = 0x3F;     // Start ADC via the ST bit; Disable the random number generator
  ADCCON2 = 0x37;     // Select internal 1.25 volt reference; use 12 bit resolution (512 decimation rate); Select AIN7
  
  ADCCON1 |= 0x40;    // Start the ADC
  
  return;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief	Initialize timer3.
///
/// Initialize for use as TX timeout timer. 
/// 
////////////////////////////////////////////////////////////////////////////////

void macTimer3Init(void) {
  T3CCTL0 = 0;
  T3CCTL1 = 0;
  T3CTL = 0xE5;               // tick frequency = 128/26.000 = 4.923076923 usec
                              // interrupt on overflow disabled
                              // Clear the counter and set mode to Down (count from T3CCO to 0)  
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

