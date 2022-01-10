#include "Neutral.h"

Neutral::~Neutral()
{
    SDL_DestroyTexture(texture);
}
void Neutral::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.ren, texture, NULL, &rect);
}
void Neutral::tick()
{
    if (rect.y >= screenHeight)
        delComp();
    else
    {
        movement();
    }
}
void Neutral::collisionHandler(int other)
{
}
bool Neutral::collsionAftermath(int other)
{
    if (other == 1 || other == 4)
        return true;
    return false;
}