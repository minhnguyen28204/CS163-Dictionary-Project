#ifndef SETTINGSCREEN_HPP
#define SETTINGSCREEN_HPP

#include "cScreen.hpp"

class SettingScreen : public cScreen
{
public:
    SettingScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
};

#endif // SETTINGSCREEN_HPP
