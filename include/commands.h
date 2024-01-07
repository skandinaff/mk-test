#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

#ifndef LED_PIN1
    #define LED_PIN1 0
#endif
#ifndef LED_PIN2
    #define LED_PIN2 1  
#endif
#ifndef LED_PIN3
    #define LED_PIN3 2  
#endif
#ifndef LED_PIN4
    #define LED_PIN4 3  
#endif


void process_command(const char *cmd);
void led_control(uint8_t led_id, uint32_t duration_ms);
void echo_data(const char *data, uint16_t len);
void update_led_status(void);

#endif // COMMANDS_H
