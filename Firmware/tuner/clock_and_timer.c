/*
 * clock_and_timer.c
 *
 *  Created on: Mar 10, 2021
 *      Author: vishn
 */

#include "clock_and_timer.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <stdint.h>

void CLK_Init(void) {
    CS->KEY = CS_KEY_VAL; // unlock clock register
    CS->CTL0 = 0; // reset clock control register
    CS->CTL0 |= CS_CTL0_DCORSEL_5; // 12MHz clock
    CS->CTL1 = CS_CTL1_SELA_2 |    // Select ACLK = REFO (32.768kHz)
                CS_CTL1_SELS_3 |   // SMCLK = DCO
                CS_CTL1_SELM_3;    // MCLK = DCO
    CS->KEY = 0;
}


void timer_init(int8_t duty_cycle) {
    P2->DIR |= BIT4;
    P2->SEL0 |= BIT4;

    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_6 |
                TIMER_A_CCTLN_CCIE;

    TIMER_A0->CTL = TIMER_A_CTL_SSEL__ACLK |  // ACLK
                TIMER_A_CTL_MC__UP;             // Enable timer overflow interrupt

    TIMER_A0->CCR[1] = 32767 * duty_cycle / 100;
    TIMER_A0->CCR[0] = 32767;
}


void change_duty_cycle(int8_t duty_cycle) {
    TIMER_A0->CCR[1] = 32767 * duty_cycle / 100;
}


void TA0_N_IRQHandler(void) {
    if (TIMER_A0->CCTL[1] & TIMER_A_CCTLN_CCIFG) {
        TIMER_A0->CCTL[1] &= ~TIMER_A_CCTLN_CCIFG;
    }
}
