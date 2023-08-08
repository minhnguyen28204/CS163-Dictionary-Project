#include "AddScreen.hpp"

AddScreen::AddScreen(void){
    _font.loadFromFile("Font/BeVietnamPro-Regular.ttf");

    boder.setSize(sf::Vector2f(1400,260));
    boder.setFillColor(c2);

    Title.setFont(_font);
    Title.setString("Add a word");
    Title.setCharacterSize(30);
    Title.setFillColor(c4);
    Title.setPosition(150,150);

    keyText.setFont(_font);
    keyText.setString("Word:");
    keyText.setFillColor(c4);
    keyText.setCharacterSize(25);
    keyText.setPosition(150,210);

    keyInput.SetProperties(_font,25,c4,250,200,950,50,true);

    okWord.setPosition(1250,200);
    okWord.setSize(sf::Vector2f(100,50));
    okWord.setFillColor(c1);

    okTest.setString("Add");
    okTest.setFont(_font);
    okTest.setCharacterSize(25);
    okTest.setFillColor(c4);
    okTest.setPosition(1250 + (100 - okTest.getLocalBounds().width)/2, 200 + (50 - okTest.getLocalBounds().height)/4);

    addDef.setPosition(150,300);
    addDef.setSize(sf::Vector2f(240,45));
    addDef.setFillColor(c2);

    delDef.setFillColor(c2);
    delDef.setSize(sf::Vector2f(100,45));

    addText.setFont(_font);
    addText.setString("Add new definition");
    addText.setCharacterSize(25);
    addText.setFillColor(c4);
    addText.setPosition(155,305);

    delText.setFont(_font);
    delText.setString("Delete");
    delText.setCharacterSize(25);
    delText.setFillColor(c4);
}

int AddScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){
    keyInput.handleEvent(App,event);
    for(int i=0; i<defInput.size(); i++){
        defInput[i].handleEvent(App,event);
    }

    if (event.type == sf::Event::MouseWheelScrolled || (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))){
        if (defInput.size()){
            float delta = 0;
            if (event.type == sf::Event::MouseWheelScrolled) delta = event.mouseWheelScroll.delta;
            else if (event.key.code == sf::Keyboard::Up) delta = 1;
            else delta = -1;

            if (delta < 0 && addDef.getPosition().y + 55 > 850){
                for(int i=0; i<defInput.size(); i++){
                    defInput[i].setPosition(defInput[i].getPosition().first, defInput[i].getPosition().second + delta*20);
                }
                addDef.setPosition(addDef.getPosition().x,addDef.getPosition().y + delta*20);
                delDef.setPosition(delDef.getPosition().x,delDef.getPosition().y + delta*20);
                addText.setPosition(addText.getPosition().x,addText.getPosition().y + delta*20);
                delText.setPosition(delText.getPosition().x,delText.getPosition().y + delta*20);
            }
            if (delta > 0 && defInput[0].getPosition().second < 300){
                for(int i=0; i<defInput.size(); i++){
                    defInput[i].setPosition(defInput[i].getPosition().first, defInput[i].getPosition().second + delta*20);
                }
                addDef.setPosition(addDef.getPosition().x,addDef.getPosition().y + delta*20);
                delDef.setPosition(delDef.getPosition().x,delDef.getPosition().y + delta*20);
                addText.setPosition(addText.getPosition().x,addText.getPosition().y + delta*20);
                delText.setPosition(delText.getPosition().x,delText.getPosition().y + delta*20);
            }
        }
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
    sf::FloatRect shape = addDef.getGlobalBounds();
    bool isMousedOn = shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    if (isMousedOn){
        addDef.setFillColor(c3);
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            TextField newField;
            newField.SetProperties(_font,25,c4,150,addDef.getPosition().y,905,50,true);
            defInput.push_back(newField);
            delDef.setPosition(1100,addDef.getPosition().y);
            delText.setPosition(1105,addDef.getPosition().y+5);
            addDef.setPosition(addDef.getPosition().x,addDef.getPosition().y+100);
            addText.setPosition(addText.getPosition().x,addText.getPosition().y+100);
        }
    }
    else{
        addDef.setFillColor(c2);
    }
    shape = delDef.getGlobalBounds();
    isMousedOn = shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    if (isMousedOn){
        delDef.setFillColor(c3);
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            defInput.pop_back();
            float y = 0;
            if (defInput.size()) y = defInput[defInput.size()-1].getPosition().second;
            else y = 200;
            addDef.setPosition(150,y+100);
            addText.setPosition(155,y+105);
            delDef.setPosition(1100,y);
            delText.setPosition(1105,y+5);
        }
    }
    else{
        delDef.setFillColor(c2);
    }
    shape = okWord.getGlobalBounds();
    isMousedOn = shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    if (isMousedOn){
        okWord.setFillColor(c3);
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            wstring def = L"";
            wstring key = keyInput.getText();
            if (key.size() && defInput.size()){
                for(int i=0; i<defInput.size(); i++){
                    def += defInput[i].getText();
                    def += L"|";
                }
                WordSet::addNew(key,def);
                defInput.clear();
                keyInput.SetIniStr(L"");
                addDef.setPosition(150,300);
                addText.setPosition(155,305);
            }
            else{
                sf::RectangleShape outBox;
                outBox.setPosition(300,375);
                outBox.setSize(sf::Vector2f(800,100));
                outBox.setFillColor(c3);
                sf::Text errorText;
                errorText.setFont(_font);
                errorText.setCharacterSize(40);
                errorText.setString("Missing key word or definition! Try again.");
                errorText.setPosition(300 + (800 - errorText.getLocalBounds().width)/2, 375 + (100 - errorText.getLocalBounds().height)/4);
                errorText.setFillColor(c4);
                App.draw(outBox);
                App.draw(errorText);
                App.display();
                sf::sleep(sf::seconds(1.5));
            }
        }
    }
    else{
        okWord.setFillColor(c1);
    }
    return 4;
}

void AddScreen::ScreenDraw(sf::RenderWindow &App){
    if (defInput.size()) App.draw(delDef), App.draw(delText);
    for(int i=0; i<defInput.size(); i++){
        defInput[i].draw(App);
    }
    App.draw(boder);
    App.draw(Title); App.draw(keyText);
    App.draw(okWord);
    App.draw(okTest);
    App.draw(addDef);
    App.draw(addText);
    keyInput.draw(App);
}

void AddScreen::updateScene(sf::Time &deltaTime){
    keyInput.update(deltaTime);
    for(int i=0; i<defInput.size(); i++){
        defInput[i].update(deltaTime);
    }
}

void AddScreen::SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4){
    c1 = f1; c2 = f2; c3 = f3; c4 = f4;
    boder.setFillColor(c2);
    Title.setFillColor(c4);
    keyText.setFillColor(c4);
    okTest.setFillColor(c4);
    addText.setFillColor(c4);
    delText.setFillColor(c4);
}
