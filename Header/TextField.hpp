#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H
#define SFML_NO_DEPRECATED_WARNINGS

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class TextField
{
public:
    TextField();
    TextField(sf::Font& font, unsigned int size, sf::Color color, float x, float y, float width, float height, bool showText);

    void SetProperties(sf::Font& font, unsigned int size, sf::Color color, float x, float y, float width, float height, bool showText);
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::RenderWindow &App, sf::Event &event);
    void update(sf::Time &deltaTime);
    void clear_str();
    void Tab_handle();
    bool cur_state();
    void SetIniStr(std::wstring str);
    std::wstring getText() const;

private:
    float cursor_stacked_time = 0;
    wstring real_text;
    float pos_x, pos_y;
    int m_cursorIndex;
    sf::Text cursorText;
    sf::Font _font;
    sf::Color color;
    unsigned int Size;
    sf::RectangleShape m_background;
    sf::Text m_text;
    sf::RectangleShape m_cursor; // New member variable for the cursor
    bool m_selected;
    bool m_cursorVisible;// New member variable to keep track of cursor visibility
    bool is_entering_text = false;
    sf::Clock m_cursorClock; // New member variable to keep track of elapsed time since last cursor toggle
    bool ShowTxt;
};

#endif // TEXT_FIELD_H
