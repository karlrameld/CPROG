#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL2/SDL.h>
#include <iostream>

class Component
{
public:
	virtual ~Component() = 0;
	virtual void draw() const = 0;
	SDL_Rect getRect() const { return rect; }
	virtual void tick() = 0;
	int getType() const { return type; }
	bool Compare(const Component *other)
	{
		return rect.x == other->getRect().x && rect.y == other->getRect().y && rect.w == other->getRect().w && rect.h == other->getRect().h;
	}
	virtual void collisionHandler(int other) = 0;
	virtual bool collsionAftermath(int other) = 0;
	void delComp();
	void addComp(Component *);

protected:
	Component(int x, int y, int w, int h, int t) : rect{x, y, w, h}
	{
		type = t; // 0 = no type, 1 = player, 2 = neutral, 3 = enemy, 4 = bullet
	}
	SDL_Rect rect;

private:
	int type;
	Component(const Component &) = delete;
	const Component &operator=(const Component &) = delete;
};

#endif
