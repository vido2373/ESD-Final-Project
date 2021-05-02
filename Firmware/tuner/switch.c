/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   switch.c
 * Author   :   Vishnu Dodballapur
 * Date     :   04/2/2021
 *******************************************************************************/
#include "switch.h"
#include <ti/devices/msp432p4xx/inc/msp.h>

#include <stdint.h>

volatile static uint8_t output_mode;

/*
 * Function     :   void init_switch(void)
 * Brief        :   Initializes push button for falling-edge interrupt detection
 */
void init_switch(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	P4->DIR = ~(uint8_t) BIT1;
    P4->OUT |= BIT1;
    P4->SEL0 &= ~BIT1;
    P4->SEL1 &= ~BIT1;
    P4->IES = BIT1;                         // Interrupt on high-to-low transition
    P4->IFG = 0;                            // Clear all P1 interrupt flags
    P4->IE = BIT1;                          // Enable interrupt for P1.1

    // Enable Port 1 interrupt on the NVIC
    NVIC->ISER[1] = 1 << ((PORT4_IRQn) & 31);

}

/*
 * Function     :   uint8_t get_output_mode(void)
 * Brief        :   Returns the output mode of the tuner
 * Return       :   1 if pitch mode, 0 if tuner mode
 */
uint8_t get_output_mode(void) {
    return output_mode;
}


/*
 * Function     :   void PORT4_IRQHandler(void)
 * Brief        :   GPIO IRQ Handler
 */
void PORT4_IRQHandler(void)
{
    if(P4->IFG & BIT1) {
        output_mode ^= 1;
    }

    P4->IFG &= ~BIT1;
}
