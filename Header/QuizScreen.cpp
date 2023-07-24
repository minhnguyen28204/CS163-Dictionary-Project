#include "QuizScreen.hpp"

QuizScreen::QuizScreen(){
    is_game = false;
    state_reset = true;
    _font.loadFromFile("Font/BeVietnamPro-Regular.ttf");

    w1.setFont(_font); w1.setCharacterSize(30); w1.setFillColor(c4);
    w2.setFont(_font); w2.setCharacterSize(30); w2.setFillColor(c4);
    w3.setFont(_font); w3.setCharacterSize(30); w3.setFillColor(c4);
    w4.setFont(_font); w4.setCharacterSize(30); w4.setFillColor(c4);
    d1.setFont(_font); d1.setCharacterSize(30); d1.setFillColor(c4);
    d2.setFont(_font); d2.setCharacterSize(30); d2.setFillColor(c4);
    d3.setFont(_font); d3.setCharacterSize(30); d3.setFillColor(c4);
    d4.setFont(_font); d4.setCharacterSize(30); d4.setFillColor(c4);
    d1.setPosition(150,150);
    d2.setPosition(150,150);
    d3.setPosition(150,150);
    d4.setPosition(150,150);


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
        for(int i=2; i<6; i++) App.draw(myBound[i]);
        if (is_def){
            App.draw(w1); App.draw(w2); App.draw(w3); App.draw(w4);
            if (selected==0) App.draw(d1);
            if (selected==1) App.draw(d2);
            if (selected==2) App.draw(d3);
            if (selected==3) App.draw(d4);
        }
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
        if (state_reset){
            //Get 4 random strings here

            //

            w1.setString(sw1); w2.setString(sw2); w3.setString(sw3); w4.setString(sw4);
            d1.setString(sd1); d2.setString(sd2); d3.setString(sd3); d4.setString(sd4);

            if (is_def){
                SetCenter(w1,q1);
                SetCenter(w2,q2);
                SetCenter(w3,q3);
                SetCenter(w4,q4);
            }
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
}
