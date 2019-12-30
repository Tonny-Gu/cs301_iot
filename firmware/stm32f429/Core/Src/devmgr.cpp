/*
 * devmgr.cpp
 *
 *  Created on: Dec 15, 2019
 *      Author: tonny
 */

#include "devmgr.hpp"

extern SPI_HandleTypeDef hspi4;
extern SPI_HandleTypeDef hspi5;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

static LED_State _dev_led, _dev_led_default;
static Motor_State _dev_motor;
static Env_State _dev_env;
static Node_State _dev_self;
static void* _dev_reg_table[16];

char debug_log_buf[ DEBUG_LOG_BUF_SIZE ];
uint16_t debug_log_size;

Env_State get_env_state()
{
	return _dev_env;
}

Motor_State get_motor_state()
{
	return _dev_motor;
}

LED_State get_led_state()
{
	return _dev_led;
}

Node_State get_node_state()
{
	return _dev_self;
}

void set_motor(Motor_State state)
{
	_dev_motor = state;

	TIM_OC_InitTypeDef sConfigOC;

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	sConfigOC.Pulse = state.speed;
	HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void set_led(LED_State state)
{
	_dev_led = state;

	TIM_OC_InitTypeDef sConfigOC;

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	sConfigOC.Pulse = state.r;
	HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

	sConfigOC.Pulse = state.g;
	HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

	sConfigOC.Pulse = state.b;
	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

void turn_led_on()
{
	set_led(_dev_led_default);
}

void turn_led_off()
{
	const LED_State led_off = {0, 0, 0};
	set_led(led_off);
}

void set_env(Env_State state)
{
	_dev_env = state;
}

void set_node(Node_State state)
{
	_dev_self = state;
}

void debug_print(const char* szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);
	vsnprintf(&debug_log_buf[ debug_log_size ], DEBUG_LOG_BUF_SIZE-debug_log_size-1, szFormat, args);
	debug_log_size = debug_log_size + strlen(&debug_log_buf[ debug_log_size ]);
	va_end(args);
}

char* get_debug_log_buf()
{
	return debug_log_buf;
}

void clear_debug_log_buf()
{
	memset(debug_log_buf, 0, sizeof(debug_log_buf));
	debug_log_size = 0;
}

uint8_t exec_spi_cmd(uint8_t cmd[])
{
	uint8_t rel = cmd[4];
	switch(cmd[0])
	{
	case 0x11:
		*((uint8_t*)_dev_reg_table[ cmd[1] ]) = cmd[3];
		// debug_print("SPI: write r%d = %d\n", cmd[1], cmd[3]);
		break;
	case 0x12:
		*((uint16_t*)_dev_reg_table[ cmd[1] ]) = (cmd[2]<<8) | cmd[3];
		// debug_print("SPI: write r%d = %d\n", cmd[1], (cmd[2]<<8) | cmd[3]);
		break;
	case 0x21:
		rel = *((uint8_t*)_dev_reg_table[ cmd[1] ]);
		break;
	case 0x22:
		rel = *((uint16_t*)_dev_reg_table[ cmd[1] ]) >> 8;
		break;
	default: debug_print("SPI: undef cmd\n");
	}
	return rel;
}

void reg_table_init()
{
	_dev_reg_table[0] = (void*)&_dev_self.ambi_throttle;
	_dev_reg_table[1] = (void*)&_dev_led.r;
	_dev_reg_table[2] = (void*)&_dev_led.g;
	_dev_reg_table[3] = (void*)&_dev_led.b;
	_dev_reg_table[4] = (void*)&_dev_motor.speed;
	_dev_reg_table[5] = (void*)&_dev_env.temp;
	_dev_reg_table[6] = (void*)&_dev_env.humi;
	_dev_reg_table[7] = (void*)&_dev_env.ambi;
	_dev_reg_table[8] = (void*)&_dev_led_default.r;
	_dev_reg_table[9] = (void*)&_dev_led_default.g;
	_dev_reg_table[10] = (void*)&_dev_led_default.b;
	_dev_reg_table[11] = (void*)&_dev_self.auto_mode;
	_dev_reg_table[12] = (void*)&_dev_self.ambi_throttle;

}

void devmgr_init()
{
	clear_debug_log_buf();
	reg_table_init();
	memset(&_dev_led, 0, sizeof(LED_State));
	memset(&_dev_led_default, 0, sizeof(LED_State));
	memset(&_dev_self, 0, sizeof(Node_State));
	memset(&_dev_env, 0, sizeof(Env_State));
	memset(&_dev_motor, 0, sizeof(Motor_State));
	_dev_self.ambi_throttle = 950;
	_dev_led_default.b = 100;
	debug_print("Hello World!\n");
}
