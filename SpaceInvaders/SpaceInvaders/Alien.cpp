#include "SpaceInvaders_header.h"

bool Alien::isHit(const Point& bulletPosition, vector<Blast>& blasts)
{
	if (isAlive && bulletPosition.x >= position.x - 1 && bulletPosition.x <= position.x + 1 &&
		bulletPosition.y >= position.y && bulletPosition.y <= position.y + 1)
	{
		hitsTaken++;
		if (hitsTaken == 2)
		{
			isAlive = false;
			blasts.push_back(Blast(position));
		}
		return true;
	}
	return false;
}

void Alien::drop()
{
	position.y++;
}

void Alien::draw(Screen& screen)
{
	screen.put('#', { position.x - 1, position.y });
	screen.put('#', { position.x, position.y });
	screen.put('#', { position.x + 1, position.y });

	screen.put('$', { position.x, position.y + 1 });
}

void Alien::move()
{
	if (globalClock.getTicks() % ALIEN_PERIOD != 0) return;
	if (currentDirection == Dir::LEFT)
	{
		position.x--;
	}
	else if (currentDirection == Dir::RIGHT)
	{
		position.x++;
	}
}

bool Alien::isOnFire(vector<Alien>& aliens)
{
	// ѕровер€ем, есть ли инопланет€нин ниже текущего
	for (Alien& alien : aliens)
	{
		// ≈сли инопланет€нин находитс€ пр€мо перед текущим инопланет€нином
		if (alien.getIsAlive() && alien.getPosition().x == position.x && alien.getPosition().y > position.y)
		{
			return true; // ѕеред кораблЄм есть другой корабль
		}
	}
	return false; 
}

bool Alien::tryShoot(vector<Alien>& aliens)
{
	if ((rand() % ALIEN_SHOOT_PARAM) < 1 && !isOnFire(aliens))
	{
		return true;
	}
	return false;
}