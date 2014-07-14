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
--- MODULE   : spi_com.c
--- VERSION  : 1.00
---===========================================================================---
--- Environment : Device      : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#include "msp430g2553.h"
#include "spi_com.h"
#include "i2c_msg.h"
#include "uscia0_spi_drv.h"
#include "app_status.h"
#include "stdtypes.h"
#include "uscib0_i2c_drv.h"
#include "eprom_sdq.h"

//***** Definitions *****

//***** Function Prototypes *****


//***** Global Data *****
SPI_Rx_State_T SPI_MsgStateMachine = RX_INIT;
Boolean        SPI_to_I2C_WriteInd = FALSE;
Boolean        SPI_to_I2C_ReadInd = FALSE;
u08            Rx_Num_Bytes;
u08			   Tx_True = 0;
u08     	   byte_counter = 0;
u08			   call_i2c;

u08 Rx_Buffer[128] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
u08 Tx_Buffer[128] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


/***********************************************************
  Function: SPI_Rx_Msg_ISR
*/
void SPI_Rx_Msg_ISR(u08 rx_byte)
{
//  static volatile u08 byte_counter;

   switch(SPI_MsgStateMachine)
   {
     case RX_INIT:
    	 byte_counter = 0;
    	 Rx_Num_Bytes = 0;
    	 Tx_True = 0;
    	 SPI_Tx_Byte_Counter = 0;

     case RX_CMD_BYTE:
    	 Rx_Buffer[byte_counter] = rx_byte;
    	 byte_counter++;

    	 //check for CMD Write to Read
    	 if ((rx_byte == 0x00) || (rx_byte==0x01))		//rx_byte == 0x00
    	 {
    		 SPI_MsgStateMachine = RX_NUM_BYTES;
    	 }

    	 else if (rx_byte == 0x06) {				//reading data from MCU buffer
    	     SPI_MsgStateMachine = TX_BYTES;
    	     Tx_True = 1;
    	     SPI_Tx_Byte_Counter = 0;
    	 }

    	 else if (rx_byte == 0x20) {				//reading serial number from battery command
    		 SPI_MsgStateMachine = ONE_WIRE;
    	 }

    	 else if (rx_byte == 0x21) {				//reading FG status
    	     SPI_MsgStateMachine = FG_STATUS;
    	 }

    	 else if (rx_byte == 0x31) {				//reading ADC data from battery buffer
//    	     SPI_MsgStateMachine = ADC_READ;
        	 ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
        	 while (!(ADC10CTL0 && ADC10IFG));		//wait for conversion to be complete
        	 Rx_Buffer[1]=0x02;						//load rx buffer with size for tx later
        	 _delay_cycles(250);
        	 Tx_Buffer[0] = (ADC10MEM >> 8);		//right shift for 10bit
        	 Tx_Buffer[1] = ADC10MEM;
        	 ADC10CTL0 &= ~ADC10IFG;
        	 SPI_MsgStateMachine = RX_INIT;			//back to start to receive read command 0x06
    	 }


    	 else if (rx_byte == 0x40)		// Read Firmware Version
    	 {
    		 SPI_MsgStateMachine = TX_BYTES;
        	 Rx_Buffer[1]=0x02;
        	 Tx_True = 1;

   			 SPI_Tx_Byte_Counter = 0;

        	 Tx_Buffer[0] = App_SW_Header.swVER[0];
        	 Tx_Buffer[1] = App_SW_Header.swVER[1];
    	 }

    	 else SPI_MsgStateMachine = RX_INIT;			//in case of bad command******* insert error routine to discard all until CS toggles

    	 break;

     case ONE_WIRE:
    	 Rx_Buffer[byte_counter++] = rx_byte;
    	 if (byte_counter==3) {
//    		 Rx_Buffer[byte_counter++] = rx_byte;
    		 if (Rx_Buffer[2]==0x04) {
    			 Rx_Buffer[1]=8;
    			 battery_read_rom();
    		 }
    		 else if (Rx_Buffer[2]==0x02)
    		 {
    			 Rx_Buffer[1]=128;
    			 battery_read_eeprom();
    		 }
    	 }
    	 break;

     case FG_STATUS:
         Rx_Buffer[byte_counter++] = rx_byte;
         if (byte_counter==2 && Rx_Buffer[1]==0x04) {
         	Tx_True = 1;
//       	Tx_Buffer[0] = 0x55;					//test code for monitoring
         	Tx_Buffer[0] = fg_status;				//load Tx_Buffer with status of FG
         	SPI_MsgStateMachine = TX_BYTES;
         	SPI_Tx_Byte_Counter = 0;
         	Rx_Buffer[1]=0x01;
         }
         break;

//     case ADC_READ:
//    	 ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
//    	 while (!(ADC10CTL0 && ADC10IFG));		//wait for conversion to be complete
//    	 Rx_Buffer[1]=0x02;						//load rx buffer with size for tx later
//    	 Tx_Buffer[0] = (ADC10MEM >> 8);		//right shift for 10bit
//    	 Tx_Buffer[1] = ADC10MEM;
//    	 SPI_MsgStateMachine = RX_INIT;			//back to start to receive read command 0x06
//    	 break;

     case RX_NUM_BYTES:
    	 if (rx_byte > 128) rx_byte = 128;		//do not exceed buffer allocation of 128
    	 Rx_Buffer[byte_counter] = rx_byte;
    	 byte_counter++;

    	 SPI_MsgStateMachine = RX_SLAVE_ADDRS;

    	 break;

     case RX_SLAVE_ADDRS:
    	 Rx_Buffer[byte_counter] = rx_byte;
    	 locSlaveAddr = (rx_byte>>1);
    	 byte_counter++;

    	 // Check if Slave Address W/R
    	 if ( (rx_byte & 0x01) == 0x01 )		//read command
    	 {
//          Rx_Num_Bytes = Rx_Buffer[1] + byte_counter;
    		SPI_MsgStateMachine = RX_INIT;
    		SPI_to_I2C_ReadInd = TRUE;
//    		SPI_to_I2C_Task();
    		call_i2c = 1;					//variable to call i2c task from main loop instead of from ISR
    	 }

    	 else
    	 {
        	SPI_MsgStateMachine = RX_BYTES;
            Rx_Num_Bytes = Rx_Buffer[1] + byte_counter;
    		SPI_to_I2C_WriteInd = TRUE;
    	 }

    	 break;

     case RX_BYTES:
    	 Rx_Buffer[byte_counter] = rx_byte;
         byte_counter++;

         if ( byte_counter >= Rx_Num_Bytes )
         {
//       	SPI_to_I2C_Task();
        	SPI_MsgStateMachine = RX_INIT;	//reset state machine
        	byte_counter = 0;				//reset byte received counter
        	call_i2c = 1;					//variable to call i2c task from main loop instead of from ISR
         }
         break;

     case TX_BYTES:
//    	 while (!(IFG2 & UCA0TXIFG));
//    	 UCA0TXBUF = (Tx_Buffer[1]);
//    	 USCIA0_SPI_Tx(Tx_Buffer[byte_counter-1]);
//    	 byte_counter++;
    	 break;

     default:
    	 SPI_MsgStateMachine = RX_INIT;
       break;
   }
}

/***********************************************************
  Function: SPI_to_I2C_Task
*/
void SPI_to_I2C_Task(void)
{
   if (SPI_to_I2C_WriteInd)
   {
	   SPI_to_I2C_WriteInd = FALSE;

//	   I2C_Write_Cmd();				//removed because this was an extra step
	   USCIB0_I2C_TX_MultiByte((Rx_Buffer + 3), Rx_Buffer[1]);			//(rx_buffer + 3) = rx_buffer[3] = first data byte to Tx to slave
	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	   	//rx_buffer[1] = number of bytes to Tx
   }
   else if (SPI_to_I2C_ReadInd)
   {
	   SPI_to_I2C_ReadInd = FALSE;

	   I2C_Read_Cmd();
   }
}


/*-===========================================================================--
--- Version Information
--- 1.00 (01/25/2013) - Initial Release
---
---=========================================================================---*/
