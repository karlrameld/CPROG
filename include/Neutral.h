#ifndef NEUTRAL_H
#define NEUTRAL_H

#include "Component.h"
#include "System.h"
#include <SDL2/SDL_image.h>

class Neutral : public Component
{
public:
    ~Neutral();
    void draw() const;
    void tick();
    void collisionHandler(int other);
    bool collsionAftermath(int other);
    virtual void movement() = 0;

protected:
    Neutral(int x, std::string imgPath) : Component(x, -60, 60, 60, 2)
    {
        texture = IMG_LoadTexture(sys.ren, (resPath + imgPath).c_str());
    }

private:
    SDL_Texture *texture;
    Neutral(const Neutral &) = delete;
    const Neutral &operator=(const Neutral &) = delete;
};

#endif