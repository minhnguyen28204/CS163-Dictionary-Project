#include "MenuSideBar.hpp"
#include <iostream>

SideBar::SideBar(){}

SideBar::SideBar(const sf::Vector2f &ini_pos, const sf::Vector2f &size, const sf::Color &color){
    Bar.setPosition(ini_pos);
    Bar.setFillColor(color);
    Bar.setSize(size);
}

void SideBar::AddButton(const string &path, const string &name){
    sf::Texture object;
    if (!object.loadFromFile(path)){
        cout << "Cannot find the path!!!\n";
    }
    MyTexture.push_back(object);
    sf::Sprite Icon;
    Icon.setTexture(MyTexture.back());
    Icon.scale(sf::Vector2f(0.5f,0.5f));
    int Size = MyIcon.size();
    Icon.setPosition(sf::Vector2f(10,110+Size*50));
    sf::RectangleShape Button;
    Button.setPosition(sf::Vector2f(100,110+Size*50));
    Button.setSize(sf::Vector2f(250,50));
    Button.setFillColor(sf::Color(34,40,49));
    Button.setOutlineColor(sf::Color(57,62,70));
    Button.setOutlineThickness(5.0f);
    button.push_back(Button);
    MyIcon.push_back(Icon);
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
    for(auto &x : MyIcon){
        window.draw(x);
    }
    if (IsOpen){
        for(auto &x : button){
            window.draw(x);
        }
    }
}

void SideBar::UpdateState(sf::RenderWindow &window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f cursorPos(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    cursorPos = window.mapPixelToCoords(mousePos);
    if (Bar.getGlobalBounds().contains(cursorPos)){
        if (IsOpen==false){
            Bar.setFillColor(sf::Color(0,173,181));
            Bar.setSize(sf::Vector2f(Bar.getSize().x * 4, Bar.getSize().y));
            IsOpen = true;
        }
    }
    else{
        if (IsOpen){
            Bar.setFillColor(sf::Color(57,62,70));
            Bar.setSize(sf::Vector2f(Bar.getSize().x * 0.25, Bar.getSize().y));
            IsOpen = false;
        }
    }
}
