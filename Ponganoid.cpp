#include "stdafx.h"
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Pickup.h"
#include "Menu.h"

using namespace sf;
using namespace std;

template <class T1, class T2> bool isIntersecting(T1& A, T2& B);

bool collisionTest(Paddle& paddle, Ball& ball, int bonus);

bool collisionTest(Block& block, Ball& ball, Pickup& pickup, Paddle& paddle1, Paddle& paddle2, int bonus);

bool collisionTest(Paddle& paddle, Ball& ball, Pickup& pickup, int bonus);

void placeBlocks(unsigned int x, unsigned int y, unsigned int w, unsigned int h, vector<Block> &blocks);

Color randomColor();

int main()
{
	srand(time(NULL));
	int scorebonus;
	int difficulty;
	int timer;
	int timerTarget;
	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 720;
	bool isGameOver = false;
	RenderWindow window{ VideoMode{ windowWidth, windowHeight }, "Ponganoid" };
	Paddle playerPaddle(windowWidth / 2, windowHeight * 17 / 18, 1);
	Paddle aiPaddle(windowWidth / 2, windowHeight / 18, 2);
	Ball ball(windowWidth / 2, playerPaddle.top() - 50);
	Texture backgroundTexture;
	Sprite background;
	Text score1;
	Text score2;
	string overviewsuffix;
	Font font;
	Pickup pickup(-10, -10);
	Event event;
	Menu menu(windowWidth, windowHeight);
	unsigned blocksX{ 17 }, blocksY{ 6 }, blockWidth{ 60 }, blockHeight{ 20 };
	vector<Block> blocks;
	Color blockFillColor;
	Color blockOutlineColor;

	window.setFramerateLimit(60);

	font.loadFromFile("arial.ttf");
	backgroundTexture.loadFromFile("background.jpg");
	background.setTexture(backgroundTexture);

	score1.setPosition(5, 5);
	score1.setFont(font);
	score1.setFillColor(Color::White);
	score1.setScale(0.5, 0.5);
	score2.setPosition(5, 25);
	score2.setFont(font);
	score2.setFillColor(Color::White);
	score2.setScale(0.5, 0.5);

	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setOutlineColor(Color::Cyan);
	gameOverText.setFillColor(Color::Blue);
	gameOverText.setOutlineThickness(5);
	gameOverText.setPosition(windowWidth / 3 + 50, windowHeight / 3 - 20);
	gameOverText.setCharacterSize(60);
	gameOverText.setString("Koniec Gry");

	Text overview;
	overview.setFont(font);
	overview.setOutlineColor(Color::Cyan);
	overview.setFillColor(Color::Blue);
	overview.setOutlineThickness(5);
	overview.setPosition(windowWidth / 3 - 30, windowHeight / 2.3);

	Text pressEscapeText;
	pressEscapeText.setFont(font);
	pressEscapeText.setOutlineThickness(5);
	pressEscapeText.setOutlineColor(Color::Cyan);
	pressEscapeText.setFillColor(Color::Blue);
	pressEscapeText.setPosition(windowWidth / 3 + 20, windowHeight / 2);
	pressEscapeText.setString("Wcisnij escape, aby wyjsc.");

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::T:
					menu.setTitleColor(randomColor(), randomColor());
					break;

				case Keyboard::Up:
					menu.moveUp();
					break;

				case Keyboard::Down:
					menu.moveDown();
					break;

				case Keyboard::Return:
					difficulty = menu.GetPressedItem();
					if (difficulty == 3)
					{
						window.close();
						break;
					}
					
					placeBlocks(blocksX, blocksY, blockWidth, blockHeight, blocks);
					aiPaddle.setFillColor(randomColor());
					aiPaddle.setOutlineColor(randomColor());
					playerPaddle.setFillColor(randomColor());
					playerPaddle.setOutlineColor(randomColor());
					isGameOver = false;
					scorebonus = 1;
					playerPaddle.reset(windowWidth / 2, windowHeight * 17 / 18);
					aiPaddle.reset(windowWidth / 2, windowHeight * 1 / 18);
					timer = rand() % 2;
					if (timer == 0)
						ball.reset(windowWidth / 2, playerPaddle.top() - 10);
					else
						ball.reset(windowWidth / 2, aiPaddle.bottom() + 10);
					
					pickup.despawn();
					timer = 0;
					timerTarget = 0;
					while (!Keyboard::isKeyPressed(Keyboard::Escape))
					{
						while (!isGameOver)
						{
							window.clear(Color::Black);
							window.pollEvent(event);
							if (event.type == Event::Closed)
							{
								window.close();
								break;
							}

							window.draw(background);
							score1.setString("Gracz: " + std::to_string(playerPaddle.getScore()));
							score2.setString("Przeciwnik: " + std::to_string(aiPaddle.getScore()));
							if (playerPaddle.getScore() > aiPaddle.getScore())
							{
								score2.setStyle(Text::Regular);
								score1.setStyle(Text::Bold);
							}
							else if (aiPaddle.getScore() > playerPaddle.getScore())
							{
								score1.setStyle(Text::Regular);
								score2.setStyle(Text::Bold);
							}
							ball.update(windowWidth, windowHeight);
							if (ball.bottom() >= windowHeight)
							{
								playerPaddle.destroy();
								isGameOver = true;
								if (playerPaddle.getScore() % 10 == 2 || playerPaddle.getScore() % 10 == 3 || playerPaddle.getScore() % 10 == 4)
									overviewsuffix = " punkty";
								else
									overviewsuffix = " punktow";
								if (playerPaddle.getScore() > aiPaddle.getScore() && aiPaddle.isDestroyed())
									overview.setString("Wygrales, uzyskujac " + std::to_string(playerPaddle.getScore()) + overviewsuffix);
								else
									overview.setString("Przegrales, uzyskujac " + std::to_string(playerPaddle.getScore()) + overviewsuffix);
								break;
							}
							if (ball.top() <= 0)
							{
								aiPaddle.destroy();
								ball.setLastPlayer(1);
							}
							if (playerPaddle.isDestroyed() == false)
							{
								playerPaddle.playerUpdate(windowWidth);
								collisionTest(playerPaddle, ball, scorebonus);
								if (pickup.isSpawned())
								{
									collisionTest(playerPaddle, ball, pickup, scorebonus);
								}
								window.draw(playerPaddle);
							}
							if (aiPaddle.isDestroyed() == false)
							{
								aiPaddle.aiUpdate(windowWidth, ball.left(), ball.right(), difficulty, timer, timerTarget);
								collisionTest(aiPaddle, ball, scorebonus);
								if (pickup.isSpawned())
								{
									collisionTest(aiPaddle, ball, pickup, scorebonus);
								}
								window.draw(aiPaddle);
							}

							for (auto& block : blocks) if (collisionTest(block, ball, pickup, playerPaddle, aiPaddle, scorebonus)) break;

							auto iterator = remove_if(begin(blocks), end(blocks), [](Block& block) {return block.isDestroyed(); });
							blocks.erase(iterator, end(blocks));

							window.draw(ball);
							if (pickup.isSpawned())
							{
								pickup.update(windowHeight);
								window.draw(pickup);
							}
							
							if (Keyboard::isKeyPressed(Keyboard::Z) && Keyboard::isKeyPressed(Keyboard::X))
							{
								playerPaddle.setFillColor(randomColor());
								playerPaddle.setOutlineColor(randomColor());
							}
							/*
							if (Keyboard::isKeyPressed(Keyboard::P))
								placeBlocks(blocksX, blocksY, blockWidth, blockHeight, blocks);
							*/
							if (begin(blocks) == end(blocks))
							{
								placeBlocks(blocksX, blocksY, blockWidth, blockHeight, blocks);
								scorebonus += 1;
							}

							timer++;

							window.draw(score1);
							window.draw(score2);
							for (auto& block : blocks)
								window.draw(block);
							window.display();
						}
						window.clear(Color::Black);
						window.draw(background);
						if (aiPaddle.isDestroyed() == false)
						{
							window.draw(aiPaddle);
						}
						window.draw(ball);
						if (pickup.isSpawned())
						{
							window.draw(pickup);
						}
						window.draw(score1);
						window.draw(score2);
						for (auto& block : blocks)
							window.draw(block);
						window.draw(gameOverText);
						window.draw(overview);
						window.draw(pressEscapeText);

						window.display();

						if (!window.isOpen())
							break;
					}
				}
				break;
			case Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		window.draw(menu);
		window.display();
	}
}

template <class T1, class T2> bool isIntersecting(T1& A, T2& B)
{
	return A.right() >= B.left() && A.left() <= B.right()
		&& A.bottom() >= B.top() && A.top() <= B.bottom();
}

bool collisionTest(Paddle& paddle, Ball& ball, int bonus)
{
	if (!isIntersecting(paddle, ball))
		return false;

	ball.setOutlineColor(paddle.getOutlineColor());
	ball.setFillColor(paddle.getFillColor());

	if (ball.top() >= paddle.bottom() - 6 && ball.top() <= paddle.bottom())
	{
		ball.moveDown();
		paddle.addScore(bonus);
		ball.setLastPlayer(paddle.getPlayerID());
	}
	if (ball.bottom() >= paddle.top() && ball.bottom() <= paddle.top() + 6)
	{
		ball.moveUp();
		paddle.addScore(bonus);
		ball.setLastPlayer(paddle.getPlayerID());
	}

	if (ball.getPosition().x < paddle.getPosition().x)
	{
		ball.moveLeft();
	}
	if (ball.getPosition().x > paddle.getPosition().x)
	{
		ball.moveRight();
	}
}

bool collisionTest(Block& block, Ball& ball, Pickup& pickup, Paddle& paddle1, Paddle& paddle2, int bonus)
{
	if (!isIntersecting(block, ball)) return false;

	block.destroy();
	ball.setOutlineColor(block.getOutlineColor());
	ball.setFillColor(block.getFillColor());
	ball.addBallVelocity(0.01);
	if (ball.getLastPlayer() == 1)
	{
		paddle1.addScore(bonus * 10);
	}
	else if (ball.getLastPlayer() == 2)
	{
		paddle2.addScore(bonus * 10);
	}
	int random = rand() % 6;
	if (!pickup.isSpawned() && random == 0)
	{
		pickup.spawn(block.getPosition(), ball.getLastPlayer());
		pickup.setOutlineColor(block.getFillColor());
	}

	float overlapLeft{ ball.right() - block.left() };
	float overlapRight{ block.right() - ball.left() };

	float overlapTop{ ball.bottom() - block.top() };
	float overlapBottom{ block.bottom() - block.top() };

	bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
	bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

	float minOverLapX{ ballFromLeft ? overlapLeft : overlapRight };
	float minOverLapY{ ballFromTop ? overlapTop : overlapBottom };

	if (abs(minOverLapX) < abs(minOverLapY))
	{
		ballFromLeft ? ball.moveLeft() : ball.moveRight();
	}
	else
	{
		ballFromTop ? ball.moveUp() : ball.moveDown();
	}
}

bool collisionTest(Paddle& paddle, Ball& ball, Pickup& pickup, int bonus)
{
	if (!isIntersecting(paddle, pickup)) return false;

	ball.addBallVelocity(0.01);
	paddle.addScore(bonus * 50);
	pickup.despawn();
	pickup.activate(pickup.getType(), ball, paddle);

}

void placeBlocks(unsigned int x, unsigned int y, unsigned int w, unsigned int h, vector<Block>& blocks)
{
	blocks.clear();
	for (int i = 0; i < y; i++)
	{
		Color blockFillColor = randomColor();
		Color blockOutlineColor = randomColor();
		for (int j = 0; j < x; j++)
		{
			blocks.emplace_back((j + 1)*(w + 10), (i + 10)*(h + 5), w, h);
			blocks.at(i*x + j).setFillColor(blockFillColor);
			blocks.at(i*x + j).setOutlineColor(blockOutlineColor);
		}
	}
}

Color randomColor()
{
	int random = rand() % 6;

	switch (random)
	{
	case 0:
		return Color::Blue;
	case 1:
		return Color::Cyan;
	case 2:
		return Color::Green;
	case 3:
		return Color::Magenta;
	case 4:
		return Color::Red;
	case 5:
		return Color::Yellow;
	}
}
