#ifndef ADDSCR_HPP
#define ADDSCR_HPP
#include "cScreen.hpp"

class AddScreen : public cScreen{
private:
public:
    AddScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
};

#endif // ADDSCR_HPP

