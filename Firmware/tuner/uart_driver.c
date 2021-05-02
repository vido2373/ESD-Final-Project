/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   uart_driver.c
 * Author   :   Vishnu Dodballapur
 * Date     :   03/10/2021
 *******************************************************************************/


#include "uart_driver.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <stdint.h>

//variables for uart functionality
volatile static uint8_t uart_byte = 0;
volatile static uint8_t uart_received = 0;
volatile static uint8_t uart_transmit_ready = 1;

/*
 * Function     :   void uart_init(void)
 * Brief        :   Initializes UART to run at 9600 buad rate, 1 stop bit, no parity
 */
void uart_init(void) {
    P1->SEL0 |= (BIT2 | BIT3); // set as UART

    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; // reset eUSCI
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | // Keep eUSCI in reset
            EUSCI_B_CTLW0_SSEL__SMCLK;      // Configure eUSCI clock source for SMCLK

    // Baud Rate calculation
    // 12000000/(16*9600) = 78.125
    // Fractional portion = 0.125
    // User's Guide Table 21-4: UCBRSx = 0x10
    // UCBRFx = int ( (78.125-78)*16) = 2
    EUSCI_A0->BRW = 312;                     // 12000000/16/9600
    EUSCI_A0->MCTLW = (8 << EUSCI_A_MCTLW_BRF_OFS) |
            EUSCI_A_MCTLW_OS16; // Enable oversampling

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;    // Clear eUSCI RX interrupt flag
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_TXIFG; // Clear eUSCI TXCPT interrupt flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE | EUSCI_A_IE_TXIE;        // Enable USCI_A0 RX interrupt and TX interrupt

    NVIC->ISER[0] |= 1 << ((EUSCIA0_IRQn) & 31);
}

/*
 * Function     :   uint8_t get_uart_received(void)
 * Brief        :   Checks if RX has received a byte
 * Returns      :   1 if RX has received a byte, 0 else
 */
uint8_t get_uart_received(void) {
    return uart_received;
}

/*
 * Function     :   uint8_t get_uart_byte(void)
 * Brief        :   Reads byte RX has received
 * Returns      :   Byte received by RX
 */
uint8_t get_uart_byte(void) {
    return uart_byte;
}

/*
 * Function     :   void clear_uart_received(void)
 * Brief        :   Clears uart_received flag
 */
void clear_uart_received(void) {
    uart_received = 0;
}

/*
 * Function     :   uint8_t get_uart_transmit_ready(void)
 * Brief        :   Checks if uart can transmit
 * Returns      :   1 if uart can transmit, 0 else
 */
uint8_t get_uart_transmit_ready(void) {
    return uart_transmit_ready;
}

/*
 * Function     :   uint8_t get_uart_transmit_ready(void)
 * Brief        :   Sends byte to TX
 * Inputs       :   uart_byte - byte to transmit
 */
void uart_transmit(uint8_t uart_byte) {
    uart_transmit_ready = 0;
    EUSCI_A0->TXBUF = uart_byte;
}

/*
 * Function     :   void EUSCIA0_IRQHandler(void)
 * Brief        :   UART IRQ Handler
 */
void EUSCIA0_IRQHandler(void) {
    if (EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG) {
        EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG;
        uart_byte = EUSCI_A0->RXBUF;
        uart_received = 1;
    }
    else if (EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG) {
        EUSCI_A0->IFG &= ~EUSCI_A_IFG_TXIFG;
        uart_transmit_ready = 1;
    }
}


