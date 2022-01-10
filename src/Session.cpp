#include "Session.h"
#include <SDL2/SDL.h>
#include "Component.h"
#include "Player.h"
#include "System.h"
#include <iostream>

using namespace std;

#define FPS 144

Session::~Session()
{
	for (Component *c : comps)
	{
		delete[] c;
	}
	for (Component *c : added)
	{
		delete[] c;
	}
	for (Component *c : removed)
	{
		delete[] c;
	}
}

void Session::setPlayer(Player *play)
{
	player = play;
	added.push_back(play);
}

void Session::add(Component *comp)
{
	added.push_back(comp);
}

void Session::remove(Component *comp)
{
	removed.push_back(comp);
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}

void Session::run()
{
	bool quit = false;
	Uint32 tickInterval = 200 / FPS;
	while (!quit)
	{
		Uint32 nextTick = SDL_GetTicks() + tickInterval;
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				player->mouseDown(event.button.x, event.button.y);
				break;
			default:
				break;
			}
		}
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W])
		{
			player->moveUp(event.button.x, event.button.y);
		}
		if (state[SDL_SCANCODE_S])
		{
			player->moveDown(event.button.x, event.button.y);
		}
		if (state[SDL_SCANCODE_A])
		{
			player->moveLeft(event.button.x, event.button.y);
		}
		if (state[SDL_SCANCODE_D])
		{
			player->moveRight(event.button.x, event.button.y);
		}

		for (Component *c : comps)
			c->tick();

		for (Component *c : added)
			comps.push_back(c);
		added.clear();

		for (Component *c : comps)
		{
			SDL_Rect check = c->getRect();
			for (Component *c2 : comps)
			{
				SDL_Rect collider = c2->getRect();
				if (!(c->Compare(c2)))
				{
					if (checkCollision(check, collider))
					{
						c->collisionHandler(c2->getType());
						if (c->collsionAftermath(c2->getType()))
							removed.push_back(c);
					}
				}
			}
		}

		for (Component *c : removed)
			for (vector<Component *>::iterator i = comps.begin();
				 i != comps.end();)
				if (*i == c)
				{
					i = comps.erase(i);
				}
				else
					i++;
		removed.clear();

		SDL_SetRenderDrawColor(sys.ren, 255, 255, 255, 255);
		SDL_RenderClear(sys.ren);
		SDL_RenderCopy(sys.ren, sys.bgImage, NULL, NULL);
		for (Component *c : comps)
			c->draw();
		SDL_RenderPresent(sys.ren);

		int delay = nextTick - SDL_GetTicks();
		bool b = false;
		for (Component *c : comps)
		{
			if (c->Compare(player))
				b = true;
		}
		if (!b)
			quit = true;
		if (delay > 0)
			SDL_Delay(delay);
	} // yttre while
}