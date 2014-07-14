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
--- MODULE   : stdtypes.h
--- VERSION  : 1.00
---===========================================================================---
--- Environment : Device     : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#ifndef _STDTYPES_H
#define _STDTYPES_H

//***** Definitions *****



#define TRUE    1
#define FALSE   0

typedef unsigned char  u08;
typedef unsigned short u16;
typedef unsigned long  u32;

typedef signed char  s08;
typedef signed short s16;
typedef signed long  s32;

typedef void ( *function_ptr_T )         ( void );
typedef void ( *function_ptr_u08_T )     ( u08 );

typedef unsigned char Boolean;

typedef union
{
  u32  dword;
  u08  byte[4];
} Long_T;

typedef union
{
  u16  word;
  u08  byte[2];
} Word_T;

#ifndef NULL
#define NULL ((void *) 0)
#endif

#endif

/*-===========================================================================--
--- Version Information
--- 1.00 (01/25/2013) - Initial Release
---
---=========================================================================---*/
