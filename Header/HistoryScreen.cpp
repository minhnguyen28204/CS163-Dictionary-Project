#include "HistoryScreen.hpp"

HistoryScreen::HistoryScreen(void){
	_font.loadFromFile("Font/BeVietnamPro-Regular.ttf");
	tickObj.loadFromFile("Image/tickbox.png");
	
	sf::Vector2f coorIcon(1294, 110);

	delObj.loadFromFile("Image/delete.png");
	delSprite.setTexture(delObj);
	delSprite.setScale(1.5, 1.5);
	delSprite.setPosition(coorIcon);

	delBound.setPosition(coorIcon);
	delBound.setSize(sf::Vector2f(40, 40));
	delBound.setFillColor(c2);

	tickAllObj.loadFromFile("Image/tick.png");
	tickAllSprite.setTexture(tickAllObj);
	delSprite.setScale(1.5, 1.5);
	tickAllSprite.setPosition(coorIcon.x + 50, coorIcon.y);

	tickAllBound.setPosition(coorIcon.x + 50, coorIcon.y);
	tickAllBound.setSize(sf::Vector2f(40, 40));
	tickAllBound.setFillColor(c2);

	border.setSize(sf::Vector2f(1400,210));
	border.setFillColor(c2);
	
	title.setString("Search History");
	title.setFont(_font);
	title.setCharacterSize(50);
	title.setFillColor(c4);
	title.setPosition(130,100);
	updateScene();
}

int HistoryScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){
	sf::Vector2f coorText(150, 225);
	sf::Vector2i mousePosition = sf::Mouse::getPosition(App);

	sf::FloatRect shapeDel = delBound.getGlobalBounds();
	bool isMousedOnDel = shapeDel.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
	if (isMousedOnDel)
	{
		delBound.setFillColor(c3);
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			int size = tick.size();
			if (is_tickAll == true)
			{
				deleteSearchHistory();
			}
			else
			{
				for (int i = 0; i < size; i++)
				{
					if (tick[i])
					{
						wstring Cur_str = textSet[i].getString();
						string tmp = Character::backToString(Cur_str);
						deleteWordInHistory(tmp);
					}
				}
			}
			is_tickAll = false;
			updateScene();
		}
	}
	else
	{
		delBound.setFillColor(c2);
	}

	sf::FloatRect shapeTick = tickAllBound.getGlobalBounds();
	bool isMousedOnTick = shapeTick.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
	if (isMousedOnTick)
	{
		tickAllBound.setFillColor(c3);
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (is_tickAll == false) {
				int size = tick.size();
				for (int i = 0; i < size; i++)
				{
					tick[i] = true;
				}
				is_tickAll = true;
			}
			else {
				int size = tick.size();
				for (int i = 0; i < size; i++)
				{
					tick[i] = false;
				}
				is_tickAll = false;
			}
		}
	}
	else
	{
		tickAllBound.setFillColor(c2);
	}

	int size = recSet.size();
	for (int i = 0; i < size; i++)
	{
		sf::FloatRect shape = recSet[i].getGlobalBounds();
		bool isMousedOn = shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		if (isMousedOn)
		{
			sf::FloatRect tickshape = tickBoundSet[i].getGlobalBounds();
			bool isMousedOnTick = tickshape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
			if (isMousedOnTick)
			{
				tickBoundSet[i].setFillColor(c3);
				recSet[i].setFillColor(c1);
				sf::FloatRect shapeBorder = border.getGlobalBounds();
				bool isMousedOnBorder = shapeBorder.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
				if (!isMousedOnBorder)
				{
					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
					{
						tick[i] = !tick[i];
					}
				}
				else tickBoundSet[i].setFillColor(c1);
			}
			else
			{
				tickBoundSet[i].setFillColor(c1);
				recSet[i].setFillColor(c3);
				sf::FloatRect shapeBorder = border.getGlobalBounds();
				bool isMousedOnBorder = shapeBorder.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
				if (!isMousedOnBorder)
				{
					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
					{
						wstring Cur_str = textSet[i].getString();
						wstring Definition = Character::stringToWString(WordSet::definition(Cur_str));
						MyKey = Cur_str;
						MyDef = Definition;
						is_search = true;
						return 7;
					}
				}
				else recSet[i].setFillColor(c1);
			}
		}
		else
		{
			recSet[i].setFillColor(c1);
		}
	}

	if (event.type == sf::Event::MouseWheelScrolled || (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)))
	{
		if (recSet.size())
		{
			float delta = 0;
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				delta = event.mouseWheelScroll.delta;
			}
			else if (event.key.code == sf::Keyboard::Up) delta = 1;
			else delta = -1;

			if (delta < 0 && recSet[recSet.size() - 1].getPosition().y + 55>840)
			{
				for (int i = 0; i < recSet.size(); i++)
				{
					recSet[i].setPosition(recSet[i].getPosition().x, recSet[i].getPosition().y + delta * 20);
					textSet[i].setPosition(textSet[i].getPosition().x, textSet[i].getPosition().y + delta * 20);
					tickBoundSet[i].setPosition(tickBoundSet[i].getPosition().x, tickBoundSet[i].getPosition().y + delta * 20);
				}
				for (int i = 0; i < tickSpriteSet.size(); i++)
				{
					tickSpriteSet[i].setPosition(tickSpriteSet[i].getPosition().x, tickSpriteSet[i].getPosition().y + delta * 20);
				}
			}
			else if (delta > 0 && recSet[0].getPosition().y < 210)
			{
				for (int i = 0; i < recSet.size(); i++)
				{
					recSet[i].setPosition(recSet[i].getPosition().x, recSet[i].getPosition().y + delta * 20);
					textSet[i].setPosition(textSet[i].getPosition().x, textSet[i].getPosition().y + delta * 20);
					tickBoundSet[i].setPosition(tickBoundSet[i].getPosition().x, tickBoundSet[i].getPosition().y + delta * 20);
				}
				for (int i = 0; i < tickSpriteSet.size(); i++)
				{
					tickSpriteSet[i].setPosition(tickSpriteSet[i].getPosition().x, tickSpriteSet[i].getPosition().y + delta * 20);
				}
			}
		}
	}

    return 2;
}

void HistoryScreen::ScreenDraw(sf::RenderWindow &App){
	for (int i = 0; i < recSet.size(); i++)
	{
		App.draw(recSet[i]);
		App.draw(textSet[i]);
		App.draw(tickBoundSet[i]);
		if (tick[i] == true) App.draw(tickSpriteSet[i]);
	}
	App.draw(border);
	App.draw(title);
	App.draw(delBound);
	App.draw(delSprite);
	App.draw(tickAllBound);
	App.draw(tickAllSprite);
}

void HistoryScreen::updateScene(sf::Time& deltaTime) {

}

void HistoryScreen::updateScene(){
	std::vector<std::string> vec = SearchHistory();
	tickSpriteSet.clear();
	tickBoundSet.clear();
	textSet.clear();
	recSet.clear();
	tick.clear();
	is_tickAll = false;

	sf::Vector2f coorText(150, 225);
	sf::Vector2f coorRec(70, 210);
	int size = vec.size();
	for (int i = size - 1; i >= 0; i--)
	{
		sf::Text tmp;
		tmp.setString(Character::stringToWString(vec[i]));
		tmp.setFont(_font);
		tmp.setCharacterSize(35);
		tmp.setFillColor(c4);
		tmp.setPosition(coorText.x, coorText.y + (size - i - 1) * 70);
		textSet.push_back(tmp);

		sf::RectangleShape ext;
		ext.setSize(sf::Vector2f(1330, 70));
		ext.setFillColor(c1);
		ext.setPosition(coorRec.x, coorRec.y + (size - i - 1) * 70);
		recSet.push_back(ext);

		sf::Sprite tickSprite;
		tickSprite.setTexture(tickObj);
		tickSprite.setScale(0.6, 0.6);
		tickSprite.setPosition(coorText.x + 1200, coorText.y + (size - i - 1) * 70 + 10);
		tickSpriteSet.push_back(tickSprite);

		sf::RectangleShape tickBound;
		tickBound.setSize(sf::Vector2f(30, 30));
		tickBound.setFillColor(c1);
		tickBound.setOutlineThickness(1);
		tickBound.setOutlineColor(c3);
		tickBound.setPosition(coorText.x + 1200, coorText.y + (size - i - 1) * 70 + 10);
		tickBoundSet.push_back(tickBound);

		tick.push_back(false);
	}
}

void HistoryScreen::SetColor(sf::Color& f1, sf::Color& f2, sf::Color& f3, sf::Color& f4) {
	c1 = f1;
	c2 = f2;
	c3 = f3;
	c4 = f4;
	for (int i = 0; i < textSet.size(); i++)
	{
		textSet[i].setFillColor(c4);
		recSet[i].setFillColor(c2);
		tickBoundSet[i].setFillColor(c1);
		tickBoundSet[i].setOutlineColor(c3);
	}
	border.setFillColor(c2);
	title.setFillColor(c4);
	delBound.setFillColor(c2);
	tickAllBound.setFillColor(c2);
	if (is_dark)
	{
		tickObj.loadFromFile("Image/tickbox2.png");
		delObj.loadFromFile("Image/delete2.png");
		tickAllObj.loadFromFile("Image/tick.png");
		is_dark = false;
	}
	else
	{
		tickObj.loadFromFile("Image/tickbox.png");
		delObj.loadFromFile("Image/delete.png");
		tickAllObj.loadFromFile("Image/tick.png");
		is_dark = true;
	}
}

