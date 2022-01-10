#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "System.h"
#include <SDL2/SDL_image.h>

class Bullet : public Component
{
public:
    ~Bullet();
    void draw() const;
    void tick();
    void collisionHandler(int other);
    bool collsionAftermath(int other);
    virtual void action() = 0;

protected:
    Bullet(int x, int y, std::string imgPath) : Component(x, y, 30, 30, 4)
    {
        texture = IMG_LoadTexture(sys.ren, (resPath + imgPath).c_str());
    }

private:
    SDL_Texture *texture;
    Bullet(const Bullet &) = delete;
    const Bullet &operator=(const Bullet &) = delete;
};

#endif