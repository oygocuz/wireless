/*******************************************************************************************************
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Texas Instruments CC1110                                                   *
 * Author:                  TOS                                                                        *
 ******************************************************************************************************/

#include "twoway.h"
#include "codec_TLV320AIC26.h"

// External variables

extern UINT16 __xdata audiocontrol1; 
extern UINT16 __xdata adcgainctrl; 

// Some additional defines originally from "hal_CC2510.h"

// Example usage:
//   CLR_USART0_TX_STATUS();
//     ...
#define CLR_USART_TX_STATUS(num)    U##num##CSR &= ~0x02
#define CLR_USART0_TX_STATUS()      CLR_USART_TX_STATUS(0)
#define CLR_USART1_TX_STATUS()      CLR_USART_TX_STATUS(1)

INT16 __xdata tmpRegRead;

INT16 readCodecRegister(BYTE pageaddress, BYTE address) {
  INT16 returnValue;
  P0_4 = 0;                       // SS low

  CLR_USART0_TX_STATUS();

  // First byte
  U0DBUF = (0x80|(pageaddress&0x07)<<3|(address&0x38)>>3);   // Setup read bit, page address and 3 msb of register address
  while(!USART0_BYTE_TRANSMITTED());
  CLR_USART0_TX_STATUS();
  returnValue = U0DBUF;           // Dummy read

  // Second byte
  U0DBUF = (address&0x07)<<5;     // Setup 3 lsb of register address
  while(!USART0_BYTE_TRANSMITTED());
  CLR_USART0_TX_STATUS();
  returnValue = U0DBUF;           // Dummy read

  // Third byte
  U0DBUF = 0x00;                  // Read register high byte
  while(!USART0_BYTE_TRANSMITTED());
  CLR_USART0_TX_STATUS();
  returnValue = U0DBUF<<8;

  // Fourth byte
  U0DBUF = 0x00;                  // Read register low byte
  while(!USART0_BYTE_TRANSMITTED());
  CLR_USART0_TX_STATUS();
  returnValue |= U0DBUF;
  P0_4 = 1;                       // SS high

  return returnValue;
}

void writeCodecRegister(BYTE pageaddress, BYTE address, INT16 data) {
  P0_4 = 0;                       // SS low

  CLR_USART0_TX_STATUS();

  // SPI First byte:
  // SPI Bit  [   15] => Write bit (0)
  // SPI Bits [13:11] => PG[2:0] (3 lsb of page address)
  // SPI Bits [10: 8] => ADDR[5:3] (3 msb of register address)
  U0DBUF = ((pageaddress&0x07)<<3|(address&0x38)>>3);   // Setup write bit, page address and 3 msb of register address
  while(!USART0_BYTE_TRANSMITTED());
  CLR_USART0_TX_STATUS();

  // SPI Second byte:
  // SPI Bits [7:5] => ADDR[2:0] (3 lsb of register address)
  // SPI Bits [4:0] => Not used.
  U0DBUF = (address&0x07)<<5;     // Setup 3 lsb of register address
  while(!USART0_BYTE_TRANSMITTED());
  CLR_USART0_TX_STATUS();

  // SPI Third byte:
  // 8 msb of SPI data
  U0DBUF = (data&0xFF00)>>8;      // Write register high byte
  while(!USART0_BYTE_TRANSMITTED());
  CLR_USART0_TX_STATUS();

  // SPI Fourth byte:
  // 8 lsb of SPI data
  U0DBUF = (data&0x00FF);         // Write register high byte
  while(!USART0_BYTE_TRANSMITTED());
  CLR_USART0_TX_STATUS();

  P0_4 = 1;                       // SS high
}


void initCodec (void) {

  // Codec Power-up sequence:
  // 1. Power up all power supply pins of the CODEC device (already taken care of in EVM)
  // 2. Release hardware power down and issue a hardware reset signal to the reset pin
  // 3. Set up, generate and enable MCLK to the CODEC
 
  P0 &= ~0x80;
  P0 |= 0x80;           // low-to-high pulse on P0_7 (RESET)
   
// Timer 4 was set up in 'main'c'

  T4CTL |= 0x10;        // Start Timer 4  
  
  // Write to [TLV320AIC26.Reset Control]:
  // [Reset Control.Bits15:0]    => RZALL = 0xBB00 => Reset all TLV320AIC26 registers
  writeCodecRegister(1,0x04,0xBB00);

  // Write to [TLV320AIC26.Audio Control 1]:
  // [Audio Control 1.Bits15:14] => ADCHPF = 00b => Disabled
  // [Audio Control 1.Bits13:12] => ADCIN = 00b => Single-ended input MIC
  // [Audio Control 1.Bits11:10] => WLEN = 00b => CODEC Word length is 16 bit
  // [Audio Control 1.Bits9:8]   => DATFM = 00b => Digital Data Format is I2S mode
  // [Audio Control 1.Bits7:6]   => Reserved (read only)
  
#ifdef SR8KHZ  
  // [Audio Control 1.Bit5:3]    => DACFS = 111b => DAC FS = Fsref/6 = 8 kHz
  // [Audio Control 1.Bit2:0]    => ADCFS = 111b => ADC FS = Fsref/6 = 8 kHz
  audiocontrol1 = 0x003F;
#endif  

#ifdef SR12KHZ  
  // [Audio Control 1.Bit5:3]    => DACFS = 100b => DAC FS = Fsref/4 = 12 kHz
  // [Audio Control 1.Bit2:0]    => ADCFS = 100b => ADC FS = Fsref/4 = 12 kHz
  audiocontrol1 = 0x0024;
#endif    
  
#ifdef SR16KHZ  
  // [Audio Control 1.Bit5:3]    => DACFS = 011b => DAC FS = Fsref/3 = 16 kHz
  // [Audio Control 1.Bit2:0]    => ADCFS = 011b => ADC FS = Fsref/3 = 16 kHz
  audiocontrol1 = 0x001B;
#endif  
  
#ifdef SR24KHZ  
  // [Audio Control 1.Bit5:3]    => DACFS = 010b => DAC FS = Fsref/2 = 24 kHz
  // [Audio Control 1.Bit2:0]    => ADCFS = 010b => ADC FS = Fsref/2 = 24 kHz
  audiocontrol1 = 0x0012;
#endif  
  
  writeCodecRegister(AUDIO_CONTROL_1, audiocontrol1);
  
  // Write to [TLV320AIC26.CODEC ADC Gain Control]:
  // [CODEC ADC Gain Control.Bit15]    => ADMUT = 0b => ADC Channel not muted
  // [CODEC ADC Gain Control.Bits14:8] => ADPGA = 0110100b => ADC PGA = 26 dB
  // [CODEC ADC Gain Control.Bits7:5]  => AGCTG = 000b => AGC Target Level = -5.5 dB
  // [CODEC ADC Gain Control.Bits4:1]  => AGCTC = 0000b => AGC Time Constant = 0000 (Attack Time = 8 msec, Decay Time = 100 msec)
  // [CODEC ADC Gain Control.Bit0]     => AGCEN => AGC Enable
  
  adcgainctrl = 0x3400;
  writeCodecRegister(ADC_GAIN_CONTROL, adcgainctrl);

  // Write to [TLV320AIC26.CODEC DAC Gain Control]:
  // [CODEC DAC Gain Control.Bit15]    => DALMU = 0b => DAC left channel not muted
  // [CODEC DAC Gain Control.Bits14:8] => DALVL = 0000000b => DAC left channel volume control = 0 dB
  // [CODEC DAC Gain Control.Bit7]     => DARMU = 0b => DAC right channel not muted
  // [CODEC DAC Gain Control.Bits6:0]  => DARVL = 0000000b => DAC right channel volume control = 0 dB
  writeCodecRegister(2,0x02,0x0000);

  // Write to [TLV320AIC26.CODEC Sidetone Control]:
  // [CODEC Sidetone Control.Bit15]    => ASTMU = 1b => Analog sidetone muted
  // [CODEC Sidetone Control.Bits14:8] => ASTG = 1000101b => Analog sidetone gain setting = 0 dB
  // [CODEC Sidetone Control.Bit7]     => DSTMU = 1b => Digital sidetone muted
  // [CODEC Sidetone Control.Bits6:1]  => DSTG = 000000b => Digital sidetone gain = 0 dB
  // [CODEC Sidetone Control.Bit0]     => ASTGF => Analog sidetone PGA flag (read only)
  writeCodecRegister(2,0x03,0xC580);

  // Write to [TLV320AIC26.Audio Control 2]:
  // [CODEC Audio Control 2.Bit15]     => KCLEN = 0b => Keyclick disabled
  // [CODEC Audio Control 2.Bits14:12] => KCLAC = 100b => Medium amplitude
  // [CODEC Audio Control 2.Bit11]     => APGASS = 0b => 0.5 dB change every ADWS
  // [CODEC Audio Control 2.Bits10:8]  => KCLFRQ = 100b => Keyclick freqyency = 1 kHz
  // [CODEC Audio Control 2.Bits7:4]   => KCLLN = 1111b => Keyclick length = 32 periods key click
  // [CODEC Audio Control 2.Bit3]      => DLGAF = DAC Left Channel PGA Flag (read only)
  // [CODEC Audio Control 2.Bit2]      => DRGAF = DAC Right Channel PGA Flag (read only)
  // [CODEC Audio Control 2.Bit1]      => DASTC = 0.5 dB change every LRCK
  // [CODEC Audio Control 2.Bit0]      => ADGAF = ADC Channel PGA Flag (read only)
  writeCodecRegister(2,0x04,0x44F0);

  // Write to [TLV320AIC26.CODEC Power Control]:
  // [CODEC Power Control.Bit15]       => PWDNC = 0b => Codec powered up
  // [CODEC Power Control.Bit14]       => Reserved (read only)
  // [CODEC Power Control.Bit13]       => ASTPWD = 1b => Analog sidetone powered down
  // [CODEC Power Control.Bit12]       => DAODRC = 0b => Output driver in low-power mode
  // [CODEC Power Control.Bit11]       => ASTPWF = 0b => Analog Sidetone Power-Down Flag (read only)
  // [CODEC Power Control.Bit10]       => DAPWDN = 0b => Power up the DAC
  // [CODEC Power Control.Bit9]        => ADPWDN = 0b => Power up the ADC
  // [CODEC Power Control.Bit8]        => VGPWDN = 0b => Power up the VGND amp
  // [CODEC Power Control.Bit7]        => ADPWDF = ADC Power-Down Flag (read only)
  // [CODEC Power Control.Bit6]        => DAPWDF = DAC Power-Down Flag (read only)
  // [CODEC Power Control.Bit5]        => ADWSF = 1b => ADWS pin acts as ADC Word-Select => NB!!!
  // [CODEC Power Control.Bit4]        => VBIAS = 0b => VBIAS output = 2.5 V
  // [CODEC Power Control.Bits2:2]     => Reserved (read only)
  // [CODEC Power Control.Bit1]        => EFFCTL = 0 => Disable digital audio effects filter
  // [CODEC Power Control.Bit0]        => DEEMPF = 0 => Disable de-emphasis filter
  writeCodecRegister(2,0x05,0x2020);

  // Write to [TLV320AIC26.Audio Control 3]:
  // [Audio Control 3.Bits15:14]       => DMSVOL = 00b => Left channel and right channel have independant volume controls => CORRECT?
  // [Audio Control 3.Bit13]           => REFFS = 1b => 44.1 kHz
  // [Audio Control 3.Bit12]           => DAXFM = 1b => 256-s data transfer mode
  // [Audio Control 3.Bit11]           => SLVMS = 0b => AIC26 is slave CODEC
  // [Audio Control 3.Bits10-9]        => DAPK2PK = 10b => DAC max output signal swing = 2.402 V, Vcm = 1.62 V
  // [Audio Control 3.Bit8]            => ADCOVF => ADC Channel Overflow Flag (read only)
  // [Audio Control 3.Bit7]            => DALOVF => DAC Left Channel Overflow Flag (read only)
  // [Audio Control 3.Bit6]            => DAROVF => DAC Right Channel Overflow Flag (read only)
  // [Audio Control 3.Bits5:4]         => AGCNL = 11b => AGC noise threshold = -90 dB
  // [Audio Control 3.Bit3]            => CLPPST = 0b => AGC clip stepping disabled
  // [Audio Control 3.Bits2:0]         => REVID = Reserved (read only)
  writeCodecRegister(2,0x06,0x3430);

// Set up the PLL to generate a fsref clock frequency of 48 kHz from the MCLK frequency of 13 MHz
// Fsref = (MCLK x K) / 2048 x P) where K = J.D
// 
// MCLK = 13.0 MHz; P = 1; J = 7; D = 5618 
// Fsref = 13000 x 7.5618 / 2048 = 47.999707 kHz  
  
  // Write to [TLV320AIC26.PLL Programmability]:
  // [PLL Programmability.Bit15]       => PLLSEL = 1b => PLL enabled
  // [PLL Programmability.Bits14:11]   => QVAL = 0010b => Q value = 2
  // [PLL Programmability.Bits10:8]    => PVAL = 0001b => P value = 1
  // [PLL Programmability.Bits7:2]     => JVAL = 000111b => J value = 7
  // [PLL Programmability.Bits1:0]     => Reserved (read only)
  writeCodecRegister(2,0x1B,0x911C);

  // Write to [TLV320AIC26.PLL Programmability]:
  // [PLL Programmability.Bits15:2]    => DVAL = 01010111110010b (5618d)
  writeCodecRegister(2,0x1C,0x57C8);

  // Write to [TLV320AIC26.Audio Control 5]:
  // [Audio Control 5.Bits15:9]        => MAX_AGC_PGA = 100000b => 40 dB
  // [Audio Control 5.Bits8:6]         => AGC_NOI_DEB = 000b => 32 msec
  // [Audio Control 5.Bits5:3]         => AGC_SIG_DEB = 16.0 msec
  // [Audio Control 5.Bit2]            => DRV_POP_DIS = 0 => Audio Outout Driver POP Redution Enabled
  // [Audio Control 5.Bit1]            => DRV_POP_LEN = 0 => Audio Outout Driver POP Redution Duration = 4 sec
  // [Audio Control 5.Bit0]            => Reserved (read only)
  writeCodecRegister(2,0x1E,0x8030);

  return;
}

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


