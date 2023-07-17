#ifndef FAVORSCR_HPP
#define FAVORSCR_HPP
#include "cScreen.hpp"

class FavoriteScreen : public cScreen{
private:
public:
    FavoriteScreen(void);
    virtual void ScreenDraw(sf::RenderWindow &App);
    virtual int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    virtual void updateScene(sf::Time &deltaTime);
};

#endif // FAVORSCR_HPP

