#include "SpaceInvaders_header.h"

bool Alien::isHit(const Point& bulletPosition)
{
	if (bulletPosition.x == position.x && bulletPosition.y == position.y)
	{
		isAlive = false;
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