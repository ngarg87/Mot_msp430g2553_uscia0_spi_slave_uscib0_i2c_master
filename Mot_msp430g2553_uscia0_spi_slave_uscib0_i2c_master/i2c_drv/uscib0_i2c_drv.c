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
--- MODULE   : uscib0_i2c_drv.c
--- VERSION  : 1.00
---===========================================================================---
--- Environment : Device      : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#include "msp430g2553.h"
#include "stdtypes.h"
#include "spi_com.h"
#include "uscia0_spi_drv.h"

u08 USCIB0_I2C_SetSlaveAddress(u08 address);

//***** Definitions *****
//typedef enum
//{
//	OK = 0,
//	ERROR
//}I2C_BusState_T;

//***** Function Prototypes *****


//***** Global Data *****
u08 locSlaveAddr;
u08 fg_status;
u08 TXByteCtr;
u08 RXByteCtr;
u08 *PTxData;
u08 *PRxData;
u08 SPI_Tx_Byte_Counter;
Boolean MultiByteReadFG = FALSE;
Boolean WaitforSTPCondition = FALSE;
//Boolean RPTCondition = FALSE;

/***********************************************************
  Function: USCIB0_I2C_Init
*/
void USCIB0_I2C_Init(void)
{
	P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0

	IE2 &= ~UCB0RXIE;  						  // Disable RX interrupt
	IE2 &= ~UCB0TXIE;  						  // Disable TX interrupt

	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode

	UCB0BR0 = 0xA0;                           // fSCL = SMCLK/160 = ~100kHz
//	UCB0BR0 = 0x28;                           // fSCL = SMCLK/40 = ~400kHz
	UCB0BR1 = 0;

//	SlavePresent = USCIB0_I2C_SetSlaveAddress(0x55);	// Etai added 6-7-13 to see if it solves init issue with RXMultiByte...
}

/***********************************************************
  Function: USCIB0_I2C_TX_Init
*/
void USCIB0_I2C_TX_Init(u08 SlaveAddress)
{
	IE2 &= ~UCB0RXIE;

	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0I2CSA = SlaveAddress;                 // Slave Address
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation

	IE2 |= UCB0TXIE;                          // Enable TX interrupt
}

/***********************************************************
  Function: USCIB0_I2C_RX_Init
*/
void USCIB0_I2C_RX_Init(u08 SlaveAddress)
{
	IE2 &= ~UCB0TXIE;

	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0I2CSA = SlaveAddress;                 // Slave Address
	UCB0CTL1 &= ~(UCTR + UCSWRST);            // Clear SW reset & transmit mode, resume operation

//	UCB0I2CIE |= UCNACKIE;					  // Interrupt on NACK
//	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
//	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset

	IE2 |= UCB0RXIE;                          // Enable RX interrupt
}

/***********************************************************
  Function: USCIB0_I2C_Ready
*/
//I2C_BusState_T USCIB0_I2C_Ready(void)
//{
//  u16 locCounter = 1;
//
//  while ( ( UCB0STAT & UCBBUSY ) && ( locCounter++ ) );
//
//  if (locCounter != 0)
//  {
//	return (OK);
//  }
//  else
//  {
//	return (ERROR);
//  }
//}

/***********************************************************
  Function: USCIB0_I2C_SetSlaveAddress
*/
//u08 USCIB0_I2C_SetSlaveAddress(u08 address)
//{
//	u08 ie2_bak;
//	u08 slaveadr_bak;
//	u08 ucb0i2cie;
//	u08 returnValue;
//	u16 locCounter = 1;
//
//    /* Verify that Slave is present */
//	ucb0i2cie = UCB0I2CIE;                      // store old UCB0I2CIE
//	ie2_bak = IE2;                              // store IE2 register
//	slaveadr_bak = UCB0I2CSA;                   // store old slave address
//
//	UCB0CTL1 |= UCSWRST;                        // Enable SW reset
////	UCB0I2CIE &= ~ UCNACKIE;                    // no NACK interrupt
//	UCB0I2CSA = address;                        // set slave address
//	UCB0CTL1 &= ~UCSWRST;                       // Clear SW reset, resume operation
//
//	IE2 &= ~(UCB0TXIE + UCB0RXIE);              // no RX or TX interrupts
//
//	__disable_interrupt();
//
////	UCB0CTL1 |= UCTR + UCTXSTT + UCTXSTP;       // I2C TX, start condition // REMOVED by Etai - 2-20-12 No need and it creates an address sent with no data before sending the actual Address with data.. no need for double address
//
//	while ( (UCB0CTL1 & UCTXSTP) &&  (locCounter++ ) );             // wait for STOP condition
//
//	if (locCounter)
//	{
//		returnValue = !(UCB0STAT & UCNACKIFG);
//	}
//	else
//	{
//		returnValue = locCounter;
//	}
//
//	UCB0CTL1 |= UCSWRST;                        // Enable SW reset
//	IE2 = ie2_bak;                              // restore IE2
//	UCB0I2CSA = slaveadr_bak;                   // restore old slave address
//	UCB0I2CIE = ucb0i2cie;                      // restore old UCB0CIE
//
//	__enable_interrupt();
//
//	/* Set the new Slave address*/
//	locSlaveAddr = address;
//
//	return returnValue;                         // return whether or not a NACK occurred
//}


/***********************************************************
  Function: USCIB0_I2C_TX_MultiByte
*/
void USCIB0_I2C_TX_MultiByte(u08 *i2cArray, u08 NumBytes)			//(rx_buffer[3], rx_buffer[1])
{
	u32 locCounter = 1;

	WaitforSTPCondition = FALSE;
	fg_status = 0xFF;						//reset fg_status flag

	while (UCB0STAT & UCBBUSY);				//check if i2c line is busy

	USCIB0_I2C_TX_Init(locSlaveAddr);         // re-init i2c with new slave address


	// Wait for bus to be free
	PTxData = i2cArray;                       // TX array start address
	TXByteCtr = NumBytes;                     // Load TX byte counter

	/* start transmitting */
	UCB0CTL1 |= UCTR + UCTXSTT;               // I2C TX, start condition
	while (UCB0CTL1 & UCTXSTT);               // Ensure start condition got sent

	while (!WaitforSTPCondition)  		// Ensure stop condition got sent
	{
		locCounter++;
		if ((UCB0STAT & UCNACKIFG ) != 0)
		{
			Tx_True = 0;
			UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
			while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
			WaitforSTPCondition = TRUE;
			fg_status = 0xFF;
			IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
			UCB0STAT = ~UCNACKIFG;
			if (SPI_MsgStateMachine != RX_INIT) SPI_MsgStateMachine = RX_INIT;
			IE2 &= ~(UCA0RXIE + UCA0TXIE);                          // Disable USCI0 RX interrupt
			UCB0CTL1 |= UCSWRST;                        // **Put state machine in reset**
		}
		else fg_status = 0xF0;
	}
}

/***********************************************************
  Function: USCIB0_I2C_RX_MultiByte
*/
void USCIB0_I2C_RX_MultiByte(u08 *i2cArray, u08 RxNumBytes)
{
	u32 locCounter = 1;

	fg_status = 0xFF;						//reset fg_status flag

	while (UCB0STAT & UCBBUSY);								//wait for i2c bus to be free

	USCIB0_I2C_RX_Init(locSlaveAddr);	               // Initialize I2C read operation

	PRxData = i2cArray;                 // RX array start address
	MultiByteReadFG = TRUE;					  // Multi-byte transaction starting

	RXByteCtr = RxNumBytes - 1;               // Load RX byte counter
	UCB0CTL1 |= UCTXSTT;                      // Send I2C start condition

	// Wait for read operation to complete
	while (MultiByteReadFG) {
		locCounter++;
		if ((UCB0STAT & UCNACKIFG ) != 0)
			{
				Tx_True = 0;
				UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
				while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
				MultiByteReadFG = FALSE;
				fg_status = 0xFF;
				IFG2 &= ~UCB0RXIFG;                     // Clear USCI_B0 RX int flag
				UCB0STAT = ~UCNACKIFG;
				if (SPI_MsgStateMachine != RX_INIT) SPI_MsgStateMachine = RX_INIT;
				IE2 &= ~(UCA0RXIE + UCA0TXIE);                          // Disable USCI0 RX interrupt
				UCB0CTL1 |= UCSWRST;
			}
		else fg_status = 0xF0;					//fg_status = ACK
//		if (locCounter == 30000) MultiByteReadFG = FALSE;
	}
}

/***********************************************************
  Function: USCIB0_I2C_RX_SingleByte
*/
void USCIB0_I2C_RX_SingleByte(u08 *i2cArray)
{
//	I2C_BusState_T locBusState = ERROR;

	// Wait for bus to be free
	while (UCB0STAT & UCBBUSY);								//wait for i2c bus to be free

	USCIB0_I2C_RX_Init(locSlaveAddr);	               // Initialize I2C read operation

	fg_status = 0xFF;						//reset fg_status flag
	PRxData = i2cArray;                 // RX array start address
	MultiByteReadFG = TRUE;					  // Multi-byte transaction starting

	USCIB0_I2C_RX_Init(locSlaveAddr);	    // Initialize I2C read operation

	// Clear Rx Counter
	RXByteCtr = 0;

	UCB0CTL1 |= UCTXSTT;                    // Send I2C start condition
	while (UCB0CTL1 & UCTXSTT);             // Ensure start condition got sent
	UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
	while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent

	if ((UCB0STAT & UCNACKIFG ) != 0)
		{
			Tx_True = 0;
			IFG2 &= ~UCB0RXIFG;                     // Clear USCI_B0 RX int flag
			UCB0STAT = ~UCNACKIFG;
			fg_status = 0xFF;
			if (SPI_MsgStateMachine != RX_INIT) SPI_MsgStateMachine = RX_INIT;
			IE2 &= ~(UCA0RXIE + UCA0TXIE);                          // Disable USCI0 RX interrupt
			UCB0CTL1 |= UCSWRST;
		}
	else fg_status = 0xF0;					//fg_status = ACK
}

/***********************************************************
  Function: USCIB0TX_ISR
*/
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIB0TX_ISR(void)
{
	if (IFG2 & UCB0RXIFG)				// RX - if a receive interrupt (byte received in buffer)
	{
	    if (RXByteCtr)
	    {
			*PRxData = UCB0RXBUF;             // Load RX buffer
			PRxData++;
	        RXByteCtr--;                      // Decrement TX byte counter
	    }
	    else if ((RXByteCtr == 0) && (MultiByteReadFG))                    // Check RX byte counter
		{
			*PRxData = UCB0RXBUF;                   // Load RX buffer
			PRxData++;
			UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
			while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
			MultiByteReadFG = FALSE;				// Multi-byte transaction done
		}
		else
		{
			*PRxData = UCB0RXBUF;                   // Load RX buffer
		}
	}
	else if (IFG2 & UCB0TXIFG)
	{
		if (TXByteCtr)                        // Check TX byte counter
		{
			UCB0TXBUF = *PTxData;                   // Load TX buffer
			PTxData++;
			TXByteCtr--;                            // Decrement TX byte counter
		}
//		else if (RPTCondition)
//		{
//			UCB0TXBUF = 0xFF;                       // Dummy write, it will not go out due to the RPT condition
//			RPTCondition = FALSE;
//		}
		else
		{
			UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
			while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
			WaitforSTPCondition = TRUE;
			IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
		}
	}
	else if (IFG2 & UCA0TXIFG)
//		{
//
//		if (Tx_True == 1 && SPI_Tx_Byte_Counter < (Rx_Buffer[1]+1))
//		{
//			UCA0TXBUF = Tx_Buffer[SPI_Tx_Byte_Counter];
//			Tx_Buffer[SPI_Tx_Byte_Counter++] = 0;
//		}
//
//		else
//		{
//			UCA0TXBUF = 0x00;
//			Tx_True = 0;
//			byte_counter = 0;
//			SPI_Tx_Byte_Counter = 0;
//		}
//	}

		{
			if (Tx_True == 1)
			{
				UCA0TXBUF = Tx_Buffer[SPI_Tx_Byte_Counter];
//				if (Tx_Buffer[SPI_Tx_Byte_Counter]==0xF0) {
//					__no_operation();
//				}
				Tx_Buffer[SPI_Tx_Byte_Counter++] = 0;
			}

			else UCA0TXBUF = 0x00;

			if (SPI_Tx_Byte_Counter == (Rx_Buffer[1]+1))
			{
				Tx_True = 0;
				byte_counter = 0;
				SPI_Tx_Byte_Counter = 0;
			}
		}
}

/*-===========================================================================--
--- Version Information
--- 1.00 (01/25/2013) - Initial Release
---
---=========================================================================---*/
