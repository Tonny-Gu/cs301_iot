/*
 * devmgr.hpp
 *
 *  Created on: Dec 15, 2019
 *      Author: tonny
 */

#ifndef INC_DEVMGR_HPP_
#define INC_DEVMGR_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "stdarg.h"
#include "string.h"
#include "stdio.h"

#ifdef __cplusplus
}
#endif

#define DEBUG_LOG_BUF_SIZE 1024

struct LED_State {
	uint16_t r, g, b;
};

struct Motor_State {
	uint16_t speed;
};

struct Env_State {
	uint8_t temp;
	uint8_t humi;
	uint16_t ambi;
};

struct Node_State {
	uint8_t auto_mode;
	uint16_t ambi_throttle;
};

Env_State get_env_state();
Motor_State get_motor_state();
LED_State get_led_state();
Node_State get_node_state();
void set_motor(Motor_State state);
void set_led(LED_State state);
void set_env(Env_State state);
void set_node(Node_State state);
void turn_led_on();
void turn_led_off();
void debug_print(const char* szFormat, ...);
char* get_debug_log_buf();
void clear_debug_log_buf();
uint8_t exec_spi_cmd(uint8_t cmd[]);
void devmgr_init();

#endif /* INC_DEVMGR_HPP_ */
