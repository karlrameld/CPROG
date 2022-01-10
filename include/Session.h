#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include "Player.h"
#include "Label.h"
#include <vector>

class Session
{
public:
	~Session();
	void setPlayer(Player *);
	void setLabel(Label *);
	void add(Component *);
	void remove(Component *);
	void run();

private:
	std::vector<Component *> comps;
	std::vector<Component *> added, removed;
	Player *player;
	Label *label;
};

#endif