#include "SpaceInvaders_header.h"

void PlayerShip::draw(Screen& screen)
{
    if (!isInvincible || (globalClock.getTicks() / 5) % 4 == 0)
    {
        screen.put('^', { position.x , position.y });
        screen.put('^', { position.x - 1, position.y + 1 });
        screen.put('^', { position.x, position.y + 1 });
        screen.put('^', { position.x + 1, position.y + 1 });
    }
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

bool PlayerShip::isHit(Point bulletPosition)
{
    if (!isInvincible &&
        bulletPosition.x >= position.x - 1 && bulletPosition.x <= position.x + 1 &&
        bulletPosition.y >= position.y && bulletPosition.y <= position.y + 1)
    {
        lives--;
        isInvincible = true;
        invinsible_timer = INVINCIBLE_TIME * 1000 / SLEEP;
        return true;
    }
    return false;
}
void PlayerShip::updateInvincibility(double currentTime)
{
    if (isInvincible) invinsible_timer--;
    if (invinsible_timer == 0) isInvincible = false;
}