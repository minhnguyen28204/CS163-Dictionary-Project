#ifndef FAVORSCR_HPP
#define FAVORSCR_HPP
#include "cScreen.hpp"
#include "Trie.hpp"
#include "FavouriteList.hpp"

class FavoriteScreen : public cScreen{
private:
	sf::Font _font;
	sf::Text title;
	sf::RectangleShape border;
	sf::Color c1 = sf::Color(34, 40, 49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238, 238, 238);
public:
	std::vector<sf::RectangleShape> recSet;
	std::vector<sf::Text> textSet;
  FavoriteScreen(void);
  void ScreenDraw(sf::RenderWindow &App);
  int ProcessEvent(sf::RenderWindow &App, sf::Event event);
  void updateScene(sf::Time &deltaTime);
	void updateScene();
	void SetColor(sf::Color& f1, sf::Color& f2, sf::Color& f3, sf::Color& f4);
	std::wstring MyDef;
	std::wstring MyKey;
	bool is_search = false;

};

#endif // FAVORSCR_HPP
