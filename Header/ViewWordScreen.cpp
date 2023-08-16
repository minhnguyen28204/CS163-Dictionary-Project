#include "ViewWordScreen.hpp"
#include <iostream>
#include <sstream>

using namespace std;

WordScreen::WordScreen(void) {
	_font.loadFromFile("Font/BeVietnamPro-Regular.ttf");

	KeyWord.setPosition(100, 100);
	KeyWord.setCharacterSize(30);
	KeyWord.setFont(_font);
	KeyWord.setFillColor(c4);

	Header.setPosition(70, 0);
	Header.setSize(sf::Vector2f(1330, 145));
	Header.setFillColor(c1);

	objTexture.loadFromFile("Image/edit.png");
	object.setTexture(objTexture);

	editBound.setSize(sf::Vector2f(25, 25));
	editBound.setFillColor(c1);

	saveObj.loadFromFile("Image/save.png");
	saveSprite.setTexture(saveObj);

	saveBound.setSize(sf::Vector2f(25, 25));
	saveBound.setFillColor(c1);

	cancelObj.loadFromFile("Image/cancel.png");
	cancelSprite.setTexture(cancelObj);

	cancelBound.setSize(sf::Vector2f(25, 25));
	cancelBound.setFillColor(c1);

	addBound.setSize(sf::Vector2f(200, 50));
	addBound.setFillColor(c2);

	addText.setString("Add new definition");
	addText.setFont(_font);
	addText.setCharacterSize(20);
	addText.setFillColor(c4);

	deleteObj.loadFromFile("Image/delete.png");
	deleteSprite.setTexture(deleteObj);

	deleteBound.setSize(sf::Vector2f(25, 25));
	deleteBound.setFillColor(c1);

	heartObj.loadFromFile("Image/heart.png");
	heartSprite.setTexture(heartObj);

	heartBound.setSize(sf::Vector2f(25, 25));
	heartBound.setFillColor(c1);

	tickObj.loadFromFile("Image/tick.png");
	tickSprite.setTexture(tickObj);

	tickBound.setSize(sf::Vector2f(25, 25));
	tickBound.setFillColor(c1);
}

void wrapText(sf::Text& text, float maxWidth) {
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
		}
		else {
			std::wstring word;
			std::wstringstream wordStream(line);
			while (wordStream >> word) {
				sf::Text wordText(word, font, characterSize);
				sf::FloatRect wordBounds = wordText.getLocalBounds();
				float wordWidth = wordBounds.width;

				if (lineWidth + wordWidth > maxWidth) {
					wrappedText += L"\n" + word + L" ";
					lineWidth = wordWidth;
				}
				else {
					wrappedText += word + L" ";
					lineWidth += wordWidth;
				}
			}
			wrappedText += L"\n";
		}
	}

	text.setString(wrappedText);
}

void WordScreen::ScreenDraw(sf::RenderWindow& App) {
	if (!is_edit) {
		for (int i = 0; i < Def.size(); i++) {
			App.draw(Def[i]);
		}
	}
	else {
		for (int i = 0; i < editDef.size(); i++) {
			editDef[i].draw(App);
			App.draw(delShape[i]);
			App.draw(delText[i]);
		}
	}
	App.draw(Header);
	App.draw(KeyWord);
	if (!is_edit) {
		App.draw(editBound);
		App.draw(deleteBound);
		App.draw(heartBound);
		App.draw(object);
		App.draw(deleteSprite);
		App.draw(heartSprite);
	}
	else if (is_edit) {
		App.draw(saveBound);
		App.draw(saveSprite);
		App.draw(cancelBound);
		App.draw(cancelSprite);
		App.draw(addBound);
		App.draw(addText);
	}
}

int WordScreen::ProcessEvent(sf::RenderWindow& App, sf::Event event) {
	float maxWidth = App.getSize().x - 300;
	if (loadWord) {
		Def.clear();
		wstring tmp = L"";
		int cnt = 150;
		for (int i = 0; i < MyDef.size(); i++) {
			if (MyDef[i] != L'|') tmp += MyDef[i];
			else {
				sf::Text Def_i;
				Def_i.setPosition(100, cnt);
				Def_i.setCharacterSize(20);
				Def_i.setFont(_font);
				Def_i.setString(tmp);
				Def_i.setFillColor(c4);
				wrapText(Def_i, maxWidth);


				Def.push_back(std::move(Def_i));
				cnt += Def_i.getGlobalBounds().height + 5;
				tmp = L"";
			}
		}
		if (tmp.size()) {
			sf::Text Def_i;
			Def_i.setPosition(100, cnt);
			Def_i.setCharacterSize(20);
			Def_i.setFont(_font);
			Def_i.setString(tmp);
			Def_i.setFillColor(c4);
			wrapText(Def_i, maxWidth);

			Def.push_back(std::move(Def_i));
			cnt += Def_i.getGlobalBounds().height + 5;
			tmp = L"";
		}
		loadWord = false;
	}
	if (is_found == false) {
		sf::Text Def_i;
		Def_i.setPosition(100, 150);
		Def_i.setCharacterSize(20);
		Def_i.setFont(_font);
		Def_i.setString(L"Not found");
		Def_i.setFillColor(c4);
		wrapText(Def_i, maxWidth);
		Def.push_back(std::move(Def_i));
		is_found = true;
	}
	if (!is_edit) {
		if (event.type == sf::Event::MouseWheelScrolled || (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))) {
			if (Def.size()) {
				float delta = 0;
				if (event.type == sf::Event::MouseWheelScrolled) delta = event.mouseWheelScroll.delta;
				else if (event.key.code == sf::Keyboard::Up) delta = 1;
				else delta = -1;

				if (delta < 0 && Def[Def.size() - 1].getPosition().y + Def[Def.size() - 1].getGlobalBounds().height > 850) {
					for (int i = 0; i < Def.size(); i++) {
						Def[i].setPosition(Def[i].getPosition().x, Def[i].getPosition().y + delta * 20);
					}
				}
				if (delta > 0 && Def[0].getPosition().y < 150) {
					for (int i = 0; i < Def.size(); i++) {
						Def[i].setPosition(Def[i].getPosition().x, Def[i].getPosition().y + delta * 20);
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < editDef.size(); i++) editDef[i].handleEvent(App, event);
		if (event.type == sf::Event::MouseWheelScrolled || (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))) {
			if (editDef.size()) {
				float delta = 0;
				if (event.type == sf::Event::MouseWheelScrolled) delta = event.mouseWheelScroll.delta;
				else if (event.key.code == sf::Keyboard::Up) delta = 1;
				else delta = -1;

				if (delta < 0 && addBound.getPosition().y + 50 > 850) {
					for (int i = 0; i < editDef.size(); i++) {
						editDef[i].setPosition(editDef[i].getPosition().first, editDef[i].getPosition().second + delta * 20);
						delShape[i].setPosition(delShape[i].getPosition().x, editDef[i].getPosition().second);
						delText[i].setPosition(delText[i].getPosition().x, editDef[i].getPosition().second + (delShape[i].getGlobalBounds().height - delText[i].getLocalBounds().height) / 4);
					}
					addBound.setPosition(addBound.getPosition().x, addBound.getPosition().y + delta * 20);
					addText.setPosition(addText.getPosition().x, addText.getPosition().y + 20 * delta);
				}
				if (delta > 0 && editDef[0].getPosition().second < 150) {
					for (int i = 0; i < editDef.size(); i++) {
						editDef[i].setPosition(editDef[i].getPosition().first, editDef[i].getPosition().second + delta * 20);
						delShape[i].setPosition(delShape[i].getPosition().x, editDef[i].getPosition().second);
						delText[i].setPosition(delText[i].getPosition().x, editDef[i].getPosition().second + (delShape[i].getGlobalBounds().height - delText[i].getLocalBounds().height) / 4);
					}
					addBound.setPosition(addBound.getPosition().x, addBound.getPosition().y + delta * 20);
					addText.setPosition(addText.getPosition().x, addText.getPosition().y + 20 * delta);
				}
			}
		}
	}

	sf::Vector2i mousePosition = sf::Mouse::getPosition(App);

	if (is_edit) {
		//save
		sf::FloatRect shape = saveBound.getGlobalBounds();
		if (shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
			saveBound.setFillColor(c3);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				Def.clear();
				int cnt = 150;
				wstring newDef = L"";
				for (int i = 0; i < editDef.size(); i++) {
					wstring tmp = editDef[i].getText();
					newDef += tmp;
					newDef += L'|';
					sf::Text Def_i;
					Def_i.setPosition(100, cnt);
					Def_i.setCharacterSize(20);
					Def_i.setFont(_font);
					Def_i.setString(tmp);
					Def_i.setFillColor(c4);
					wrapText(Def_i, maxWidth);


					Def.push_back(std::move(Def_i));
					cnt += Def_i.getGlobalBounds().height + 5;
				}
				WordSet::erase(MyKey);
				WordSet::addNew(MyKey, newDef);
				is_edit = false;
			}
		}
		else {
			saveBound.setFillColor(c1);
		}

		//cancel
		shape = cancelBound.getGlobalBounds();
		if (shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && is_edit) {
			cancelBound.setFillColor(c3);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				is_edit = false;
			}
		}
		else {
			cancelBound.setFillColor(c1);
		}

		//delete text field
		for (int i = 0; i < delShape.size(); i++) {
			sf::FloatRect ShapeBound = delShape[i].getGlobalBounds();
			if (ShapeBound.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
				delShape[i].setFillColor(c3);
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					delShape.pop_back();
					delText.pop_back();
					for (int j = i; j < editDef.size() - 1; j++) {
						editDef[j].SetIniStr(editDef[j + 1].getText());
					}
					editDef.pop_back();
					if (editDef.size()) {
						addBound.setPosition(100, editDef.back().getPosition().second + 100);
						addText.setPosition(addText.getPosition().x, addBound.getPosition().y + (50 - addText.getLocalBounds().height) / 4);
					}
					else {
						addBound.setPosition(100, 150);
						addText.setPosition(100 + (200 - addText.getLocalBounds().width) / 2, 150 + (50 - addText.getLocalBounds().height) / 4);
					}
				}
			}
			else {
				delShape[i].setFillColor(c2);
			}
		}

		//add text field
		shape = addBound.getGlobalBounds();
		if (shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
			addBound.setFillColor(c3);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				TextField newField;
				newField.SetProperties(_font, 20, c4, 100, editDef.back().getPosition().second + 100, 1100, 50, true);
				editDef.push_back(newField);

				sf::RectangleShape delshape;
				delshape.setPosition(1250, editDef.back().getPosition().second);
				delshape.setSize(sf::Vector2f(100, 50));
				delshape.setFillColor(c2);
				delShape.push_back(move(delshape));

				sf::Text deltext;
				deltext.setString("Delete");
				deltext.setFont(_font);
				deltext.setCharacterSize(20);
				deltext.setFillColor(c4);
				deltext.setPosition(1250 + (delshape.getGlobalBounds().width - deltext.getLocalBounds().width) / 2, editDef.back().getPosition().second + (delshape.getGlobalBounds().height - deltext.getLocalBounds().height) / 4);
				delText.push_back(move(deltext));

				addBound.setPosition(100, editDef.back().getPosition().second + 100);
				addText.setPosition(100 + (200 - addText.getLocalBounds().width) / 2, editDef.back().getPosition().second + 100 + (50 - addText.getLocalBounds().height) / 4);
			}
		}
		else {
			addBound.setFillColor(c2);
		}
	}
	else if (!is_edit && !is_delete) {
		sf::FloatRect shape = editBound.getGlobalBounds();
		if (shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && !is_edit) {
			editBound.setFillColor(c3);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				is_edit = !is_edit;
				editDef.clear();
				delShape.clear();
				delText.clear();
				int cnt1 = 150;
				for (int i = 0; i < Def.size(); i++) {
					wstring tmp = Def[i].getString();
					TextField newField;
					newField.SetProperties(_font, 20, c4, 100, cnt1, 1100, 50, true);
					if (tmp.back() == L'\n') tmp.pop_back();
					newField.SetIniStr(tmp);
					editDef.push_back(newField);

					sf::RectangleShape delshape;
					delshape.setPosition(1250, cnt1);
					delshape.setSize(sf::Vector2f(100, 50));
					delshape.setFillColor(c2);
					delShape.push_back(move(delshape));

					sf::Text deltext;
					deltext.setString("Delete");
					deltext.setFont(_font);
					deltext.setCharacterSize(20);
					deltext.setFillColor(c4);
					deltext.setPosition(1250 + (delshape.getGlobalBounds().width - deltext.getLocalBounds().width) / 2, cnt1 + (delshape.getGlobalBounds().height - deltext.getLocalBounds().height) / 4);
					delText.push_back(move(deltext));
					cnt1 += 100;
				}
				addBound.setPosition(100, cnt1);
				addText.setPosition(100 + (200 - addText.getLocalBounds().width) / 2, cnt1 + (50 - addText.getLocalBounds().height) / 4);
			}
		}
		else {
			editBound.setFillColor(c1);
		}

		shape = deleteBound.getGlobalBounds();
		if (shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
			deleteBound.setFillColor(c3);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				WordSet::erase(MyKey);
				return 0;
			}
		}
		else {
			deleteBound.setFillColor(c1);
		}

		shape = heartBound.getGlobalBounds();
		if (shape.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
			heartBound.setFillColor(c3);
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				if (heart_state == false) {
					heartObj.loadFromFile("Image/heart3.png");
					wstring tmp = KeyWord.getString();
					string fav = Character::backToString(tmp);
					addWordToFavList(fav);
					heart_state = true;
				}
				else
				{
					if(is_dark) heartObj.loadFromFile("Image/heart.png");
					else heartObj.loadFromFile("Image/heart2.png");
					wstring tmp = KeyWord.getString();
					string fav = Character::backToString(tmp);
					removeWordFromFavList(fav);
					heart_state = false;
				}
			}
		}
		else {
			heartBound.setFillColor(c1);
		}
	}
	return 7;
}

void WordScreen::updateScene(sf::Time& deltaTime) {
	if (is_edit) {
		for (int i = 0; i < editDef.size(); i++) editDef[i].update(deltaTime);
	}
}

void WordScreen::SetColor(sf::Color& f1, sf::Color& f2, sf::Color& f3, sf::Color& f4) {
	c1 = f1;
	c2 = f2;
	c3 = f3;
	c4 = f4;
	for (auto& x : Def) x.setFillColor(c4);
	for (auto& x : delText) x.setFillColor(c4);
	KeyWord.setFillColor(c4);
	Header.setFillColor(c1);
	addText.setFillColor(c4);
	if (is_dark) {
		is_dark = false;
		objTexture.loadFromFile("Image/edit2.png");
		saveObj.loadFromFile("Image/save2.png");
		cancelObj.loadFromFile("Image/cancel2.png");
		deleteObj.loadFromFile("Image/delete2.png");
		std::wstring tmp = KeyWord.getString();
		std::string ext = Character::backToString(tmp);
		if (isFavourite(ext))
		{
			heart_state = true;
			heartObj.loadFromFile("Image/heart3.png");
		}
		else
		{
			heart_state = false;
			heartObj.loadFromFile("Image/heart2.png");
		}
	}
	else {
		is_dark = true;
		objTexture.loadFromFile("Image/edit.png");
		saveObj.loadFromFile("Image/save.png");
		cancelObj.loadFromFile("Image/cancel.png");
		deleteObj.loadFromFile("Image/delete.png");
		//if (heart_state == true) std::cout << "tim" << std::endl;
		//else std::cout << "Not tim" << std::endl;
		std::wstring tmp = KeyWord.getString();
		std::string ext = Character::backToString(tmp);
		if (isFavourite(ext))
		{
			heart_state = true;
			heartObj.loadFromFile("Image/heart3.png");
		}
		else
		{
			heart_state = false;
			heartObj.loadFromFile("Image/heart.png");
		}
	}
}

void WordScreen::setString(wstring _def, wstring _key) {
	MyDef = _def;
	if (_def.size() == 0) is_found = false;
	else is_found = true;
	KeyWord.setString(_key);
	std::string tmp = Character::backToString(_key);
	if (isFavourite(tmp))
	{
		heart_state = true;
		heartObj.loadFromFile("Image/heart3.png");
	}
	else
	{
		heart_state = false;
		if (is_dark) heartObj.loadFromFile("Image/heart.png");
		else heartObj.loadFromFile("Image/heart2.png");
	}
	MyKey = _key;
	is_edit = false;
	is_delete = false;
	_setmode(_fileno(stdout), _O_U16TEXT);

	object.setPosition(130 + KeyWord.getLocalBounds().width, 109);
	editBound.setPosition(130 + KeyWord.getLocalBounds().width, 109);

	deleteBound.setPosition(editBound.getPosition().x + 35, 109);
	deleteSprite.setPosition(deleteBound.getPosition().x, 109);

	heartBound.setPosition(deleteBound.getPosition().x + 35, 109);
	heartSprite.setPosition(heartBound.getPosition().x, 109);

	saveSprite.setPosition(130 + KeyWord.getLocalBounds().width, 109);
	saveBound.setPosition(saveSprite.getPosition().x, saveSprite.getPosition().y);

	cancelSprite.setPosition(saveSprite.getPosition().x + 35, 109);
	cancelBound.setPosition(cancelSprite.getPosition().x, cancelSprite.getPosition().y);


	loadWord = true;
}
