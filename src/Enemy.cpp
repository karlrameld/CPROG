#include "Enemy.h"

Enemy::~Enemy()
{
    SDL_DestroyTexture(texture);
}
void Enemy::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.ren, texture, NULL, &rect);
}
void Enemy::tick()
{
    if (getRect().y >= screenHeight + 60)
        delComp();
    else
    {
        action();
    }
}
void Enemy::collisionHandler(int other)
{
}
bool Enemy::collsionAftermath(int other)
{
    if (other == 1 || other == 4)
        return true;
    return false;
}