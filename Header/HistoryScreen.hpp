#ifndef HISTORYSCREEN_HPP
#define HISTORYSCREEN_HPP
#include "cScreen.hpp"
#include "History.hpp"
#include "Trie.hpp"

class HistoryScreen : public cScreen{
private:
	sf::Font _font;
	sf::Text title;
	sf::RectangleShape border;
	sf::Color c1 = sf::Color(34, 40, 49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238, 238, 238);
	sf::Texture tickObj;
	sf::Texture delObj;
	sf::Sprite delSprite;
	sf::RectangleShape delBound;
	sf::Texture tickAllObj;
	sf::Sprite tickAllSprite;
	sf::RectangleShape tickAllBound;
	bool is_tickAll = false;
	bool is_dark = true;
public:
	std::vector<sf::RectangleShape> recSet;
	std::vector<sf::Text> textSet;
	std::vector<sf::RectangleShape> tickBoundSet;
	std::vector<sf::Sprite> tickSpriteSet;
	std::vector<bool> tick;
    HistoryScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
	void updateScene();
	void SetColor(sf::Color& f1, sf::Color& f2, sf::Color& f3, sf::Color& f4);
	wstring MyDef;
	wstring MyKey;
	bool is_search = false;
};

#endif // HISTORYSCREEN_HPP
