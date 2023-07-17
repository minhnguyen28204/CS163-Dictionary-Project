#include "HomeScreen.hpp"
#include <iostream>

HomeScreen::HomeScreen(void){
    _font.loadFromFile("Font/BeVietnamPro-Regular.ttf");

    object.loadFromFile("Image/Dictionary_Pic.png");
    Image.setTexture(object);

    enter_object.loadFromFile("Image/enter_search.png");
    enter_image.setTexture(enter_object);
    enter_image.setPosition(sf::Vector2f(1200,150));
    enter_bound.setPosition(sf::Vector2f(1200,150));
    enter_bound.setSize(sf::Vector2f(75,75));
    enter_bound.setFillColor(c2);

    //150, 150
    //1140 75
    inputField.SetProperties(_font,35,sf::Color(238,238,238),150,150,1000,75,true);

    RandomWord.setPosition(120,280);
    RandomWord.setSize(sf::Vector2f(590,100));
    RandomWord.setFillColor(c2);
    ranw.setString("Random word a day!");
    ranw.setPosition(243,310);
    ranw.setFont(_font);
    ranw.setCharacterSize(35);
    ranw.setFillColor(c4);

    Image.setPosition(800,200);

    HistoryWord.setPosition(sf::Vector2f(120,655));
    HistoryWord.setSize(sf::Vector2f(590,100));
    HistoryWord.setFillColor(c2);
    hisw.setString("History");
    hisw.setPosition(356,685);
    hisw.setFont(_font);
    hisw.setCharacterSize(35);
    hisw.setFillColor(c4);

    FavoriteWord.setPosition(120,405);//550
    FavoriteWord.setSize(sf::Vector2f(590,100));
    FavoriteWord.setFillColor(c2);
    favw.setString("Favourite words");
    favw.setPosition(279,435);//580
    favw.setFont(_font);
    favw.setCharacterSize(35);
    favw.setFillColor(c4);

    Quiz.setPosition(120,530);
    Quiz.setSize(sf::Vector2f(590,100));
    Quiz.setFillColor(c2);
    quizw.setString("Quiz");
    quizw.setPosition(380,560);
    quizw.setFont(_font);
    quizw.setCharacterSize(35);
    quizw.setFillColor(c4);

    MyButton.push_back(Quiz);
    MyButton.push_back(FavoriteWord);
    MyButton.push_back(HistoryWord);
    MyButton.push_back(RandomWord);
}

int HomeScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){
    inputField.handleEvent(App,event);
    sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
    for(int i=0; i<4; i++){
        auto &x = MyButton[i];
        sf::FloatRect ShapeBound = x.getGlobalBounds();
        bool isMousedOn = ShapeBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        if (isMousedOn){
            x.setFillColor(c3);
        }
        else{
            x.setFillColor(c2);
        }
    }
    sf::FloatRect enterBound = enter_bound.getGlobalBounds();
    bool isMousedOn = enterBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    if (isMousedOn){
        enter_bound.setFillColor(c3);
    }
    else{
        enter_bound.setFillColor(c2);
    }
    return 0;
}

void HomeScreen::ScreenDraw(sf::RenderWindow &App){
    for(auto &x : MyButton) App.draw(x);
    App.draw(ranw);
    App.draw(hisw);
    App.draw(favw);
    App.draw(quizw);
    App.draw(Image);
    App.draw(enter_bound);
    App.draw(enter_image);
    inputField.draw(App);
}

void HomeScreen::updateScene(sf::Time &deltaTime){
    inputField.update(deltaTime);
}
