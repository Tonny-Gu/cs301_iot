#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <cstring>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{
}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::sethw_led_r(int value)
{
	model->sethw_led(value, -1, -1);
}

void Screen1Presenter::sethw_led_g(int value)
{
	model->sethw_led(-1, value, -1);
}

void Screen1Presenter::sethw_led_b(int value)
{
	model->sethw_led(-1, -1, value);
}

void Screen1Presenter::sethw_motor(int value)
{
	model->sethw_motor(value);
}

void Screen1Presenter::sethw_automode(int value)
{
	model->sethw_automode(value);
}

void Screen1Presenter::setui_log_append(const char* str)
{
	for(int i = 0; i<int(strlen(str)); ++i)
	{
		view.add_debug_log("%c", str[i]);
	}
}

void Screen1Presenter::setui_led(int r, int g, int b)
{
	view.setui_led_slider(r, g, b);
}

void Screen1Presenter::setui_vibrate(int v)
{
	view.setui_vibrate_slider(v);
}

void Screen1Presenter::setui_env(int temp, int humi, int ambi)
{
	view.setui_temp_val(temp);
	view.setui_humi_val(humi);
	view.setui_ambi_val(ambi);
}
