#include "commands.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Drivers/Include/stm32l011xx.h"

static volatile uint32_t led_timer = 0;
static uint8_t led_id = 0;  // Assuming LED ID corresponds to a GPIO pin

void process_command(const char *cmd) {
    if (strncmp(cmd, "set-led ", 8) == 0) {
        uint8_t led_id = atoi(&cmd[8]);
        char *comma_pos = strchr(&cmd[8], ',');
        if (comma_pos) {
            uint32_t duration_ms = atoi(comma_pos + 1);
            led_control(led_id, duration_ms);
            uart_transmit("OK\r\n", 4);
        }
    } else if (strncmp(cmd, "echo ", 5) == 0) {
        uint16_t len = atoi(&cmd[5]);
        char *comma_pos = strchr(&cmd[5], ',');
        if (comma_pos && len > 0 && len <= 300) {
            echo_data(comma_pos + 1, len);
            uart_transmit("OK\r\n", 4);
        }
    } else {
        uart_transmit("ERROR\r\n", 7);
    }
}

void led_control(uint8_t id, uint32_t duration_ms) {

    if (id != PIN1 && id != PIN2) {
        uart_transmit("ERROR\r\n", 7);
        return;  // Invalid ID, return from the function
    }
    // Enable clock for GPIOB
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

    // Configure the selected GPIO pin as output
    GPIOB->MODER &= ~(0x3 << (id * 2));      // Clear mode bits for the pin
    GPIOB->MODER |= (0x1 << (id * 2));       // Set pin as output

    led_id = id;     // Set the global variable for LED ID
    led_timer = duration_ms;  // Set the timer

    // Turn on the LED by setting the corresponding pin in GPIOB ODR
    GPIOB->ODR |= (1 << led_id);          // Set pin high to turn on LED
}
void echo_data(const char *data, uint16_t len) {
    char buffer[302]; // Maximum length of "data: " + 300 chars + "\r\n"
    sprintf(buffer, "data: %.*s\r\n", len, data);
    uart_transmit(buffer, strlen(buffer));
}

void update_led_status(void) {
    if (led_timer > 0) {
        // Decrement the timer
        led_timer--;

        if (led_timer == 0) {
            // Turn off the LED
            GPIOB->ODR &= ~(1 << led_id);

            // Send the "led-off" message
            char message[20];
            sprintf(message, "led-off: %d\r\n", led_id);
            uart_transmit(message, strlen(message));
        }
    }
}