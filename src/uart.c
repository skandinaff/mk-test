#include <string.h>
#include "../include/uart.h"
#include "../include/commands.h"

#define UART_BUFFER_SIZE 64

static char uart_buffer[UART_BUFFER_SIZE];
static uint16_t uart_buffer_index = 0;

void uart_init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

    // Configure GPIO pins PA9 (TX) and PA10 (RX) in Alternate Function mode
    // PA9: AF4 (USART2_TX), PA10: AF4 (USART2_RX)
    GPIOA->MODER &= ~(GPIO_MODER_MODE9 | GPIO_MODER_MODE10); // Clear mode bits
    GPIOA->MODER |= (GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1); // Set to Alternate Function
    GPIOA->AFR[1] |= (0x4 << (4 * (9 - 8))) | (0x4 << (4 * (10 - 8))); // Set AF4 for USART2

    // Configure USART2 (8 data bits, no parity, 1 stop bit)
    USART2->BRR = (uint16_t)(SystemCoreClock / UART_BAUD_RATE);
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
    
    USART2->CR1 |= USART_CR1_RXNEIE;

    // Enable USART2 interrupt

    NVIC_EnableIRQ(USART2_IRQn);
}

void uart_transmit(const char *data, uint16_t size) {
    for (uint16_t i = 0; i < size; ++i) {
        while (!(USART2->ISR & USART_ISR_TXE)) {}
        USART2->TDR = data[i];
    }
    while (!(USART2->ISR & USART_ISR_TC)) {}
}

void USART2_IRQHandler(void) {
    if (USART2->ISR & USART_ISR_RXNE) {
        char received_char = USART2->RDR;  // Read received character

        // Check for carriage return, indicating end of command
        if (received_char == '\r') {
            uart_buffer[uart_buffer_index] = '\0';  // Null-terminate the command
            process_command(uart_buffer);  // Process the received command
            uart_buffer_index = 0;  // Reset the buffer for the next command
        } else if (uart_buffer_index < UART_BUFFER_SIZE - 1) {
            uart_buffer[uart_buffer_index++] = received_char;  // Store character
        }
        // Optionally handle buffer overflow here
    }
}
