#include "SpaceInvaders_header.h"

void Game::update()
{
	moveAliens();
	playerShip.move();
	if (playerShip.hasShot())
	{
		playerBullets.push_back(Bullet(playerShip.getPosition(), false));
	}
	moveBullets();
}

void Game::moveAliens()
{
	bool needToDrop = false;

	// ѕровер€ем границы только дл€ крайних инопланет€н
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
		// —пускаем всех инопланет€н вниз и мен€ем направление
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
			if (alien.tryShoot(alien.getPosition(), aliens, globalClock.getTicks() / 10.0))
			{
				alienBullets.push_back(Bullet({ alien.getPosition().x, alien.getPosition().y + 1 }, true));
			}
		}
	}
}

void Game::run()
{
	createAlienGrid();
	while (true)
	{
		globalClock.tick();
		draw();
		update();
		processInput();
		Sleep(SLEEP);
	}
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
			int x = ALIEN_INITIAL_POS + col * ALIEN_INTERVAL;
			int y = ALIEN_INITIAL_POS + row * (ALIEN_INTERVAL - 2); 
			aliens.push_back(Alien(x, y));
		}
	}
}

void Game::moveBullets()
{
	for (auto it = playerBullets.begin(); it != playerBullets.end();)
	{
		it->move();

		if (it->isOutOfBounds())
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

		if (it->isOutOfBounds())
		{
			it = alienBullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}


void Game::draw()
{
	playerShip.draw(screen);

	for (auto& alien : aliens)
	{
		alien.draw(screen);
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
	//
	//    for (auto& blast : blasts) 
	//    {
	//        blast.draw();
	//    }
}

