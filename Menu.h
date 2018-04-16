#pragma once
#include <SFML\Graphics.hpp>
#define optionsNumber 4
using namespace sf;

class Menu : public Drawable
{
public:
	Menu(unsigned int screenWidth, unsigned int screenHeight);
	~Menu();

	void draw(RenderTarget& target, RenderStates state) const override;
	void moveUp();
	void moveDown();
	int GetPressedItem();
	void setTitleColor(Color & fillColor, Color & outlineColor);

private:
	int selectedItemIndex;
	Font font;
	Text title;
	Text menu[optionsNumber];
};