/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

/*-===========================================================================--
--- MODULE   : msp430_sdqlib.c
--- VERSION  : 1.60
---===========================================================================---
--- Environment : Device     : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#include "msp430_sdqlib.h"
#include "sdq_writebyte.h"
#include "stdtypes.h"

//******************************************************************************
// void SDQ_Init(void)
//
// Description : Initializes the SDQ module as a whole
// Returns : None
// Resources used : DCO @ 16 MHz, TACCR0
//******************************************************************************
void SDQ_Init(void)
{
  TACTL = (TASSEL_2 | MC_2 | TACLR);        // Use SMCLK, continuous mode
  P1SEL &= ~(P1_SDQ);                       // P1.0 GPIO function
  SDQ_HIGH;                                 // Keep SDQ bus in IDLE state
  SDQ_OUTPUT;                               // P1.0 SDQ output direction
}

//******************************************************************************
// void SDQ_delayUSEC(u16 usec)
//
// Description : Goes to sleep for the specified number of microseconds
// Returns : None			
// Notes : This only works when (usec > 5) AND (usec < 4096)
//         For a delay of 5 usec or less, use one _NOP per usec instead
//******************************************************************************
void SDQ_delayUSEC(u16 usec)
{
  TACCTL0 = CCIE;                           // TACCR0 interrupt enabled
//  _EINT();
  TACCR0 += ((SMCLKFREQHZ/1000000)*usec);
  LPM0;
//  _DINT();
  TACCTL0 &= ~CCIE;                         // TACCR0 interrupt disabled
}

//******************************************************************************
// void SDQ_reset(void)
//
// Description : Creates the Reset signal to initiate SDQ communication
// Arguments : None  										 
// Returns: None
//******************************************************************************
void SDQ_reset(void)
{
  u16 index;

  SDQ_HIGH;
  SDQ_OUTPUT;
  SDQ_LOW;
  for (index = 0; index < ((480/65)+1); index++)    // Reset time should be > 480 usec
  {
    DLYUSEC_65();
  }
  SDQ_HIGH;
}

//******************************************************************************
// u08 SDQ_detect(void)
//
// Description : Detects if a device responds to Reset signal
// Arguments : PresenceTimer - Sets timeout if no device present
//             InputData - Actual state of GPIO
//             GotPulse - States if a pulse was detected								  
// Returns : GotPulse
//******************************************************************************
u08 SDQ_detect(void)
{
  u16 PresenceTimer = 300;
  u08 InputData;
  u08 GotPulse = 0;

  SDQ_INPUT;
  while ( (PresenceTimer > 0) && (GotPulse == 0) )
  {
    InputData = SDQ_READ;                   // Capture state of the SDQ bus
    if (InputData == 0)                     // If SDQ bus got pulled low,
    {                                       // then the device responded
      GotPulse = 1;
    }
    else                                    // If SDQ bus is still high,
    {                                       // then the device did not respond
      GotPulse = 0;
      --PresenceTimer;                      // Decrease timeout counter
    }
  }
//  SDQ_delayUSEC(200);                       // Delay before attempting command
  DLYUSEC_65();                             // Wait for end of read bit cycle
  DLYUSEC_65();                             // Wait for end of read bit cycle
  DLYUSEC_65();                             // Wait for end of read bit cycle
  DLYUSEC_65();                             // Wait for end of read bit cycle
  DLYUSEC_65();                             // Wait for end of read bit cycle
  
  return GotPulse;                          // Return if device detected or not
}

//******************************************************************************
// u08 SDQ_readBit(void)
//
// Description : Receives the bit value returned by the SDQ slave
// Arguments : none
// Returns : State of the SDQ bus (0 or 1)
//******************************************************************************
u08 SDQ_readBit(void)
{
  static u08 InBit;
  u16 index;
	
  SDQ_HIGH;
  SDQ_OUTPUT;
  SDQ_LOW;
  SDQ_INPUT;
  for (index = 0; index < 32 /*12*/; index++)      // The total delay time between SDQ
  {                                         // going LOW and the actual read of
    _NOP();                                 // the SDQ bus should be ~12 usec
  }
  InBit = SDQ_READ;                         // Capture state of the SDQ bus
  //SDQ_delayUSEC(65);                        // Wait for end of read bit cycle
  DLYUSEC_65();                             // Wait for end of read bit cycle
  SDQ_HIGH;
  SDQ_OUTPUT;
  
  if (InBit)
  {
    return 1;                               // Return SDQ HIGH
  }
  else
  {
    return 0;                               // Return SDQ LOW
  }
}

//******************************************************************************
// u08 SDQ_readByte(void)
//
// Description : Reads 8 bits on the SDQ line and returns the byte value.
// Arguments : Databyte - Byte value returned by SDQ slave
//	           MaskByte - Used to seperate each bit
//             index - Used for 8 time loop
// Returns : DataByte
//******************************************************************************
u08 SDQ_readByte(void)
{
  u08 data = 0x00;
  u08 mask;
  u08 index;

  _DINT();

  for (index = 0; index < 8; index++)                   // Select one bit at a time
  {
    mask = SDQ_readBit();		            // Read One Bit
    mask <<= index;                             // Determine bit position in byte
    data = (data | mask);                   // Keep adding bits to form the byte
  }

//  SDQ_delayUSEC(200);                       // Delay before attempting command
  DLYUSEC_65();                             // Wait for end of read bit cycle
  DLYUSEC_65();                             // Wait for end of read bit cycle
  DLYUSEC_65();                             // Wait for end of read bit cycle

  _EINT();

  return (data);                            // Return byte value read
}

// Timer A0 Interrupt Service Routine
void Timer_A0_ISR (void)
{
//  LPM0_EXIT;                                // Exit LPM0 on RETI
}

/*-===========================================================================--
--- Version Information
--- 1.00 (08/31/2012) - Initial Release
--- 1.10 (10/25/2012) - Updated the file with project's standard types
--- 1.20 (11/06/2012) - Renamed SDQ_init to SDQ_Init
---                     Added SDQ_readByte_no_delay and SDQ_readByte_1 for
---                     testing purposes
--- 1.30 (11/08/2012) - Removed SDQ_readByte_no_delay and SDQ_readByte_1
--- 1.40 (11/26/2012) - Updated GPIO SDQ macros to use with PACE HW (P1.5)
--- 1.50 (01/16/2013) - Removed the static volatile attribute to the variables
---                     inside SDQ_detect.
--- 1.60 (01/30/2013) - Added Boot Loader support. Relocated interrupt vectors
---                     to app_vect.c
---
---=========================================================================---*/
