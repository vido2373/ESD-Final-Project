/*******************************************************************************
 * Project  :   Embedded Tuner
 * File     :   uart_driver.h
 * Author   :   Vishnu Dodballapur
 * Date     :   03/10/2021
 * Brief    :   defines related to UART
 *******************************************************************************/

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <stdint.h>

/*
 * Function     :   void uart_init(void)
 * Brief        :   Initializes UART to run at 9600 buad rate, 1 stop bit, no parity
 */
void uart_init(void);
/*
 * Function     :   uint8_t get_uart_received(void)
 * Brief        :   Checks if RX has received a byte
 * Returns      :   1 if RX has received a byte, 0 else
 */
uint8_t get_uart_received(void);
/*
 * Function     :   uint8_t get_uart_byte(void)
 * Brief        :   Reads byte RX has received
 * Returns      :   Byte received by RX
 */
uint8_t get_uart_byte(void);
/*
 * Function     :   void clear_uart_received(void)
 * Brief        :   Clears uart_received flag
 */
void clear_uart_received(void);
/*
 * Function     :   uint8_t get_uart_transmit_ready(void)
 * Brief        :   Checks if uart can transmit
 * Returns      :   1 if uart can transmit, 0 else
 */
uint8_t get_uart_transmit_ready(void);
/*
 * Function     :   uint8_t get_uart_transmit_ready(void)
 * Brief        :   Sends byte to TX
 * Inputs       :   uart_byte - byte to transmit
 */
void uart_transmit(uint8_t uart_byte);



#endif /* UART_DRIVER_H_ */
