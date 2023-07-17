#ifndef ADDSCR_HPP
#define ADDSCR_HPP
#include "cScreen.hpp"

class AddScreen : public cScreen{
private:
public:
    AddScreen(void);
    virtual void ScreenDraw(sf::RenderWindow &App);
    virtual int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    virtual void updateScene(sf::Time &deltaTime);
};

#endif // ADDSCR_HPP

