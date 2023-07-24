#include "MainFunction.hpp"

Dictionary::Dictionary()
: mWindow(sf::VideoMode(1400,850),"Dictionary",sf::Style::Titlebar | sf::Style::Close)
{
    Screens.push_back(&s0);
    Screens.push_back(&s1);
    Screens.push_back(&s2);
    Screens.push_back(&s3);
    Screens.push_back(&s4);
    Screens.push_back(&s5);
    Screens.push_back(&s6);
    Screens.push_back(&s7);

    WordSet::switchWordSet(3);
    WordSet::loadAllData();

    if (_font.loadFromFile("Font/BeVietnamPro-Regular.ttf")) cout << "Load succeded!\n";
    sideBar.setPosition(0,0);
    sideBar.setSize(sf::Vector2f(70,850));
    sideBar.setFillColor(c2);
    Title.setString("Dictionary");
    Title.setFont(_font);
    Title.setCharacterSize(65);
    Title.setFillColor(c4);
    Title.setOutlineThickness(2);
    Title.setOutlineColor(c3);
    sf::FloatRect textBounds = Title.getGlobalBounds();
    Title.setPosition(70 + (1330 - textBounds.width) / 2, 10);

    //Home
    ihome.loadFromFile("Image/home.png");
    Ihome.setTexture(ihome);
    Ihome.setPosition(sf::Vector2f(10,10));
    MySprite.push_back(Ihome);

    sf::RectangleShape BoundHome;
    BoundHome.setPosition(0,0);
    BoundHome.setSize(sf::Vector2f(70,70));
    BoundHome.setFillColor(c2);
    MyBounder.push_back(BoundHome);

    thome.setFont(_font);
    thome.setCharacterSize(15);
    thome.setFillColor(sf::Color::White);
    thome.setOutlineThickness(1);
    thome.setString("Main Page");
    MyCursorText.push_back(thome);


    //Search
    isearch.loadFromFile("Image/mag_glass.png");
    Isearch.setTexture(isearch);
    Isearch.setPosition(sf::Vector2f(10,80));
    MySprite.push_back(Isearch);

    sf::RectangleShape BoundSearch;
    BoundSearch.setPosition(0,70);
    BoundSearch.setSize(sf::Vector2f(70,70));
    BoundSearch.setFillColor(c2);
    MyBounder.push_back(BoundSearch);

    tsearch.setFont(_font);
    tsearch.setCharacterSize(15);
    tsearch.setFillColor(sf::Color::White);
    tsearch.setOutlineThickness(1);
    tsearch.setString("Search");
    MyCursorText.push_back(tsearch);

    //History
    ihistory.loadFromFile("Image/history.png");
    Ihistory.setTexture(ihistory);
    Ihistory.setPosition(sf::Vector2f(10,150));
    MySprite.push_back(Ihistory);

    sf::RectangleShape BoundHistory;
    BoundHistory.setPosition(0,140);
    BoundHistory.setSize(sf::Vector2f(70,70));
    BoundHistory.setFillColor(c2);
    MyBounder.push_back(BoundHistory);

    thistory.setFont(_font);
    thistory.setCharacterSize(15);
    thistory.setFillColor(sf::Color::White);
    thistory.setOutlineThickness(1);
    thistory.setString("History");
    MyCursorText.push_back(thistory);

    //Favorite
    ifavorite.loadFromFile("Image/favorite.png");
    Ifavorite.setTexture(ifavorite);
    Ifavorite.setPosition(sf::Vector2f(10,220));
    MySprite.push_back(Ifavorite);

    sf::RectangleShape BoundFavorite;
    BoundFavorite.setPosition(0,210);
    BoundFavorite.setSize(sf::Vector2f(70,70));
    BoundFavorite.setFillColor(c2);
    MyBounder.push_back(BoundFavorite);

    tfavorite.setFont(_font);
    tfavorite.setCharacterSize(15);
    tfavorite.setFillColor(sf::Color::White);
    tfavorite.setOutlineThickness(1);
    tfavorite.setString("Favourite");
    MyCursorText.push_back(tfavorite);

    //Add
    iadd.loadFromFile("Image/add.png");
    Iadd.setTexture(iadd);
    Iadd.setPosition(sf::Vector2f(10,290));
    MySprite.push_back(Iadd);

    sf::RectangleShape BoundAdd;
    BoundAdd.setPosition(0,280);
    BoundAdd.setSize(sf::Vector2f(70,70));
    BoundAdd.setFillColor(c2);
    MyBounder.push_back(BoundAdd);

    tadd.setFont(_font);
    tadd.setCharacterSize(15);
    tadd.setFillColor(sf::Color::White);
    tadd.setOutlineThickness(1);
    tadd.setString("Add a word");
    MyCursorText.push_back(tadd);

    //Quiz
    iquiz.loadFromFile("Image/quiz.png");
    Iquiz.setTexture(iquiz);
    Iquiz.setPosition(sf::Vector2f(10,360));
    MySprite.push_back(Iquiz);

    sf::RectangleShape BoundQuiz;
    BoundQuiz.setPosition(0,350);
    BoundQuiz.setSize(sf::Vector2f(70,70));
    BoundQuiz.setFillColor(c2);
    MyBounder.push_back(BoundQuiz);

    tquiz.setFont(_font);
    tquiz.setCharacterSize(15);
    tquiz.setFillColor(sf::Color::White);
    tquiz.setOutlineThickness(1);
    tquiz.setString("Quiz");
    MyCursorText.push_back(tquiz);

    //setting
    isetting.loadFromFile("Image/setting.png");
    Isetting.setTexture(isetting);
    Isetting.setPosition(sf::Vector2f(10,790));
    MySprite.push_back(Isetting);

    sf::RectangleShape BoundSetting;
    BoundSetting.setPosition(0,780);
    BoundSetting.setSize(sf::Vector2f(70,70));
    BoundSetting.setFillColor(c2);
    MyBounder.push_back(BoundSetting);

    tsetting.setFont(_font);
    tsetting.setCharacterSize(15);
    tsetting.setFillColor(sf::Color::White);
    tsetting.setOutlineThickness(1);
    tsetting.setString("Setting");
    MyCursorText.push_back(tsetting);

    //Change theme
    itheme.loadFromFile("Image/theme.png");
    Itheme.setTexture(itheme);
    Itheme.setPosition(sf::Vector2f(10,720));
    MySprite.push_back(Itheme);

    sf::RectangleShape BoundTheme;
    BoundTheme.setPosition(0,710);
    BoundTheme.setSize(sf::Vector2f(70,70));
    BoundTheme.setFillColor(c2);
    MyBounder.push_back(BoundTheme);

    ttheme.setFont(_font);
    ttheme.setCharacterSize(15);
    ttheme.setFillColor(sf::Color::White);
    ttheme.setOutlineThickness(1);
    ttheme.setString("Change theme");
    MyCursorText.push_back(ttheme);
}

void Dictionary::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::milliseconds(16.6);
    while (mWindow.isOpen()){
        processEvent();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;
            processEvent();
            update(TimePerFrame);
        }
        render();
    }
}

void Dictionary::processIconColor(sf::Event event){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
    for(int i=0; i<MyBounder.size(); i++){
        auto &x = MyBounder[i];
        sf::FloatRect RecBound = x.getGlobalBounds();
        bool isMousedOn = RecBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        if (isMousedOn){
            x.setFillColor(c3);
            is_on[i] = true;
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                if (i < 7) screen = i;
                else{
                    dark = !dark;
                    if (dark) c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238,238,238);
                    else c1 = sf::Color(83,127,231), c2 = sf::Color(233, 248, 249), c3 = sf::Color(192, 238, 242), c4 = sf::Color(24, 24, 35);
                    sideBar.setFillColor(c2);
                    Title.setFillColor(c4);
                    Title.setOutlineColor(c3);
                    s0.SetColor(c1,c2,c3,c4);
                    s5.SetColor(c1,c2,c3,c4);
                    if (dark) {
                        ihome.loadFromFile("Image/home.png");
                        ihistory.loadFromFile("Image/history.png");
                        isearch.loadFromFile("Image/mag_glass.png");
                        iquiz.loadFromFile("Image/quiz.png");
                        isetting.loadFromFile("Image/setting.png");
                        itheme.loadFromFile("Image/theme.png");
                        iadd.loadFromFile("Image/add.png");
                        ifavorite.loadFromFile("Image/favorite.png");
                    }
                    else{
                        iadd.loadFromFile("Image/add2.png");
                        ifavorite.loadFromFile("Image/favorite2.png");
                        ihome.loadFromFile("Image/home2.png");
                        ihistory.loadFromFile("Image/history - Copy.png");
                        isearch.loadFromFile("Image/mag_glass2.png");
                        iquiz.loadFromFile("Image/quiz - Copy.png");
                        isetting.loadFromFile("Image/setting - Copy.png");
                        itheme.loadFromFile("Image/theme - Copy.png");
                    }
                }
            }
        }
        else{
            x.setFillColor(c2);
            is_on[i] = false;
        }
    }
}

void Dictionary::processEvent(){
    sf::Event event;
    while (mWindow.pollEvent(event)){
        if (screen == 7 && s0.is_search) s7.setString(s0.MyDef,s0.MyKey), s0.is_search = false;
        screen = Screens[screen]->ProcessEvent(mWindow,event);
        processIconColor(event);
        if (event.type == sf::Event::Closed){
            mWindow.close();
        }
    }
}

void Dictionary::update(sf::Time &deltaTime){
    sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
    for(auto &x : MyCursorText){
        x.setPosition(static_cast<float>(mousePosition.x + 10), static_cast<float>(mousePosition.y + 10));
    }
    Screens[screen]->updateScene(deltaTime);
}

void Dictionary::render(){
    mWindow.clear(c1);
    mWindow.draw(sideBar);
    mWindow.draw(Title);
    Screens[screen]->ScreenDraw(mWindow);
    for(auto &x : MyBounder) mWindow.draw(x);
    for(auto &x : MySprite) mWindow.draw(x);
    for(int i=0; i<MyCursorText.size(); i++) if (is_on[i]) mWindow.draw(MyCursorText[i]);
    mWindow.display();
}
