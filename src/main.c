#include "../include/stm32l011xx.h"

void delay(uint32_t count) {
    while(count--) {
        __NOP(); // NOPs generated to consume time
    }
}

int main(void) {
    // Enable GPIOA clock
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

    // Set PA5 (connected to the LED) as output
    GPIOA->MODER &= ~(GPIO_MODER_MODE5);
    GPIOA->MODER |= GPIO_MODER_MODE5_0;

    while(1) {
        // Toggle PA5
        GPIOA->ODR ^= GPIO_ODR_OD5;

        // Delay
        delay(100000);
    }
}
