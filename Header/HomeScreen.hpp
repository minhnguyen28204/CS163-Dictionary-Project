#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP
#include <iostream>
#include <vector>
#include "cScreen.hpp"
#include "TextField.hpp"
#include <SFML/Graphics.hpp>

class HomeScreen : public cScreen
{
private:
    sf::RectangleShape RandomWord;
    sf::RectangleShape HistoryWord;
    sf::RectangleShape FavoriteWord;
    sf::RectangleShape Quiz;
    sf::Text ranw, hisw, favw, quizw;
    sf::Font _font;
    TextField inputField;


    sf::Texture object;
    sf::Sprite Image;

    sf::Texture enter_object;
    sf::Sprite enter_image;
    sf::RectangleShape enter_bound;

    std::vector<sf::RectangleShape> MyButton;

    float cur_stack_time = 0;

    sf::Color c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238,238,238);
public:
    HomeScreen(void);
    virtual void ScreenDraw(sf::RenderWindow &App);
    virtual int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    virtual void updateScene(sf::Time &deltaTime);
};

#endif // HOMESCREEN_HPP
