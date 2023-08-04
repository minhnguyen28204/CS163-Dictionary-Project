#ifndef SETTINGSCREEN_HPP
#define SETTINGSCREEN_HPP

#include "cScreen.hpp"
#include "Trie.hpp"
#include <fstream>
#include <vector>

class SettingScreen : public cScreen
{
private:
    sf::Text emoticon, slang, engToEng, engToVie, vieToEng, dataSet;
    sf::CircleShape semo, ssla, seen, sevi, sven;
    sf::CircleShape selected;
    sf::Font _font;
    std::vector<sf::CircleShape> myShape;
    std::vector<sf::Text> myText;
    sf::RectangleShape resetButton;
    sf::Text resetText;
    sf::Color c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238,238,238);
public:
    SettingScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
    void SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4);
};

#endif // SETTINGSCREEN_HPP
