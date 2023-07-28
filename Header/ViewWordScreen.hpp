#ifndef WORDSCREEN_HPP
#define WORDSCREEN_HPP
#include <string>
#include "SFML/Graphics.hpp"
#include "cScreen.hpp"
using namespace std;

class WordScreen : public cScreen
{
private:
    sf::RectangleShape Header;
    sf::Text KeyWord;
    sf::Text TestDef;
    sf::Font _font;
    vector<sf::Text> Def;
    wstring MyDef;
    wstring MyKey;
    bool loadWord = false;
    bool is_found = false;
    sf::Color c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238,238,238);
public:
    WordScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
    void setString(wstring _def, wstring _key);
    void SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4);
};

#endif // WORDSCREEN_HPP
