#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR

#include "devmgr.hpp"

extern "C" {

}
#endif

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
#ifndef SIMULATOR
	tick_counter ++;
	if(tick_counter == TICK_PRESCALER) {
		tick_counter = 0;
		LED_State led = get_led_state();
		Motor_State motor = get_motor_state();
		Env_State env = get_env_state();
		Node_State node = get_node_state();
		modelListener->setui_led(led.r, led.g, led.b);
		modelListener->setui_vibrate(motor.speed);
		modelListener->setui_env(env.temp, env.humi, env.ambi/10.24);
		modelListener->setui_log_append( get_debug_log_buf() );
		if(node.auto_mode) {
			if(env.ambi > node.ambi_throttle) turn_led_off();
			else turn_led_on();
		}
		clear_debug_log_buf();
	}
#endif
}

void Model::sethw_led(int r, int g, int b)
{
#ifndef SIMULATOR
	LED_State state = get_led_state();
	if(r>=0) state.r = r;
	if(g>=0) state.g = g;
	if(b>=0) state.b = b;
	set_led(state);
#endif
}

void Model::sethw_motor(int speed)
{
#ifndef SIMULATOR
	Motor_State state = get_motor_state();
	state.speed = speed;
	set_motor(state);
#endif
}

void Model::sethw_automode(int mode)
{
#ifndef SIMULATOR
	Node_State state = get_node_state();
	state.auto_mode = mode;
	set_node(state);
#endif
}
