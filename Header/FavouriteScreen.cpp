#include "FavouriteScreen.hpp"

FavoriteScreen::FavoriteScreen(void){
	_font.loadFromFile("Font/BeVietnamPro-Regular.ttf");

	border.setSize(sf::Vector2f(1400, 210));
	border.setFillColor(c2);

	title.setString("Favourite Words");
	title.setFont(_font);
	title.setCharacterSize(50);
	title.setFillColor(c4);
	title.setPosition(130, 100);
	updateScene();
}

int FavoriteScreen::ProcessEvent(sf::RenderWindow &App, sf::Event event){

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
				}
			}
			else if (delta > 0 && recSet[0].getPosition().y < 210)
			{
				for (int i = 0; i < recSet.size(); i++)
				{
					recSet[i].setPosition(recSet[i].getPosition().x, recSet[i].getPosition().y + delta * 20);
					textSet[i].setPosition(textSet[i].getPosition().x, textSet[i].getPosition().y + delta * 20);
				}
			}
		}
	}

	sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
	for (int i = 0; i < recSet.size(); i++)
	{
		sf::FloatRect shape = recSet[i].getGlobalBounds();
		bool isMousedOn = shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
		if (isMousedOn)
		{
			recSet[i].setFillColor(c3);
			sf::FloatRect shapeBorder = border.getGlobalBounds();
			bool isMousedOnBorder = shapeBorder.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
			if (!isMousedOnBorder)
			{
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				{
					std::wstring Cur_str = textSet[i].getString();
					std::wstring Definition = Character::stringToWString(WordSet::definition(Cur_str));
					MyKey = Cur_str;
					MyDef = Definition;
					is_search = true;
					return 7;
				}
			}
			else recSet[i].setFillColor(c1);
		}
		else
		{
			recSet[i].setFillColor(c1);
		}
	}
    return 3;
}

void FavoriteScreen::ScreenDraw(sf::RenderWindow &App){
	for (int i = 0; i < recSet.size(); i++)
	{
		App.draw(recSet[i]);
		App.draw(textSet[i]);
	}
	App.draw(border);
	App.draw(title);
}


void FavoriteScreen::updateScene(sf::Time &deltaTime){

}

void FavoriteScreen::updateScene() {
	std::vector<std::string> vec = favouriteList();
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
	}
}

void FavoriteScreen::SetColor(sf::Color& f1, sf::Color& f2, sf::Color& f3, sf::Color& f4) {
	c1 = f1;
	c2 = f2;
	c3 = f3;
	c4 = f4;
	for (int i = 0; i < textSet.size(); i++)
	{
		textSet[i].setFillColor(c4);
		recSet[i].setFillColor(c2);
	}
	border.setFillColor(c2);
	title.setFillColor(c4);
}
