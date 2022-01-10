#include "Bullet.h"
#include <iostream>
Bullet::~Bullet()
{
    SDL_DestroyTexture(texture);
}
void Bullet::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.ren, texture, NULL, &rect);
}
void Bullet::tick()
{
    if (rect.y <= 0 || rect.y == screenHeight)
        delComp();
    else
    {
        action();
    }
}
void Bullet::collisionHandler(int other)
{
}
bool Bullet::collsionAftermath(int other)
{
    if (other == 4)
        return false;
    return true;
}
