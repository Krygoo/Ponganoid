#include "stdafx.h"
#include "Block.h"


Block::Block(float t_X, float t_Y, float t_Width, float t_Height)
{
	shape.setPosition(t_X, t_Y);
	shape.setSize({ t_Width, t_Height });
	shape.setFillColor(Color::Blue);
	shape.setOutlineThickness(-2);
	shape.setOutlineColor(Color::Cyan);
	shape.setOrigin(t_Width / 2.f, t_Height / 2.f);
}

void Block::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->shape, state);
}

float Block::top()
{
	return this->shape.getPosition().y - shape.getSize().y / 2;
}

float Block::bottom()
{
	return this->shape.getPosition().y + shape.getSize().y / 2;
}

bool Block::isDestroyed()
{
	return this->destroyed;
}

void Block::destroy()
{
	this->destroyed = true;
}

void Block::setFillColor(Color & color)
{
	this->shape.setFillColor(color);
}

void Block::setOutlineColor(Color & color)
{
	this->shape.setOutlineColor(color);
}

Color Block::getFillColor()
{
	return this->shape.getFillColor();
}

Color Block::getOutlineColor()
{
	return this->shape.getOutlineColor();
}

Vector2f Block::getSize()
{
	return shape.getSize();
}

float Block::left()
{
	return this->shape.getPosition().x - shape.getSize().x / 2;
}

float Block::right()
{
	return this->shape.getPosition().x + shape.getSize().x / 2;
}

Vector2f  Block::getPosition()
{
	return shape.getPosition();
}