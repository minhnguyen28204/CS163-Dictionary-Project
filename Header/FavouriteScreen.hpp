#ifndef FAVORSCR_HPP
#define FAVORSCR_HPP
#include "cScreen.hpp"

class FavoriteScreen : public cScreen{
private:
public:
    FavoriteScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
};

#endif // FAVORSCR_HPP

