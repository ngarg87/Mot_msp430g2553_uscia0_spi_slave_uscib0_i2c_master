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
--- MODULE   : os.c
--- VERSION  : 1.00
---===========================================================================---
--- Environment : Device      : MSP430G2553
---   Compiler/Assembler/IDE : CCS V5.2
---=========================================================================---*/
#include "stdtypes.h"
#include "os_tasks.h"
#include "os.h"

// Global Variables
u16 Os_Clock = 0;
u16 Prev_Os_Clock = 0;
Os_Task_Table_Type *curr_task_list = (Os_Task_Table_Type *)&Os_Table;

// Types

// Constants

// Prototype Declarations

// Local Function Declarations
//****************************************************************************
// Name: RTOS
// Details: 
//****************************************************************************
void RTOS (void)
{
   u08  task_count;
   u16 index;
   u16 mask_result;
   Os_Task_Type *task_ptr;
   Os_Task_Type *task_table;

   while(1)
   {
      task_count = curr_task_list->num_of_tasks;

      task_table = curr_task_list->Os_task;

      for (index = 0; index < task_count; index++)
	  {
         task_ptr = &task_table[index];
	     mask_result = Prev_Os_Clock & task_ptr->rate;

	     if (mask_result == task_ptr->offset)
		 {
		    (*task_ptr->action)();
		 }
      }

      Background();
      Prev_Os_Clock++;
   }
}
//****************************************************************************
// Name: Os_Set_Current_Task_Table
// Details: 
//****************************************************************************
void Os_Set_Current_Task_Table(Os_Task_Table_Type *new_task_list)
{
   Os_Task_List_Type *table = &Os_Task_Ptrs;

   do
   {
      if (table->task_ptr == new_task_list)
      {
         curr_task_list = new_task_list;
         break;
      }
      table = table->task_next;
   } while (table != NULL);
}

/*-===========================================================================--
--- Version Information
--- 1.00 (01/25/2013) - Initial Release
---
---=========================================================================---*/
