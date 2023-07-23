#ifndef SEARCH_SCREEN_HPP
#define SEARCH_SCREEN_HPP
#include "cScreen.hpp"

class SearchScreen : public cScreen{
private:
public:
    SearchScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
};

#endif // SEARCH_SCREEN_HPP
