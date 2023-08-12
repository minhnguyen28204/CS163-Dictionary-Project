#ifndef WORDSCREEN_HPP
#define WORDSCREEN_HPP
#include <string>
#include "SFML/Graphics.hpp"
#include "cScreen.hpp"
#include "TextField.hpp"
#include "Trie.hpp"
#include "FavouriteList.hpp"
#include <io.h>
#include <fcntl.h>
using namespace std;

class WordScreen : public cScreen
{
private:
	sf::RectangleShape Header;
	sf::Sprite object, saveSprite, cancelSprite, deleteSprite, tickSprite, heartSprite;
	sf::Texture objTexture, saveObj, cancelObj, deleteObj, tickObj, heartObj;
	sf::RectangleShape editBound, saveBound, cancelBound, addBound, deleteBound, tickBound, heartBound;
	sf::Text KeyWord;
	sf::Text TestDef;
	sf::Text addText;
	sf::Text delProtection;
	sf::Font _font;
	vector<sf::Text> Def;
	vector<TextField> editDef;
	vector<sf::RectangleShape> delShape;
	vector<sf::Text> delText;
	wstring MyDef;
	wstring MyKey;
	bool loadWord = false;
	bool is_found = false;
	bool is_dark = true;
	bool is_edit = false;
	bool is_delete = false;
	sf::Color c1 = sf::Color(34, 40, 49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238, 238, 238);
public:
	WordScreen(void);
	void ScreenDraw(sf::RenderWindow& App);
	int ProcessEvent(sf::RenderWindow& App, sf::Event event);
	void updateScene(sf::Time& deltaTime);
	void setString(wstring _def, wstring _key);
	void SetColor(sf::Color& f1, sf::Color& f2, sf::Color& f3, sf::Color& f4);

	bool heart_state = false;
};

#endif // WORDSCREEN_HPP
