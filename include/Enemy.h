#ifndef ENEMY_H
#define ENEMY_H

#include "Component.h"
#include "System.h"
#include <SDL2/SDL_image.h>

class Enemy : public Component
{
public:
    ~Enemy();
    void draw() const;
    void tick();
    void collisionHandler(int other);
    bool collsionAftermath(int other);
    virtual void action() = 0;
protected:
    Enemy(int x, std::string imgPath) : Component(x, -60, 60, 60, 3)
    {
        texture = IMG_LoadTexture(sys.ren, (resPath + imgPath).c_str());
    }
private:
    SDL_Texture *texture;
};

#endif