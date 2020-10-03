#include "stdafx.h"
#include "Menu.h"
using namespace sf;

Menu::Menu(unsigned int screenWidth, unsigned int screenHeight)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}

	title.setFont(font);
	title.setFillColor(Color::Green);
	title.setOutlineColor(Color::Yellow);
	title.setOutlineThickness(3);
	title.setString("Ponganoid");
	title.setPosition(screenWidth / 4, screenHeight / 10);
	title.setCharacterSize(130);

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setOutlineThickness(1);
	menu[0].setOutlineColor(Color(100, 0, 0, 255));
	menu[0].setString("Latwy");
	menu[0].setPosition(screenWidth / 2 - 50, screenHeight / (optionsNumber + 1) *2.5);

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setOutlineThickness(1);
	menu[1].setOutlineColor(Color::Cyan);
	menu[1].setString("Sredni");
	menu[1].setPosition(screenWidth / 2 - 50, screenHeight / (optionsNumber + 1) * 3);

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setOutlineThickness(1);
	menu[2].setOutlineColor(Color::Cyan);
	menu[2].setString("Trudny");
	menu[2].setPosition(screenWidth / 2 - 50, screenHeight / (optionsNumber + 1) * 3.5);

	menu[3].setFont(font);
	menu[3].setFillColor(Color::White);
	menu[3].setOutlineThickness(1);
	menu[3].setOutlineColor(Color::Cyan);
	menu[3].setString("Wyjdz");
	menu[3].setPosition(screenWidth / 2 - 50, screenHeight / (optionsNumber + 1) * 4);

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(RenderTarget& target, RenderStates state) const
{
	for (int i = 0; i < optionsNumber; i++)
	{
		target.draw(menu[i]);
		target.draw(title);
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(Color::White);
		menu[selectedItemIndex].setOutlineColor(Color::Cyan);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);
		menu[selectedItemIndex].setOutlineColor(Color(100, 0, 0, 255));
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < optionsNumber)
	{
		menu[selectedItemIndex].setFillColor(Color::White);
		menu[selectedItemIndex].setOutlineColor(Color::Cyan);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Red);
		menu[selectedItemIndex].setOutlineColor(Color(100, 0, 0, 255));
	}
}

int Menu::GetPressedItem()
{
	return selectedItemIndex;
}

void Menu::setTitleColor(Color & fillColor, Color & outlineColor)
{
	title.setFillColor(fillColor);
	title.setOutlineColor(outlineColor);
}
