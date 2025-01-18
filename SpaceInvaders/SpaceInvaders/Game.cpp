#include "SpaceInvaders_header.h"

Clock globalClock;

void Game::update()
{
	double currentTime = globalClock.getTicks() / 10.0;
	playerShip.updateInvincibility(currentTime);
	moveAliens();
	playerShip.move();
	if (playerShip.hasShot())
	{
		playerBullets.push_back(Bullet(playerShip.getPosition(), false));
	}
	moveBullets();
	removeDeadAliens();
}

void Game::moveAliens()
{
	bool needToDrop = false;

	for (Alien& alien : aliens)
	{
		if (!alien.getIsAlive()) continue;

		if (alien.isOnEdge())
		{
			needToDrop = true;
			break;
		}
	}

	if (needToDrop)
	{
		for (Alien& alien : aliens)
		{
			alien.drop();
			alien.reverseDir();
		}	
	}
	else
	{
		for (Alien& alien : aliens)
		{
			alien.move();
			if (alien.tryShoot(aliens))
			{
				alienBullets.push_back(Bullet({ alien.getPosition().x, alien.getPosition().y + 1 }, true));
			}
		}
	}

	for (Blast& blast : blasts)
	{
		blast.move(aliens[0].getDirection()); 
	}
}

void Game::run()
{
	createAlienGrid();
	while (playerShip.getLives() != 0 && aliens.size() != 0)
	{
		globalClock.tick();
		draw();
		update();
		processInput();
		Sleep(SLEEP);
		if (isAlienOnDefZone()) break;
	}
	if (playerShip.getLives() == 0 || isAlienOnDefZone())
	{
		screen.showGameOverMessage();
		screen.moveCursorToBottom();
	}
	else
	{
		screen.showWonMessage();
		screen.moveCursorToBottom();
	}

}

void Game::removeDeadAliens()
{
	aliens.erase(std::remove_if(aliens.begin(), aliens.end(), [](const Alien& a)
	{ 
		return !a.getIsAlive();
	}), aliens.end());
}

void Game::checkPause()
{
	screen.showPauseMessage();
	_getch();
	screen.clearPauseMessage();
	screen.drawBorders();
	draw();
}

void Game::processInput()
{
	if (_kbhit())
	{
		int key = _getch();
		if (key == ARROW)
		{
			key = _getch();
			if (key == LEFT)
			{
				playerShip.setDir(Dir::LEFT);
			}
			if (key == RIGHT)
			{
				playerShip.setDir(Dir::RIGHT);
			}
		}
		else if (key == ' ')
		{
			playerShip.tryShoot();
		}
		if (key == PAUSE_LOWER || key == PAUSE_UPPER)
		{
			checkPause();
		}
	}
	else
	{
		playerShip.setDir(Dir::STOP);
	}
}

void Game::createAlienGrid()
{
	for (int row = 0; row < ALIEN_ROWS; row++)
	{
		for (int col = 0; col < ALIEN_COLUMNS; col++)
		{
			int x = ALIEN_INITIAL_POS + col * ALIEN_H_INTERVAL;
			int y = ALIEN_INITIAL_POS + row * ALIEN_V_INTERVAL;
			aliens.push_back(Alien(x, y));
		}
	}
}

void Game::moveBullets()
{
	for (auto it = playerBullets.begin(); it != playerBullets.end();)
	{
		it->move();

		bool hit = false;
		for (auto& alien : aliens)
		{
			if (alien.getIsAlive() && alien.isHit(it->getPosition(), blasts))
			{
				int scoreIncrease = alien.getIsAlive() ? 50 : 150;
				screen.setScoreAndLives(screen.getScore() + scoreIncrease, playerShip.getLives());
				hit = true;
				break;
			}
		}

		if (hit || it->isOutOfBounds())
		{
			it = playerBullets.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = alienBullets.begin(); it != alienBullets.end();)
	{
		it->move();

		if (playerShip.isHit(it->getPosition()))
		{
			screen.setScoreAndLives(screen.getScore(), playerShip.getLives());
			it = alienBullets.erase(it);
		}
		else if (it->isOutOfBounds())
		{
			it = alienBullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool Game::isAlienOnDefZone()
{
	for (auto alien : aliens)
	{
		if (alien.getPosition().y == FIELD_HEIGHT - DEFENDED_ZONE - 1) return true;		
	}
	return false;
}


void Game::draw()
{
	playerShip.draw(screen);

	for (auto& alien : aliens)
	{
		if (alien.getIsAlive())
		{
			alien.draw(screen);
		}
	}

	screen.draw();

	for (auto& bullet : playerBullets) 
	{
		bullet.draw(screen);
	}

	for (auto& bullet : alienBullets)
	{
		bullet.draw(screen);
	}

	for (auto it = blasts.begin(); it != blasts.end();)
	{
		it->draw(screen);
		it->tick();
		if (!it->isAlive())
		{
			it = blasts.erase(it);
		}
		else
		{
			++it;
		}
	}
}

