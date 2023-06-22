#include "MenuSideBar.hpp"

SideBar::SideBar(){}

SideBar::SideBar(const sf::Vector2f &ini_pos, const sf::Vector2f &size, const sf::Color &color){
    Bar.setPosition(ini_pos);
    Bar.setFillColor(color);
    Bar.setSize(size);
}

void SideBar::SetOutColor(const sf::Color &color){
    Bar.setFillColor(color);
}

void SideBar::SetPosition(const sf::Vector2f &pos){
    Bar.setPosition(pos);
}

void SideBar::SetSize(const sf::Vector2f &size){
    Bar.setSize(size);
}

void SideBar::Draw(sf::RenderWindow &window){
    window.draw(Bar);
}

void SideBar::UpdateState(sf::RenderWindow &window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f cursorPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    cursorPos = window.mapPixelToCoords(mousePos);
    if (Bar.getGlobalBounds().contains(cursorPos)){
        if (IsOpen==false){
            Bar.setFillColor(sf::Color(0,173,181));
            Bar.setSize(sf::Vector2f(Bar.getSize().x * 2, Bar.getSize().y));
            IsOpen = true;
        }
    }
    else{
        if (IsOpen){
            Bar.setFillColor(sf::Color(57,62,70));
            Bar.setSize(sf::Vector2f(Bar.getSize().x * 0.5, Bar.getSize().y));
            IsOpen = false;
        }
    }
}
