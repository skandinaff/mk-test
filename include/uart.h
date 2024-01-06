#ifndef UART_H
#define UART_H

#include "../Drivers/Include/stm32l011xx.h"

#ifdef UART_BAUD_RATE
#define BAUD_RATE UART_BAUD_RATE
#else
#define BAUD_RATE 9600  // Default baud rate
#endif

void uart_init(void);
void uart_transmit(const char *data, uint16_t size);
void uart_process(void);

#endif // UART_H