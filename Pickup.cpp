#include "stdafx.h"
#include "Pickup.h"
#include "time.h"



Pickup::Pickup(float t_X, float t_Y)
{
	shape.setPosition(t_X, t_Y);
	shape.setOutlineThickness(-2);
	shape.setSize({ this->pickupWidth, this->pickupHeight });
	shape.setOrigin(pickupWidth / 2, pickupHeight / 2);
}

float Pickup::top()
{
	return this->shape.getPosition().y - shape.getSize().y / 2;
}

float Pickup::bottom()
{
	return this->shape.getPosition().y + shape.getSize().y / 2;
}

float Pickup::left()
{
	return this->shape.getPosition().x - shape.getSize().x / 2;
}

float Pickup::right()
{
	return this->shape.getPosition().x + shape.getSize().x / 2;
}

Vector2f Pickup::getPosition()
{
	return shape.getPosition();
}

void Pickup::activate(int type, Ball& ball, Paddle& paddle)
{
	switch (type)
	{
	case 1:
		if (paddle.counter1 < 5)
		{
			paddle.multPaddleWidth(1.4);
			paddle.incCounter(paddle.counter1, paddle.counter2);
			break;
		}
	case 2:
		if (paddle.counter2 < 5)
		{
			paddle.multPaddleWidth(0.7);
			paddle.incCounter(paddle.counter2, paddle.counter1);
			break;
		}
	case 3:
		if (paddle.counter3 < 5)
		{
			paddle.multPaddleVelocity(1.2);
			paddle.incCounter(paddle.counter3, paddle.counter4);
			break;
		}
	case 4:
		if (paddle.counter4 < 5)
		{
			paddle.multPaddleVelocity(0.85);
			paddle.incCounter(paddle.counter4, paddle.counter3);
			break;
		}
	case 5:
		if (ball.counter5 < 5)
		{
			ball.addBallRadius(2);
			ball.incCounter(ball.counter5, ball.counter6);
			break;
		}
	case 6:
		if (ball.counter6 < 3)
		{
			ball.addBallRadius(-2);
			ball.incCounter(ball.counter6, ball.counter5);
			break;
		}
	case 7:
		if (ball.counter7 < 5)
		{
			ball.multBallVelocity(0.8);
			ball.incCounter(ball.counter7, ball.counter8);
			break;
		}
	case 8:
		if (ball.counter8 < 5)
		{
			ball.multBallVelocity(1.25);
			ball.incCounter(ball.counter8, ball.counter7);
			break;
		}
	}
}

void Pickup::update(unsigned int windowHeight)
{
	this->shape.move(this->velocity);
	if (this->top() >= windowHeight || this->bottom() <= 0)
		this->despawn();
}

void Pickup::spawn(Vector2f position, int id)
{
	this->spawned = true;
	if (id == 1)
		this->velocity.y = pickupVelocity;
	else
		this->velocity.y = -pickupVelocity;
	type = rand() % 8 + 1;
	switch (type)
	{
	case 1:
		this->shape.setFillColor(Color::Green);
		break;
	case 2:
		this->shape.setFillColor(Color::Yellow);
		break;
	case 3:
		this->shape.setFillColor(Color::Magenta);
		break;
	case 4:
		this->shape.setFillColor(Color::Red);
		break;
	case 5:
		this->shape.setFillColor(Color::Cyan);
		break;
	case 6:
		this->shape.setFillColor(Color::Blue);
		break;
	case 7:
		this->shape.setFillColor(Color(0, 100, 0, 255));
		break;
	case 8:
		this->shape.setFillColor(Color(100, 0, 0, 255));
		break;
	}
	this->shape.setPosition(position);
}

void Pickup::despawn()
{
	this->spawned = false;
}

void Pickup::setOutlineColor(Color & color)
{
	this->shape.setOutlineColor(color);
}

bool Pickup::isSpawned()
{
	return this->spawned;
}

int Pickup::getType()
{
	return this->type;
}

void Pickup::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}