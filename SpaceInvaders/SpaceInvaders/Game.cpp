#include "SpaceInvaders_header.h"

void Game::update()
{
	moveAliens();
}

void Game::moveAliens()
{
	bool needToDrop = false;

	// ��������� ������� ������ ��� ������� �����������
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
		// �������� ���� ����������� ���� � ������ �����������
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
			if (key == LEFT || key == RIGHT)
			{
				playerShip.move(key);
			}
		}
	}
}

void Game::createAlienGrid()
{
	// ������� ����������� � ���� �����: 10 �� ����������� � 3 �� ���������
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


void Game::draw()
{
	playerShip.draw(screen);

	for (auto& alien : aliens)
	{
		alien.draw(screen);
	}

	screen.draw();
	//
	//    for (auto& bullet : playerBullets) 
	//    {
	//        bullet.draw();
	//    }
	//
	//    for (auto& blast : blasts) 
	//    {
	//        blast.draw();
	//    }
}

