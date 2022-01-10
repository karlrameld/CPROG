#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include "Player.h"
#include <vector>

class Session
{
public:
	~Session();
	void setPlayer(Player *player);
	void add(Component *comp);
	void remove(Component *comp);
	void run();

private:
	std::vector<Component *> comps;
	std::vector<Component *> added, removed;
	Player *player;
};

#endif