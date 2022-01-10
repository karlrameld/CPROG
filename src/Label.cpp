#include "Label.h"
#include <iostream>

void Label::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.ren, texture, NULL, &rect);
}

Label::~Label()
{
    SDL_DestroyTexture(texture);
}

void Label::increaseValue()
{
    data++;
    create();
}

void Label::decreaseValue()
{
    data--;
    create();
}

void Label::create()
{
    SDL_DestroyTexture(texture);
    SDL_Surface *text =
        TTF_RenderText_Solid(TTF_OpenFont((resPath + "fonts/default.ttf").c_str(), size), (base + std::to_string(data)).c_str(), {255, 255, 255});
    texture = SDL_CreateTextureFromSurface(sys.ren, text);
    SDL_FreeSurface(text);
}
