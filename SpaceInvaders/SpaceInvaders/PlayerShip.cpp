#include "SpaceInvaders_header.h"

void PlayerShip::draw(Screen& screen)
{
    screen.put('^', { position.x , position.y });
    screen.put('^', { position.x - 1, position.y + 1 });
    screen.put('^', { position.x, position.y + 1 });
    screen.put('^', { position.x + 1, position.y + 1 });
}

void PlayerShip::move()
{
    Screen screen;

    if (direction == Dir::LEFT && position.x > 1) 
    {
        position.x--;
    }
    else if (direction == Dir::RIGHT && position.x < FIELD_WIDTH - 2) 
    {
        position.x++;
    }
}

void PlayerShip::tryShoot()
{
    double currentTime = globalClock.getTicks() / 10.0;
    if (canShoot(currentTime))
    {
        shoot = true;
        updateLastShotTime(currentTime);
    }
}