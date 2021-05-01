#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <stdint.h>

void uart_init(void);

uint8_t get_uart_received(void);

uint8_t get_uart_byte(void);

void clear_uart_received(void);

uint8_t get_uart_transmit_ready(void);

void uart_transmit(uint8_t uart_byte);



#endif /* UART_DRIVER_H_ */
