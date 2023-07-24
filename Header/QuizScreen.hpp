#ifndef QUIZSCREEN_HPP
#define QUIZSCREEN_HPP
#include "cScreen.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace std;

class QuizScreen : public cScreen
{
private:
    bool is_game = false;
    bool is_def = false;
    bool state_reset = true;
    int selected = 0;
    sf::RectangleShape bound_wordDef, bound_defWord;
    sf::Texture wordDef;
    sf::Sprite swordDef;
    sf::Texture defWord;
    sf::Sprite sdefWord;
    sf::RectangleShape q1, q2, q3, q4;
    sf::Font _font;
    sf::Text w1, w2, w3, w4, d1, d2, d3, d4;
    wstring sw1 = L"word 1";
    wstring sd1 = L"Định nghĩa word 1";
    wstring sw2 = L"word 2";
    wstring sd2 = L"Định nghĩa word 2";
    wstring sw3 = L"word 3";
    wstring sd3 = L"Định nghĩa word 3";
    wstring sw4 = L"word 4";
    wstring sd4 = L"Định nghĩa word 4";
    vector<sf::Sprite> mySprite;
    vector<sf::RectangleShape> myBound;
    sf::Color c1 = sf::Color(34,40,49), c2 = sf::Color(57, 62, 70), c3 = sf::Color(0, 173, 181), c4 = sf::Color(238,238,238);
public:
    QuizScreen(void);
    void ScreenDraw(sf::RenderWindow &App);
    int ProcessEvent(sf::RenderWindow &App, sf::Event event);
    void updateScene(sf::Time &deltaTime);
    void SetColor(sf::Color &f1, sf::Color &f2, sf::Color &f3, sf::Color &f4);
};

#endif // QUIZSCREEN_HPP
