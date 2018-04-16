#include "stdafx.h"
#include "Paddle.h"


Paddle::Paddle(float t_X, float t_Y, int id)
{
	shape.setPosition(t_X, t_Y);
	shape.setSize({ this->paddleWidth, this->paddleHeight });
	shape.setFillColor(Color::Green);
	shape.setOutlineThickness(-3);
	shape.setOutlineColor(Color::Yellow);
	shape.setOrigin(paddleWidth / 2, paddleHeight / 2);
	playerID = id;
	score = 0;
}

void Paddle::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

float Paddle::top()
{
	return this->shape.getPosition().y - shape.getSize().y/2;
}

float Paddle::bottom()
{
	return this->shape.getPosition().y + shape.getSize().y/2;
}

float Paddle::left()
{
	return this->shape.getPosition().x - shape.getSize().x/2;
}

float Paddle::right()
{
	return this->shape.getPosition().x + shape.getSize().x/2;
}

Vector2f  Paddle::getPosition()
{
	return shape.getPosition();
}

void Paddle::playerUpdate(unsigned int screenwidth)
{
	this->shape.move(this->velocity);

	if (Keyboard::isKeyPressed(Keyboard::Left) && this->left() > 0)
	{
		velocity.x = -paddleVelocity;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && this->right() < screenwidth)
	{
		velocity.x = paddleVelocity;
	}
	else
	{
		velocity.x = 0;
	}
}

void Paddle::aiUpdate(unsigned int screenwidth, float left, float right, int difficulty, int & time, int & targetTime)
{
	if (!(this->left() <= 0 && velocity.x == -paddleVelocity) && !(this->right() >= screenwidth && velocity.x == paddleVelocity))
		this->shape.move(this->velocity);

	switch (difficulty)
	{
	case 0:

		if (this->left() <= 0)
			velocity.x = paddleVelocity;
		else if (this->right() >= screenwidth)
			velocity.x = -paddleVelocity;

		if (time == targetTime)
		{
			time = 0;
			targetTime = rand() % 7 + 1;
			int direction = rand() % 50;
			if (direction < 4)
				velocity.x = 0;
			else if (direction == 5)
				velocity.x = -paddleVelocity;
			else if (direction == 6)
				velocity.x = paddleVelocity;
			else
			{
				if (left - 20 < this->left())
				{
					velocity.x = -paddleVelocity;
				}
				else if (right + 20 > this->right())
				{
					velocity.x = paddleVelocity;
				}
				else
				{
					velocity.x = 0;
				}
			}
		}
		break;
	case 1:
		if (time == targetTime)
		{
			time = 0;
			targetTime = rand() % 4 + 1;
			int direction = rand() % 100;
			if (direction < 5)
				velocity.x = 0;
			else if (direction == 6)
				velocity.x = -paddleVelocity;
			else if (direction == 7)
				velocity.x = paddleVelocity;
			else
			{
				if (left - 20 < this->left())
				{
					velocity.x = -paddleVelocity;
				}
				else if (right + 20 > this->right())
				{
					velocity.x = paddleVelocity;
				}
				else
				{
					velocity.x = 0;
				}
			}
		}
		break;
	case 2:
		if (left - 10 < this->left())
		{
			velocity.x = -paddleVelocity;
		}
		else if (right + 10 > this->right())
		{
			velocity.x = paddleVelocity;
		}
		else
		{
			velocity.x = 0;
		}
		break;
	}
}

void Paddle::destroy()
{
	destroyed = true;
}

void Paddle::multPaddleVelocity(float bonus)
{
	this->paddleVelocity *= bonus;
}

void Paddle::multPaddleWidth(float bonus)
{
	this->paddleWidth *= bonus;
	this->shape.setSize({ this->paddleWidth, this->paddleHeight });
	this->shape.setOrigin(paddleWidth / 2, paddleHeight / 2);
}

void Paddle::incCounter(int c1, int c2)
{
	c1++;
	c2--;
}

void Paddle::reset(float t_X, float t_Y)
{
	this->score = 0;
	this->counter1 = 0;
	this->counter2 = 0;
	this->counter3 = 0;
	this->counter4 = 0;
	this->destroyed = false;
	this->paddleWidth = 80.0f;
	this->paddleVelocity = 10.0f;
	this->shape.setSize({ this->paddleWidth, this->paddleHeight });
	this->shape.setOrigin(paddleWidth / 2, paddleHeight / 2);
	this->shape.setPosition(t_X, t_Y);
}

void Paddle::addScore(int bonus)
{
	this->score += bonus;
}

void Paddle::setColor(Color & color1, Color & color2)
{
	this->shape.setFillColor(color1);
	this->shape.setOutlineColor(color2);
}

Color Paddle::getFillColor()
{
	return this->shape.getFillColor();
}

Color Paddle::getOutlineColor()
{
	return this->shape.getOutlineColor();
}

int Paddle::getScore()
{
	return this->score;
}

bool Paddle::isDestroyed()
{
	return this->destroyed;
}

int Paddle::getPlayerID()
{
	return this->playerID;
}
