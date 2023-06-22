#ifndef MENUSIDEBAR_H
#define MENUSIDEBAR_H
#include <bits/stdc++.h>
#include "SFML/Graphics.hpp"
using namespace std;

class SideBar{
private:
    sf::RectangleShape Bar;
    bool IsOpen = false;
public:
    SideBar();
    SideBar(const sf::Vector2f &ini_pos, const sf::Vector2f &size, const sf::Color &color);
    void SetOutColor(const sf::Color &color);
    void SetPosition(const sf::Vector2f &pos);
    void SetSize(const sf::Vector2f &size);
    void Draw(sf::RenderWindow &window);
    void UpdateState(sf::RenderWindow &window);
};

#endif // MENUSIDEBAR_H
