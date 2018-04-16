#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class Ball : public Drawable
{
public:
	Ball(float t_X, float t_Y);
	Ball() = delete;
	~Ball() = default;

	float top();
	float bottom();
	float left();
	float right();

	Vector2f getPosition();
	void update(unsigned int width, unsigned int height);

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void invertVertically();
	void invertHorizontally();
	void incCounter(int c1, int c2);
	void setLastPlayer(int player);
	void multBallVelocity(float bonus);
	void addBallVelocity(float bonus);
	void addBallRadius(float bonus);
	void reset(float t_X, float t_Y);
	void setFillColor(Color & color);
	void setOutlineColor(Color &color);

	int getLastPlayer();
	int counter5 = 0, counter6 = 0, counter7 = 0, counter8 = 0;

private:
	float ballRadius{ 10.0f };
	float ballVelocity{ 4.0f };
	int lastplayer;
	CircleShape shape;
	Vector2f velocity{ ballVelocity, ballVelocity };
	void draw(RenderTarget& target, RenderStates state) const override;
};

