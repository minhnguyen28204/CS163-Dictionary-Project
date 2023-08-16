#ifndef SEARCH_SCREEN_HPP
#define SEARCH_SCREEN_HPP
#include "cScreen.hpp"
#include "TextField.hpp"
#include "Trie.hpp"
#include <vector>
using namespace std;

class SearchScreen : public cScreen{
private:
    TextField defField;
    sf::Font _font;
    sf::Color c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238,238,238);
    sf::Text SubTit2;
    vector<sf::Text> suggestBox;
    vector<sf::RectangleShape> outlineBox;
    vector<sf::Text> numberBox;
    vector<string> recommendString;
    int l, r;
public:
    SearchScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
    void SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4);
    wstring MyDef;
    wstring MyKey;
    bool is_search = false;

};

#endif // SEARCH_SCREEN_HPP
