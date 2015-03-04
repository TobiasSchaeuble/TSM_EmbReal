#pragma once
/*-------------------------
  timer
  (c) H.Buchmann FHNE 2012
  $Id$
  [1] literature/realview_emulation_basebord_ug.pdf
  [2] literature/sp-804-timer-DDI0271.pdf
---------------------------*/
typedef struct /* see [2] 3.1 */
{
       unsigned Load;   
    /* The TimerXLoad Register is a 32-bit register that contains
       the value from which the counter is to decrement. 
       This is the value used to reload the counter 
       when Periodic mode is enabled, and the current count 
       reaches zero.*/
 const unsigned Value; 
    /*  The TimerXValue Register is a 32-bit read-only register 
       that gives the current value ofthe decrementing counter. */
       unsigned Control; 
    /*    [31:8] - - Reserved bits, do not modify, 
                     and ignore on read
             [7] TimerEn Read/write Enable bit:
                0 = Timer module disabled (default)
                1 = Timer module enabled.
             [6] TimerMode Read/write Mode bit:
                0 = Timer module is in free-running mode (default)
                1 = Timer module is in periodic mode.
             [5] IntEnable Read/write Interrupt Enable bit:
                0 = Timer module Interrupt disabled
                1 = Timer module Interrupt enabled (default).
             [4] - - Reserved bits, do not modify, 
                     and ignore on read
           [3:2] TimerPre Read/write Prescale bits:
                00 = 0 stages of prescale, clock is divided by 1 (default)
                01 = 4 stages of prescale, clock is divided by 16
                10 = 8 stages of prescale, clock is divided by 256
                11 = Undefined, do not use.

             [1] TimerSize Read/write Selects 16/32 bit 
                 counter operation:
                0 = 16-bit counter (default)
                1 = 32-bit counter.

             [0] OneShot Read/write Selects one-shot or wrapping 
                 counter mode:
                 0 = wrapping mode (default)
                 1 = one-shot mode.*/      
       unsigned IntClr;
 const unsigned RIS;
 const unsigned MIS;
       unsigned BGLoad;
} Timer;

extern volatile Timer TIMER0;              /* see linker script */
extern volatile Timer TIMER1;
extern volatile Timer TIMER2;
extern volatile Timer TIMER3;
