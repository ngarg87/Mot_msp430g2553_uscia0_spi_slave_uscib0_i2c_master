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
--- MODULE   : msp430_sdqlib.h
--- VERSION  : 1.50
---===========================================================================---
--- Environment : Device     : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#ifndef MSP430_SDQLIB_H
#define MSP430_SDQLIB_H

#include "stdtypes.h"
#include "msp430g2553.h"

#define P1_SDQ BIT0                         // P1.0 used for the SDQ interface

#define SDQ_INPUT  (P1DIR&=~P1_SDQ)
#define SDQ_OUTPUT (P1DIR|=P1_SDQ)
#define SDQ_HIGH   (P1OUT|=P1_SDQ)
#define SDQ_LOW    (P1OUT&=~P1_SDQ)
#define SDQ_TOGGLE (P1OUT^=P1_SDQ)
#define SDQ_READ   (P1IN&P1_SDQ)

//------------------------------------------------------------------------------
// Define the SMCLK frequency
//------------------------------------------------------------------------------
#define SMCLKFREQHZ 16000000u                    // Timer clock frequency (Hz)
//------------------------------------------------------------------------------
// Define HDQ Protocol Related Timing Constants
//------------------------------------------------------------------------------
#define tUSEC       (1 * SMCLKFREQHZ / 1000000) // 1 usec worth of Timer_A tics
//------------------------------------------------------------------------------
// Exported functions (only for use with C)
//------------------------------------------------------------------------------
#ifdef __STDC__
extern void  SDQ_Init(void);
extern void  SDQ_delayUSEC(u16 value);
extern void  SDQ_reset(void);
extern u08   SDQ_detect(void);
extern u08   SDQ_readBit(void);
extern u08   SDQ_readByte(void);
extern void  Timer_A0_ISR (void);
#endif
//------------------------------------------------------------------------------

#endif /* MSP430_SDQLIB_H */

/*-===========================================================================--
--- Version Information
--- 1.00 (08/31/2012) - Initial Release
--- 1.10 (10/25/2012) - Updated the I/O SDQ macros with the P2.1
--- 1.20 (11/06/2012) - Renamed SDQ_init to SDQ_Init
--- 1.30 (11/08/2012) - Removed SDQ_readByte_no_delay and SDQ_readByte_1
--- 1.40 (11/26/2012) - Updated GPIO SDQ macros to use with PACE HW (P1.0)
--- 1.50 (01/30/2013) - Added Boot Loader support. Relocated interrupt vectors
---                     to app_vect.c
---
---=========================================================================---*/
