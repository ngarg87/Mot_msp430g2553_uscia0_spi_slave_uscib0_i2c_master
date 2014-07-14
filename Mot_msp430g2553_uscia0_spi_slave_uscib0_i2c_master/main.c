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
--- MODULE   : main.c
--- VERSION  : 1.00
---===========================================================================---
--- Environment : Device     : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#include "msp430g2553.h"
#include "uscia0_spi_drv.h"
#include "uscib0_i2c_drv.h"
#include "msp430_sdqlib.h"
#include "os.h"
#include "os_tasks.h"
#include "spi_com.h"
#include "stdtypes.h"

//***** Definitions *****

//***** Function Prototypes *****
void Clock_Init(void);   
void RTOS_Timer_Init(void);

//***** Global Data *****


/***********************************************************
  Function: main
*/
void main(void)
{
	__disable_interrupt();

    WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

    /* Clock initialization - 16 MHz */
    Clock_Init();

//	/* SYNC Signal LOW */
//	SYNC_SIGNAL_LOW;
//	SYNC_SIGNAL_OUTPUT;

//	/* 10ms RTOS Tick */
//	RTOS_Timer_Init();
	//enabled ADC
	ADC10CTL0 = SREF_1 + ADC10SHT_1 + REFON + REF2_5V + ADC10ON;	//use internal reference of 2.5V
	ADC10CTL1 = INCH_3;                       // input A3

    /* Initialize SPI Low Layer */
    USCIA0_SPI_Init();

    /* Init I2C Low Layer */
    USCIB0_I2C_Init();

    /* Initialize SDQ Low Layer */
    SDQ_Init();

    __enable_interrupt();

	// Set Os Table
//	Os_Set_Current_Task_Table(&Os_Table);

	// Run RTOS
//	RTOS ();
    while(1)
    {
    	if (call_i2c)
    	{
    		SPI_to_I2C_Task();
    		call_i2c=0;
    	}
    }
}
/***********************************************************
  Function: Clock_Init
*/
void Clock_Init(void)
{
	if (CALBC1_16MHZ ==0xFF || CALDCO_16MHZ == 0xFF)
	{
		while(1); // If cal constants erased, trap CPU!!
	}

	BCSCTL1 = CALBC1_16MHZ; // Set range
	DCOCTL = CALDCO_16MHZ; // Set DCO step + modulation
	BCSCTL3 |= LFXT1S_2;
}

/***********************************************************
  Function: RTOS_Timer_Init (10 ms Tick)
 */
void RTOS_Timer_Init(void)
{
	/* Timer A1 for OS */
	TA1CTL = ID_3 | TASSEL_2 | MC_1;           // 16MHz / 8 = 2MHz, TACLK = SMCLK, Up mode.
	TA1CCR0 = 0x4E20;                          // 10ms
	TA1CCTL0 = CCIE;
}

// Timer 1 A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR (void)
{
    Increment_System_Clock();
}

/*-===========================================================================--
--- Version Information
--- 1.00 (01/25/2013) - Initial Release
---
---=========================================================================---*/
