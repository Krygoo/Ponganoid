#pragma once
#include <SFML\Graphics.hpp>
#include "Ball.h"

using namespace sf;

class Paddle : public Drawable
{
public:
	Paddle(float t_X, float t_Y, int id);
	Paddle() = delete;
	~Paddle() = default;

	float top();
	float bottom();
	float left();
	float right();

	Vector2f getPosition();

	void playerUpdate(unsigned int screenwidth);
	void aiUpdate(unsigned int screenwidth, float left, float right, int difficulty, int & time, int & targetTime);
	void destroy();
	void multPaddleVelocity(float bonus);
	void multPaddleWidth(float bonus);
	void incCounter(int c1, int c2);
	void reset(float t_X, float t_Y);
	void addScore(int bonus);
	void setColor(Color & color1, Color & color2);

	Color getFillColor();
	Color getOutlineColor();
	
	bool isDestroyed();
	
	int getPlayerID();
	int getScore();
	int counter1 = 0, counter2 = 0, counter3 = 0, counter4 = 0;

private:

	float paddleVelocity{ 10.0f };
	float paddleWidth{ 80.0f };
	float paddleHeight{ 20.0f };

	int playerID;
	int score;
	
	void draw(RenderTarget& target, RenderStates state) const override;
	RectangleShape shape;
	Vector2f velocity{ paddleVelocity, 0.f };

	bool destroyed = false;
};

