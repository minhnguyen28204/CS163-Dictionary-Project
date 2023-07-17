#ifndef MAINFUNCTION_H
#define MAINFUNCTION_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "MenuSideBar.hpp"
#include "Screen.hpp"

class Dictionary{
public:
    Dictionary();
    void run();
private:
    void processEvent();
    void update(sf::Time &deltaTime);
    void render();
    void processIconColor(sf::Event event);
private:
    //Screen states
    vector<cScreen*> Screens;
    int screen = 0;
    HomeScreen s0;
    SearchScreen s1;
    HistoryScreen s2;
    FavoriteScreen s3;
    AddScreen s4;
    QuizScreen s5;
    sf::Text Title;

    //Variables
    sf::Color c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181);
    sf::Font _font;
    sf::RenderWindow mWindow;
    SideBar MenuBar;
    sf::RectangleShape sideBar;
    sf::Texture ihome, isearch, ihistory, ifavorite, iadd, isetting, iquiz;
    sf::Sprite Ihome, Isearch, Ihistory, Ifavorite, Iadd, Isetting, Iquiz;
    sf::Text thome, tsearch, thistory, tfavorite, tadd, tsetting, tquiz;
    vector<sf::Sprite> MySprite;
    vector<sf::RectangleShape> MyBounder;
    vector<sf::Text> MyCursorText;
    bool is_on[15];
};

#endif // MAINFUNCTION_H
