#ifndef LABEL_H
#define LABEL_H

#include "System.h"
#include "Component.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Label : public Component
{
public:
    static Label *getInstance(int x, int y, int w,
                              int h, std::string s, int size, int data)
    {
        return new Label(x, y, w, h, s, size, data);
    }
    virtual ~Label();
    void draw() const;
    void tick(){};
    void collisionHandler(int other) {}
    bool collsionAftermath(int other) { return false; }
    int getValue() { return data; }
    void increaseValue();
    void decreaseValue();
    void create();

private:
    SDL_Texture *texture;
    std::string base;
    int size;
    int data;
    Label(int x, int y, int w, int h, std::string s, int si, int d) : Component(x, y, w, h, 0)
    {
        base = s;
        size = si;
        data = d;
        SDL_Surface *temp =
            TTF_RenderText_Solid(TTF_OpenFont((resPath + "fonts/default.ttf").c_str(), size), (base + std::to_string(data)).c_str(), {255, 255, 255});
        texture = SDL_CreateTextureFromSurface(sys.ren, temp);
        SDL_FreeSurface(temp);
    }
    Label(const Label &) = delete;
    const Label &operator=(const Label &) = delete;
};

#endif