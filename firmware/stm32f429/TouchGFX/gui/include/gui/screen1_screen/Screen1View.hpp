#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void on_change_R(int value);
	virtual void on_change_G(int value);
	virtual void on_change_B(int value);
	virtual void on_change_V(int value);
	virtual void on_enter_screen();
	virtual void on_click_clear_button();
	virtual void on_click_mode();
	void setui_led_slider(int r, int g, int b);
	void setui_vibrate_slider(int v);
	void setui_temp_val(int value);
	void setui_humi_val(int value);
	void setui_ambi_val(int value);
	void add_debug_log(const char* szFormat, ...);
	uint16_t logSize;
protected:
};

#endif // SCREEN1VIEW_HPP
