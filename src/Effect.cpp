#include "Effect.h"

Effect::~Effect()
{
    SDL_DestroyTexture(texture);
}
void Effect::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.ren, texture, &iRect, &rect);
}
void Effect::tick()
{
    if (counter == 0)
    {
        currentframe++;
        if (currentframe > totalFrames)
        {
            delComp();
        }
        else if (currentframe % widthFrames == 0)
        {
            iRect.x = 0;
            iRect.y += iRect.h;
        }
        else
        {
            iRect.x += iRect.w;
        }
        counter = delay;
    }
    counter--;
}
