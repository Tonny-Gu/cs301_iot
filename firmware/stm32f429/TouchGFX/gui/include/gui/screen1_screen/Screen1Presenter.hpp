#ifndef SCREEN1PRESENTER_HPP
#define SCREEN1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Screen1View;

class Screen1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Screen1Presenter(Screen1View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~Screen1Presenter() {};

    void sethw_led_r(int value);
    void sethw_led_g(int value);
    void sethw_led_b(int value);
    void sethw_motor(int value);
    void sethw_automode(int value);
    void setui_led(int r, int g, int b);
    void setui_vibrate(int v);
    void setui_env(int temp, int humi, int ambi);
    void setui_log_append(const char* str);

private:
    Screen1Presenter();

    Screen1View& view;
};


#endif // SCREEN1PRESENTER_HPP
