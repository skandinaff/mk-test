#include "../include/stm32l011xx.h"
#include "../include/uart.h"
#include "../include/commands.h"

void delay(uint32_t count) {
    while(count--) {
        __NOP(); // NOPs generated to consume time
    }
}

int main(void) {
    uart_init();
    uart_transmit("Hello!", 5);
    while (1) {
        update_led_status();
    }
}
