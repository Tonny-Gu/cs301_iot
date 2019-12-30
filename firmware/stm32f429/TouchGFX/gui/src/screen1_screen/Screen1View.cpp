#include <gui/screen1_screen/Screen1View.hpp>
#include <cstring>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::add_debug_log(const char* szFormat, ...)
{
	va_list args;
	va_start(args, szFormat);
	Unicode::vsnprintf(&logContentBuffer[logSize], LOGCONTENT_SIZE-logSize-1, szFormat, args);
	logSize = logSize + Unicode::strlen(&logContentBuffer[logSize]);
	logContent.invalidate();
	va_end(args);
}

void Screen1View::on_change_R(int value)
{
	presenter->sethw_led_r(value);
}

void Screen1View::on_change_G(int value)
{
	presenter->sethw_led_g(value);
}

void Screen1View::on_change_B(int value)
{
	presenter->sethw_led_b(value);
}

void Screen1View::on_change_V(int value)
{
	presenter->sethw_motor(value);
}

void Screen1View::on_enter_screen()
{

}

void Screen1View::on_click_clear_button()
{
	memset(logContentBuffer, 0, sizeof(logContentBuffer));
	logSize = 0;
	logContent.invalidate();
}

void Screen1View::on_click_mode()
{
	presenter->sethw_automode(autoModeButton.getState());
}

void Screen1View::setui_led_slider(int r, int g, int b)
{
	redSlider.setValue(r);
	greenSlider.setValue(g);
	blueSlider.setValue(b);
	redSlider.invalidate();
	greenSlider.invalidate();
	blueSlider.invalidate();
}

void Screen1View::setui_vibrate_slider(int v)
{
	vibSlider.setValue(v);
	vibSlider.invalidate();
}

void Screen1View::setui_temp_val(int value)
{
	Unicode::snprintf(tempValBuffer, TEMPVAL_SIZE, "%d", value);
	tempBgBar.setValue(value);
	tempVal.invalidate();
	tempBgBar.invalidate();
}

void Screen1View::setui_humi_val(int value)
{
	Unicode::snprintf(humiValBuffer, HUMIVAL_SIZE, "%d", value);
	humiBgBar.setValue(value);
	humiVal.invalidate();
	humiBgBar.invalidate();
}

void Screen1View::setui_ambi_val(int value)
{
	Unicode::snprintf(ambiValBuffer, AMBIVAL_SIZE, "%d", value);
	ambiBgBar.setValue(value);
	ambiVal.invalidate();
	ambiBgBar.invalidate();
}
