/*******************************************************************************************************
 *                                                                                                     *
 *        **********                                                                                   *
 *       ************                                                                                  *
 *      ***        ***                                                                                 *
 *      ***   +++   ***                                                                                *
 *      ***   + +   ***     Functions for transfering stored audio samples to the Delta-Sigma          *
 *      ***   +             Modulator/Pulse Width Modulator output                                     *
 *      ***   + +   ***                                                                                *
 *      ***   +++   ***     rs_dsm.c                                                                   *
 *      ***        ***                                                                                 *
 *       ************                                                                                  *
 *        **********                                                                                   *
 *                                                                                                     *
 *******************************************************************************************************
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Chipcon CC2510                                                             *
 * Author:                  TBR, KHO, ESY                                                              *
 *******************************************************************************************************
 * Revision history:        See end of file                                                            *
 ******************************************************************************************************/

//-------------------------------------------------------------------------------------------------------
// Includes

#include "twoway.h"


//-------------------------------------------------------------------------------------------------------
// Global variables

UINT16 timerSampleRate;


//-------------------------------------------------------------------------------------------------------
// Function prototypes


// *************************************************************************************************** //
// *************************************************************************************************** //



/// On the SmartRF04EB the pwm audio output filter is connected to pin P1_1 on
/// the CC2510.
/// This requires timer 1 pin mapping to be alt 2 (see Table 36, p62 in data sheet)
/// It also requires using channel 1 of timer 1.
/// For max resolution, max counting speed should be used in timer1 =>
///   Clock source = XOSC 26 MHz
///   CLKCON.TICKSPD = 0



////////////////////////////////////////////////////////////////////////////////
/// @brief	This function enables the Delta-Sigma Modulator for 8 kHz operation
///             with 26 MHz clock.
///
/// The DSM is described in the CC2510/CC2511 data sheet, section 13.3.11
/// on page 101-102 (rev 1.02):
///
/// 1. Suspend timer 1 (T1CTL:MODE = 0)
/// 2. Clear timer counter by writing any value to T1CNTL. (T1CNT = 0x0000)
/// 3. Set the sample rate by writing the Timer 1 channel 0 count period, T1CC0.
///    (From Table 43 in data sheet: T1CC0 = 0x0CB1 for 8 kHz @ 26 MHz)
/// 4. Set Timer 1 channel 0 compare mode (T1CCTL0.MODE = 1)
/// 5. Load first sample if available (or zero if no sample available) into T1CC1H:T1CC1L
/// 6. Enable timer counter to modulo mode (T1CTL.MODE = 2)
/// 7. Configure the DSM by setting the MODE and CAP fields of the T1CCTL1 register
/// 8. Enable DSM mode (T1CCTL1.CMP = 7)
///
/// On each Timer 1 IRQ or Timer 1 DMA trigger, write a new sample to the T1CC1H:T1CC1L
/// registers. The least significant bits must be written to T1CC1L before the most
/// significant bits are written to T1CC1H.
///
/// The samples written mustbe signed 2's complement values. The 2 least significant
/// bits will always be treated as 0, thus the effective sample size is 14 bits.
////////////////////////////////////////////////////////////////////////////////

void initDsm(void) {

  // Set Port 1 bit 1 to peripheral (timer 1) function
  P1SEL |= 0x02;
  // Set location for timer 1
  PERCFG |= 0x40;
  // Set pin direction (output) for port 1 bit 1
  P1DIR |= 0x02;

  // Suspend timer 1 (T1CTL:MODE = 0)
  T1CTL &= ~0x03;
  // Clear timer counter by writing any value to T1CNTL. (T1CNT = 0x0000)
  T1CNTL = 0x00;

  // Set the sample rate by writing the Timer 1 channel 0 count period, T1CC0.
  timerSampleRate = NORMAL_SAMPLE_PERIOD;
  T1CC0H = ((timerSampleRate >> 8) & 0xFF);     // 0x0C;
  T1CC0L =  (timerSampleRate      & 0xFF);      // 0xB1;

  // Set Timer 1 channel 0 compare mode (T1CCTL0.MODE = 1)
  T1CCTL0 |= 0x04;
  // Load first sample if available (or zero if no sample available) into T1CC1H:T1CC1L
  T1CC1L = 0;
  T1CC1H = 0;
  // Enable timer counter to modulo mode (T1CTL.MODE = 2)
  T1CTL |= 0x02;
  // Configure the DSM by setting the MODE and CAP fields of the T1CCT1 register
//  T1CCTL1 &= ~0x07;
  T1CCTL1 &= 0xC0;

  // Enable interrupt on timer 1 overflow
  TIMER1_ENABLE_OVERFLOW_INT(TRUE);
  INT_ENABLE(INUM_T1, INT_ON);

#ifdef DISABLEDSM
  T1CCTL1 |= 0x2C;
#else  
  // Enable DSM mode (T1CCTL1.CMP = 7)
//  T1CCTL1 |= 0x38;
   T1CCTL1 |= 0x3A; // interpolator off, shaping on
#endif  
}

