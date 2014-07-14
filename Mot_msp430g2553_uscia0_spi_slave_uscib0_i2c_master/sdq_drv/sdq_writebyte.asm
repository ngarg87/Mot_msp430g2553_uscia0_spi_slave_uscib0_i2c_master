; --COPYRIGHT--,BSD
;  Copyright (c) 2012, Texas Instruments Incorporated
;  All rights reserved.
; 
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
; 
;  *  Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
; 
;  *  Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
; 
;  *  Neither the name of Texas Instruments Incorporated nor the names of
;     its contributors may be used to endorse or promote products derived
;     from this software without specific prior written permission.
; 
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
;  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
;  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
;  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
;  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
;  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
;  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
;  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
;  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
;  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; --/COPYRIGHT--

;-===========================================================================---
;--- MODULE   : sdq_writebyte.asm
;--- VERSION  : 1.10
;---===========================================================================-
;--- Environment : Device     : MSP430G2553
;---   Compiler/Assembler/IDE : CCS V5.2
;---=========================================================================---

; *****************************************************************************
; Assembly routine to transmit 1 whole byte via SDQ protocol
; *****************************************************************************

 .cdecls C,LIST,    "msp430_sdqlib.h"

;-------------------------------------------------------------------------------
            ;RSEG     DATA16_N                   ; Place variables in RAM
            ;EVEN                                ; Ensure it?s on an even boundary
            .align 2
;-------------------------------------------------------------------------------
;DelayTarget DS      2
            .bss DelayTarget, 2
;============================================================================
; DLYUSEC_07A
;
; Registers Used : None
;============================================================================

            ;PUBLIC  DLYUSEC_07A             ; Declare symbol to be exported
            ;RSEG    CODE                    ; Code is relocatable
            .def  DLYUSEC_07A                ; Declare symbol to be exported
            .text                            ; Code is relocatable
        
DLYUSEC_07A;
            push.w  &TAR                    ; Get current Timer_A value
            add.w   #(tUSEC*7),0(SP)        ; (Do calc on TOS)
            pop.w   &DelayTarget            ; Timer_A value to stop delay
DUSEC_07A   cmp     &TAR,&DelayTarget       ; dst >= src ?
            jge     DUSEC_07A               ; Jump if dst >= src
            ret
            
;============================================================================
; DLYUSEC_65A
;
; Registers Used : None
;============================================================================

            ;PUBLIC  DLYUSEC_65A             ; Declare symbol to be exported
            ;RSEG    CODE                    ; Code is relocatable
            .def  DLYUSEC_65A                ; Declare symbol to be exported
            .text                            ; Code is relocatable
        
DLYUSEC_65A;
            push.w  &TAR                    ; Get current Timer_A value
            add.w   #(tUSEC*65),0(SP)       ; (Do calc on TOS)
            pop.w   &DelayTarget            ; Timer_A value to stop delay
DUSEC_65A   cmp     &TAR,&DelayTarget       ; dst >= src ?
            jge     DUSEC_65A               ; Jump if dst >= src
            ret
            
;============================================================================
; DLYUSEC_07 (@ 16 MHz MCLK)
;
; Registers Used : R11 = loop counter
;============================================================================

            ;PUBLIC  DLYUSEC_07             ; Declare symbol to be exported
            ;RSEG    CODE                    ; Code is relocatable
            .def  DLYUSEC_07                 ; Declare symbol to be exported
            .text                            ; Code is relocatable
        
DLYUSEC_07;
            push    R11                     ; Save R11
            mov     #12,R11                  ; Initialize loop counter
;            mov     #6,R11                  ; Initialize loop counter
DS07D       dec     R11
            jeq     DS07E                   ; If counter = 0, we're done
            nop                             ; Do nothing
            jmp     DS07D                   ; Decrement & check counter
DS07E       pop     R11                     ; Restore R11
            ret                             ; Return from subroutine
        
;============================================================================
; DLYUSEC_65 (@ 16 MHz MCLK)
;
; Registers Used : R11 = loop counter
;============================================================================

            ;PUBLIC  DLYUSEC_65              ; Declare symbol to be exported
            ;RSEG    CODE                    ; Code is relocatable
            .def  DLYUSEC_65                 ; Declare symbol to be exported
            .text                            ; Code is relocatable
        
DLYUSEC_65;
            push    R11                     ; Save R11
            mov     #166,R11                 ; Initialize loop counter
;            mov     #83,R11                 ; Initialize loop counter
DS65D       dec     R11
            jeq     DS65E                   ; If counter = 0, we're done
            nop                             ; Do nothing
            jmp     DS65D                   ; Decrement & check counter
DS65E       pop     R11                     ; Restore R11
            ret                             ; Return from subroutine
        
;============================================================================
; SDQ_writeByte
;
; Registers Used : R6  = transmit bit counter
;                  R12 = 8-bit byte to transmit
;                  
;============================================================================

            ;PUBLIC  SDQ_writeByte           ; Declare symbol to be exported
            ;RSEG    CODE                    ; Code is relocatable
            .def  SDQ_writeByte              ; Declare symbol to be exported
            .text                            ; Code is relocatable
        
SDQ_writeByte;
            dint                            ; Disable global interrupts
            push    SR                      ; Save Status Register
            push    R6                      ; Save R6
            mov     #09h,R6                 ; Initialize bit counter
SDQTD       dec     R6
            jeq     TBEND                   ; If counter = 0, we're done
TX_BIT      bis.b   #P1_SDQ,&P1OUT          ; Pull SDQ bus to HIGH state
            bis.b   #P1_SDQ,&P1DIR          ; Set SDQ as OUTPUT direction
            bic.b   #P1_SDQ,&P1OUT          ; Pull SDQ bus to LOW state
            rra     R12                     ; LSB is shifted into CARRY bit
            jc      TX_1                    ; Jump if bit = 1
TX_0        call    #DLYUSEC_65             ; Delay 65 usec
            bis.b   #P1_SDQ,&P1OUT          ; Pull SDQ HIGH
            call    #DLYUSEC_07             ; Delay 7 usec
            jmp     TREC                    ; Delay for recovery period
TX_1        call    #DLYUSEC_07             ; Delay 7 usec
            bis.b   #P1_SDQ,&P1OUT          ; Pull SDQ HIGH
            call    #DLYUSEC_65             ; Delay 65 usec
TREC        call    #DLYUSEC_07             ; Delay 7 usec
            jmp     SDQTD                   ; Decrement bit counter
TBEND       call    #DLYUSEC_65             ; Delay 65 usec
            pop     R6                      ; Restore R6
            pop     SR                      ; Restore Status Register
            eint
            ret                             ; Return from subroutine
        
            ;END
            .end

;-===========================================================================--
;--- Version Information
;--- 1.00 (08/31/2012) - Initial Release
;--- 1.10 (11/26/2012) - Updated GPIO SDQ macros to use with PACE HW (P1.0)
;---
;---=========================================================================--
