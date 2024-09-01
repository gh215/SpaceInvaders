#include "SpaceInvaders_header.h"

void PlayerShip::draw(Screen& screen)
{
    screen.put('^', { position.x , position.y });
    screen.put('^', { position.x - 1, position.y + 1 });
    screen.put('^', { position.x, position.y + 1 });
    screen.put('^', { position.x + 1, position.y + 1 });
}

void PlayerShip::move(char direction)
{
    Screen screen;

    if (direction == LEFT && position.x > 1) 
    {
        position.x--;
    }
    else if (direction == RIGHT && position.x < FIELD_WIDTH - 2) 
    {
        position.x++;
    }
}