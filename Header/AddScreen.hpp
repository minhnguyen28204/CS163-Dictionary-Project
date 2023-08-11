#ifndef ADDSCR_HPP
#define ADDSCR_HPP
#include "cScreen.hpp"
#include "TextField.hpp"
#include <vector>
#include <iostream>
#include "Trie.hpp"

using namespace std;

class AddScreen : public cScreen{
private:
    sf::RectangleShape boder;
    sf::Color c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238,238,238);
    TextField keyInput;
    vector<TextField> defInput;
    sf::RectangleShape addDef, delDef, okWord;
    sf::Text addText, delText, okTest;
    sf::Text Title, keyText;
    sf::Font _font;
public:
    AddScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
    void SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4);
};

#endif // ADDSCR_HPP

