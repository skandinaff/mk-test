#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>

void process_command(const char *cmd);
void led_control(uint8_t led_id, uint32_t duration_ms);
void echo_data(const char *data, uint16_t len);
void update_led_status(void);

#endif // COMMANDS_H
