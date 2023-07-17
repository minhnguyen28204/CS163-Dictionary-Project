#ifndef SEARCH_SCREEN_HPP
#define SEARCH_SCREEN_HPP
#include "cScreen.hpp"

class SearchScreen : public cScreen{
private:
public:
    SearchScreen(void);
    virtual void ScreenDraw(sf::RenderWindow &App);
    virtual int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    virtual void updateScene(sf::Time &deltaTime);
};

#endif // SEARCH_SCREEN_HPP
