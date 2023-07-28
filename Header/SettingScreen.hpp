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
public:
    SettingScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
};

#endif // SETTINGSCREEN_HPP
