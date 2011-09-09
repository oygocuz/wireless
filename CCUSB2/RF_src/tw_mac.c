/*******************************************************************************************************
 *                                                                                                     *
 *        **********                                                                                   *
 *       ************                                                                                  *
 *      ***        ***                                                                                 *
 *      ***   +++   ***                                                                                *
 *      ***   + +   ***     Medium Access Control layer                                                *
 *      ***   +                                                                                        *
 *      ***   + +   ***                                                                                *
 *      ***   +++   ***     rs_mac.c                                                                   *
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
// Global variables

#include "twoway.h"

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


