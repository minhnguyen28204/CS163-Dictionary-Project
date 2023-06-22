#include "MainFunction.hpp"

Dictionary::Dictionary()
: mWindow(sf::VideoMode(1280,720),"Dictionary")
{
    MenuBar.SetOutColor(sf::Color(57,62,70));
    MenuBar.SetPosition(sf::Vector2f(0,100));
    MenuBar.SetSize(sf::Vector2f(75,520));
}

void Dictionary::run(){
    while (mWindow.isOpen()){
        processEvent();
        update();
        render();
    }
}

void Dictionary::processEvent(){
    sf::Event event;
    while (mWindow.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            mWindow.close();
        }
    }
}

void Dictionary::update(){
    MenuBar.UpdateState(mWindow);
}

void Dictionary::render(){
    mWindow.clear(sf::Color(34,40,49));
    MenuBar.Draw(mWindow);
    mWindow.display();
}
