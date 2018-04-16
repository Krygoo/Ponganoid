#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;

class GameOver : public Drawable
{
public:
	GameOver(unsigned int screenWidth, unsigned int screenHeight);
	~GameOver();

	void draw(RenderTarget& target, RenderStates state) const;
	void setOverviewSuffix(int score1, int score2, bool isDestroyed);
private:
	Text gameOverText;
	Text overview;
	Text pressEscapeText;
	std::string overviewsuffix;
	Font font;
};

