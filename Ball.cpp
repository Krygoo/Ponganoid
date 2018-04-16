#include "stdafx.h"
#include "Ball.h"


Ball::Ball(float t_X, float t_Y)
{
	shape.setPosition(t_X, t_Y);
	shape.setRadius(this->ballRadius);
	shape.setFillColor(Color::White);
	shape.setOutlineThickness(-2);
	shape.setOutlineColor(Color::Cyan);
	shape.setOrigin(this->ballRadius, this->ballRadius);
}

void Ball::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

float Ball::top()
{
	return this->shape.getPosition().y - ballRadius;
}

float Ball::bottom()
{
	return this->shape.getPosition().y + ballRadius;
}

float Ball::left()
{
	return this->shape.getPosition().x - ballRadius;
}

float Ball::right()
{
	return this->shape.getPosition().x + ballRadius;
}

Vector2f Ball::getPosition()
{
	return shape.getPosition();
}

void Ball::update(unsigned int width, unsigned int height)
{
	shape.move(this->velocity);
	if (this->top() < 0)
		this->velocity.y = ballVelocity;
	else if (this->bottom() > height)
		this->velocity.y = -ballVelocity;
	else if (this->left() < 0)
		this->velocity.x = ballVelocity;
	else if (this->right() > width)
		this->velocity.x = -ballVelocity;
}

void Ball::moveUp()
{
	this->velocity.y = -ballVelocity;
}

void Ball::moveDown()
{
	this->velocity.y = ballVelocity;
}

void Ball::moveLeft()
{
	this->velocity.x = -ballVelocity;
}

void Ball::moveRight()
{
	this->velocity.x = ballVelocity;
}

void Ball::invertVertically()
{
	this->velocity.y = -this->velocity.y;
}

void Ball::invertHorizontally()
{
	this->velocity.x = -this->velocity.x;
}

void Ball::incCounter(int c1, int c2)
{
	c1++;
	c2--;
}

int Ball::getLastPlayer()
{
	return this->lastplayer;
}

void Ball::setLastPlayer(int player)
{
	this->lastplayer = player;
}

void Ball::multBallVelocity(float bonus)
{
	this->ballVelocity *= bonus;
}

void Ball::addBallVelocity(float bonus)
{
	this->ballVelocity += bonus;
}

void Ball::addBallRadius(float bonus)
{
	this->ballRadius += bonus;
	this->shape.setRadius(this->ballRadius);
	this->shape.setOrigin(this->ballRadius, this->ballRadius);
}

void Ball::reset(float t_X, float t_Y)
{
	this->ballRadius = 10.0f;
	this->shape.setRadius(this->ballRadius);
	this->shape.setOrigin(this->ballRadius, this->ballRadius);
	this->shape.setPosition(t_X, t_Y);
	this->ballVelocity = 4.0f;
	this->counter5 = 0;
	this->counter6 = 0;
	this->counter7 = 0;
	this->counter8 = 0;
}

void Ball::setFillColor(Color & color)
{
	this->shape.setFillColor(color);
}

void Ball::setOutlineColor(Color & color)
{
	this->shape.setOutlineColor(color);
}
