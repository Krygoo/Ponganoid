#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class Score : public Drawable
{
public:
	Score(unsigned int screenWidth, unsigned int screenHeight);
	~Score();

	void draw(RenderTarget& target, RenderStates state) const override;
	void setScoreText(int score1, int score2);

private:
	Text score1;
	Text score2;
	Font font;
};

