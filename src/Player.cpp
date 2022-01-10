#include <SDL2/SDL.h>
#include "Player.h"
#include "Bullet.h"
#include "System.h"

Player::~Player()
{
    SDL_DestroyTexture(texture);
}

void Player::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.ren, texture, NULL, &rect);
}
void Player::collisionHandler(int other)
{
}
bool Player::collsionAftermath(int other)
{
    if (other == 0)
        return false;
    return true;
}
void Player::tick()
{
    if (shoot)
    {
        fire();
    }
    if (rect.x < screenWidth - 120 && right)
        rect.x++;
    if (rect.x > 0 && left)
        rect.x--;
    if (rect.y < screenHeight - 120 && down)
        rect.y++;
    if (rect.y > 0 && up)
        rect.y--;
    shoot = false;
    right = false;
    left = false;
    up = false;
    down = false;
}
void Player::moveUp(int x, int y)
{
    up = true;
}
void Player::moveDown(int x, int y)
{
    down = true;
}
void Player::moveLeft(int x, int y)
{
    left = true;
}
void Player::moveRight(int x, int y)
{
    right = true;
}
void Player::mouseDown(int x, int y)
{
    shoot = true;
}