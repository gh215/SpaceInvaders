#include "SpaceInvaders_header.h"

void Bullet::move()
{
    if (globalClock.getTicks() % period == 0)
    {
        if (direction == Dir_bull::UP)
        {
            position.y--;
        }
        else if (direction == Dir_bull::DOWN)
        {
            position.y++;
        }
    }
}

bool Bullet::isOutOfBounds()
{
    return (position.y < 0 || position.y >= FIELD_HEIGHT);
}

void Bullet::draw(Screen& screen)
{
    screen.put(symb, position);
}