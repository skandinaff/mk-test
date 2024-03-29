#include "commands.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Drivers/Include/stm32l011xx.h"

#define NUMBER_OF_LEDS 4
static volatile uint32_t led_timers[NUMBER_OF_LEDS] = {0};

static uint8_t led_ids[NUMBER_OF_LEDS] = {0};

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
    uint8_t pinNumber;
    if (id == 1) {
        pinNumber = LED_PIN1;
    } else if (id == 2) {
        pinNumber = LED_PIN2;
    } else if (id == 3) {
        pinNumber = LED_PIN3;
    } else if (id == 4) {
        pinNumber = LED_PIN4;
    } else {
        uart_transmit("ERROR\r\n", 7);
        return;
    }

    led_timers[id] = duration_ms;
    led_ids[id] = pinNumber;

    // Turn on the LED by setting the corresponding pin in GPIOB ODR
    GPIOB->ODR |= (1 << led_ids[id]);          
}
void echo_data(const char *data, uint16_t len) {
    char buffer[302]; // Maximum length of "data: " + 300 chars + "\r\n"
    sprintf(buffer, "data: %.*s\r\n", len, data);
    uart_transmit(buffer, strlen(buffer));
}

void update_led_status(void) {
    for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++) {
        if (led_timers[i] > 0) {
            led_timers[i]--;
            if (led_timers[i] == 0) {
            // Turn off the LED
            GPIOB->ODR &= ~(1 << led_ids[i]);
            char message[20];
            sprintf(message, "led-off: %d\r\n", i);
            uart_transmit(message, strlen(message));
        }
    }
    }
}