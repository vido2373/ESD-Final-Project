/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   clock_and_timer.h
 * Author   :   Vishnu Dodballapur
 * Date     :   03/10/2021
 *******************************************************************************/

#include "clock_and_timer.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <stdint.h>

/*
 * Function     :   void CLK_Init(void)
 * Brief        :   Initializes clocks
 */
void CLK_Init(void) {
    CS->KEY = CS_KEY_VAL; // unlock clock register
    CS->CTL0 = 0; // reset clock control register
    CS->CTL0 |= CS_CTL0_DCORSEL_5; // 48MHz clock
    CS->CTL1 = CS_CTL1_SELA_2 |    // Select ACLK = REFO (32.768kHz)
                CS_CTL1_SELS_3 |   // SMCLK = DCO
                CS_CTL1_SELM_3;    // MCLK = DCO
    CS->KEY = 0;
}
