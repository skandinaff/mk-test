#include "../include/stm32l011xx.h"

void delay(uint32_t count) {
    while(count--) {
        __NOP(); // NOPs generated to consume time
    }
}

int main(void) {
    // Enable GPIOA clock
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;

    // Set PA5 (connected to the LED) as output
    GPIOB->MODER &= ~(GPIO_MODER_MODE4);
    GPIOB->MODER |= GPIO_MODER_MODE4_0;

    GPIOB->MODER &= ~(GPIO_MODER_MODE5);
    GPIOB->MODER |= GPIO_MODER_MODE5_0;

    GPIOB->MODER &= ~(GPIO_MODER_MODE3);
    GPIOB->MODER |= GPIO_MODER_MODE3_0;

    while(1) {
        // Toggle PA5
        GPIOB->ODR ^= GPIO_ODR_OD4;
        GPIOB->ODR ^= GPIO_ODR_OD5;
        GPIOB->ODR ^= GPIO_ODR_OD3;

        // Delay
        delay(50000);
    }
}
