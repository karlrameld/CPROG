#ifndef PLAYER_H
#define PLAYER_H
#include "Component.h"
#include "System.h"
#include <SDL2/SDL_image.h>

class Player : public Component
{
public:
    ~Player();
    void draw() const;
    void tick();
    void collisionHandler(int other);
    bool collsionAftermath(int other);
    void moveUp(int x, int y);
    void moveDown(int x, int y);
    void moveLeft(int x, int y);
    void moveRight(int x, int y);
    void mouseDown(int x, int y);
    virtual void fire() = 0;

protected:
    Player(int x, int y) : Component((x / 2) - 60, (y / 2) - 60, 120, 120, 1)
    {
        texture = IMG_LoadTexture(sys.ren, (resPath + "images/ship.png").c_str());
        shoot = false;
        right = false;
        left = false;
        up = false;
        down = false;
    }

private:
    SDL_Texture *texture;
    bool shoot;
    bool right;
    bool left;
    bool up;
    bool down;
    Player(const Player &) = delete;
    const Player &operator=(const Player &) = delete;
};

#endif
