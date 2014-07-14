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
--- MODULE   : eprom_sdq.c
--- VERSION  : 1.40
---===========================================================================---
--- Environment : Device     : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#include "msp430g2553.h"
//#include "spi_il.h"
#include "spi_com.h"
#include "uscia0_spi_drv.h"
#include "sdq_writebyte.h"
#include "msp430_sdqlib.h"
#include "eprom_sdq.h"
#include "stdtypes.h"

//***** Definitions *****

//***** Function Prototypes *****
//Boolean locRequestEprom_Data(void);
void locRequestEprom_Data(void);
void locRequestEprom_ExtData(void);
Boolean Eprom_SDQ_TX_Init(void);
Boolean Eprom_SDQ_TX_Init_SkipCmd(void);
void Eprom_SDQ_TX_MultiByte(u08 *SDQArray, u08 NumBytes);
u08 Calc_CRC(u08 data_byte, u08 crc);

// Boolean locRequestBatteryCharger_Data(void);

//***** Global Data *****
Msg_Cmd_State_T Eprom_Cmds;
u08             Eprom_MsgLength;
Boolean         Eprom_DataRxInd = FALSE;
Eprom_Cmd_t     EpromCmd;
u08             ReadCRC[2] = {0,0};

/***********************************************************
  Function: SPI_EPROM_RequestData_Msg
*/
void SPI_EPROM_RequestData_Msg(u08 MsgLength)
{
	/* Send request to EPROM task */
	Eprom_MsgLength = MsgLength;
	Eprom_DataRxInd = TRUE;
	Eprom_Cmds = REQUEST_DATA;
}

/***********************************************************
  Function: SPI_ExtEPROM_RequestData_Msg
*/
void SPI_ExtEPROM_RequestData_Msg(u08 MsgLength)
{
	/* Send request to EPROM task */
	Eprom_MsgLength = MsgLength;
	Eprom_DataRxInd = TRUE;
	Eprom_Cmds =  REQUEST_EXTDATA;
}

/***********************************************************
  Function: SPI_EPROM_ReportData_Msg
*/
void SPI_EPROM_ReportData_Msg(u08 MsgLength)
{
	u08    index;
	u08    checksum_pos;
	Word_T chksum;

	// Verify that the max read bytes is not greater than the size of EpromCmd
	if (Rx_Buffer[1] > 8)
	{
		Rx_Buffer[1] = 8;
	}

	// Checksum location
	checksum_pos = Rx_Buffer[1] + 1;
	chksum.word  = 0;

	if (Rx_Buffer[0] == EpromCmd.Cmd)
	{
		Tx_Buffer[0] = Rx_Buffer[0];

		for (index = 1; index < checksum_pos; index++)
		{
			Tx_Buffer[index] =  EpromCmd.ReadDATA[(index - 1)];
			chksum.word += Tx_Buffer[index];
		}
	}
	else
	{
		Tx_Buffer[0] = 0x7F;

		/* Command Not Found */
		for (index = 1; index < checksum_pos; index++)
		{
			Tx_Buffer[index] =  0x00;
			chksum.word += Tx_Buffer[index];
		}
	}

	chksum.word             += Tx_Buffer[0];
	chksum.word             = chksum.byte[0] + chksum.byte[1];
	Tx_Buffer[checksum_pos] = chksum.byte[0] + chksum.byte[1];

	// Checksum Calculation
	Tx_Buffer[checksum_pos] = 0xFF - Tx_Buffer[checksum_pos];
}

/***********************************************************
//  Function: Eprom_Task
*/
//void Eprom_Task(void)
//{
//	if ( ( Eprom_DataRxInd ) && (CS_State == FALSE) )
//	{
//		switch(Eprom_Cmds)
//		{
//		   case REQUEST_DATA:
////			   if ( locRequestEprom_Data() )
////			   {
//			   locRequestEprom_Data();
//			   Eprom_DataRxInd = FALSE;
////			   }
//			  break;
//
//		   case REQUEST_EXTDATA:
//			   if ( locRequestEprom_ExtData() )
//			   {
//				   Eprom_DataRxInd = FALSE;
//			   }
//			  break;
//
//		   case REPORT_DATA:
//			  break;
//		}
//	}
//}

/***********************************************************
  Function: locRequestEprom_Data
*/
//Boolean locRequestEprom_Data(void)
void locRequestEprom_Data(void)
{
	Boolean MessageComplete = FALSE;
	u08     index;

//	if (Eprom_SDQ_TX_Init())
//	{
		//reset pulse
		SDQ_reset();

		//detect
		SDQ_detect();

		// Send Command
		SDQ_writeByte(0x33);


//		if (Rx_Buffer[0] == 0x33)
//		{
			// Clear CRC
//			ReadCRC[0] = 0;

			// Rx Data
			for (index = 0; index < 7; index++)
			{
				// Read Byte Status Memory
				Tx_Buffer[index] = SDQ_readByte();

				// Calculate CRC
//				ReadCRC[0] = Calc_CRC(EpromCmd.ReadDATA[index], ReadCRC[0]);
			}
			// Rx CRC
//			ReadCRC[1] = SDQ_readByte();
			Tx_Buffer[index] = SDQ_readByte();
//		}
		//Not Valid Command
//		else
//		{
//			SDQ_reset();
//			EpromCmd.Cmd = 0x7F;
//		}
//	}
//	else
//	{
//		// Force Error
//		ReadCRC[0] = 0xA5;
//	}

//	if (ReadCRC[1] != ReadCRC[0])
//	{
//		// TODO: Re-transmit?? How many times??
//		EpromCmd.Cmd = 0x7F;
//	}
//	else
//	{
//		EpromCmd.Cmd = Rx_Buffer[0];
//	}

	MessageComplete = TRUE;

//	return (MessageComplete);
}

void locRequestEprom_ExtData(void)
{
	Boolean MessageComplete = FALSE;
	u08     index;

//	if (Eprom_SDQ_TX_Init())
//	{
		//reset pulse
		SDQ_reset();

		//detect
		SDQ_detect();

		// Send Command
		SDQ_writeByte(0xCC);
		SDQ_writeByte(0xF0);
		SDQ_writeByte(0x00);
		SDQ_writeByte(0x00);


//		if (Rx_Buffer[0] == 0x33)
//		{
			// Clear CRC
//			ReadCRC[0] = 0;

			// Rx Data
			for (index = 0; index < 128; index++)
			{
				// Read Byte Status Memory
				Tx_Buffer[index] = SDQ_readByte();

				// Calculate CRC
//				ReadCRC[0] = Calc_CRC(EpromCmd.ReadDATA[index], ReadCRC[0]);
			}
			// Rx CRC
//			ReadCRC[1] = SDQ_readByte();
			Tx_Buffer[index] = SDQ_readByte();
//		}
		//Not Valid Command
//		else
//		{
//			SDQ_reset();
//			EpromCmd.Cmd = 0x7F;
//		}
//	}
//	else
//	{
//		// Force Error
//		ReadCRC[0] = 0xA5;
//	}

//	if (ReadCRC[1] != ReadCRC[0])
//	{
//		// TODO: Re-transmit?? How many times??
//		EpromCmd.Cmd = 0x7F;
//	}
//	else
//	{
//		EpromCmd.Cmd = Rx_Buffer[0];
//	}

	MessageComplete = TRUE;

//	return (MessageComplete);
}

///***********************************************************
//  Function: locRequestEprom_ExtData
//*/
//Boolean locRequestEprom_ExtData(void)
//{
//	Boolean MessageComplete = FALSE;
//	u08     index = 0;
//
//	// Clear CRC
//	ReadCRC[0] = 0;
//
//	if (Eprom_SDQ_TX_Init_SkipCmd())
//	{
//		for ( ; index < 3; index++)
//		{
//			ReadCRC[0] = Calc_CRC(Rx_Buffer[index], ReadCRC[0]);
//		}
//
//		// Send the Cmd
//		Eprom_SDQ_TX_MultiByte(Rx_Buffer, 1);
//
//		// Send the Address
//		Eprom_SDQ_TX_MultiByte((Rx_Buffer+1), 2);
//
//		// Read Address CRC
//		ReadCRC[1] = SDQ_readByte();
//
//		// Read Memory Command
//		if ( (Rx_Buffer[0] == 0xF0) && (ReadCRC[1] == ReadCRC[0]) )
//		{
//			// Confirm max size is not greater than 8
//			if (Rx_Buffer[3] > 8)
//			{
//				Rx_Buffer[3] = 8;
//			}
//
//			for (index = 0 ; index < Rx_Buffer[3]; index++)
//			{
//				// Read Byte Memory
//				EpromCmd.ReadDATA[index] = SDQ_readByte();
//			}
//			// Stop the read
//			SDQ_reset();
//		}
//		// Read Status Command
//		else if ( (Rx_Buffer[0] == 0xAA) && (ReadCRC[1] == ReadCRC[0]) )
//		{
//			// Clear CRC
//			ReadCRC[0] = 0;
//
//			for (index = 0 ; index < 8; index++)
//			{
//				// Read Byte Status Memory
//				EpromCmd.ReadDATA[index] = SDQ_readByte();
//				ReadCRC[0] = Calc_CRC(EpromCmd.ReadDATA[index], ReadCRC[0]);
//			}
//			// Rx CRC
//			ReadCRC[1] = SDQ_readByte();
//		}
//		// Not valid command
//		else
//		{
//			SDQ_reset();
//			EpromCmd.Cmd = 0x7F;
//		}
//	}
//	else
//	{
//		// Force Error
//		ReadCRC[0] = 0xA5;
//	}
//
//	if (ReadCRC[1] != ReadCRC[0])
//	{
//		// TODO: Re-transmit?? How many times??
//		EpromCmd.Cmd = 0x7F;
//	}
//	else
//	{
//		EpromCmd.Cmd = Rx_Buffer[0];
//	}
//
//	MessageComplete = TRUE;
//	return (MessageComplete);
//}

/***********************************************************
  Function: ReadEprom_Data
*/
u16 ReadEprom_Data(u16 address)
{
	Word_T EpromValue;
	u08     index = 0;

	// Clear CRC
	ReadCRC[0] = 0;

	Rx_Buffer[0] = 0xF0;
	Rx_Buffer[1] = (u08)address;
	Rx_Buffer[2] = (u08)(address >> 8);
	Rx_Buffer[3] = 0x02; // Read 2 Bytes

	if (Eprom_SDQ_TX_Init_SkipCmd())
	{
		for ( ; index < 3; index++)
		{
			ReadCRC[0] = Calc_CRC(Rx_Buffer[index], ReadCRC[0]);
		}

		// Send the Cmd
		Eprom_SDQ_TX_MultiByte(Rx_Buffer, 1);

		// Send the Address
		Eprom_SDQ_TX_MultiByte((Rx_Buffer+1), 2);

		// Read Address CRC
		ReadCRC[1] = SDQ_readByte();

		// Read Memory Command
		if ( (Rx_Buffer[0] == 0xF0) && (ReadCRC[1] == ReadCRC[0]) )
		{
			for (index = 0 ; index < Rx_Buffer[3]; index++)
			{
				// Read Byte Memory
				EpromValue.byte[index] = SDQ_readByte();
			}
			// Stop the read
			SDQ_reset();
		}
		else
		{
			SDQ_reset();
		}
	}
	else
	{
		// Force Error
		ReadCRC[0] = 0xA5;
	}

	return (EpromValue.word);
}

/***********************************************************
  Function: Eprom_SDQ_TX_Init
*/
Boolean Eprom_SDQ_TX_Init(void)
{
	Boolean Eprom_detected = FALSE;

	SDQ_reset();
	Eprom_detected = SDQ_detect();

	return (Eprom_detected);
}

/***********************************************************
  Function: Eprom_SDQ_TX_Init_SkipCmd
*/
Boolean Eprom_SDQ_TX_Init_SkipCmd(void)
{
	Boolean Eprom_detected = FALSE;

	SDQ_reset();
	if (SDQ_detect())
	{
		SDQ_writeByte(0xCC); // SKIP ROM cmd
		Eprom_detected = TRUE;
	}

	return (Eprom_detected);
}

/***********************************************************
  Function: Eprom_SDQ_TX_MultiByte
*/
void Eprom_SDQ_TX_MultiByte(u08 *SDQArray, u08 NumBytes)
{
	u08 index;

	for (index = 0; index < NumBytes; index++)
	{
	  SDQ_writeByte(SDQArray[index]);
	}
}

/***********************************************************
  Function: Calc_CRC
*/
u08 Calc_CRC(u08 data_byte, u08 crc)
{
	u08 bit_mask = 0;
	u08 carry_check = 0;
	u08 temp_data = 0;

	temp_data = data_byte;

	for ( bit_mask = 0; bit_mask <= 7; bit_mask ++)
	{
		data_byte = data_byte ^ crc;
		crc = crc / 2;
		temp_data = temp_data / 2;
		carry_check = data_byte & 0x01;
		if (carry_check)
		{
			crc = crc ^ 0x8C;
		}
		data_byte = temp_data;
	}
	return ( crc );
}

void battery_read_rom()
{
	locRequestEprom_Data();
}

void battery_read_eeprom()
{
	locRequestEprom_ExtData();
}


///*-===========================================================================--
//--- Version Information
//--- 1.00 (10/31/2012) - Initial Release
//--- 1.10 (11/08/2012) - Removed the write Eprom functions and enabled the CRC
//---                     calculation, added Calc_CRC
//--- 1.20 (11/26/2012) - Added the force error condition, when Eprom/battery is
//---                     not connected
//--- 1.30 (12/07/2012) - Wait for SPI CS_State before doing and SDQ operations
//--- 1.40 (03/26/2013) - Implemented the function ReadEprom_Data.
//---
//---=========================================================================---*/
