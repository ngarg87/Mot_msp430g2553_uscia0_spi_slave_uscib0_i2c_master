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
--- MODULE   : os_tasks.c
--- VERSION  : 1.00
---===========================================================================---
--- Environment : Device      : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#include "stdtypes.h"
#include "os.h"
#include "os_tasks.h"
#include "spi_com.h"
#include "msp430g2553.h"

// Defines
#define NUM_TASKS_IN_TABLE 8

// Global Variables

// Types

// Prototype Declarations
/*static*/ void task1(void);
/*static*/ void task2(void);
/*static*/ void task3(void);
/*static*/ void task4(void);
/*static*/ void task5(void);
/*static*/ void task6(void);
/*static*/ void task7(void);
/*static*/ void task8(void);

// Constants
Os_Task_Type Os_Task_List[NUM_TASKS_IN_TABLE] =
{  /* rate  offset  action  */
   {    0,     0,   &task1 },       /* highest priority task */	/*  10.0 mS */
   {    0,     0,   &task2 },									/*  10.0 mS */
   {    1,     1,   &task3 },									/*  20.0 mS */
   {    7,     3,   &task4 },									/*  80.0 mS */
   {   15,     7,   &task5 },									/* 160.0 mS */
   {   31,    15,   &task6 },									/* 320.0 mS */
   {   63,    31,   &task7 },									/* 640.0 mS */
   {  127,    63,   &task8 }        /* lowest priority task */	/* 1280.0 mS */
};

Os_Task_Table_Type Os_Table =									
   { &Os_Task_List[0], NUM_TASKS_IN_TABLE };					
																
																
Os_Task_List_Type Os_Task_Ptrs =								
   { &Os_Table, NULL };

// Local Function Declarations
//****************************************************************************
// Name: task1
// Details: 
//****************************************************************************
void task1()  /* 10.0 mS */
{
    /* Service Watchdog */
}

//****************************************************************************
// Name: task2
// Details: 
//****************************************************************************
void task2()  /* 10.0 mS */
{
	/* SPI Message Task */
//	SPI_to_I2C_Task();
}

//****************************************************************************
// Name: task3
// Details: 
//****************************************************************************
void task3()  /* 20.0 mS */
{
}

//****************************************************************************
// Name: task4
// Details: 
//****************************************************************************
void task4()  /* 80.0 mS */
{
}

//****************************************************************************
// Name: task5
// Details:
//****************************************************************************
void task5()  /* 160.0 mS */
{

}

//****************************************************************************
// Name: task6
// Details:
//****************************************************************************
void task6()  /* 320.0 mS */
{
}

//****************************************************************************
// Name: task7
// Details: 
//****************************************************************************
void task7()  /* 640.0 mS */
{
	// Toggle P1.0, TI's LunchPad
//	P1OUT ^= BIT0;
}

//****************************************************************************
// Name: task8
// Details: 
//****************************************************************************
void task8()  /* 1280.0 mS */
{

}

//****************************************************************************
// Name: Background
// Details: 
//****************************************************************************
void Background()
{
   while (System_Clock() == Previous_System_Clock())
   {
   }
}

/*-===========================================================================--
--- Version Information
--- 1.00 (01/25/2013) - Initial Release
---
---=========================================================================---*/
