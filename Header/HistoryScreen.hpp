#ifndef HISTORYSCREEN_HPP
#define HISTORYSCREEN_HPP
#include "cScreen.hpp"

class HistoryScreen : public cScreen{
private:
public:
    HistoryScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
};

#endif // HISTORYSCREEN_HPP
