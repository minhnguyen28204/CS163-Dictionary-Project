#ifndef SCREEN_STATE_HPP
#define SCREEN_STATE_HPP
#include <SFML/Graphics.hpp>

class cScreen{
public:
    virtual void ScreenDraw(sf::RenderWindow &App) = 0;
    virtual int ProcessEvent(sf::RenderWindow &App, sf::Event event) = 0;
    virtual void updateScene(sf::Time &deltaTime) = 0;
};

#endif // SCREEN_STATE_HPP

