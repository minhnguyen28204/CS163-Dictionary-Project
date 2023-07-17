#ifndef SETTINGSCREEN_HPP
#define SETTINGSCREEN_HPP

#include "cScreen.hpp"

class SettingScreen : public cScreen
{
public:
    SettingScreen(void);
    virtual void ScreenDraw(sf::RenderWindow &App);
    virtual int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    virtual void updateScene(sf::Time &deltaTime);
};

#endif // SETTINGSCREEN_HPP
