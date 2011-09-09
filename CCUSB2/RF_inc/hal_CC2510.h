/*******************************************************************************************************
 * hal_CC2510.h                                                                                        *
 * Compiler:                IAR 8051 compiler for CC2510                                               *
 * Target platform:         Texas Instruments CC2510                                                   *
 * Author:                  TOS                                                                        *
 ******************************************************************************************************/


#ifndef HAL_CC2510_H
#define HAL_CC2510_H

#if(chip == 1110)
#include "ioCC1110.h"
#endif

#if(chip == 1111)
#include "ioCC1111.h"
#endif

#if(chip == 2510)
#include "ioCC2510.h"
#endif

#if(chip == 2511)
#include "ioCC2511.h"
#endif

/******************************************************************************
*******************              Commonly used types        *******************
******************************************************************************/
typedef unsigned char       BOOL;

// Data
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;

// Unsigned numbers
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned long       UINT32;

// Signed numbers
typedef signed char         INT8;
typedef signed short        INT16;
typedef signed long         INT32;

// Common values
#ifndef FALSE
   #define FALSE 0
#endif

#ifndef TRUE
   #define TRUE 1
#endif

#ifndef NULL
   #define NULL 0
#endif

#ifndef HIGH
   #define HIGH 1
#endif

#ifndef LOW
   #define LOW 0
#endif

// Typedef void pointer
//typedef void (*VFPTR)(void);

/******************************************************************************
*******************        Bit, byte and word macros        *******************
******************************************************************************/

// bit mask
#define BM( b )       ( 0x01 << ( b ))

#define HIBYTE(a)     (BYTE) ((WORD)(a) >> 8 )
#define LOBYTE(a)     (BYTE)  (WORD)(a)

#define SET_WORD(regH, regL, word) \
   do{                             \
      (regH) = HIBYTE( word );     \
      (regL) = LOBYTE( word );     \
   }while(0)

#define GET_WORD(regH, regL, word) \
   do{                             \
      word = (WORD)regH << 8;      \
      word |= regL;                \
   }while(0)

/******************************************************************************
*******************             Port functions/macros       *******************
*******************************************************************************

Macros for simplifying access to I/O pin setup and usage.

MCU pin configuration:
---------------------------------------------
| Peripheral I/O signal  |  Alt1   |   Alt2 |
---------------------------------------------
| Timer1 channel0        |  P0.2   |   P1.2 |
| Timer1 channel1        |  P0.3   |   P1.1 |
| Timer1 channel2        |  P0.4   |   P1.0 |
| Timer3 channel0        |  P1.3   |   P1.6 |
| Timer3 channel1        |  P1.4   |   P1.7 |
| Timer4 channel0        |  P1.0   |   P2.0 |
| Timer4 channel1        |  P1.1   |   P2.3 |
| USART0 TXD/MOSI        |  P0.3   |   P1.5 |
| USART0 RXD/MISO        |  P0.2   |   P1.4 |
| USART0 RTS/SCK         |  P0.5   |   P1.3 |
| USART0 CTS/SS_N        |  P0.4   |   P1.2 |
| USART1 TXD/MOSI        |  P0.4   |   P1.6 |
| USART1 RXD/MISO        |  P0.5   |   P1.7 |
| USART1 RTS/SCK         |  P0.3   |   P1.5 |
| USART1 CTS/SS_N        |  P0.2   |   P1.4 |
---------------------------------------------

******************************************************************************/


// Macros for configuring IO peripheral location:
// Example usage:
//   IO_PER_LOC_TIMER1_AT_PORT0_PIN234();
//   IO_PER_LOC_TIMER4_AT_PORT2_PIN03();
//   IO_PER_LOC_USART1_AT_PORT0_PIN2345();

#define IO_PER_LOC_TIMER1_AT_PORT0_PIN234()  do { PERCFG = (PERCFG&~0x40)|0x00; } while (0)
#define IO_PER_LOC_TIMER1_AT_PORT1_PIN012()  do { PERCFG = (PERCFG&~0x40)|0x40; } while (0)

#define IO_PER_LOC_TIMER3_AT_PORT1_PIN34()   do { PERCFG = (PERCFG&~0x20)|0x00; } while (0)
#define IO_PER_LOC_TIMER3_AT_PORT1_PIN67()   do { PERCFG = (PERCFG&~0x20)|0x20; } while (0)

#define IO_PER_LOC_TIMER4_AT_PORT1_PIN01()   do { PERCFG = (PERCFG&~0x10)|0x00; } while (0)
#define IO_PER_LOC_TIMER4_AT_PORT2_PIN03()   do { PERCFG = (PERCFG&~0x10)|0x10; } while (0)

#define IO_PER_LOC_USART1_AT_PORT0_PIN2345() do { PERCFG = (PERCFG&~0x02)|0x00; } while (0)
#define IO_PER_LOC_USART1_AT_PORT1_PIN4567() do { PERCFG = (PERCFG&~0x02)|0x02; } while (0)

#define IO_PER_LOC_USART0_AT_PORT0_PIN2345() do { PERCFG = (PERCFG&~0x01)|0x00; } while (0)
#define IO_PER_LOC_USART0_AT_PORT1_PIN2345() do { PERCFG = (PERCFG&~0x01)|0x01; } while (0)

#define IO_PER_LOC_I2S_AT_PORT1_PIN67_PORT0_PIN01()                                   \
   do {                                                                               \
      /* Alt.1 location */                                                            \
      I2SCFG1 &= ~0x01;                                                               \
                                                                                      \
      /* Assign pin function for I2S Periperhal */                                    \
      /* P0.0 = I2S.WS, P0.1 => I2S.CK */                                             \
      /* P1.6 = I2S.TX, P1.7 = I2S.RX */                                              \
      P1SEL |= 0xC0;                                                                  \
      P0SEL |= 0x03;                                                                  \
   } while(0)



// Macros for configuring IO direction:
// Example usage:
//   IO_DIR_PORT_PIN(0, 3, IO_IN);    // Set P0_3 to input
//   IO_DIR_PORT_PIN(2, 1, IO_OUT);   // Set P2_1 to output

#define IO_DIR_PORT_PIN(port, pin, dir)  \
   do {                                  \
      if (dir == IO_OUT)                 \
         P##port##DIR |= BM( pin );      \
      else                               \
         P##port##DIR &= ~BM( pin );     \
   }while(0)

// Where port={0,1,2}, pin={0,..,7} and dir is one of:
#define IO_IN   0
#define IO_OUT  1

// Macros for configuring IO input mode:
// Example usage:
//   IO_IMODE_PORT_PIN(0, 0, IO_IMODE_PUD);
//   IO_IMODE_PORT_PIN(2, 0, IO_IMODE_TRI);
//   IO_IMODE_PORT_PIN(1, 3, IO_IMODE_PUD);

#define IO_IMODE_PORT_PIN(port, pin, imode) \
   do {                                     \
      if (imode == IO_IMODE_TRI)            \
         P##port##INP |= BM( pin );         \
      else                                  \
         P##port##INP &= ~BM( pin );        \
   } while (0)

// where imode is one of:
#define IO_IMODE_PUD  0 // Pull-up/pull-down
#define IO_IMODE_TRI  1 // Tristate

// Macro for configuring IO drive mode:
// Example usage:
//   IIO_PUD_PORT(0, IO_PULLUP);
//   IIO_PUD_PORT(1, IO_PULLDOWN);
//   IIO_PUD_PORT(2, IO_PULLUP);

#define IO_PUD_PORT(port, pud)        \
   do {                               \
      if (pud == IO_PULLDOWN)         \
         P2INP |= BM( port + 5 );     \
      else                            \
         P2INP &= ~BM( port + 5 );    \
   } while (0)

#define IO_PULLUP          0
#define IO_PULLDOWN        1

// Macros for function select (General purpose I/O / Peripheral function):
// Example usage:
//   IO_FUNC_PORT_PIN(0, 0, IO_FUNC_PERIPH);
//   IO_FUNC_PORT_PIN(0, 1, IO_FUNC_GIO);
//   IO_FUNC_PORT_PIN(2, 3, IO_FUNC_PERIPH);

#define IO_FUNC_PORT_PIN(port, pin, func)  \
   do {                                    \
      if((port == 2) && (pin == 3)){       \
         if (func) {                       \
            P2SEL |= 0x02;                 \
         } else {                          \
            P2SEL &= ~0x02;                \
         }                                 \
      }                                    \
      else if((port == 2) && (pin == 4)){  \
         if (func) {                       \
            P2SEL |= 0x04;                 \
         } else {                          \
            P2SEL &= ~0x04;                \
         }                                 \
      }                                    \
      else{                                \
         if (func) {                       \
            P##port##SEL |= BM( pin );     \
         } else {                          \
            P##port##SEL &= ~BM( pin );    \
        }                                  \
      }                                    \
   } while (0)

// where func is one of:
#define IO_FUNC_GIO     0 // General purpose I/O
#define IO_FUNC_PERIPH  1 // Peripheral function

// Macros for configuring the ADC input:
// Example usage:
//   IO_ADC_PORT0_PIN(0, IO_ADC_EN);
//   IO_ADC_PORT0_PIN(4, IO_ADC_DIS);
//   IO_ADC_PORT0_PIN(6, IO_ADC_EN);

#define IO_ADC_PORT0_PIN(pin, adcEn)  \
  do {                                \
    if (adcEn)                        \
      ADCCFG |= BM( pin );            \
    else                              \
      ADCCFG &= ~BM( pin );           \
  }while (0)

// where adcEn is one of:
#define IO_ADC_EN           1 // ADC input enabled
#define IO_ADC_DIS          0 // ADC input disab


/******************************************************************************
*******************       Interrupt functions/macros        *******************
*******************************************************************************

Macros which simplify access to interrupt enables, interrupt flags and
interrupt priorities. Increases code legibility.

******************************************************************************/

#define INT_ON   1
#define INT_OFF  0
#define INT_SET  1
#define INT_CLR  0

// Global interrupt enables
#define INT_GLOBAL_ENABLE(on) EA = (!!on)

#define DISABLE_ALL_INTERRUPTS() (IEN0 = IEN1 = IEN2 = 0x00)

#if(chip == 2430 || chip == 2431)
#define INUM_RFERR 0
#endif
#if(chip == 1110 || chip == 1111 || chip == 2510 || chip == 2511)
#define INUM_RFTXRX 0
#endif
#define INUM_ADC   1
#define INUM_URX0  2
#define INUM_URX1  3
#define INUM_ENC   4
#define INUM_ST    5
#define INUM_P2INT 6
#define INUM_UTX0  7
#define INUM_DMA   8
#define INUM_T1    9
#define INUM_T2    10
#define INUM_T3    11
#define INUM_T4    12
#define INUM_P0INT 13
#define INUM_UTX1  14
#define INUM_P1INT 15
#define INUM_RF    16
#define INUM_WDT   17

#define NBR_OF_INTERRUPTS 18

// Macro used together with the INUM_* constants
// to enable or disable certain interrupts.
// Example usage:
//   INT_ENABLE(INUM_RFERR, INT_ON);
//   INT_ENABLE(INUM_URX0, INT_OFF);
//   INT_ENABLE(INUM_T1, INT_ON);
//   INT_ENABLE(INUM_T2, INT_OFF);
#if(chip == 2430 || chip == 2431)
#define INT_ENABLE(inum, on)                                                    \
   do {                                                                         \
      if      (inum==INUM_RFERR) { RFERRIE = on; }                              \
      else if (inum==INUM_ADC)   { ADCIE   = on; }                              \
      else if (inum==INUM_URX0)  { URX0IE  = on; }                              \
      else if (inum==INUM_URX1)  { URX1IE  = on; }                              \
      else if (inum==INUM_ENC)   { ENCIE   = on; }                              \
      else if (inum==INUM_ST)    { STIE    = on; }                              \
      else if (inum==INUM_P2INT) { (on) ? (IEN2 |= 0x02) : (IEN2 &= ~0x02); }   \
      else if (inum==INUM_UTX0)  { (on) ? (IEN2 |= 0x04) : (IEN2 &= ~0x04); }   \
      else if (inum==INUM_DMA)   { DMAIE   = on; }                              \
      else if (inum==INUM_T1)    { T1IE    = on; }                              \
      else if (inum==INUM_T2)    { T2IE    = on; }                              \
      else if (inum==INUM_T3)    { T3IE    = on; }                              \
      else if (inum==INUM_T4)    { T4IE    = on; }                              \
      else if (inum==INUM_P0INT) { P0IE    = on; }                              \
      else if (inum==INUM_UTX1)  { (on) ? (IEN2 |= 0x08) : (IEN2 &= ~0x08); }   \
      else if (inum==INUM_P1INT) { (on) ? (IEN2 |= 0x10) : (IEN2 &= ~0x10); }   \
      else if (inum==INUM_RF)    { (on) ? (IEN2 |= 0x01) : (IEN2 &= ~0x01); }   \
      else if (inum==INUM_WDT)   { (on) ? (IEN2 |= 0x20) : (IEN2 &= ~0x20); }   \
   } while (0)
#endif

#if(chip == 1110 || chip == 1111 || chip == 2510 || chip == 2511)
#define INT_ENABLE(inum, on)                                                    \
   do {                                                                         \
      if      (inum==INUM_RFTXRX) { RFTXRXIE = on; }                            \
      else if (inum==INUM_ADC)    { ADCIE   = on;  }                            \
      else if (inum==INUM_URX0)   { URX0IE  = on;  }                            \
      else if (inum==INUM_URX1)   { URX1IE  = on;  }                            \
      else if (inum==INUM_ENC)    { ENCIE   = on;  }                            \
      else if (inum==INUM_ST)     { STIE    = on;  }                            \
      else if (inum==INUM_P2INT)  { (on) ? (IEN2 |= 0x02) : (IEN2 &= ~0x02); }  \
      else if (inum==INUM_UTX0)   { (on) ? (IEN2 |= 0x04) : (IEN2 &= ~0x04); }  \
      else if (inum==INUM_DMA)    { DMAIE   = on;  }                            \
      else if (inum==INUM_T1)     { T1IE    = on;  }                            \
      else if (inum==INUM_T2)     { T2IE    = on;  }                            \
      else if (inum==INUM_T3)     { T3IE    = on;  }                            \
      else if (inum==INUM_T4)     { T4IE    = on;  }                            \
      else if (inum==INUM_P0INT)  { P0IE    = on;  }                            \
      else if (inum==INUM_UTX1)   { (on) ? (IEN2 |= 0x08) : (IEN2 &= ~0x08); }  \
      else if (inum==INUM_P1INT)  { (on) ? (IEN2 |= 0x10) : (IEN2 &= ~0x10); }  \
      else if (inum==INUM_RF)     { (on) ? (IEN2 |= 0x01) : (IEN2 &= ~0x01); }  \
      else if (inum==INUM_WDT)    { (on) ? (IEN2 |= 0x20) : (IEN2 &= ~0x20); }  \
   } while (0)
#endif


// Macro for setting interrupt group priority
// Example usage:
//   INT_PRIORITY(RFERR_RF_DMA, 3);
#define INT_PRIORITY(group, pri)                      \
   do {                                               \
      if (pri == 0) { IP0 &= ~group; IP1 &= ~group; } \
      if (pri == 1) { IP0 |=  group; IP1 &= ~group; } \
      if (pri == 2) { IP0 &= ~group; IP1 |=  group; } \
      if (pri == 3) { IP0 |=  group; IP1 |=  group; } \
   } while (0)
// Where pri is one of:
//   0 = Level 0 (lowest priority)
//   1 = Level 1
//   2 = Level 2
//   3 = Level 3 (highest priority)

// Where group is one of
#define RFERR_RF_DMA    0x01 // Group IP0
#define ADC_P2INT_T1    0x02 // Group IP1
#define URX0_UTX0_T2    0x04 // Group IP2
#define URX1_UTX1_T3    0x08 // Group IP3
#define ENC_P1INT_T4    0x10 // Group IP4
#define ST_WDT_P0INT    0x20 // Group IP5


// Macro used together with the INUM_* constants
// to read the interrupt flags.
// Example usage:
//   if (INT_GETFLAG(INUM_URX0))
//     ...
//   while (!INT_GETFLAG(INUM_URX0));

#if(chip == 1110 || chip == 1111 || chip == 2510 || chip == 2511)
#define INT_GETFLAG(inum) (                       \
   (inum==INUM_RFTXRX)      ? RFTXRXIF          : \
   (inum==INUM_ADC)         ? ADCIF             : \
   (inum==INUM_URX0)        ? URX0IF            : \
   (inum==INUM_URX1)        ? URX1IF            : \
   (inum==INUM_ENC)         ? ENCIF_0           : \
   (inum==INUM_ST)          ? STIF              : \
   (inum==INUM_P2INT)       ? P2IF              : \
   (inum==INUM_UTX0)        ? UTX0IF            : \
   (inum==INUM_DMA)         ? DMAIF             : \
   (inum==INUM_T1)          ? T1IF              : \
   (inum==INUM_T2)          ? T2IF              : \
   (inum==INUM_T3)          ? T3IF              : \
   (inum==INUM_T4)          ? T4IF              : \
   (inum==INUM_P0INT)       ? P0IF              : \
   (inum==INUM_UTX1)        ? UTX1IF            : \
   (inum==INUM_P1INT)       ? P1IF              : \
   (inum==INUM_RF)          ? S1CON &= ~0x03    : \
   (inum==INUM_WDT)         ? WDTIF             : \
   0                                              \
)

#endif


// Macro used to set or clear certain interrupt flags.
// Example usage:
//   INT_SETFLAG(INUM_URX0, INT_SET;
//   INT_SETFLAG(INUM_T3, INT_CLR);
#if(chip == 1110 || chip == 1111 || chip == 2510 || chip == 2511)
#define INT_SETFLAG(inum, f)                                                    \
   do {                                                                         \
      if      (inum==INUM_RFTXRX){ RFTXRXIF = f; }                              \
      else if (inum==INUM_ADC)   { ADCIF  = f; }                                \
      else if (inum==INUM_URX0)  { URX0IF = f; }                                \
      else if (inum==INUM_URX1)  { URX1IF = f; }                                \
      else if (inum==INUM_ENC)   { ENCIF_1 = ENCIF_0 = f; }                     \
      else if (inum==INUM_ST)    { STIF  = f;  }                                \
      else if (inum==INUM_P2INT) { P2IF  = f;  }                                \
      else if (inum==INUM_UTX0)  { UTX0IF= f;  }                                \
      else if (inum==INUM_DMA)   { DMAIF = f;  }                                \
      else if (inum==INUM_T1)    { T1IF  = f;  }                                \
      else if (inum==INUM_T2)    { T2IF  = f;  }                                \
      else if (inum==INUM_T3)    { T3IF  = f;  }                                \
      else if (inum==INUM_T4)    { T4IF  = f;  }                                \
      else if (inum==INUM_P0INT) { P0IF  = f;  }                                \
      else if (inum==INUM_UTX1)  { UTX1IF= f;  }                                \
      else if (inum==INUM_P1INT) { P1IF  = f;  }                                \
      else if (inum==INUM_RF)    { (f) ? (S1CON |= 0x03) : (S1CON &= ~0x03); }  \
      else if (inum==INUM_WDT)   { WDTIF = f;  }                                \
   } while (0)
#endif



/******************************************************************************
**************************   DMA structures / macros  *************************
*******************************************************************************

The macros and structs in this section simplify setup and usage of DMA.

******************************************************************************/

#define DMA_CHANNEL_0           0x01
#define DMA_CHANNEL_1           0x02
#define DMA_CHANNEL_2           0x04
#define DMA_CHANNEL_3           0x08
#define DMA_CHANNEL_4           0x10

#define VLEN_USE_LEN            0x00 // Use LEN for transfer count
#define VLEN_FIXED              0x00 // Use LEN for transfer count
#define VLEN_1_P_VALOFFIRST     0x01 // Transfer the first byte + the number of bytes indicated by the first byte
#define VLEN_VALOFFIRST         0x02 // Transfer the number of bytes indicated by the first byte (starting with the first byte)
#define VLEN_1_P_VALOFFIRST_P_1 0x03 // Transfer the first byte + the number of bytes indicated by the first byte + 1 more byte
#define VLEN_1_P_VALOFFIRST_P_2 0x04 // Transfer the first byte + the number of bytes indicated by the first byte + 2 more bytes

#define WORDSIZE_BYTE           0x00 // Transfer a byte at a time
#define WORDSIZE_WORD           0x01 // Transfer a 16-bit word at a time

#define TMODE_SINGLE            0x00 // Transfer a single byte/word after each DMA trigger
#define TMODE_BLOCK             0x01 // Transfer block of data (length len) after each DMA trigger
#define TMODE_SINGLE_REPEATED   0x02 // Transfer single byte/word (after len transfers, rearm DMA)
#define TMODE_BLOCK_REPEATED    0x03 // Transfer block of data (after len transfers, rearm DMA)

#define DMATRIG_NONE               0 // No trigger, setting DMAREQ.DMAREQx bit starts transfer
#define DMATRIG_PREV               1 // DMA channel is triggered by completion of previous channel
#define DMATRIG_T1_CH0             2 // Timer 1, compare, channel 0
#define DMATRIG_T1_CH1             3 // Timer 1, compare, channel 1
#define DMATRIG_T1_CH2             4 // Timer 1, compare, channel 2
#define DMATRIG_T2_COMP            5 // Timer 2, compare
#define DMATRIG_T2_OVFL            6 // Timer 2, overflow
#define DMATRIG_T3_CH0             7 // Timer 3, compare, channel 0
#define DMATRIG_T3_CH1             8 // Timer 3, compare, channel 1
#define DMATRIG_T4_CH0             9 // Timer 4, compare, channel 0
#define DMATRIG_T4_CH1            10 // Timer 4, compare, channel 1
#define DMATRIG_ST                11 // Sleep Timer compare
#define DMATRIG_IOC_0             12 // Port 0 I/O pin input transition
#define DMATRIG_IOC_1             13 // Port 1 I/O pin input transition
#define DMATRIG_URX0              14 // USART0 RX complete
#define DMATRIG_UTX0              15 // USART0 TX complete
#define DMATRIG_URX1              16 // USART1 RX complete
#define DMATRIG_UTX1              17 // USART1 TX complete
#define DMATRIG_FLASH             18 // Flash data write complete
#define DMATRIG_RADIO             19 // RF packet byte received/transmit
#define DMATRIG_ADC_CHALL         20 // ADC end of a conversion in a sequence, sample ready
#define DMATRIG_ADC_CH0           21 // ADC end of conversion channel 0 in sequence, sample ready
#define DMATRIG_ADC_CH1           22 // ADC end of conversion channel 1 in sequence, sample ready
#define DMATRIG_ADC_CH2           23 // ADC end of conversion channel 2 in sequence, sample ready
#define DMATRIG_ADC_CH3           24 // ADC end of conversion channel 3 in sequence, sample ready
#define DMATRIG_ADC_CH4           25 // ADC end of conversion channel 4 in sequence, sample ready
#define DMATRIG_ADC_CH5           26 // ADC end of conversion channel 5 in sequence, sample ready
#define DMATRIG_ADC_CH6           27 // ADC end of conversion channel 6 in sequence, sample ready
#define DMATRIG_ADC_CH7           28 // ADC end of conversion channel 7 in sequence, sample ready
#define DMATRIG_ADC_I2S_RX        DMATRIG_ADC_CH6 // I2S word/byte received
#define DMATRIG_ADC_I2S_TX        DMATRIG_ADC_CH7 // I2S word/byte transmitted
#define DMATRIG_ENC_DW            29 // AES encryption processor requests download input data
#define DMATRIG_ENC_UP            30 // AES encryption processor requests upload output data

#define SRCINC_0                0x00 // Increment source pointer by 0 bytes/words after each transfer
#define SRCINC_1                0x01 // Increment source pointer by 1 bytes/words after each transfer
#define SRCINC_2                0x02 // Increment source pointer by 2 bytes/words after each transfer
#define SRCINC_M1               0x03 // Decrement source pointer by 1 bytes/words after each transfer

#define DESTINC_0               0x00 // Increment destination pointer by 0 bytes/words after each transfer
#define DESTINC_1               0x01 // Increment destination pointer by 1 bytes/words after each transfer
#define DESTINC_2               0x02 // Increment destination pointer by 2 bytes/words after each transfer
#define DESTINC_M1              0x03 // Decrement destination pointer by 1 bytes/words after each transfer

#define IRQMASK_DISABLE         0x00 // Disable interrupt generation
#define IRQMASK_ENABLE          0x01 // Enable interrupt generation upon DMA channel done

#define M8_USE_8_BITS           0x00 // Use all 8 bits for transfer count
#define M8_USE_7_BITS           0x01 // Use 7 LSB for transfer count

#define PRI_LOW                 0x00 // Low, CPU has priority
#define PRI_GUARANTEED          0x01 // Guaranteed, DMA at least every second try
#define PRI_HIGH                0x02 // High, DMA has priority
#define PRI_ABSOLUTE            0x03 // Highest, DMA has priority. Reserved for DMA port access.


#pragma bitfields=reversed
typedef struct {
   BYTE SRCADDRH;
   BYTE SRCADDRL;
   BYTE DESTADDRH;
   BYTE DESTADDRL;
   BYTE VLEN      : 3;
   BYTE LENH      : 5;
   BYTE LENL      : 8;
   BYTE WORDSIZE  : 1;
   BYTE TMODE     : 2;
   BYTE TRIG      : 5;
   BYTE SRCINC    : 2;
   BYTE DESTINC   : 2;
   BYTE IRQMASK   : 1;
   BYTE M8        : 1;
   BYTE PRIORITY  : 2;
} DMA_DESC;
#pragma bitfields=default


#define DMA_SET_ADDR_DESC0(a)           \
   do{                                  \
      DMA0CFGH = HIBYTE( a );           \
      DMA0CFGL = LOBYTE( a );           \
   } while(0)

#define DMA_SET_ADDR_DESC1234(a)        \
   do{                                  \
      DMA1CFGH = HIBYTE( a );           \
      DMA1CFGL = LOBYTE( a );           \
   } while(0)

#if(chip == 1110 || chip == 1111 || chip == 2510 || chip == 2511)
#define DMA_ARM_CHANNEL(ch)           \
   do{                                \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      DMAARM = ((0x01 << ch) & 0x1F); \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
      asm("NOP");                     \
   } while(0)
#endif

#define DMA_ABORT_CHANNEL(ch)    DMAARM = (0x80 | ( BM( ch ) & 0x1F) )
#define DMA_MAN_TRIGGER(ch)      DMAREQ = BM( ch )
#define DMA_START_CHANNEL(ch)    DMA_MAN_TRIGGER( ch )

// Macro for quickly setting the destination address of a DMA structure
#define SET_DMA_DEST(pDmaDesc, dest)                  \
   do{                                                \
      pDmaDesc->DESTADDRH = HIBYTE( dest );           \
      pDmaDesc->DESTADDRL = LOBYTE( dest );           \
   } while (0)

// Macro for quickly setting the source address of a DMA structure
#define SET_DMA_SOURCE(pDmaDesc, source)              \
   do{                                                \
      pDmaDesc->SRCADDRH =  HIBYTE( source );         \
      pDmaDesc->SRCADDRL =  LOBYTE( source );         \
   } while (0)

// Macro for quickly setting the number of bytes to be transferred by the DMA.
// Max lenght is 0x1FFF
#define SET_DMA_LENGTH(pDmaDesc, length)              \
   do{                                                \
      pDmaDesc->LENH = HIBYTE( length );              \
      pDmaDesc->LENL = LOBYTE( length );              \
   } while (0)

// Macro for getting the destination address of a DMA channel
#define GET_DMA_DEST(pDmaDesc)   \
   ( (WORD)pDmaDesc->DESTADDRL | ( (WORD)pDmaDesc->DESTADDRH << 8 ))

// Macro for getting the source address of a DMA channel
#define GET_DMA_SOURCE(pDmaDesc) \
   ( (WORD)pDmaDesc->SRCADDRL  | ( (WORD)pDmaDesc->SRCADDRH << 8 ))


/******************************************************************************
*******************         Common USART functions/macros   *******************
*******************************************************************************

The macros in this section are available for both SPI and UART operation.

******************************************************************************/

// Example usage:
//   USART0_FLUSH();
#define USART_FLUSH(num)              (U##num##UCR |= 0x80)
#define USART0_FLUSH()                USART_FLUSH(0)
#define USART1_FLUSH()                USART_FLUSH(1)

// Example usage:
//   if (USART0_BUSY())
//     ...
#define USART_BUSY(num)               (U##num##CSR & 0x01)
#define USART0_BUSY()                 USART_BUSY(0)
#define USART1_BUSY()                 USART_BUSY(1)

// Example usage:
//   while(!USART1_BYTE_RECEIVED())
//     ...
#define USART_BYTE_RECEIVED(num)      (U##num##CSR & 0x04)
#define USART0_BYTE_RECEIVED()        USART_BYTE_RECEIVED(0)
#define USART1_BYTE_RECEIVED()        USART_BYTE_RECEIVED(1)

// Example usage:
//   if(USART1_BYTE_TRANSMITTED())
//     ...
#define USART_BYTE_TRANSMITTED(num)   (U##num##CSR & 0x02)
#define USART0_BYTE_TRANSMITTED()     USART_BYTE_TRANSMITTED(0)
#define USART1_BYTE_TRANSMITTED()     USART_BYTE_TRANSMITTED(1)

// Example usage:
//   CLR_USART0_TX_STATUS();
//     ...
#define CLR_USART_TX_STATUS(num)    U##num##CSR &= ~0x02
#define CLR_USART0_TX_STATUS()      CLR_USART_TX_STATUS(0)
#define CLR_USART1_TX_STATUS()      CLR_USART_TX_STATUS(1)


/******************************************************************************
*******************  USART-UART specific functions/macros   *******************
******************************************************************************/

#if (chip == 1110 || chip == 2510)
#define BAUD_E(baud, clkDivPow)( \
   (baud ==   2400) ?   6 +clkDivPow : \
   (baud ==   4800) ?   7 +clkDivPow : \
   (baud ==   9600) ?   8 +clkDivPow : \
   (baud ==  14400) ?   9 +clkDivPow : \
   (baud ==  19200) ?   9 +clkDivPow : \
   (baud ==  28800) ?  10 +clkDivPow : \
   (baud ==  38400) ?  10 +clkDivPow : \
   (baud ==  57600) ?  11 +clkDivPow : \
   (baud ==  76800) ?  11 +clkDivPow : \
   (baud == 115200) ?  12 +clkDivPow : \
   (baud == 230400) ?  13 +clkDivPow : \
   (baud == 307200) ?  13 +clkDivPow : \
   (baud == 460800) ?  14 +clkDivPow : \
   0)

#define BAUD_M(baud) ( \
   (baud ==   2400) ?  131 : \
   (baud ==   4800) ?  131 : \
   (baud ==   9600) ?  131 : \
   (baud ==  14400) ?   34 : \
   (baud ==  19200) ?  131 : \
   (baud ==  28800) ?   34 : \
   (baud ==  38400) ?  131 : \
   (baud ==  57600) ?   34 : \
   (baud ==  76800) ?  131 : \
   (baud == 115200) ?   34 : \
   (baud == 230400) ?   34 : \
   (baud == 307200) ?  131 : \
   (baud == 460800) ?   34 : \
   0)
#endif

#if (chip == 1111 || chip == 2511)
#define BAUD_E(baud, clkDivPow)( \
   (baud ==   2400) ?   6 +clkDivPow : \
   (baud ==   4800) ?   7 +clkDivPow : \
   (baud ==   9600) ?   8 +clkDivPow : \
   (baud ==  14400) ?   9 +clkDivPow : \
   (baud ==  19200) ?   9 +clkDivPow : \
   (baud ==  28800) ?  10 +clkDivPow : \
   (baud ==  38400) ?  10 +clkDivPow : \
   (baud ==  57600) ?  11 +clkDivPow : \
   (baud ==  76800) ?  11 +clkDivPow : \
   (baud == 115200) ?  12 +clkDivPow : \
   (baud == 230400) ?  13 +clkDivPow : \
   (baud == 307200) ?  13 +clkDivPow : \
   (baud == 460800) ?  14 +clkDivPow : \
   0)

#define BAUD_M(baud) ( \
   (baud ==   2400) ?  163 : \
   (baud ==   4800) ?  163 : \
   (baud ==   9600) ?  163 : \
   (baud ==  14400) ?   59 : \
   (baud ==  19200) ?  163 : \
   (baud ==  28800) ?   59 : \
   (baud ==  38400) ?  163 : \
   (baud ==  57600) ?   59 : \
   (baud ==  76800) ?  163 : \
   (baud == 115200) ?   59 : \
   (baud == 230400) ?   59 : \
   (baud == 307200) ?  163 : \
   (baud == 460800) ?   59 : \
   0)
#endif

// Macro for setting up a UART transfer channel. The macro sets the appropriate
// pins for peripheral operation, sets the baudrate, and the desired options of
// the selected uart. _uart_ indicates which uart to configure and must be
// either 0 or 1. _baudRate_ must be one of 2400, 4800, 9600, 14400, 19200,
// 28800, 38400, 57600, 76800, 115200, 153600, 230400 or 307200. Possible
// options are defined below.
//
// Example usage:
//
//      UART_SETUP(0,115200,HIGH_STOP);
//
// This configures uart 0 for contact with "hyperTerminal", setting:
//      Baudrate:           115200
//      Data bits:          8
//      Parity:             None
//      Stop bits:          1
//      Flow control:       None
//

#define UART_SETUP(uart, baudRate, options)      \
   do {                                          \
      if ((options) & FLOW_CONTROL_ENABLE){      \
         if((uart) == 0){      /* USART0       */\
            if(PERCFG & 0x01){ /* Alt 2        */\
               P1SEL |= 0x3C;                    \
            } else {           /* Alt 1        */\
               P0SEL |= 0x3C;                    \
            }                                    \
         }                                       \
         else {                /* USART1       */\
            if(PERCFG & 0x02){ /* Alt 2        */\
               P1SEL |= 0xF0;                    \
            } else {           /* Alt 1        */\
               P0SEL |= 0x3C;                    \
            }                                    \
         }                                       \
      }                                          \
      else{                    /* Flow Ctrl Dis*/\
         if((uart) == 0){      /* USART0       */\
            if(PERCFG & 0x01){ /* Alt 2        */\
               P1SEL |= 0x30;                    \
            } else {           /* Alt 1        */\
               P0SEL |= 0x0C;                    \
            }                                    \
         }                                       \
         else {                /* USART1       */\
            if(PERCFG & 0x02){ /* Alt 2        */\
               P1SEL |= 0xC0;                    \
            } else {           /* Alt 1        */\
               P0SEL |= 0x30;                    \
            }                                    \
         }                                       \
      }                                          \
                                                 \
      U##uart##GCR = BAUD_E((baudRate), CLKSPD); \
      U##uart##BAUD = BAUD_M(baudRate);          \
                                                 \
      U##uart##CSR |= 0x80;                      \
                                                 \
      U##uart##UCR |= ((options) | 0x80);        \
                                                 \
      if((options) & TRANSFER_MSB_FIRST){        \
         U##uart##GCR |= 0x20;                   \
      }                                          \
   } while(0)


// Options for UART_SETUP macro
#define FLOW_CONTROL_ENABLE         0x40
#define FLOW_CONTROL_DISABLE        0x00
#define EVEN_PARITY                 0x20
#define ODD_PARITY                  0x00
#define NINE_BIT_TRANSFER           0x10
#define EIGHT_BIT_TRANSFER          0x00
#define PARITY_ENABLE               0x08
#define PARITY_DISABLE              0x00
#define TWO_STOP_BITS               0x04
#define ONE_STOP_BITS               0x00
#define HIGH_STOP                   0x02
#define LOW_STOP                    0x00
#define HIGH_START                  0x01
#define TRANSFER_MSB_FIRST          0x80
#define TRANSFER_MSB_LAST           0x00


// Example usage:
//   if(UART0_PARERR())
//     ...
#define UART_PARERR(num)      (U##num##CSR & 0x08)
#define UART0_PARERR()        UART_PARERR(0)
#define UART1_PARERR()        UART_PARERR(1)

// Example usage:
//   if(UART1_FRAMEERR())
//     ...
#define UART_FRAMEERR(num)    (U ##num## CSR & 0x10)
#define UART0_FRAMEERR()      UART_FRAMEERR(0)
#define UART1_FRAMEERR()      UART_FRAMEERR(1)


// Example usage:
//   char ch = 'A';
//   UART1_SEND(ch);
//   ...
//   UART1_RECEIVE(ch);
#define UART_SEND(num, x)     U##num##DBUF = x
#define UART0_SEND(x)         UART_SEND(0, x)
#define UART1_SEND(x)         UART_SEND(1, x)

#define UART_RECEIVE(num, x)  x = U##num##DBUF
#define UART0_RECEIVE(x)      UART_RECEIVE(0, x)
#define UART1_RECEIVE(x)      UART_RECEIVE(1, x)



/******************************************************************************
*******************    USART-SPI specific functions/macros  *******************
*******************************************************************************

The macros in this section simplify SPI operation.

******************************************************************************/

// Macro for setting up an SPI connection. The macro configures the appropriate
// pins for peripheral operation, sets the baudrate if the chip is configured
// to be SPI master, and sets the desired clock polarity and phase. Whether to
// transfer MSB or LSB first is also determined. _spi_ indicates whether
// to use spi 0 or 1. _baudRate_ must be one of 2400, 4800, 9600, 14400, 19200,
// 28800, 38400, 57600, 76800, 115200, 153600, 230400 or 307200.
// Possible options are defined below.

#define SPI_SETUP(spi, baudRate, options)           \
   do {                                             \
      U##spi##UCR = 0x80;                           \
      U##spi##CSR = 0x00;                           \
                                                    \
      if((options) & SPI_SLAVE){  /* Slave        */\
         if(spi == 0){            /* USART0       */\
            if(PERCFG & 0x01){    /* Alt 2        */\
               P1SEL |= 0x3C;                       \
            } else {              /* Alt 1        */\
               P0SEL |= 0x3C;                       \
            }                                       \
         } else {                 /* USART1       */\
            if(PERCFG & 0x02){    /* Alt 2        */\
               P1SEL |= 0xF0;                       \
            } else {                                \
              P0SEL |= 0x3C;      /* Alt 1        */\
            }                                       \
         }                                          \
         U##spi##CSR = 0x20;                        \
      }                                             \
      else {                      /* Master       */\
         if(spi == 0){            /* USART0       */\
            if(PERCFG & 0x01){    /* Alt 2        */\
                P1SEL |= 0x38;                      \
                P1SEL &= ~0x04;                     \
            } else {              /* Alt 1        */\
               P0SEL |= 0x2C;                       \
               P0SEL &= ~0x10;                      \
            }                                       \
         } else {                 /* USART 1      */\
            if(PERCFG & 0x02){    /* Alt 2        */\
               P1SEL |= 0xE0;                       \
               P1SEL &= ~0x10;                      \
            } else {              /* Alt 1        */\
               P0SEL |= 0x38;                       \
               P0SEL &= ~0x04;                      \
            }                                       \
         }                                          \
         U##spi##GCR = BAUD_E(baudRate, CLKSPD);    \
         U##spi##BAUD = BAUD_M(baudRate);           \
      }                                             \
      U##spi##GCR |= ((options) & 0xE0);            \
   } while(0)


// Options for the SPI_SETUP macro.
#define SPI_SLAVE              0x01
#define SPI_MASTER             0x00
#define SPI_CLOCK_POL_LO       0x00
#define SPI_CLOCK_POL_HI       0x80
#define SPI_CLOCK_PHA_0        0x00
#define SPI_CLOCK_PHA_1        0x40
#define SPI_TRANSFER_MSB_FIRST 0x20
#define SPI_TRANSFER_MSB_LAST  0x00



/******************************************************************************
*******************         Common I2S macros   *******************************
*******************************************************************************

The macros in this section are available for I2S operation.

******************************************************************************/

// Definitions for the I2SCFG0 register:
#define I2SCFG0_TXIEN_ENABLE    (0x01<<7)
#define I2SCFG0_TXIEN_DISABLE   (0x00<<7)
#define I2SCFG0_RXIEN_ENABLE    (0x01<<6)
#define I2SCFG0_RXIEN_DISABLE   (0x00<<6)
#define I2SCFG0_ULAWE_XENABLE   (0x01<<5)
#define I2SCFG0_ULAWE_XDISABLE  (0x00<<5)
#define I2SCFG0_ULAWC_CENABLE   (0x01<<4)
#define I2SCFG0_ULAWC_CDISABLE  (0x00<<4)
#define I2SCFG0_TXMONO_MONO     (0x01<<3)
#define I2SCFG0_TXMONO_STEREO   (0x00<<3)
#define I2SCFG0_RXMONO_MONO     (0x01<<2)
#define I2SCFG0_RXMONO_STEREO   (0x00<<2)
#define I2SCFG0_MASTER_MASTER   (0x01<<1)
#define I2SCFG0_MASTER_SLAVE    (0x00<<1)
#define I2SCFG0_ENAB_ENABLE     (0x01<<0)
#define I2SCFG0_ENAB_DISABLE    (0x00<<0)


// I2S_MODE_SETUP(wordLength, mode)
// Example usage:
// I2S_MODE_SETUP(16, I2SCFG0_TXIEN_DISABLE | I2SCFG0_RXIEN_DISABLE | I2SCFG0_ULAWE_XDISABLE | I2SCFG0_ULAWC_CDISABLE | I2SCFG0_TXMONO_MONO | I2SCFG0_RXMONO_MONO | I2SCFG0_MASTER_MASTER | I2SCFG0_ENAB_ENABLE);
#define I2S_MODE_SETUP(wordLength, mode)                                       \
   do {                                                                        \
      /* Word length: WORDS[4:0] */                                            \
      I2SCFG1 = (I2SCFG1&~0xF8) | (unsigned char)(((wordLength-1)&0x1F)<<3);   \
      /* Set I2S mode; stereo/mono, master/slave, etc. */                      \
      I2SCFG0 = mode;                                                          \
   } while (0)

// I2S_CLK_SETUP(i2sDenom, i2sNum)
// Example usage:
// I2S_CLK_SETUP(1625, 16)
#define I2S_CLK_SETUP(i2sNum, i2sDenom)                                        \
   do {                                                                        \
      /* Set DENOM[7:0] */                                                     \
      I2SCLKF0 = (unsigned char)(i2sDenom&0x00FF);                             \
      /* Set DENOM[8] */                                                       \
      I2SCLKF2 = (I2SCLKF2&~0x80) | (unsigned char)((i2sDenom>>1)&0x80);       \
      /* Set NUM[7:0] */                                                       \
      I2SCLKF1 = (unsigned char)(i2sNum&0x00FF);                               \
      /* NUM[14:8] */                                                          \
      I2SCLKF2 = (I2SCLKF2&~0x7F) | (unsigned char)((i2sNum>>8)&0x00FF);       \
   } while(0)

// Macros for I2S clock setup:
// (assuming 26 MHz system clock frequency, and 8 bit I2S word length)
#define I2S_FCLK_26_MHZ_FS_8_KHZ_W8_BIT()         I2S_CLK_SETUP(1625, 16)
#define I2S_FCLK_26_MHZ_FS_11_025_KHZ_W8_BIT()    I2S_CLK_SETUP(32500, 441)
#define I2S_FCLK_26_MHZ_FS_12_KHZ_W8_BIT()        I2S_CLK_SETUP(1625, 24)
#define I2S_FCLK_26_MHZ_FS_16_KHZ_W8_BIT()        I2S_CLK_SETUP(1625, 32)
#define I2S_FCLK_26_MHZ_FS_22_050_KHZ_W8_BIT()    I2S_CLK_SETUP(16250, 441)
#define I2S_FCLK_26_MHZ_FS_24_KHZ_W8_BIT()        I2S_CLK_SETUP(1625, 48)
#define I2S_FCLK_26_MHZ_FS_32_KHZ_W8_BIT()        I2S_CLK_SETUP(1625, 64)
#define I2S_FCLK_26_MHZ_FS_44_1_KHZ_W8_BIT()      I2S_CLK_SETUP(8125, 441)
#define I2S_FCLK_26_MHZ_FS_48_KHZ_W8_BIT()        I2S_CLK_SETUP(1625, 96)

// Macros for I2S clock setup:
// (assuming 26 MHz system clock frequency, and 16 bit I2S word length)
#define I2S_FCLK_26_MHZ_FS_8_KHZ_W16_BIT()        I2S_CLK_SETUP(1625, 32)
#define I2S_FCLK_26_MHZ_FS_11_025_KHZ_W16_BIT()   I2S_CLK_SETUP(16250, 441)
#define I2S_FCLK_26_MHZ_FS_12_KHZ_W16_BIT()       I2S_CLK_SETUP(1625, 48)
#define I2S_FCLK_26_MHZ_FS_16_KHZ_W16_BIT()       I2S_CLK_SETUP(1625, 64)
#define I2S_FCLK_26_MHZ_FS_22_050_KHZ_W16_BIT()   I2S_CLK_SETUP(8125, 441)
#define I2S_FCLK_26_MHZ_FS_24_KHZ_W16_BIT()       I2S_CLK_SETUP(1625, 96)
#define I2S_FCLK_26_MHZ_FS_32_KHZ_W16_BIT()       I2S_CLK_SETUP(1625, 128)
#define I2S_FCLK_26_MHZ_FS_44_1_KHZ_W16_BIT()     I2S_CLK_SETUP(2607, 283)
#define I2S_FCLK_26_MHZ_FS_48_KHZ_W16_BIT()       I2S_CLK_SETUP(1625, 192)

#define I2S_ENABLE() I2SCFG0 |= 0x01;


/******************************************************************************
*******************      Power and clock management        ********************
*******************************************************************************

These macros are used to set power-mode, clock source and clock speed.

******************************************************************************/

// Macro for getting the clock division factor
#if (chip == 2510 || chip == 2511 || chip == 1110 || chip == 1111)
#define CLKSPD  (CLKCON & 0x07)
#endif

// Macro for getting the timer tick division factor
#define TICKSPD ((CLKCON & 0x38) >> 3)

// Macro for checking status of the crystal oscillator
#define XOSC_STABLE (SLEEP & 0x40)

// Macro for checking status of the high frequency RC oscillator.
#define HIGH_FREQUENCY_RC_OSC_STABLE    (SLEEP & 0x20)

// Macro for setting power mode
#define SET_POWER_MODE(mode)    \
   do {                         \
      SLEEP &= ~0x03;           \
      SLEEP |= mode;            \
      PCON |= 0x01;             \
   }while (0)

// Where _mode_ is one of
#define POWER_MODE_0  0x00  // Clock oscillators on, voltage regulator on
#define POWER_MODE_1  0x01  // 32.768 KHz oscillator on, voltage regulator on
#define POWER_MODE_2  0x02  // 32.768 KHz oscillator on, voltage regulator off
#define POWER_MODE_3  0x03  // All clock oscillators off, voltage regulator off

// Macro for setting the 32 kHz clock source
// Please not that this macro only can be run when the device run on the RC osc
#define SET_32KHZ_CLOCK_SOURCE(source) \
   do {                                \
      if( source ) {                   \
         CLKCON |= 0x80;               \
      } else {                         \
         CLKCON &= ~0x80;              \
      }                                \
   } while (0)

// Where _source_ is one of
#define CRYSTAL 0x00
#define RC      0x01

// Macro for setting the main clock oscillator source,
// turns off the clock source not used. Settings TICKSPD
// equal CLKSPD

#if (chip == 1110 || chip == 1111 || chip == 2510 || chip == 2511)
#define SET_MAIN_CLOCK_SOURCE( source )       \
  do {                                        \
    if(source) {                              \
      CLKCON |= 0x40;                         \
      while(!HIGH_FREQUENCY_RC_OSC_STABLE);   \
      SLEEP |= 0x04;                    \
    }                                         \
    else {                                    \
      SLEEP &= ~0x04;                   \
      while(!XOSC_STABLE);                    \
      asm("NOP");                             \
      CLKCON &= ~0x40;               	\
      SLEEP |= 0x04;                    \
    }                                         \
  }while(0)
#endif


#if (chip == 1110 || chip == 2510)
// Macro for setting the main clock division,
#define SET_MAIN_CLOCK_SPEED(frequency)   \
   do {                                   \
        CLKCON = ((CLKCON & ~0x07) | (frequency & 0x07));     \
   }while (0)

// where frequency is one of
#define MHZ_26          0x00
#define MHZ_13          0x01
#define MHZ_6_5         0x02
#define MHZ_3_25        0x03
#define MHZ_1_62        0x04
#define MHZ_0_81        0x05
#define MHZ_0_40        0x06
#define MHZ_0_20        0x07
#endif

#if (chip == 1111 || chip == 2511)
// Macro for setting the main clock division,
#define SET_MAIN_CLOCK_SPEED(frequency)   \
   do {                                   \
        CLKCON = ((CLKCON & ~0x07) | (frequency & 0x07));     \
   }while (0)

// where frequency is one of
#define MHZ_24          0x00
#define MHZ_12          0x01
#define MHZ_6           0x02
#define MHZ_3           0x03
#define MHZ_1_5         0x04
#define MHZ_0_75        0x05
#define MHZ_0_37        0x06
#define MHZ_0_19        0x07
#endif

/******************************************************************************
*******************           Timer macros/functions        *******************
*******************************************************************************
General:
The timers/counters can be configured in a number of ways. The following
functions allow basic configuration of the timers as interrupt timers,
pulse width modulators (PWM) and capture timers. Other uses require manual
configuration of the timers/counters.

Generally 3 steps are nescessary to start a timer:

   TIMERx_INIT();
   BOOL halSetTimerxPeriod(period);
   TIMERx_RUN(TRUE);

where x is the timer number. Please see the function / macro in question for
details.

All timers can generate interrupts. The configuration of interrupts is not
included in the HAL.

******************************************************************************/

#define CLR_TIMER34_IF( bitMask )\
  TIMIF = ( TIMIF & 0x40 ) | ( 0x3F & (~bitMask) )

#define CLR_TIMER1_IF( bitMask )\
  T1CTL = ( T1CTL & 0x0F ) | ( 0xF0 & (~bitMask) )

/******************************************************************************
* @fn  halSetTimer1Period
*
* @brief
*      This function sets up timer 1 to run with a given period. If _period_ is
*      set to 0, maximum period length will be used. The first time the timer
*      is used the macro TIMER1_INIT() should be run to clear all settings. The
*      timer is started and stopped with the macro TIMER1_RUN(TRUE / FALSE).
*
* Parameters:
*
* @param  DWORD	 period
*         The desired timer period in u-seconds.
*
* @return WORD
*         The timer value written to the register if the configuration was
*         successful and 0 if the period could not be achieved. This return
*         value can be used for determining pulse widths when the timer is
*         used in PWM mode.
*
******************************************************************************/
WORD halSetTimer1Period(DWORD period);


// Macro for initialising timer 1. Resets all involved registers and disables
// all interrupt masks
#define TIMER1_INIT()   \
   do {                 \
      T1CTL  = 0x00;    \
      T1CCTL0 = 0x00;   \
      T1CCTL1 = 0x00;   \
      T1CCTL2 = 0x00;   \
      TIMIF = ~0x40;    \
   } while (0)

// Macro for configuring a channel of timer 1 for PWM. Channel may be
// either 1 or 2
#define TIMER1_PWM_CONFIG(channel)                    \
   do {                                               \
      T1CCTL##channel## = 0x24;                       \
      if(PERCFG&0x40) {                               \
         if(channel == 0x01){                         \
            IO_FUNC_PORT_PIN(1,1,IO_FUNC_PERIPH);     \
         }                                            \
         else {                                       \
            IO_FUNC_PORT_PIN(1,0,IO_FUNC_PERIPH);     \
         }                                            \
      }                                               \
      else {                                          \
         if(channel == 0x01){                         \
            IO_FUNC_PORT_PIN(0,3,IO_FUNC_PERIPH);     \
         }                                            \
         else {                                       \
            IO_FUNC_PORT_PIN(0,4,IO_FUNC_PERIPH);     \
         }                                            \
      }                                               \
   } while(0)

// Macro for changing the pulse length of a timer in PWM mode. The value is
// not scaled and the user must verify that it is correct. _channel_ is the
// channel (1 or 2) configured for PWM operation, whereas _value_ is the
// 16 bit word giving the pulse length. This argument should be shorter than
// or equal to the value returned from the function halSetTimer1Period(...).
#define TIMER1_SET_PWM_PULSE_LENGTH(channel, value)   \
   do {                                               \
      T1CC##channel##L = LOBYTE( value );             \
      T1CC##channel##H = HIBYTE( value );             \
   } while(0)


// Macro for configuring a channel of timer 1 for capture.
#define TIMER1_CAPTURE_CHANNEL(channel, edge)         \
   do {                                               \
      T1CCTL ##channel = edge;                        \
      if(PERCFG&0x40) {                               \
         if(channel == 0x01){                         \
            IO_FUNC_PORT_PIN(1,1,IO_FUNC_PERIPH);     \
         }                                            \
         else {                                       \
            IO_FUNC_PORT_PIN(1,0,IO_FUNC_PERIPH);     \
         }                                            \
      }                                               \
      else {                                          \
         if(channel == 0x01){                         \
            IO_FUNC_PORT_PIN(0,3,IO_FUNC_PERIPH);     \
         }                                            \
         else {                                       \
            IO_FUNC_PORT_PIN(0,4,IO_FUNC_PERIPH);     \
         }                                            \
      }                                               \
   } while(0)

// Where _edge_ is either
#define POS_EDGE 0x01  // Capture when a positive edge on the channel input is detected
#define NEG_EDGE 0x02  // Capture when a negative edge on the channel input is detected
#define ANY_EDGE 0x03  // Capture when either a positive or a negative edge on the
                       // channel input is detected.

// Macro for enabling or disabling overflow interrupts of timer 1.
#define TIMER1_ENABLE_OVERFLOW_INT(val) \
   (TIMIF =  (val) ? TIMIF | 0x40 : TIMIF & ~0x40)


#if (chip == 2430 || chip == 2431)
/******************************************************************************
* @fn  halSetTimer2Period
*
* @brief
*      This function sets the period and overflow counter value of the MAC timer
*      (timer 2). The timer can be set up with 320 u-second periods according to
*      IEEE 802.15.4 or as a normal counter with 1 m-second period by using the
*      option TIMER2_MAC_TIMER or TIMER2_NORMAL_TIMER respectively. The value of
*      _period_ gives the number of periods (320 u-seconds or 1 m-seconds) to
*      generate a compare event. The timer is set up to compensate for any clock
*      division. The timer is also set up to be synchronised with the 32.768 KHz
*      clock when entering or leaving power mode 0. When starting synchronously
*      from power mode 1 or 2, the timer value is updated by adding the time
*      passed since PM 0 was left. This time is kept by the 32.768 KHz clock.
*      This way the time is kept as if the chip had been in power mode 0 the
*      whole time. The timer must be started with the macro
*      TIMER2_RUN(TRUE) or MAC_TIMER_RUN(TRUE). The macro TIMER2_INIT() should be
*      run in advance to reset all register values.
*
* Parameters:
*
* @param  BYTE	 mode
*         Determines which time period Timer 2 is to use. The period of Timer 2
*         is either 320 u-seconds (TIMER2_MAC_TIMER) or 1 m-second
*         (TIMER2_NORMAL_TIMER).
* @param  DWORD	 period
*         This value indicates how many periods (320 u-second or 1 m-second) to
*         pass before an overflow compare event is generated.
*
* @return BOOL
          Returns 0 if period is too large, 1 otherwise.
*
******************************************************************************/
BOOL halSetTimer2Period(BYTE mode, DWORD period);

// _mode_ may be of the following:
#define TIMER2_MAC_TIMER    0x01  // Counts 320 u-second periods
#define TIMER2_NORMAL_TIMER 0x02  // Uses the timer as a normal timer with 1 m-second period.

// Macro for initialising timer 2
#define TIMER2_INIT()  \
   do {                \
      T2THD = 0x00;    \
      T2TLD = 0x00;    \
      T2CMP = 0x00;    \
      T2OF0 = 0x00;    \
      T2OF1 = 0x00;    \
      T2OF2 = 0x00;    \
      T2CAPHPH = 0x00; \
      T2CAPLPL = 0x00; \
      T2PEROF0 = 0x00; \
      T2PEROF1 = 0x00; \
      T2PEROF2 = 0x00; \
      T2CNF = 0x06;    \
   } while (0)

#define TIMER2_ENABLE_OVERFLOW_COMP_INT(val) (T2PEROF2 =  (val) ? T2PEROF2 | 0x20 : T2PEROF2 & ~0x20)
#endif


#if (chip == 1110 || chip == 1111 || chip == 2510 || chip == 2511)
/******************************************************************************
* @fn  halSetTimer2Period
*
* @brief
*      This function sets the period timer 2. The values for the counter,
*      prescaler and tick period is calculated and written to the corresponding
*      registers.
*
* Parameters:
*
* @param  UINT32 period
*         Period of the timer in u-seconds.
* @param  UINT8* cnt
*         The value written to T2CT (counter). This value is returned to enable
*         a fast setup (without calculation) using the SET_TIMER2_COUNTER.
* @param  UINT8* presc
*         The value written to T2PR (prescaler). This value is returned to enable
*         a fast setup (without calculation) using the SET_TIMER2_PRESCALER.
*
* @return BOOL
          Returns FALSE if period is too large, TRUE otherwise.
*
******************************************************************************/
BOOL halSetTimer2Period(UINT32 period, UINT8* cnt, UINT8* presc);

#define TIMER2_INIT()  \
   do {                \
      T2CTL = 0x00;    \
      T2CT = 0x00;     \
      T2PR = 0x00;     \
   } while (0)

#define TIMER2_SET_COUNTER(counter)     do{ T2CT = counter; }while(0)
#define TIMER2_SET_PRESCALER(prescaler) do{ T2PR = prescaler; }while(0)
#define TIMER2_SET_TICK_PERIOD(tick)    do{ T2CTL = ((T2CTL & ~0x03) | tick); }while(0)
#define TIMER2_ENABLE_INTERRUPT()       do{ T2CTL |= 0x10; }while(0)
#define TIMER2_DISABLE_INTERRUPT()      do{ T2CTL &= ~0x10; }while(0)
#define TIMER2_CLEAR_EXPIRED()          do{ T2CTL &= ~0x40; }while(0)
#define TIMER2_EXPIRED                  (T2CTL & 0x40)
#define TIMER2_SET_MODE(mode)           (T2CTL  = (mode) ? T2CTL|0x04  : T2CTL&~0x04)

#define TIMER2_USE_REG  FALSE
#define TIMER2_FREE     TRUE

#endif
/******************************************************************************
* @fn  halSetTimer34Period
*
* @brief
*      This function sets the period of timer 3 or 4 according to the value of
*      _timer_. The two timers are identical. Clock division is used to fit the
*      desired period within the timer range. If the period is too short or too
*      long the function returns 0. If the period is successfully set, the
*      function returns the BYTE value written to the timer register. This
*      value can be used to set the pulse length if the timer is used for PWM.
*      If _period_ is set to 0, maximum timeout value will be used.
*
* Parameters:
*
* @param  BYTE	 timer
*         Indicates which timer to configure. Must be either 3 or 4
*         (0x03 or 0x04).
* @param  DWORD	 period - Describe value.
*         The desired period in microseconds.
*
* @return BYTE
*         The value written to the TxCC0 register. The timer is incremented up
*         to this value before the timer is reset. This value may be used to
*         set the pulse length in PWM mode.
*
******************************************************************************/
BYTE halSetTimer34Period(BYTE timer, DWORD period);

// Macro for initialising timer 3 or 4
#define TIMER34_INIT(timer)   \
   do {                       \
      T##timer##CTL   = 0x06; \
      T##timer##CCTL0 = 0x00; \
      T##timer##CC0   = 0x00; \
      T##timer##CCTL1 = 0x00; \
      T##timer##CC1   = 0x00; \
   } while (0)

// Macro for enabling overflow interrupt
#define TIMER34_ENABLE_OVERFLOW_INT(timer, val)   \
   (T##timer##CTL =  (val) ? T##timer##CTL | 0x08 : T##timer##CTL & ~0x08)


// Macro for configuring channel 1 of timer 3 or 4 for PWM mode.
#define TIMER34_PWM_CONFIG(timer)                 \
   do{                                            \
      T##timer##CCTL1 = 0x24;                     \
      if(timer == 3){                             \
         if(PERCFG & 0x20) {                      \
            IO_FUNC_PORT_PIN(1,7,IO_FUNC_PERIPH); \
         }                                        \
         else {                                   \
            IO_FUNC_PORT_PIN(1,4,IO_FUNC_PERIPH); \
         }                                        \
      }                                           \
      else {                                      \
         if(PERCFG & 0x10) {                      \
             IO_FUNC_PORT_PIN(2,3,IO_FUNC_PERIPH);\
         }                                        \
         else {                                   \
            IO_FUNC_PORT_PIN(1,1,IO_FUNC_PERIPH); \
         }                                        \
      }                                           \
   } while(0)

// Macro for setting pulse length of the timer in PWM mode
#define TIMER34_SET_PWM_PULSE_LENGTH(timer, value) \
   do {                                            \
      T##timer##CC1 = (BYTE)value;                 \
   } while (0)


// Macros for turning timers on or off
#define TIMER1_RUN(value)      (T1CTL = (value) ? T1CTL | 0x02 : T1CTL & ~0x03)
#define TIMER3_RUN(value)      (T3CTL = (value) ? T3CTL | 0x10 : T3CTL & ~0x10)
#define TIMER4_RUN(value)      (T4CTL = (value) ? T4CTL | 0x10 : T4CTL & ~0x10)

// Macro for enabling/ disabling interrupts from the channels of timer 1, 3 or 4.
#define TIMER_CHANNEL_INTERRUPT_ENABLE(timer, channel, value) \
   do{                                                        \
      if(value){                                              \
         T##timer##CCTL##channel## |= 0x40;                   \
      } else {                                                \
         T##timer##CCTL##channel## &= ~0x40;                  \
      }                                                       \
   } while(0)

#if (chip == 1110 || chip == 1111 || chip == 2510 || chip == 2511)
// Sleep Timer / Wake On Radio (WOR) Timer

// Macro for initialising the sleep timer / WOR timer.
#define SLEEP_TIMER_INIT()                                    \
   do{                                                        \
      WOREVT1 = 0x87;                                         \
      WOREVT0 = 0x6B;                                         \
      WORCTRL = 0x74;                                          \
      WORIRQ = 0x00;                                          \
   } while(0)

// Macros for enabling / disabling interrupt for event 0 and 1.
#define SLEEP_TIMER_ENABLE_EVENT0_INT(val) do{ WORIRQ = (val) ? WORIRQ | 0x10 : WORIRQ & ~0x10; }while(0)
#define SLEEP_TIMER_ENABLE_EVENT1_INT(val) do{ WORIRQ = (val) ? WORIRQ | 0x20 : WORIRQ & ~0x20; }while(0)

// Macro for resetting the Sleep / WOR timer
#define SLEEP_TIMER_RESET()      WORCTRL |= 0x04

#endif

#endif  // HAL_CC2510_H

/***********************************************************************************
  Copyright 2010 Texas Instruments Incorporated. All rights reserved.

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
  PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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



