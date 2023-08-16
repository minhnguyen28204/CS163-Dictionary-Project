#include "SearchScreen.hpp"

SearchScreen::SearchScreen(){
    _font.loadFromFile("Font/BeVietnamPro-Regular.ttf");
    defField.SetProperties(_font,30,c4,150,150,1000,50,true);

    SubTit2.setString("Search for keyword");
    SubTit2.setCharacterSize(30);
    SubTit2.setPosition(150,100);
    SubTit2.setFillColor(c4);
    SubTit2.setFont(_font);
}

int SearchScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){
    defField.handleEvent(App,event);

    if (MyDef != defField.getText()){
        suggestBox.clear();
        outlineBox.clear();
        numberBox.clear();
        MyDef = defField.getText();
        if (MyDef.size()!=0){
            recommendString = DefinitionSet::allDefinitionContain(MyDef);
            while (recommendString.size()>20) recommendString.pop_back();
            l = 0, r = min(7,(int)recommendString.size())-1;
            int cnt = 0;
            for(int i = 0; i < min(7,(int)recommendString.size()); i++){
                wstring word = Character::stringToWString(recommendString[i]);
                sf::Text word_i;
                sf::Text numb_i;

                numb_i.setFont(_font);
                numb_i.setCharacterSize(30);
                numb_i.setString(to_string(i+1) + ".");
                numb_i.setFillColor(c4);
                numb_i.setPosition(160,210+cnt*75);

                word_i.setFont(_font);
                word_i.setCharacterSize(30);
                word_i.setString(word);
                word_i.setFillColor(c4);
                word_i.setPosition(160 + numb_i.getLocalBounds().width + 5,210+cnt*75);

                sf::RectangleShape outline_i;
                outline_i.setPosition(150,200+cnt*75);
                outline_i.setSize(sf::Vector2f(1000,75));
                outline_i.setFillColor(c2);
                cnt++;

                numberBox.push_back(std::move(numb_i));
                suggestBox.push_back(std::move(word_i));
                outlineBox.push_back(std::move(outline_i));
            }
        }
    }

    if (defField.cur_state() && suggestBox.size()){
		if (event.type == sf::Event::MouseWheelScrolled || (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))){
            float delta = 0;
            if (event.type == sf::Event::MouseWheelScrolled) delta = event.mouseWheelScroll.delta;
            else if (event.key.code == sf::Keyboard::Up) delta = 1;
            else delta = -1;
            if (delta > 0 && l > 0){
                l--;
                r--;
                int i = l;
                for(int idx = 0; idx < suggestBox.size(); idx++, i++){
                    wstring tmp = Character::stringToWString(recommendString[i]);
                    suggestBox[idx].setString(tmp);
                    numberBox[idx].setString(to_string(i+1) + ".");
                    suggestBox[idx].setPosition(160 + numberBox[idx].getLocalBounds().width + 5, suggestBox[idx].getPosition().y);
                }
            }
            if (delta < 0 && r < recommendString.size()-1){
                l++;
                r++;
                int i = l;
                for(int idx = 0; idx < suggestBox.size(); idx++, i++){
                    wstring tmp = Character::stringToWString(recommendString[i]);
                    suggestBox[idx].setString(tmp);
                    numberBox[idx].setString(to_string(i+1) + ".");
                    suggestBox[idx].setPosition(160 + numberBox[idx].getLocalBounds().width + 5, suggestBox[idx].getPosition().y);
                }
            }
		}
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
    for(int i=0; i<outlineBox.size(); i++){
        auto &x = outlineBox[i];
        sf::FloatRect ShapeBound = x.getGlobalBounds();
        bool isMousedOn = ShapeBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        if (isMousedOn){
            x.setFillColor(c3);
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                wstring Cur_str = suggestBox[i].getString();
                wstring Definition = Character::stringToWString(WordSet::definition(Cur_str));
                MyDef = Definition;
                MyKey = Cur_str;
                is_search = true;
                return 7;
            }
        }
        else{
            x.setFillColor(c2);
            x.setOutlineThickness(0);
        }
    }

    return 1;
}

void SearchScreen::ScreenDraw(sf::RenderWindow &App){
    defField.draw(App);
    App.draw(SubTit2);
    if (suggestBox.size() && defField.cur_state()){
        for(int i=0; i<outlineBox.size(); i++) App.draw(outlineBox[i]);
        for(int i=0; i<numberBox.size(); i++) App.draw(numberBox[i]);
        for(int i=0; i<suggestBox.size(); i++) App.draw(suggestBox[i]);
    }
}

void SearchScreen::updateScene(sf::Time &deltaTime){
    defField.update(deltaTime);
}

void SearchScreen::SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4){
    c1 = f1; c2 = f2; c3 = f3; c4 = f4;
    SubTit2.setFillColor(c4);
    for(auto &x : suggestBox) x.setFillColor(c4);
}
