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
--- MODULE   : uscia0_spi_drv.c
--- VERSION  : 1.00
---===========================================================================---
--- Environment : Device      : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#include "msp430g2553.h"
#include "spi_com.h"
#include "i2c_msg.h"
#include "stdtypes.h"
#include "uscib0_i2c_drv.h"

//***** Definitions *****


//***** Function Prototypes *****


//***** Global Data *****
u08 locRxData;
Boolean CS_State = FALSE;

/***********************************************************
  Function: USCIA0_SPI_Init
*/

void USCIA0_SPI_Init(void)
{
  /* Configure CS and SPI 3-pin mode */
  P1DIR &= ~BIT5;
  P1OUT |= BIT5;
  P1REN |= BIT5;
  P1IES |= BIT5;  // Falling edge
  P1IFG &= ~BIT5;
  P1IE |= BIT5;

  // Configure SPI function
  P1SEL |= BIT1 + BIT2 + BIT4;
  P1SEL2 |= BIT1 + BIT2 + BIT4;

  UCA0CTL1 = UCSWRST;                       // **Put state machine in reset**
  UCA0CTL0 |= UCCKPH + UCMSB + UCSYNC;      // 3-pin, 8-bit SPI slave
}

/***********************************************************
  Function: USCIA0_SPI_Tx
*/

//void USCIA0_SPI_Tx(u08 Tx_Byte)
//{
//	while (!(IFG2 & UCA0TXIFG));
////	UCA0TXBUF = Tx_Byte;
//}


/***********************************************************
  Function: USCIA0RX_ISR
*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR (void)
{
	if (CS_State)
	  {
	    locRxData = UCA0RXBUF;
	    SPI_Rx_Msg_ISR(locRxData);
	  }
	else IFG2 &= ~UCB0RXIFG;                     // Clear USCI_B0 RX int flag
}

/***********************************************************
  Function: PORT1_ISR
*/
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
	/* Do not process any SPI message if I2C are being sent */
//	if ( ( (!I2C_ProcessInd) ) || (CS_State) )
//	{
		if (CS_State == TRUE)
		{
			CS_State = FALSE;
			P1IES |= BIT5;  // Falling edge

			if (SPI_MsgStateMachine != RX_INIT)
			{
				SPI_MsgStateMachine = RX_INIT;
			}

			IE2 &= ~(UCA0RXIE + UCA0TXIE);                          // Disable USCI0 RX interrupt
			UCA0CTL1 = UCSWRST;                        // **Put state machine in reset**
		}
		else
		{
			P1IES &= ~BIT5;  // Raising edge
			UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI0 state machine**

			UCA0TXBUF = 0x00;						// pre-load TXBUF to keep timing on-sync

			IE2 |= UCA0RXIE + UCA0TXIE;                          // Enable USCI0 RX interrupt
			CS_State = TRUE;
		}
//	}
	/* Clear P1 Interrupt Flag */
	P1IFG &= ~BIT5;
}

/*-===========================================================================--
--- Version Information
--- 1.00 (01/25/2013) - Initial Release
---
---=========================================================================---*/
