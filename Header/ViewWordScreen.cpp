#include "ViewWordScreen.hpp"
#include <iostream>
#include <sstream>

using namespace std;

WordScreen::WordScreen(void){
    _font.loadFromFile("Font/BeVietnamPro-Regular.ttf");
    KeyWord.setPosition(100,100);
    KeyWord.setCharacterSize(30);
    KeyWord.setFont(_font);
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
    App.draw(KeyWord);
    for(int i=0; i<Def.size(); i++) App.draw(Def[i]);
}

int WordScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){
    float maxWidth = App.getSize().x - 300;
    if (loadWord){
        Def.clear();
        wstring tmp = L"";
        int cnt = 0;
        for(int i=0; i<MyDef.size(); i++){
            if (MyDef[i]!=L'|') tmp += MyDef[i];
            else{
                sf::Text Def_i;
                Def_i.setPosition(100,150+cnt);
                Def_i.setCharacterSize(20);
                Def_i.setFont(_font);
                Def_i.setString(tmp);
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
    return 7;
}

void WordScreen::updateScene(sf::Time &deltaTime){

}

void WordScreen::setString(wstring _def, wstring _key){
    MyDef = _def;
    if (_def.size() == 0) is_found = false;
    else is_found = true;
    KeyWord.setString(_key);
    loadWord = true;
}
