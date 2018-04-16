#include "stdafx.h"
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Pickup.h"
#include "Menu.h"
#include "Score.h"
#include "GameOver.h"

using namespace sf;
using namespace std;

template <class T1, class T2> bool isIntersecting(T1& A, T2& B);

bool collisionTest(Paddle& paddle, Ball& ball, int bonus);

bool collisionTest(Block& block, Ball& ball, Pickup& pickup, Paddle& paddle1, Paddle& paddle2, int bonus);

bool collisionTest(Paddle& paddle, Ball& ball, Pickup& pickup, int bonus);

void placeBlocks(unsigned int x, unsigned int y, unsigned int w, unsigned int h, vector<Block> &blocks);

bool blockTimeOut(vector<Block> &blocks, int &timer, int timerTarget);

Color randomColor();

int main()
{
	srand(time(NULL));
	int scorebonus;
	int difficulty;
	int timer;
	int timerTarget;
	int blockTimer;
	int blockTimerTarget = 600;
	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 720;
	bool isGameOver = false;
	RenderWindow window{ VideoMode{ windowWidth, windowHeight }, "Ponganoid", Style::Fullscreen };
	Paddle playerPaddle(windowWidth / 2, windowHeight * 17 / 18, 1);
	Paddle aiPaddle(windowWidth / 2, windowHeight / 18, 2);
	Ball ball(windowWidth / 2, playerPaddle.top() - 50);
	Texture backgroundTexture;
	Texture menuBackgroundTexture;
	Sprite background;
	Sprite menuBackground;
	Score score(windowWidth, windowHeight);
	GameOver gameOver(windowWidth, windowHeight);
	Pickup pickup(-10, -10);
	Event event;
	Menu menu(windowWidth, windowHeight);
	unsigned blocksX{ 17 }, blocksY{ 6 }, blockWidth{ 60 }, blockHeight{ 20 };
	vector<Block> blocks;
	Color blockFillColor;
	Color blockOutlineColor;

	window.setFramerateLimit(60);

	backgroundTexture.loadFromFile("background.jpg");
	background.setTexture(backgroundTexture);
	menuBackgroundTexture.loadFromFile("menuBackground.jpg");
	menuBackground.setTexture(menuBackgroundTexture);

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
					
					blockTimer = 0;
					placeBlocks(blocksX, blocksY, blockWidth, blockHeight, blocks);
					aiPaddle.setColor(randomColor(), randomColor());
					playerPaddle.setColor(randomColor(), randomColor());
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

							score.setScoreText(playerPaddle.getScore(), aiPaddle.getScore());
							
							ball.update(windowWidth, windowHeight);
							if (ball.bottom() >= windowHeight)
							{
								playerPaddle.destroy();
								isGameOver = true;
								gameOver.setOverviewSuffix(playerPaddle.getScore(), aiPaddle.getScore(), aiPaddle.isDestroyed());
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

							blockTimeOut(blocks, blockTimer, blockTimerTarget);

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
								playerPaddle.setColor(randomColor(), randomColor());
							}

							if (Keyboard::isKeyPressed(Keyboard::M) && Keyboard::isKeyPressed(Keyboard::N))
							{
								aiPaddle.setColor(randomColor(), randomColor());
							}
							
							if (blocks.empty())
							{
								placeBlocks(blocksX, blocksY, blockWidth, blockHeight, blocks);
								scorebonus += 1;
							}

							timer++;

							window.draw(score);

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
						window.draw(score);
						for (auto& block : blocks)
							window.draw(block);
						window.draw(gameOver);

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
		window.draw(menuBackground);
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

	if (ball.top() >= paddle.bottom() - 8 && ball.top() <= paddle.bottom())
	{
		ball.moveDown();
		paddle.addScore(bonus);
		ball.setLastPlayer(paddle.getPlayerID());
	}
	if (ball.bottom() >= paddle.top() && ball.bottom() <= paddle.top() + 8)
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
	ball.addBallVelocity(0.02);
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
	float overlapBottom{ block.bottom() - ball.top() };

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

	ball.addBallVelocity(0.02);
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

bool blockTimeOut(vector<Block>& blocks, int & timer, int timerTarget)
{
	if (blocks.size() > 4)
		return false;
	timer++;
	if (timer == timerTarget)
	{
		blocks.at(0).destroy();
		timer = 0;
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
