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
    if(other == 1 || other == 2 || other == 3)
        impact();
}
bool Bullet::collsionAftermath(int other)
{
    if (other == 4 || other == 0)
        return false;
    return true;
}
