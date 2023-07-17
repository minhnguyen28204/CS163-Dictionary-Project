#ifndef HISTORYSCREEN_HPP
#define HISTORYSCREEN_HPP
#include "cScreen.hpp"

class HistoryScreen : public cScreen{
private:
public:
    HistoryScreen(void);
    virtual void ScreenDraw(sf::RenderWindow &App);
    virtual int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    virtual void updateScene(sf::Time &deltaTime);
};

#endif // HISTORYSCREEN_HPP
