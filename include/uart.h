#ifndef UART_H
#define UART_H

#include "stm32l011xx.h"

#ifndef UART_BAUD_RATE
#define UART_BAUD_RATE 9600  // Default baud rate if not specified during build
#endif

void uart_init(void);
void uart_transmit(const char *data, uint16_t size);
void uart_process(void);

#endif // UART_H