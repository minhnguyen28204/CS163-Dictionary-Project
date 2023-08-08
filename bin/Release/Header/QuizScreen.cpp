#include "QuizScreen.hpp"

void QuizScreen::wrapText(sf::Text& text, float maxWidth) {
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

QuizScreen::QuizScreen(){
    is_game = false;
    state_reset = true;
    _font.loadFromFile("Font/BeVietnamPro-Regular.ttf");

    back_button.setSize(sf::Vector2f(50,50));
    back_button.setPosition(80,10);
    back_button.setFillColor(c2);
    tback_button.setCharacterSize(12);
    tback_button.setString("Back");
    tback_button.setFont(_font);
    tback_button.setFillColor(c4);
    tback_button.setPosition(90,23);

    w1.setFont(_font); w1.setCharacterSize(25); w1.setFillColor(c4);
    w2.setFont(_font); w2.setCharacterSize(25); w2.setFillColor(c4);
    w3.setFont(_font); w3.setCharacterSize(25); w3.setFillColor(c4);
    w4.setFont(_font); w4.setCharacterSize(25); w4.setFillColor(c4);
    d1.setFont(_font); d1.setCharacterSize(25); d1.setFillColor(c4);
    d2.setFont(_font); d2.setCharacterSize(25); d2.setFillColor(c4);
    d3.setFont(_font); d3.setCharacterSize(25); d3.setFillColor(c4);
    d4.setFont(_font); d4.setCharacterSize(25); d4.setFillColor(c4);
    d1.setPosition(100,100);
    d2.setPosition(100,100);
    d3.setPosition(100,100);
    d4.setPosition(100,100);


    wordDef.loadFromFile("Image/QuizIcon.png");
    swordDef.setTexture(wordDef);
    swordDef.setPosition(180,200);
    mySprite.push_back(swordDef);
    bound_wordDef.setSize(sf::Vector2f(520,520));
    bound_wordDef.setPosition(170,190);
    bound_wordDef.setFillColor(c1);
    myBound.push_back(bound_wordDef);

    defWord.loadFromFile("Image/QuizIcon2.png");
    sdefWord.setTexture(defWord);
    sdefWord.setPosition(790,200);
    mySprite.push_back(sdefWord);
    bound_defWord.setSize(sf::Vector2f(520,520));
    bound_defWord.setPosition(780,190);
    bound_defWord.setFillColor(c1);
    myBound.push_back(bound_defWord);

    q1.setSize(sf::Vector2f(590,150));
    q1.setPosition(120,350);
    q1.setFillColor(c2);

    q2.setSize(sf::Vector2f(590,150));
    q2.setPosition(760,350);
    q2.setFillColor(c2);

    q3.setSize(sf::Vector2f(590,150));
    q3.setPosition(120,550);
    q3.setFillColor(c2);

    q4.setSize(sf::Vector2f(590,150));
    q4.setPosition(760,550);
    q4.setFillColor(c2);

    myBound.push_back(q1);
    myBound.push_back(q2);
    myBound.push_back(q3);
    myBound.push_back(q4);
}

void QuizScreen::ScreenDraw(sf::RenderWindow &App){
    if (!is_game){
        for(int i=0; i<2; i++) App.draw(myBound[i]);
        for(int i=0; i<2; i++) App.draw(mySprite[i]);
    }
    else{
        App.draw(back_button);
        App.draw(tback_button);
        for(int i=2; i<6; i++) App.draw(myBound[i]);
        App.draw(w1); App.draw(w2); App.draw(w3); App.draw(w4);
        if (selected==0) App.draw(d1);
        if (selected==1) App.draw(d2);
        if (selected==2) App.draw(d3);
        if (selected==3) App.draw(d4);
    }
}

void SetCenter(sf::Text &myText, sf::RectangleShape &myBound){
    sf::FloatRect textBound = myText.getGlobalBounds();
    float textX = myBound.getPosition().x + (myBound.getSize().x - textBound.width) / 2;
    float textY = myBound.getPosition().y + (myBound.getSize().y - textBound.height) / 2;
    myText.setPosition(textX, textY);
}

int QuizScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
    srand(time(0));
    if (!is_game){
        for(int i=0; i<2; i++){
            auto &x = myBound[i];
            sf::FloatRect ShapeBound = x.getGlobalBounds();
            bool isMousedOn = ShapeBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            if (isMousedOn){
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    is_game = true;
                    if (i==0) is_def = true;
                    else is_def = false;
                }
                x.setFillColor(c3);
            }
            else{
                x.setFillColor(c1);
            }
        }
    }
    else{
        sf::FloatRect bacbut_bound = back_button.getGlobalBounds();
        bool isOn = bacbut_bound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        if (isOn){
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                is_game = false;
                state_reset = true;
            }
            back_button.setFillColor(c3);
        }
        else{
            back_button.setFillColor(c2);
        }
        if (state_reset){

            //Get 4 random strings here
            vector<string> myString;
            string temp;
            wstring def_temp;
            int cnt = 0;
            while (cnt < 4){
                temp = randomWordFromFile();
                bool ok = true;
                for(int i=0; i<myString.size(); i++) if (temp == myString[i]) ok = false;
                if (ok){
                    myString.push_back(temp);
                    cnt++;
                }
            }
            sw1 = Character::stringToWString(myString[0]);
            def_temp = Character::stringToWString(WordSet::definition(sw1));
            for(int i=0; i<def_temp.size(); i++){
                if (def_temp[i]==L'|'){
                    int lef = def_temp.size() - i;
                    def_temp.erase(i,lef);
                }
            }
            sd1 = def_temp;

            sw2 = Character::stringToWString(myString[1]);
            def_temp = Character::stringToWString(WordSet::definition(sw2));
            for(int i=0; i<def_temp.size(); i++){
                if (def_temp[i]==L'|'){
                    int lef = def_temp.size() - i;
                    def_temp.erase(i,lef);
                }
            }
            sd2 = def_temp;

            sw3 = Character::stringToWString(myString[2]);
            def_temp = Character::stringToWString(WordSet::definition(sw3));
            for(int i=0; i<def_temp.size(); i++){
                if (def_temp[i]==L'|'){
                    int lef = def_temp.size() - i;
                    def_temp.erase(i,lef);
                }
            }
            sd3 = def_temp;

            sw4 = Character::stringToWString(myString[3]);
            def_temp = Character::stringToWString(WordSet::definition(sw4));
            for(int i=0; i<def_temp.size(); i++){
                if (def_temp[i]==L'|'){
                    int lef = def_temp.size() - i;
                    def_temp.erase(i,lef);
                }
            }
            sd4 = def_temp;
            //

            if (is_def){
                w1.setString(sw1); w2.setString(sw2); w3.setString(sw3); w4.setString(sw4);
                d1.setString(sd1); d2.setString(sd2); d3.setString(sd3); d4.setString(sd4);
                wrapText(d1,1100); wrapText(w1,500);
                wrapText(d2,1100); wrapText(w2,500);
                wrapText(d3,1100); wrapText(w3,500);
                wrapText(d4,1100); wrapText(w4,500);
            }
            else{
                w1.setString(sd1); w2.setString(sd2); w3.setString(sd3); w4.setString(sd4);
                d1.setString(sw1); d2.setString(sw2); d3.setString(sw3); d4.setString(sw4);
                wrapText(d1,1100); wrapText(w1,500);
                wrapText(d2,1100); wrapText(w2,500);
                wrapText(d3,1100); wrapText(w3,500);
                wrapText(d4,1100); wrapText(w4,500);
            }


            SetCenter(w1,q1);
            SetCenter(w2,q2);
            SetCenter(w3,q3);
            SetCenter(w4,q4);
            state_reset = false;
        }

        for(int i=2; i<6; i++){
            auto &x = myBound[i];
            sf::FloatRect ShapeBound = x.getGlobalBounds();
            bool isMousedOn = ShapeBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            if (isMousedOn){
                x.setFillColor(c3);
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    if (i-2 == selected){
                        selected = rand()%4;
                        state_reset = true;
                    }
                    else{
                        x.setFillColor(sf::Color::Red);
                    }
                }
            }
            else{
                x.setFillColor(c2);
            }
        }
    }
    return 5;
}

void QuizScreen::updateScene(sf::Time &deltaTime){

}

void QuizScreen::SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4){
    c1 = f1;
    c2 = f2;
    c3 = f3;
    c4 = f4;
    for(auto &x : myBound) x.setFillColor(c1);
    w1.setFillColor(c4);
    w2.setFillColor(c4);
    w3.setFillColor(c4);
    w4.setFillColor(c4);
    d1.setFillColor(c4);
    d2.setFillColor(c4);
    d3.setFillColor(c4);
    d4.setFillColor(c4);
    back_button.setFillColor(c2);
    tback_button.setFillColor(c4);
}
