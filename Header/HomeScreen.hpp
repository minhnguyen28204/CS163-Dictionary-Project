#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP
#include <vector>
#include "cScreen.hpp"
#include "TextField.hpp"
#include "Trie.hpp"
#include "History.hpp"
#include <SFML/Graphics.hpp>

class HomeScreen : public cScreen
{
public:
    void SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4);
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

    //elements for suggest box
    std::vector<sf::Text> suggestBox;
    std::vector<sf::RectangleShape> outlineBox;

    float cur_stack_time = 0;


    sf::Color c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238,238,238);
public:
    HomeScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
    void findString(wstring &def, wstring &key);
    wstring MyDef;
    wstring MyKey;
    bool is_search = false;
    bool previous_state = false;
};

#endif // HOMESCREEN_HPP
