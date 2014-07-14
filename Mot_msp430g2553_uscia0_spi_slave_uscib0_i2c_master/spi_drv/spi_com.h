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
--- MODULE   : spi_com.h
--- VERSION  : 1.00
---===========================================================================---
--- Environment : Device      : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#ifndef SPI_COM_H
#define SPI_COM_H

#include "stdtypes.h"

//***** Definitions *****
 typedef enum
 {
  RX_INIT,
  RX_CMD_BYTE,
  ONE_WIRE,
  FG_STATUS,
//  ADC_READ,
  RX_NUM_BYTES,
  RX_SLAVE_ADDRS,
  RX_BYTES,
  TX_BYTES
 } SPI_Rx_State_T;


//#define P2_SYNC_SIGNAL     (BIT7)                         // P2.7 is used for sync with the Master
//#define SYNC_SIGNAL_INPUT  (P2DIR&=~P2_SYNC_SIGNAL)
//#define SYNC_SIGNAL_OUTPUT (P2DIR|=P2_SYNC_SIGNAL)
//#define SYNC_SIGNAL_HIGH   (P2OUT|=P2_SYNC_SIGNAL)
//#define SYNC_SIGNAL_LOW    (P2OUT&=~P2_SYNC_SIGNAL)
//#define SYNC_SIGNAL_TOGGLE (P2OUT^=P2_SYNC_SIGNAL)
//#define SYNC_SIGNAL_READ   (P2IN&P2_SYNC_SIGNAL)


//***** Exported Variables *****
extern SPI_Rx_State_T SPI_MsgStateMachine;
extern u08 Rx_Buffer[128];
extern u08 Tx_Buffer[128];
extern u08 Tx_True;
extern u08 byte_counter;
extern u08 call_i2c;

//***** Exported Functions *****
extern void SPI_to_I2C_Task(void);
extern void SPI_Rx_Msg_ISR(u08);

#endif

/*-===========================================================================--
--- Version Information
--- 1.00 (01/25/2013) - Initial Release
---
---=========================================================================---*/
