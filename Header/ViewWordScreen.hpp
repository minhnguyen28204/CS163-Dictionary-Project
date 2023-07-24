#ifndef WORDSCREEN_HPP
#define WORDSCREEN_HPP
#include <string>
#include "SFML/Graphics.hpp"
#include "cScreen.hpp"
using namespace std;

class WordScreen : public cScreen
{
private:
    sf::Text KeyWord;
    sf::Text TestDef;
    sf::Font _font;
    vector<sf::Text> Def;
    wstring MyDef;
    wstring MyKey;
    bool loadWord = false;
    bool is_found = false;
public:
    WordScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
    void setString(wstring _def, wstring _key);
};

#endif // WORDSCREEN_HPP
