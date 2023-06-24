#ifndef MAINFUNCTION_H
#define MAINFUNCTION_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "MenuSideBar.hpp"

class Dictionary{
public:
    Dictionary();
    void run();
private:
    void processEvent();
    void update();
    void render();
private:
    sf::RenderWindow mWindow;
    SideBar MenuBar;
};

#endif // MAINFUNCTION_H
