/*
 *******************************************************************************************************
 * board.h                  Hardware Description File                                                  *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Texas Instruments CC1110                                                   *
 * Author:                  MJB                                                                        *
 * Last Update:             06 April 2011                                                              * 
 *******************************************************************************************************
*/

#ifndef BOARD_H
#define BOARD_H

//-------------------------------------------------------------------------------------------------------
// Includes

#include "ioCC1110.h"
#include "hal.h"

//-------------------------------------------------------------------------------------------------------
// Hardware assignments

#define I2C_PORT          P0        // Port 0
#define I2C_Px_DIR     P0DIR
#define I2C_SCL         0x08        // bit 3
#define I2C_SDA         0x10        // bit 4

//-------------------------------------------------------------------------------------------------------
// Compile-time options

#define MAC_ADDR  0x73

// Battery voltage lower limit

#define BVLIMIT 0x07BE      // Approximately 3650 mV

// ADC/DAC Sample Rate Options
// Choose one and only one option!

//#define SR8KHZ
//#define SR12KHZ
#define SR16KHZ
//#define SR24KHZ

// data rate and modulation options
// Select (uncomment) only one!

//#define BAUD250GFSK         // 250 kbps, GFSK modulation
//#define BAUD300MSK          // 300 kbps, MSK modulation
#define BAUD300GFSK         // 300 kbps, GFSK modulation
//#define BAUD300_2FSK        // 300 kbps, 2-FSK modulation

// Global definitions

// Number of ADC samples per packet. Each ADC sample is 16 bits (2 bytes).
#define AF_LEN  96

// Audio frame and buffer size
#define AF_BUF_SIZE  AF_LEN    // Size of audio buffer in words

// Packet format and segment lengths (bytes)
#define PHY_FIELD_LEN               1       // Length byte
#define MAC_FIELD_LEN               1       // MAC address (NOT TO BE CHANGED FROM DEFAULT VALUE (1) without changing througout the code!)

#define TX_PAYLOAD_LEN  (MAC_FIELD_LEN + AF_LEN*2)

// DMA Channels
#define DMA_RX  1
#define DMA_TX  2
#define DMA_AUDIO_IN  3
#define DMA_AUDIO_OUT 4

// Timer flags
#define T3OVFIF                         0x01

// Marcstates
#define MARCSTATE_TX                    0x13
#define MARCSTATE_RX                    0x0D
#define MARCSTATE_IDLE                  0x01

// "LISTENFORMASTER" value calculation:
// Packet length (bytes) = 2 * AF_LEN + preamble bytes + sync bytes + CRC bytes + 3
// Packet length (usec) = packet length (bytes) * 8000 / data_rate in kbps
// Start Listening for Master packet length + 600 usec before the end of frame
//
// Examples:
//
// data rate = 250 kbaud, sample rate = 12 kHz: 
// packet length (bytes) = 2 * 54 + 4 + 4 + 2 + 3 = 121 bytes
// packet length (usec) = 121 * 8000 / 250 = 3872 usec
// LISTENFORMASTER = 4472 / 29.538 = 151
//
// data rate = 300 kbaud, sample rate = 12 kHz: 
// packet length (bytes) = 2 * 54 + 4 + 4 + 2 + 3 = 121 bytes
// packet length (usec) = 121 * 8000 / 300 = 3226.7 usec
// LISTENFORMASTER = 3826.7 / 29.538 = 130

  
#define FRAME_TIMEOUT_DEFAULT           161       // (T2CT) Timeout = 161 * 29.538 us = 4.756 msec
                                                  // Note that this is 250 usec longer than a frame, so T2 should never reach zero
#define END_OF_FRAME                      8       // T2CT count at end of frame (4.519 msec)

// T3 Timeout defines (First parameter is timeout in 4.923076923 us, Second parameter is multiplier since this is a 8 bit timer only)
// For RX, the T3 timer sets the point (with reference to RX turn on) at which RX activity is checked. This is done by
// looking for high level on P1_5 (GDO0), which will be high from the time that SYNC is detected until the end of a packet.

// Packet legth is 
// SYNC bytes + Preamble bytes + 2 + 96*2 + CRC bytes
//  = 4 + 4 + 2 + 96*2 + 2 = 204 bytes
// At a data rate of 300 kbps, Tx On = 204*8000/300 + 88 = 5528 usec

#ifdef BAUD500MSK
#define MASTER_TX_TIMEOUT_WO_CALIB      213, 3    // Timeout = 213 * 4.923076923 us * 2 = 2097.2 us
#endif

#ifdef BAUD300MSK
#define MASTER_TX_TIMEOUT_WO_CALIB      228, 5    // Timeout = 226 * 4.923076923 us * 5 = 5612.3 us
#endif

#ifdef BAUD300GFSK
#define MASTER_TX_TIMEOUT_WO_CALIB      228, 5    // Timeout = 226 * 4.923076923 us * 5 = 5612.3 us
#endif

#ifdef BAUD300_2FSK
#define MASTER_TX_TIMEOUT_WO_CALIB      228, 5    // Timeout = 226 * 4.923076923 us * 5 = 5612.3 us
#endif

// TX status flags

#define TX_IN_PROGRESS                  0x80
#define TX_SUCCESSFUL                   0x40
#define DEST_UNREACHABLE                0x20
#define TX_WAIT                         0x10
#define TX_IDLE                         0x00

// LED, Pushbutton Assignments

#define LED_BLUE_REG P1
#define LED_BLUE 0x01     // P1_0
#define LED_GREEN_REG P1
#define LED_GREEN  0x02   // P1_1

#define GDO0MSK 0x20                      // GDO0 appears on bit 5 of P1

// TX struct
typedef struct{
  BYTE macPayloadLen;                     // Length byte
  BYTE macField;                          // MAC address
  UINT16 payload[AF_LEN];                 // Audio samples
} __xdata TX_MASTER_STRUCT;


//-------------------------------------------------------------------------------------------------------
// Function prototype declarations

// init_peripherals.c
void init_peripherals(void);
void macTimer3Init(void);

// init_Codec.c
void init_codec(void);

// i2c.c
void I2Cwrite(char page_addr, char reg_addr, char data);

// tw_dma.c
void dmaAudio(void);
void dmaToRadio(WORD length, WORD srcAddr);
void dmaMemtoMem(UINT8 length);

// tw_rf.c
void rfConfigRadio(void);
BOOL initRf(void);
BOOL rfSendPacket(UINT8 timeout, UINT8 multiplier);

// tw_mac.c
void macsetT3TimeoutAndWait(UINT8 timeout, UINT8 multiplier);
void setChannel(UINT8 ch);

// Global extern variables

extern TX_MASTER_STRUCT __xdata MAStxData;      // Data packet struct

extern volatile BYTE __xdata txStatus;          // Status flags

extern UINT16 __xdata audioOut[2][AF_BUF_SIZE];     // Audio Out (playback) Buffer
extern UINT8  __xdata activeOut;                    // Audio Out active buffer (0 | 1)

// DMA
extern DMA_DESC __xdata DmaDesc0;
extern DMA_DESC __xdata DmaDesc1_4[];

extern UINT8 audioInindx;
extern UINT8 audioOutindx;
extern UINT16 timerSampleRate;
extern BOOL __xdata audioFrameReady;

#endif

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

