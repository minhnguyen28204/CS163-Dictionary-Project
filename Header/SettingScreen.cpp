#include "SettingScreen.hpp"
using namespace std;

SettingScreen::SettingScreen(void){
    _font.loadFromFile("Font/BeVietnamPro-Regular.ttf");
    int curSet;
    ifstream ifs("Data/OldSettings.txt");
    ifs >> curSet;
    ifs.close();

    dataSet.setString("Data set");
    dataSet.setPosition(150,100);
    dataSet.setFont(_font);
    dataSet.setCharacterSize(35);

    semo.setPosition(sf::Vector2f(150,150));
    semo.setRadius(16);
    emoticon.setString("Emoji");
    emoticon.setFont(_font);
    emoticon.setPosition(190,147);
    emoticon.setCharacterSize(30);

    ssla.setPosition(sf::Vector2f(150,200));
    ssla.setRadius(16);
    slang.setString("Slang");
    slang.setFont(_font);
    slang.setPosition(190,197);
    slang.setCharacterSize(30);

    seen.setPosition(sf::Vector2f(150,250));
    seen.setRadius(16);
    engToEng.setString("English to English");
    engToEng.setFont(_font);
    engToEng.setPosition(190,247);
    engToEng.setCharacterSize(30);

    sevi.setPosition(sf::Vector2f(150,300));
    sevi.setRadius(16);
    engToVie.setString("English to Vietnamese");
    engToVie.setFont(_font);
    engToVie.setPosition(190,297);
    engToVie.setCharacterSize(30);

    sven.setPosition(sf::Vector2f(150,350));
    sven.setRadius(16);
    vieToEng.setString("Vietnamese to English");
    vieToEng.setFont(_font);
    vieToEng.setPosition(190,347);
    vieToEng.setCharacterSize(30);

    selected.setRadius(10);
    selected.setPosition(sf::Vector2f(156,156 + curSet*50));
    selected.setFillColor(sf::Color::Black);

    myShape.push_back(semo);
    myShape.push_back(ssla);
    myShape.push_back(seen);
    myShape.push_back(sevi);
    myShape.push_back(sven);
    myText.push_back(emoticon);
    myText.push_back(slang);
    myText.push_back(engToEng);
    myText.push_back(engToVie);
    myText.push_back(vieToEng);
}

void SettingScreen::ScreenDraw(sf::RenderWindow &App){
    App.draw(dataSet);
    for(auto x : myShape) App.draw(x);
    for(auto x : myText) App.draw(x);
    App.draw(selected);
}

int SettingScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
    for(int i=0; i<myShape.size(); i++){
        sf::CircleShape x = myShape[i];
        sf::FloatRect ShapeBound = x.getGlobalBounds();
        bool isMousedOn = ShapeBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        if (isMousedOn){
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                WordSet::switchWordSet(i);
                selected.setPosition(x.getPosition().x+6,x.getPosition().y+6);
                ofstream ofs("Data/OldSettings.txt");
                ofs << i;
                ofs.close();
            }
        }
    }
    return 6;
}

void SettingScreen::updateScene(sf::Time &deltaTime){

}
