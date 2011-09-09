/*
 *******************************************************************************************************
 * tw_rf.c                  Radio Initilization, Packet Send Routines                                  *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         TexasInstruments CC1110                                                    *
 * Author:                  MJB                                                                        *
 * Last Update:             06 April 2011                                                              *
 *******************************************************************************************************
*/


#include "board.h"
#include "TLV320AIC3104.h"

void init_codec(void)
{
// TLV320AIC3104 Setup
  
// Timer 4 was set up in 'main'c'

  T4CTL |= 0x10;        // Start Timer 4 (Codec MCLK) 

// Reset the Codec

  I2Cwrite(SOFTWARE_RESET, CODEC_RESET);
  
// PLL - set fsref to 48 kHz (MCLK is 13.000 MHz)
  
#ifdef SR8KHZ  
  I2Cwrite(CODEC_SAMPLE_RATE, 0xAA);                // ADC and DAC Sample Rate = fsref/6 (8 kHz)
#endif
#ifdef SR12KHZ  
  I2Cwrite(CODEC_SAMPLE_RATE, 0x66);                // ADC and DAC Sample Rate = fsref/4 (12 kHz)
#endif
#ifdef SR16KHZ  
  I2Cwrite(CODEC_SAMPLE_RATE, 0x44);                // ADC and DAC Sample Rate = fsref/3 (16 kHz)
#endif
#ifdef SR24KHZ  
  I2Cwrite(CODEC_SAMPLE_RATE, 0x22);                // ADC and DAC Sample Rate = fsref/2 (24 kHz)
#endif  

  I2Cwrite(PLL_PROGRAMMING_REG_A, PLL_EN | 0x11);   // Enable PLL; Q = 2, P = 1
  I2Cwrite(PLL_PROGRAMMING_REG_B, 0x13);            // J = 7; 0x7 * 4 (left shift two bits) =0x13 
  I2Cwrite(PLL_PROGRAMMING_REG_C, 0x57);            // D = 5618 = 0x1562; x4 (left shift two bits) = 0x57C8
  I2Cwrite(PLL_PROGRAMMING_REG_D, 0xC8);        
  
// Set up the Serial Data Interface  
  
  I2Cwrite(SDI_REG_B, 0x00);                        // Serial Data Bus uses I2S mode; Audio data word length = 16 bits

// Microphone Bias
  
  I2Cwrite(MICBIAS_CNTRL, MICBIAS_2V);              // Set Microphone Bias voltage to 2.0 Volts

// ADCs
//
// In this application, only the Left ADC is used. Leave the right ADC powered down.
// The internal and external microphomes are connected to the MIC1 Left inputs, and the Line (AUX) input to the MIC2\Line2 Right inputs
  
  I2Cwrite(MIC1LP_LEFTADC, 0x84);                   // Connect the internal microphone to the Left ADC using differential inputs (gain = 0 dB); Power Up the Left ADC
  I2Cwrite(LEFT_ADC_PGA_GAIN, 0x3C);                // Enable PGA and set gain to 30 dB
  
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


