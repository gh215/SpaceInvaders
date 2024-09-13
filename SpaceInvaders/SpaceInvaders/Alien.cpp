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

bool Alien::isOnFire(Point position, vector<Alien>& aliens)
{
	// ���������, ���� �� ������������� ���� ��������
	for (Alien& alien : aliens)
	{
		// ���� ������������� ��������� ����� ����� ������� ���������������
		if (alien.getIsAlive() && alien.getPosition().x == position.x && alien.getPosition().y > position.y &&
			//������������� �������� �����������, ������� ��������� ������� ������ � ������ ������� ����
			alien.getPosition().y < FIELD_HEIGHT - DEFENDED_ZONE)
		{
			return true; // ����� ������� ���� ������ �������
		}
	}
	return false; 
}

bool Alien::tryShoot(Point position, vector<Alien>& aliens, double currentTime)
{
	if (currentTime - lastShotTime < ALIEN_SHOOT_COOLDOWN + (rand() % 100) / 100.0) return false;
	// ���������� ��������� ����� �� 0 �� 99
	if (rand() % 100 < 5 && !isOnFire(position, aliens)) // ��������, 5% ���� �� �������
	{
		lastShotTime = currentTime;
		return true;
	}
	return false;
}