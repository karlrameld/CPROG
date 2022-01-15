#include "Session.h"

using namespace std;

#define FPS 360

Session::~Session()
{ // idk if I should delete player and label separately here, I get a segmentation fault when I do which I
//iterporate as a no, but then again I'm not that smart
	for (Component *c : comps)
	{
		delete c;
	}
	for (Component *c : added)
	{
		delete c;
	}
	for (Component *c : removed)
	{
		delete c;
	}
}

void Session::setPlayer(Player *play)
{
	player = play;
	added.push_back(play);
}

void Session::setLabel(Label *l)
{
	label = l;
	added.push_back(label);
}

void Session::add(Component *comp)
{
	added.push_back(comp);
}

void Session::remove(Component *comp)
{
	removed.push_back(comp);
}

bool Session::collision(SDL_Rect one, SDL_Rect two) // this might be hard to follow so explanation is provided.
{ // this works by checking if opposing sides of the rects don't intersect and returing false if that condition is met
// source: https://gamedev.net/forums/topic/594298-very-simple-collision-detection-in-sdl-and-c/4767560/
	if (one.y + one.h <= two.y || // if bottom of one(y cord + height) lower than top of two(y cord)
		one.y >= two.y + two.h || // if top of one(y cord) bellow bottom of two(y cord + height)
		one.x + one.w <= two.x || // if right side of one(x cord + width) left of the left side of two(x cord)
		one.x >= two.x + two.w)	  // if left side of one(x cord) right of the right side of two(x cord + width)
		return false;
	return true;
}

void Session::hit(Component *c)
{
	int x = c->getType();
	switch (x)
	{
	case 2:
		label->decreaseValue();
		break;
	case 3:
		label->increaseValue();
		break;
	default:
		break;
	}
}

void Session::run()
{
	int gameOver = 10000; // tics until auto close
	bool quit = false;
	Uint32 tickInterval = 1000 / FPS;
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
		// this happens outside while SDL_PollEvent loop to make movements smoother.
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
					if (collision(check, collider))
					{
						c->collisionHandler(c2->getType());
						if (c->collsionAftermath(c2->getType()))
							removed.push_back(c);
						if (c->getType() == 4)
							hit(c2);
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
		{
			if (gameOver == 10000)
			{
				tickInterval = 10;
				Label *l = Label::getInstance((screenWidth / 2) - 150, (screenHeight / 2) - 50, 300, 100, "Game Over! Score: ", 100, label->getValue());
				add(l);
				remove(label);
			}
			if (gameOver == 0)
				quit = true;
			gameOver--;
		}
		if (delay > 0)
			SDL_Delay(delay);
	} // yttre while
}
