#include "SearchScreen.hpp"

SearchScreen::SearchScreen(){
    _font.loadFromFile("Font/BeVietnamPro-Regular.ttf");
    keyField.SetProperties(_font,30,c4,120,425,590,70,true);
    defField.SetProperties(_font,30,c4,120+590+50,425,590,70,true);

    SubTit1.setString("Search for keyword");
    SubTit1.setCharacterSize(50);
    SubTit1.setPosition(120+30,300);
    SubTit1.setFillColor(c4);
    SubTit1.setOutlineColor(c3);
    SubTit1.setOutlineThickness(0.5);
    SubTit1.setFont(_font);

    SubTit2.setString("Search for definition");
    SubTit2.setCharacterSize(50);
    SubTit2.setPosition(120+590+50+30,300);
    SubTit2.setFillColor(c4);
    SubTit2.setOutlineColor(c3);
    SubTit2.setOutlineThickness(0.5);
    SubTit2.setFont(_font);
}

int SearchScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){
    keyField.handleEvent(App,event);
    defField.handleEvent(App,event);
    return 1;
}

void SearchScreen::ScreenDraw(sf::RenderWindow &App){
    keyField.draw(App);
    defField.draw(App);
    App.draw(SubTit1);
    App.draw(SubTit2);
}

void SearchScreen::updateScene(sf::Time &deltaTime){
    keyField.update(deltaTime);
    defField.update(deltaTime);
}
