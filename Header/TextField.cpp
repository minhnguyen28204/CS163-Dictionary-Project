#include "TextField.hpp"
#include <iostream>

TextField::TextField()
    : m_selected(false), m_cursorVisible(false)
{

}

TextField::TextField(sf::Font& font, unsigned int size, sf::Color _color, float x, float y, float width, float height, bool showText = true)
    : m_selected(false), m_cursorVisible(false)
{
    m_background.setSize(sf::Vector2f(width, height));
    m_background.setPosition(x, y);
    m_background.setFillColor(sf::Color::White);
    m_background.setOutlineThickness(1);
    m_background.setOutlineColor(sf::Color::Black);

    m_text.setFont(font);
    m_text.setCharacterSize(size);
    m_text.setFillColor(color);
    m_text.setPosition(x+10,y+7);

    m_cursor.setSize(sf::Vector2f(1, size));
    m_cursor.setFillColor(color);
    m_cursor.setPosition(x + 10, y + 7);

    pos_x = x;
    pos_y = y;
    _font = font;
    Size = size;
    color = _color;

    ShowTxt = showText;

    m_text.setString("");
}

void TextField::SetProperties(sf::Font& font, unsigned int size, sf::Color _color, float x, float y, float width, float height, bool showText = true){
    m_selected = false;

    m_background.setSize(sf::Vector2f(width, height));
    m_background.setPosition(x, y);
    m_background.setFillColor(sf::Color::White);
    m_background.setOutlineThickness(1);
    m_background.setOutlineColor(sf::Color::Black);

    m_text.setFont(font);
    m_text.setCharacterSize(size);
    m_text.setFillColor(color);
    sf::FloatRect textbound = m_text.getGlobalBounds();
    m_text.setPosition(x+10,y + (height-textbound.height)/4 );

    m_cursor.setSize(sf::Vector2f(1, size));
    m_cursor.setFillColor(color);
    m_cursor.setPosition(x + 10, y + 7);

    pos_x = x;
    pos_y = y;
    _font = font;
    Size = size;
    color = _color;

    ShowTxt = showText;
}

void TextField::clear_str(){
    m_text.setString(L"");
}

void TextField::Tab_handle(){
    if (m_selected) m_selected = false;
    else m_selected = true;
}

bool TextField::cur_state(){
    return m_selected;
}

void TextField::SetIniStr(std::wstring str){
    m_text.setString(str);
}

void TextField::draw(sf::RenderWindow& window)
{
    window.draw(m_background);
    if (ShowTxt==true) window.draw(m_text);
    else{
        sf::Text tmp;
        std::wstring temp = L"";
        for(int i=0; i<m_text.getString().getSize(); i++) temp += L"*";
        tmp.setString(temp);
        tmp.setFont(_font);
        tmp.setCharacterSize(Size);
        tmp.setColor(color);
        tmp.setPosition(pos_x+10,pos_y+10);
        window.draw(tmp);
    }

    if (m_selected && m_cursorVisible)
    {
        window.draw(m_cursor);
    }
}

void TextField::handleEvent(sf::RenderWindow &App, sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (m_background.getGlobalBounds().contains(mousePos))
        {
            m_selected = true;
        }
        else
        {
            m_selected = false;
        }
    }
    else if (event.type == sf::Event::TextEntered && m_selected)
    {
        is_entering_text = true;
        if (event.text.unicode == '\b' && m_text.getString().getSize() > 0) // Handle backspace
        {
            if (real_text.size()) real_text.pop_back();
            m_text.setString(real_text);
            while (m_text.getLocalBounds().width >= m_background.getLocalBounds().width - 20){
                m_text.setString(m_text.getString().substring(1,m_text.getString().getSize()));
            }
            m_cursorIndex--;
            m_cursorIndex = max(m_cursorIndex, 0);
        }
        else if (event.text.unicode != '\b') // Handle printable characters
        {
            real_text += static_cast<wchar_t>(event.text.unicode);
            m_text.setString(real_text);
            m_cursorIndex++;
            while (m_text.getLocalBounds().width >= m_background.getLocalBounds().width - 20){
                m_text.setString(m_text.getString().substring(1,m_text.getString().getSize()));
            }
        }
    }
    else if (event.type == sf::Event::KeyReleased) is_entering_text = false;
}

void TextField::update(sf::Time &deltaTime){
// Handle cursor blinking
    cursor_stacked_time += deltaTime.asSeconds();
    if (m_selected)
    {

        if (cursor_stacked_time >= 0.5)
        {
            if (is_entering_text) m_cursorVisible = true;
            else m_cursorVisible = !m_cursorVisible;
            cursor_stacked_time -= 0.5;
        }
        if (ShowTxt) m_cursor.setPosition(m_text.getPosition().x + m_text.getLocalBounds().width + 4, m_text.getPosition().y);
        else{
            sf::Text tmp;
            std::wstring temp = L"";
            for(int i=0; i<m_text.getString().getSize(); i++) temp += L"*";
            tmp.setString(temp);
            tmp.setFont(_font);
            tmp.setCharacterSize(Size);
            tmp.setColor(color);
            tmp.setPosition(pos_x+10,pos_y+10);
            m_cursor.setPosition(tmp.getPosition().x + tmp.getLocalBounds().width + 4, tmp.getPosition().y);
        }
    }
    else
    {
        m_cursorVisible = false;
    }
}

std::wstring TextField::getText() const
{
    return m_text.getString();
}
