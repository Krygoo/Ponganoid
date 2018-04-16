#include "stdafx.h"
#include "GameOver.h"
using namespace sf;


GameOver::GameOver(unsigned int screenWidth, unsigned int screenHeight)
{
	font.loadFromFile("arial.ttf");

	gameOverText.setFont(font);
	gameOverText.setOutlineColor(Color::Cyan);
	gameOverText.setFillColor(Color::Blue);
	gameOverText.setOutlineThickness(5);
	gameOverText.setPosition(screenWidth / 3 + 50, screenHeight / 3 - 20);
	gameOverText.setCharacterSize(60);
	gameOverText.setString("Koniec Gry");

	overview.setFont(font);
	overview.setOutlineColor(Color::Cyan);
	overview.setFillColor(Color::Blue);
	overview.setOutlineThickness(5);
	overview.setPosition(screenWidth / 3 - 30, screenHeight / 2.3);

	pressEscapeText.setFont(font);
	pressEscapeText.setOutlineThickness(5);
	pressEscapeText.setOutlineColor(Color::Cyan);
	pressEscapeText.setFillColor(Color::Blue);
	pressEscapeText.setPosition(screenWidth / 3 + 20, screenHeight / 2);
	pressEscapeText.setString("Wcisnij escape, aby wyjsc.");
}


GameOver::~GameOver()
{
}

void GameOver::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(gameOverText);
	target.draw(overview);
	target.draw(pressEscapeText);
}

void GameOver::setOverviewSuffix(int score1, int score2, bool isDestroyed)
{
	if (score1 % 10 == 2 || score1 % 10 == 3 || score1 % 10 == 4)
		this->overviewsuffix = " punkty";
	else
		this->overviewsuffix = " punktow";
	if (score1 > score2 && isDestroyed)
		this->overview.setString("Wygrales, uzyskujac " + std::to_string(score1) + this->overviewsuffix);
	else
		this->overview.setString("Przegrales, uzyskujac " + std::to_string(score1) + this->overviewsuffix);
}
