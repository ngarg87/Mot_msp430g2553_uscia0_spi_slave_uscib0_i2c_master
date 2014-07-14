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
--- MODULE   : i2c_msg.c
--- VERSION  : 1.00
---===========================================================================---
--- Environment : Device     : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#include "msp430g2553.h"
#include "uscib0_i2c_drv.h"
#include "i2c_msg.h"
#include "spi_com.h"
#include "stdtypes.h"

//***** Definitions *****

//***** Function Prototypes *****

//***** Global Data *****
//Boolean I2C_ProcessInd = FALSE;
//u08     Command_Byte = 0x00;

/***********************************************************
//  Function: I2C_Write_Cmd
//*/
//Boolean I2C_Write_Cmd(void)
//{
//	Boolean MessageComplete = FALSE;
//    Boolean SlavePresent = FALSE;
//
//    // Update Slave Address
//	SlavePresent = USCIB0_I2C_SetSlaveAddress((Rx_Buffer[2] >> 1));		//check if slave is present, not necessary?
////	UCB0I2CSA = (Rx_Buffer[2] >> 1);									//set slave address right away
////	locSlaveAddr = Rx_Buffer[2] >> 1;									//global variable for slave addressl; optimize out
//
//	if (SlavePresent)
//	{
//		Command_Byte =  Rx_Buffer[3];
//
//		// Send after the slave address
//		USCIB0_I2C_TX_MultiByte((Rx_Buffer + 3), Rx_Buffer[1]);
//	}
//
//	MessageComplete = TRUE;
//
//	return (MessageComplete);
//}

/***********************************************************
  Function: I2C_Read_Cmd
*/
Boolean I2C_Read_Cmd(void)
{
	Boolean MessageComplete = FALSE;

//	Tx_Buffer[0] = Command_Byte;

	if (Rx_Buffer[1] > 1)									//call for multibyte read from i2c
	{
		USCIB0_I2C_RX_MultiByte(Tx_Buffer, Rx_Buffer[1]);
	}
	else													//else call for single byte read via i2c
	{
		USCIB0_I2C_RX_SingleByte(Tx_Buffer);
	}

	MessageComplete = TRUE;

	return (MessageComplete);
}

/*-===========================================================================--
--- Version Information
--- 1.00 (01/25/2013) - Initial Release
---
---=========================================================================---*/
