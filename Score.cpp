#include "stdafx.h"
#include "Score.h"


Score::Score(unsigned int screenWidth, unsigned int screenHeight)
{
	font.loadFromFile("arial.ttf");

	score1.setPosition(5, 5);
	score1.setFont(font);
	score1.setFillColor(Color::White);
	score1.setScale(0.5, 0.5);
	score1.setOutlineThickness(1);

	score2.setPosition(5, 25);
	score2.setFont(font);
	score2.setFillColor(Color::White);
	score2.setScale(0.5, 0.5);
	score2.setOutlineThickness(1);
}


Score::~Score()
{
}

void Score::draw(RenderTarget & target, RenderStates state) const
{
	target.draw(score1);
	target.draw(score2);
}

void Score::setScoreText(int score1, int score2)
{
	this->score1.setString("Gracz: " + std::to_string(score1));
	this->score2.setString("Przeciwnik: " + std::to_string(score2));

	if (score1 > score2)
	{
		this->score2.setStyle(Text::Regular);
		this->score2.setOutlineColor(Color::Transparent);
		this->score1.setStyle(Text::Bold);
		this->score1.setOutlineColor(Color::Yellow);
	}
	else if (score2 > score1)
	{
		this->score1.setStyle(Text::Regular);
		this->score1.setOutlineColor(Color::Transparent);
		this->score2.setStyle(Text::Bold);
		this->score2.setOutlineColor(Color::Yellow);
	}
}
