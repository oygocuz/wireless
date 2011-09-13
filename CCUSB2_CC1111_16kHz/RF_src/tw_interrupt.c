/*******************************************************************************************************
 * tw_interrupt.c           Interrupt Service Routines                                                 *
 * Compiler:                IAR C Compiler for 8051                                                    *
 * Target platform:         Texas Instruments CC1111/CC2511                                            *
 * Author:                  MJB                                                                        *
 * Last Update:             02 June 2009                                                               *
 ******************************************************************************************************/

//-------------------------------------------------------------------------------------------------------
// Includes

#include "twoway.h"

//-------------------------------------------------------------------------------------------------------

//  Global variables

/// Local variables

BOOL __xdata audioFrameReady = FALSE;
BOOL sfdDetected;

///////////////////////////////////////////////////////////////////////////////
/// @brief	This ISR handles the possible RF interrupts that may occur
///             when using the SPP
///
/// When the start of a packet is received, the RX-state will be set
/// accordingly. When a packet is sent and no ACK is requested, the TX_DONE
/// interrupt will be run. Reception of a complete packet will only be used
/// for receiving an ACK. This ISR will handle the ACK reception.
////////////////////////////////////////////////////////////////////////////////

#pragma vector=RF_VECTOR
__interrupt void spp_rf_IRQ(void)
{
  BYTE enabledAndActiveInterrupt;

  INT_GLOBAL_ENABLE(INT_OFF);         // Disable all other interrupts
  INT_SETFLAG(INUM_RF, INT_CLR);      // Clear main (MCU) interrupt flag
  enabledAndActiveInterrupt = RFIF;
  enabledAndActiveInterrupt &= RFIM;  // Mask local copy of interrupt flags
  RFIF = ~enabledAndActiveInterrupt;  // Clear all interrupt flags in RFIF register

// Start of frame delimiter (TX) or SYNC detected (RX)

  if(enabledAndActiveInterrupt & IRQ_SFD)
  {
    sfdDetected = TRUE;
    rxStatus = RX_IN_PROGRESS;
    rxPacketStatus = 0x00;
    RFIM &= ~IRQ_SFD;                 // Clear interrupt mask for SFD in RFIM
  }

// Packet Done (TX) or Packet Received (RX)

  if(enabledAndActiveInterrupt & IRQ_DONE)
  {
    rxStatus = PACKET_RECEIVED;
    RFIM &= ~IRQ_DONE;                // Clear interrupt mask for DONE in RFIM
  }

  INT_GLOBAL_ENABLE(INT_ON);
}

// Timer 1 interrupt handler
// Timer 1 will generate an interrupt ever 250 milliseconds

#pragma vector=T1_VECTOR
__interrupt void T1_IRQ(void){

  P1 ^= 0x02;     // toggle the LED
 
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


