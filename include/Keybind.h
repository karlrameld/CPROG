#ifndef KEYBIND_H
#define KEYBIND_H

#include "Component.h"

class Keybind : public Component
{
public:
    ~Keybind(){};
    void draw() const {}
    void tick();
    void collisionHandler(int other) {}
    bool collsionAftermath(int other) { return false; }
    virtual void action() = 0;

protected:
    Keybind(SDL_Scancode k) : Component(0, 0, 0, 0, 0)
    {
        key = k;
    }

private:
    SDL_Scancode key;
    Keybind(const Keybind &) = delete;
    const Keybind &operator=(const Keybind &) = delete;
};

#endif