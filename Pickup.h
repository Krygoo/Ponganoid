#pragma once
#include <SFML\Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

using namespace sf;

class Pickup : public Drawable
{
public:
	Pickup(float t_X, float t_Y);
	Pickup() = delete;
	~Pickup() = default;

	float top();
	float bottom();
	float left();
	float right();

	Vector2f getPosition();

	void activate(int type, Ball& ball, Paddle& paddle);
	void update(unsigned int windowHeight);
	void spawn(Vector2f position, int id);
	void despawn();
	void setOutlineColor(Color &color);

	bool isSpawned();

	int getType();

private:
	void draw(RenderTarget& target, RenderStates state) const override;
	RectangleShape shape;
	int type = 0;
	float pickupVelocity{ 2.5f };
	float pickupWidth{ 60.0f };
	float pickupHeight{ 20.0f };
	Vector2f velocity{ 0.f, pickupVelocity };
	bool spawned = false;
};

