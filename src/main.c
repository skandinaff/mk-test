#include "../include/stm32l011xx.h"
#include "../include/uart.h"
#include "../include/commands.h"

void tim2_init(void) {
    // Enable clock for TIM2
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    // Prescaler to scale clock to 21,000 Hz (2,097,152 / 100)
    TIM2->PSC = 100 - 1;  // Prescaler
    // Auto-reload value for 1ms interval at 21,000 Hz
    TIM2->ARR = 21 - 1;  // Auto-Reload
    TIM2->DIER |= TIM_DIER_UIE;  // Enable update interrupt
    TIM2->CR1 |= TIM_CR1_CEN;  // Enable the timer
    // Enable TIM2 interrupt in NVIC
    NVIC_EnableIRQ(TIM2_IRQn);  // Enable TIM2 interrupt in NVIC
}


int main(void) {
    uart_init();
    tim2_init();
    while (1) {
    }
}
void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {  // Check if update interrupt flag is set
        TIM2->SR &= ~TIM_SR_UIF;  // Clear update interrupt flag
        update_led_status();
    }
}