#include "HomeScreen.hpp"
#include <iostream>
#include <string>
using namespace std;

HomeScreen::HomeScreen(void)
{
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
    inputField.SetProperties(_font,35,c4,150,150,1000,75,true);

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

    if (MyKey != inputField.getText()){
        if (Path::curPath == 0) WordSet::loadAllData();
        suggestBox.clear();
        outlineBox.clear();
        MyKey = inputField.getText();
        if (MyKey.size()!=0){
            vector<string> temp = WordSet::displayWordTree(MyKey,5);
            int cnt = 0;
            for(auto t : temp){
                wstring word = Character::stringToWString(t);
                sf::Text word_i;
                word_i.setFont(_font);
                word_i.setCharacterSize(30);
                word_i.setString(word);
                word_i.setFillColor(c4);
                word_i.setPosition(160,235+cnt*75);
                sf::RectangleShape outline_i;
                outline_i.setPosition(150,225+cnt*75);
                outline_i.setSize(sf::Vector2f(1000,75));
                outline_i.setFillColor(c2);
                cnt++;
                suggestBox.push_back(std::move(word_i));
                outlineBox.push_back(std::move(outline_i));
            }
        }
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
    if (inputField.cur_state() || (inputField.cur_state()==false && previous_state==true)){
        for(int i=0; i<outlineBox.size(); i++){
            auto &x = outlineBox[i];
            sf::FloatRect ShapeBound = x.getGlobalBounds();
            bool isMousedOn = ShapeBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            if (isMousedOn){
                x.setFillColor(c3);
                x.setOutlineThickness(1);
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    wstring Cur_str = suggestBox[i].getString();
                    wstring Definition = Character::stringToWString(WordSet::definition(Cur_str));
                    string tmp = Character::backToString(Cur_str);
                    saveWordToTextFile(tmp);
                    MyKey = Cur_str;
                    MyDef = Definition;
                    is_search = true;
                    return 7;
                }
            }
            else{
                x.setFillColor(c2);
                x.setOutlineThickness(0);
            }
        }
        previous_state = inputField.cur_state();
    }
    else {
        int MyMap[4] = {5,3,2,7};
        for(int i=0; i<4; i++){
            auto &x = MyButton[i];
            sf::FloatRect ShapeBound = x.getGlobalBounds();
            bool isMousedOn = ShapeBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            if (isMousedOn){
                x.setFillColor(c3);
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    if (MyMap[i]==7){
                        wstring Cur_str = Character::stringToWString(randomWordFromFile());
                        wstring Definition = Character::stringToWString(WordSet::definition(Cur_str));
                        MyKey = Cur_str;
                        MyDef = Definition;
                        string tmp = Character::backToString(Cur_str);
                        saveWordToTextFile(tmp);
                        is_search = true;
                    }
                    return MyMap[i];
                }
            }
            else{
                x.setFillColor(c2);
            }
        }
    }

    //process when pressing the glass icon
    sf::FloatRect enterBound = enter_bound.getGlobalBounds();
    bool isMousedOn = enterBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    if (isMousedOn){
        enter_bound.setFillColor(c3);
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            wstring Cur_str = inputField.getText();
            wstring Definition = Character::stringToWString(WordSet::definition(Cur_str));
            string tmp = Character::backToString(Cur_str);
            saveWordToTextFile(tmp);
            MyKey = Cur_str;
            MyDef = Definition;
            is_search = true;
            return 7;
        }
    }
    else{
        enter_bound.setFillColor(c2);
        is_search = false;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter){
        wstring Cur_str = inputField.getText();
        wstring Definition = Character::stringToWString(WordSet::definition(Cur_str));
        string tmp = Character::backToString(Cur_str);
        saveWordToTextFile(tmp);
        MyKey = Cur_str;
        MyDef = Definition;
        is_search = true;
        return 7;
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
    if (suggestBox.size() && inputField.cur_state()){
        for(int i=0; i<outlineBox.size(); i++) App.draw(outlineBox[i]);
        for(int i=0; i<suggestBox.size(); i++) App.draw(suggestBox[i]);
    }
}

void HomeScreen::updateScene(sf::Time &deltaTime){
    inputField.update(deltaTime);
}

void HomeScreen::SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4){
    c1 = f1;
    c2 = f2;
    c3 = f3;
    c4 = f4;
    ranw.setFillColor(c4);
    hisw.setFillColor(c4);
    favw.setFillColor(c4);
    quizw.setFillColor(c4);
    if (c4 == sf::Color(238,238,238)) enter_object.loadFromFile("Image/enter_search.png");
    else enter_object.loadFromFile("Image/enter_search - Copy.png");
}
