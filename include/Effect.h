#ifndef Effect_H
#define Effect_H

#include "Component.h"
#include "System.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Effect : public Component
{
public:
    virtual ~Effect();
    void draw() const;
    void tick();
    void collisionHandler(int other) {}
    bool collsionAftermath(int other) { return false; };

protected:
    Effect(int x, int y, std::string imgPath, int w, int h, int d) : Component(x, y, 60, 60, 0)
    {
        heightFrames = h;
        widthFrames = w;
        totalFrames = heightFrames * widthFrames;
        delay = d;
        counter = delay;
        SDL_Surface *temp = IMG_Load((resPath + imgPath).c_str());
        texture = SDL_CreateTextureFromSurface(sys.ren, temp);
        SDL_QueryTexture(texture, NULL, NULL, &iRect.w, &iRect.h);
        iRect.w /= widthFrames;
        iRect.h /= heightFrames;
        iRect.x = 0;
        iRect.y = 0;
        SDL_FreeSurface(temp);
    }

private:
    SDL_Texture *texture;
    SDL_Rect iRect;
    int totalFrames;
    int heightFrames;
    int widthFrames;
    int delay;
    int counter;
    int currentframe = 0;
    Effect(const Effect &) = delete;
    const Effect &operator=(const Effect &) = delete;
};

#endif