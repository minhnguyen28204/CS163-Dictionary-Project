#include "ViewWordScreen.hpp"
#include <iostream>
#include <sstream>

using namespace std;

WordScreen::WordScreen(void){
    _font.loadFromFile("Font/BeVietnamPro-Regular.ttf");
    KeyWord.setPosition(100,100);
    KeyWord.setCharacterSize(30);
    KeyWord.setFont(_font);
    KeyWord.setFillColor(c4);
    Header.setPosition(70,0);
    Header.setSize(sf::Vector2f(1330,150));
    Header.setFillColor(c1);
}

void wrapText(sf::Text& text, float maxWidth) {
    std::wstring textString = text.getString();
    std::wstringstream ss(textString);
    std::wstring line;
    std::wstring wrappedText;

    sf::Font font = *text.getFont();
    unsigned int characterSize = text.getCharacterSize();

    while (std::getline(ss, line, L'\n')) {
        sf::Text lineText(line, font, characterSize);
        sf::FloatRect lineBounds = lineText.getLocalBounds();
        float lineWidth = lineBounds.width;

        if (lineWidth <= maxWidth) {
            wrappedText += line + L"\n";
        } else {
            std::wstring word;
            std::wstringstream wordStream(line);
            while (wordStream >> word) {
                sf::Text wordText(word, font, characterSize);
                sf::FloatRect wordBounds = wordText.getLocalBounds();
                float wordWidth = wordBounds.width;

                if (lineWidth + wordWidth > maxWidth) {
                    wrappedText += L"\n" + word + L" ";
                    lineWidth = wordWidth;
                } else {
                    wrappedText += word + L" ";
                    lineWidth += wordWidth;
                }
            }
            wrappedText += L"\n";
        }
    }

    text.setString(wrappedText);
}

void WordScreen::ScreenDraw(sf::RenderWindow &App){
    for(int i=0; i<Def.size(); i++){
        App.draw(Def[i]);
    }
    App.draw(Header);
    App.draw(KeyWord);
}

int WordScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){
    float maxWidth = App.getSize().x - 300;
    if (loadWord){
        Def.clear();
        wstring tmp = L"";
        int cnt = 150;
        for(int i=0; i<MyDef.size(); i++){
            if (MyDef[i]!=L'|') tmp += MyDef[i];
            else{
                sf::Text Def_i;
                Def_i.setPosition(100,cnt);
                Def_i.setCharacterSize(20);
                Def_i.setFont(_font);
                Def_i.setString(tmp);
                Def_i.setFillColor(c4);
                wrapText(Def_i,maxWidth);
                Def.push_back(std::move(Def_i));
                cnt += Def_i.getGlobalBounds().height + 5;
                tmp = L"";
                cnt++;
            }
        }
        loadWord = false;
    }
    if (is_found == false){
        sf::Text Def_i;
        Def_i.setPosition(100,150);
        Def_i.setCharacterSize(20);
        Def_i.setFont(_font);
        Def_i.setString(L"Not found");
        wrapText(Def_i,maxWidth);
        Def.push_back(std::move(Def_i));
    }
    if (event.type == sf::Event::MouseWheelScrolled || (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))){
        if (Def.size()){
            float delta = 0;
            if (event.type == sf::Event::MouseWheelScrolled) delta = event.mouseWheelScroll.delta;
            else if (event.key.code == sf::Keyboard::Up) delta = 1;
            else delta = -1;

            if (delta < 0 && Def[Def.size()-1].getPosition().y + Def[Def.size()-1].getGlobalBounds().height > 850){
                cout << Def[Def.size()-1].getPosition().y << '\n';
                for(int i=0; i<Def.size(); i++){
                    Def[i].setPosition(Def[i].getPosition().x,Def[i].getPosition().y + delta*20);
                }
            }
            if (delta > 0 && Def[0].getPosition().y < 150){
                for(int i=0; i<Def.size(); i++){
                    Def[i].setPosition(Def[i].getPosition().x,Def[i].getPosition().y + delta*20);
                }
            }
        }
    }
    return 7;
}

void WordScreen::updateScene(sf::Time &deltaTime){

}

void WordScreen::SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4){
    c1 = f1;
    c2 = f2;
    c3 = f3;
    c4 = f4;
    for(auto &x : Def) x.setFillColor(c4);
    KeyWord.setFillColor(c4);
    Header.setFillColor(c1);
}

void WordScreen::setString(wstring _def, wstring _key){
    MyDef = _def;
    if (_def.size() == 0) is_found = false;
    else is_found = true;
    KeyWord.setString(_key);
    loadWord = true;
}
