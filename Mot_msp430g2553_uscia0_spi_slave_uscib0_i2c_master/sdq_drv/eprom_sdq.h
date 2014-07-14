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
--- MODULE   : eprom_sdq.h
--- VERSION  : 1.10
---===========================================================================---
--- Environment : Device     : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#ifndef EPROM_SDQ_H
#define EPROM_SDQ_H

//#include "spi_il.h"

//***** Definitions *****
typedef struct
{
   u08   Cmd;
   u08   ReadDATA[8];
}Eprom_Cmd_t;

typedef enum
{
	WRITE_DATA,
	WRITE_EXTDATA,
	REQUEST_DATA,
	REQUEST_EXTDATA,
	REPORT_DATA
}Msg_Cmd_State_T;

typedef struct
{
   u08   Cmd;
   u08   LowDataByte;
   u08   HighDataByte;
}Msg_Cmd_t;

//typedef union
//{
//  Msg_Cmd_t  Msg_Cmd;
//  u08  byte[3];
//} Safety_Mon_t;


//***** Exported Variables *****
extern Boolean         Eprom_DataRxInd;
extern Msg_Cmd_State_T Eprom_Cmds;
extern u08             Eprom_MsgLength;
extern Eprom_Cmd_t     EpromCmd;

//***** Exported Functions *****
extern void SPI_EPROM_RequestData_Msg(u08);
extern void SPI_ExtEPROM_RequestData_Msg(u08);
extern void SPI_EPROM_ReportData_Msg(u08);

extern void Eprom_Task(void);
extern u16 ReadEprom_Data(u16 );

extern void battery_read_rom();
extern void battery_read_eeprom();

#endif

/*-===========================================================================--
--- Version Information
--- 1.00 (10/31/2012) - Initial Release
--- 1.10 (03/26/2013) - Implemented the function ReadEprom_Data.
---
---=========================================================================---*/
