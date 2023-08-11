#ifndef MENUSIDEBAR_H
#define MENUSIDEBAR_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

class SideBar{
private:
    sf::RectangleShape Bar;
    vector<sf::Texture> MyTexture;
    vector<sf::Sprite> MyIcon;
    vector<sf::RectangleShape> button;
    bool IsOpen = false;
public:
    SideBar();
    SideBar(const sf::Vector2f &ini_pos, const sf::Vector2f &size, const sf::Color &color);
    void AddButton(const string &path, const string &name);
    void SetOutColor(const sf::Color &color);
    void SetPosition(const sf::Vector2f &pos);
    void SetSize(const sf::Vector2f &size);
    void Draw(sf::RenderWindow &window);
    void UpdateState(sf::RenderWindow &window);
};

#endif // MENUSIDEBAR_H
