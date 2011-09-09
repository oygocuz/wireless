//----------------------------------------------------------------------------
//  Description:  This file contains definitions specific to the TLV320AIC3104 Codec.
//
//  Texas Instruments, Inc.
//  April 2011
//  
//----------------------------------------------------------------------------

#define CODEC_I2C_ADDR 0x18

// Page 0 Register 1 - Software Reset

#define SOFTWARE_RESET        0, 1

#define CODEC_RESET 0x80    // Software Reset

// Page 0 Register 2 - Codec Sample Rate

#define CODEC_SAMPLE_RATE     0, 2

#define ADC_SR      0xF0    // ADC Sample Rate Select
#define DAC_SR      0x0F    // DAC Sample Rate Select

// Page 0 Register 3 - PLL Programing Register A

#define PLL_PROGRAMMING_REG_A 0, 3

#define PLL_EN      0x80    // PLL Enable
#define PLL_Q       0x78    // PLL Q Value
#define PLL_P       0x07    // PLL P Value

// Page 0 Register 4 - PLL Programing Register B

#define PLL_PROGRAMMING_REG_B 0, 4

#define PLL_J       0xFC    // PLL J Value

// Page 0 Register 5 - PLL Programing Register C

#define PLL_PROGRAMMING_REG_C 0, 5

#define PLL_D_MSB   0xFF    // PLL J Value

// Page 0 Register 6 - PLL Programing Register D

#define PLL_PROGRAMMING_REG_D 0, 6

#define PLL_D_LSB   0xFC    // PLL J Value

// Page 0 Register 7 - Codec Data Path Setup

#define CODEC_DATA_PATH_SETUP 0, 7

#define FSREF           0x80        // 0 - fsref = 48 kHz; 1 - fsref = 44.1 kHz
#define ADC_DUAL_RATE   0x40
#define DAC_DUAL_RATE   0x20
#define LEFT_DAC_PATH   0x18
#define RIGHT_DAC_PATH  0x06
#define MUTED           0x00
#define RIGHT_CHANNEL   0x01
#define LEFT_CHANNEL    0x02
#define MONO_MIX        0x03

// Page 0 Register 8 - Audio Serial Data Interface Control Regsiter A

#define SDI_REG_A 0, 8

// Page 0 Register 9 - Audio Serial Data Interface Control Regsiter B

#define SDI_REG_B 0, 9

#define INTERFACE_MODE_I2S  0x00
#define INTERFACE_MODE_DSP  0x40
#define INTERFACE_MODE_RJ   0x80                // Right Justified Mode
#define INTERFACE_MODE_LJ   0xC0                // Left Justified Mode
#define SERIAL_DATA_WORD_LEN_16BITS  0x00       // Audio data word length = 16 bits
#define SERIAL_DATA_WORD_LEN_20BITS  0x10       // Audio data word length = 20 bits
#define SERIAL_DATA_WORD_LEN_24BITS  0x20       // Audio data word length = 24 bits
#define SERIAL_DATA_WORD_LEN_32BITS  0x30       // Audio data word length = 32 bits
#define DAC_RE-SYNC         0x04
#define ADC_RE-SYNC         0x02
#define RE-SYNC_MUTE        0x01

#define SDI_REG_C 0, 10                               // Page 0 Register 10 - Audio Serial Data Interface Control Regsiter C

// Page 0 Register 11 - Codec Overflow Flag Register

#define CODEC_OVERFLOW 0, 11                          // Page 0 Register 11 - Codec Overflow Flag Register

#define PLL_R   0x0F;

#define CODEC_DIGITAL_FILTER_CNTRL 0, 12              // Page 0 Register 12 - Codec Digital Filter Control Register
#define HEADSET_OUTPUT_DRIVER 0, 14                   // Page 0 Register 14 - Headset Detection and Output Driver Configuration
 
#define LEFT_ADC_PGA_GAIN 0, 15                       // Page 0 Register 15 - Left ADC PGA Gain Control
#define RIGHT_ADC_PGA_GAIN 0, 16                      // Page 0 Register 15 - Left ADC PGA Gain Control
#define ADC_MUTE  0x80;

#define MIC2L_MIC2R_LEFTADC 0, 17                     // Page 0 Register 17 - MIC2 Left / MIC2 Right to Left ADC Control Register
#define MIC2L_MIC2R_RIGHTADC 0, 18                    // Page 0 Register 18 - MIC2 Left / MIC2 Right to Right ADC Control Register

#define MIC1LP_LEFTADC 0, 19                          // Page 0 Register 19 - MIC1 Left Pos to Left ADC Control Register
#define MIC1RP_LEFTADC 0, 21                          // Page 0 Register 21 - MIC1 Right Pos to Left ADC Control Register
#define MIC1RP_RIGHTADC 0, 22                         // Page 0 Register 22 - MIC1 Right Pos to Right ADC Control Register
#define MIC1LP_RIGHTADC 0, 24                         // Page 0 Register 24 - MIC1 Left Pos to Right ADC Control Register

#define ADC_PWR_UP  0x04                              // ADC is powered up when true (applies to Registers 19 and 22)

#define MICBIAS_CNTRL 0, 25                           // Page 0 Register 25 - Microphone Bias Control Register

#define MICBIAS_PWR_DWN 0x00                          // MCBIAS Powered Down
#define MICBIAS_2V      0x40                          // MCBIAS 2 Volts
#define MICBIAS_2P5V    0x80                          // MCBIAS 2.5 Volts
#define MICBIAS_AVDD    0xC0                          // MCBIAS connected to AVDD

#define LEFT_AGC_CNTRL_A 0, 26                        // Page 0 Register 26 - Left AGC Control Register A
#define LEFT_AGC_CNTRL_B 0, 27                        // Page 0 Register 27 - Left AGC Control Register B
#define LEFT_AGC_MAX_GAIN LEFT_AGC_CNTRL_B            // Pseudomym for above
#define LEFT_AGC_CNTRL_C 0, 28                        // Page 0 Register 28 - Left AGC Control Register C
#define LEFT_AGC_NOISE_THRESHOLD LEFT_AGC_CNTRL_C     // Pseudomym for above

#define RIGHT_AGC_CNTRL_A 0, 29                       // Page 0 Register 29 - Right AGC Control Register A
#define RIGHT_AGC_CNTRL_B 0, 30                       // Page 0 Register 30 - Right AGC Control Register B
#define RIGHT_AGC_MAX_GAIN RIGHT_AGC_CNTRL_B          // Pseudomym for above
#define RIGHT_AGC_CNTRL_C 0, 31                       // Page 0 Register 31 - Right AGC Control Register C
#define RIGHT_AGC_NOISE_THRESHOLD RIGHT_AGC_CNTRL_C   // Pseudomym for above

#define AGC_ENA    0x80                               // AGC Enable (applies to Registers 26 and 29)

#define DAC_PWR_DRIVER_CNTRL 0, 37                    // Page 0 Register 37 - DAC Power and Output Driver Control Register

#define LEFT_DAC_PWR_UP     0x80
#define RIGHT_DAC_PWR_UP    0x40

#define HPWR_DRIVER_CNTRL 0, 38                       // Page 0 Register 38 - High_Power Output Driver Control Register
#define HPWR_STAGE_CNTRL 0, 40                        // Page 0 Register 40 - High_Power Output Stage Control Register
#define DAC_SWITCHING_CNTRL 0, 41                     // Page 0 Register 41 - DAC Output Switching Control Register

#define LEFT_DAC_VOLUME 0, 43                         // Page 0 Register 43 - Left DAC Volume Control Register
#define RIGHT_DAC_VOLUME 0, 44                        // Page 0 Register 44 - Right DAC Volume Control Register

#define DAC_MUTED 0x80                                // DAC is Muted when true (Registers 43 and 44)  

#define LEFT_DAC_HPLOUT_VOLUME 0, 47                  // Page 0 Register 47 - Left DAC to HPLOUT Volume Control Register
#define RIGHT_DAC_HPLOUT_VOLUME 0, 50                 // Page 0 Register 50 - Right DAC to HPLOUT Volume Control Register
#define HPLOUT_CNTRL 0, 51                            // Page 0 Register 51 - HPLOUT Control Register
#define LEFT_DAC_HPLCOM_VOLUME 0, 54                  // Page 0 Register 54 - Left DAC to HPLCOM Volume Control Register
#define RIGHT_DAC_HPLCOM_VOLUME 0, 57                 // Page 0 Register 57 - Right DAC to HPLCOM Volume Control Register
#define HPLCOM_CNTRL 0, 58                            // Page 0 Register 58 - HPLOUT Control Register

#define LEFT_DAC_HPROUT_VOLUME 0, 61                  // Page 0 Register 61 - Left DAC to HPROUT Volume Control Register
#define RIGHT_DAC_HPROUT_VOLUME 0, 64                 // Page 0 Register 64 - Right DAC to HPROUT Volume Control Register
#define HPROUT_CNTRL 0, 65                            // Page 0 Register 65 - HPROUT Control Register
#define LEFT_DAC_HPRCOM_VOLUME 0, 68                  // Page 0 Register 68 - Left DAC to HPRCOM Volume Control Register
#define RIGHT_DAC_HPRCOM_VOLUME 0, 71                 // Page 0 Register 71 - Right DAC to HPRCOM Volume Control Register
#define HPRCOM_CNTRL 0, 72                            // Page 0 Register 72 - HPROUT Control Register

#define LEFT_DAC_LEFT_LOUT_VOLUME 0, 82               // Page 0 Register 82 - Left DAC to Left LOP/LOM Volume Control Register
#define RIGHT_DAC_LEFT_LOUT_VOLUME 0, 85              // Page 0 Register 85 - Right DAC to Left LOP/LOM Volume Control Register
#define LEFT_LOUT_CNTRL 0, 86                         // Page 0 Register 86 - Left LOP/LOM Control Register

#define LEFT_DAC_RIGHT_LOUT_VOLUME 0, 89              // Page 0 Register 89 - Left DAC to Right LOP/LOM Volume Control Register
#define RIGHT_DAC_RIGHT_LOUT_VOLUME 0, 92             // Page 0 Register 92 - Right DAC to Right LOP/LOM Volume Control Register
#define RIGHT_LOUT_CNTRL 0, 93                        // Page 0 Register 93 - Right LOP/LOM Control Register

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













