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
    sf::Color c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238,238,238);
    //Screen states
    vector<cScreen*> Screens;
    int screen = 0;
    sf::Text Title;

    //Variables
    HomeScreen s0;
    SearchScreen s1;
    HistoryScreen s2;
    FavoriteScreen s3;
    AddScreen s4;
    QuizScreen s5;
    SettingScreen s6;
    bool dark = true;
    sf::Font _font;
    sf::RenderWindow mWindow;
    SideBar MenuBar;
    sf::RectangleShape sideBar;
    sf::Texture ihome, isearch, ihistory, ifavorite, iadd, isetting, iquiz, itheme;
    sf::Sprite Ihome, Isearch, Ihistory, Ifavorite, Iadd, Isetting, Iquiz, Itheme;
    sf::Text thome, tsearch, thistory, tfavorite, tadd, tsetting, tquiz, ttheme;
    vector<sf::Sprite> MySprite;
    vector<sf::RectangleShape> MyBounder;
    vector<sf::Text> MyCursorText;
    bool is_on[15];
};

#endif // MAINFUNCTION_H
