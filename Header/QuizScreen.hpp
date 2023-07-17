#ifndef QUIZSCREEN_HPP
#define QUIZSCREEN_HPP
#include "cScreen.hpp"
#include <SFML/Graphics.hpp>

class QuizScreen : public cScreen
{
private:
    sf::RectangleShape rec;
public:
    QuizScreen(void);
    virtual void ScreenDraw(sf::RenderWindow &App);
    virtual int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    virtual void updateScene(sf::Time &deltaTime);
};

#endif // QUIZSCREEN_HPP
