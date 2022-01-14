#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <SDL2/SDL.h>
#include "Session.h"
#include "Component.h"
#include "Player.h"
#include "Bullet.h"
#include "Spawner.h"
#include "Neutral.h"
#include "Enemy.h"
#include "Label.h"
#include "Effect.h"
#include "Keybind.h"
#include <string>
#include <random>
#include <iostream>

// Paths to resource folders. Change to your own path!
// std::string resPath = "/Users/kjellna/dev/cpp21/f13b_v2/resources/";
std::string resPath = "./resources/";
int screenWidth = 1920;
int screenHeight = 1080;
std::random_device rd;
std::mt19937 rng(rd());
Session ses;

class Explosion : public Effect
{
public:
	static Explosion *getInstance(int x, int y)
	{
		return new Explosion(x, y);
	}
	~Explosion()
	{
	}

private:
	Explosion(int x, int y) : Effect(x, y, "images/expsheet.png", 5, 5, 50) {}
	Explosion(const Explosion &) = delete;
	const Explosion &operator=(const Explosion &) = delete;
};

class Laser : public Bullet
{
public:
	static Laser *getInstance(int x, int y)
	{
		return new Laser(x, y);
	}
	~Laser()
	{
	}
	void action()
	{
		rect.y -= 2;
	}
	void impact()
	{
		Explosion *e = Explosion::getInstance((rect.x - (rect.w / 2)), rect.y);
		addComp(e);
	}

private:
	Laser(int x, int y) : Bullet(x, y, "images/laser.png") {}
	Laser(const Laser &) = delete;
	const Laser &operator=(const Laser &) = delete;
};

class Ball : public Bullet
{
public:
	static Ball *getInstance(int x, int y)
	{
		return new Ball(x, y);
	}
	~Ball()
	{
	}
	void action()
	{
		rect.y++;
	}
	void impact()
	{
	}

private:
	Ball(int x, int y) : Bullet(x, y, "images/ball.png") {}
	Ball(const Ball &) = delete;
	const Ball &operator=(const Ball &) = delete;
};

class Shooter : public Enemy
{
public:
	static Shooter *getInstance(int x)
	{
		return new Shooter(x);
	}
	~Shooter()
	{
	}
	void action()
	{
		if (rect.y < 0)
		{
			rect.y++;
		}
		else
		{
			if (move)
			{
				rect.x--;
				if (rect.x == 0)
					move = false;
			}
			else
			{
				rect.x++;
				if (rect.x == screenWidth - 60)
					move = true;
			}
			if (reload == 0)
			{
				if (wait == 0)
				{
					Ball *b = Ball::getInstance(rect.x + 30, rect.y + 60);
					addComp(b);

					Mix_PlayChannel(-1, Mix_LoadWAV((resPath + "sounds/enemysound.wav").c_str()), 0);
					salvo--;
					if (salvo > 0)
						wait = 200;
				}
				else
				{
					wait--;
				}
			}
			else
			{
				reload--;
			}
			if (reload == 0 && salvo == 0 && wait == 0)
			{
				reload = 5000;
				salvo = 5;
				wait = 200;
			}
		}
	}

private:
	int salvo = 3;
	int reload = 1000;
	int wait = 200;
	bool move = false;
	Shooter(int x) : Enemy(x, "images/medium.png") {}
	Shooter(const Shooter &) = delete;
	const Shooter &operator=(const Shooter &) = delete;
};

class Dropper : public Enemy
{
public:
	static Dropper *getInstance(int x)
	{
		return new Dropper(x);
	}
	~Dropper()
	{
	}
	void action()
	{
		rect.y++;
		if (counter > 180 && rect.x < screenWidth - 60)
		{
			rect.x++;
		}
		else if (counter <= 180 && rect.x > 0)
		{
			rect.x--;
		}
		counter--;
		if (counter == 0)
			counter = 360;
	}

private:
	int counter = 360;
	Dropper(int x) : Enemy(x, "images/easy.png") {}
	Dropper(const Dropper &) = delete;
	const Dropper &operator=(const Dropper &) = delete;
};

class Earth : public Neutral
{
public:
	static Earth *getInstance(int x)
	{
		return new Earth(x);
	}
	~Earth()
	{
	}
	void movement()
	{
		rect.y++;
	}

private:
	Earth(int x) : Neutral(x, "images/earth.png") {}
	Earth(const Earth &) = delete;
	const Earth &operator=(const Earth &) = delete;
};

class GameSpawner : public Spawner
{
public:
	static GameSpawner *getInstance()
	{
		return new GameSpawner();
	}
	~GameSpawner()
	{
	}
	void spawnFunc()
	{
		counter++;
		if (counter == 200)
		{
			std::uniform_int_distribution<int> uni(0, (screenWidth - 60));
			int x = uni(rng);

			std::uniform_int_distribution<int> r(0, 100);
			int y = r(rng);
			if (y <= 20)
			{
				Earth *e = Earth::getInstance(x);
				addComp(e);
			}
			else if (y <= 40)
			{
				Shooter *s = Shooter::getInstance(x);
				addComp(s);
			}
			else
			{
				Dropper *d = Dropper::getInstance(x);
				addComp(d);
			}
		}

		if (counter > 200)
			counter = 0;
	}

private:
	int counter = 0;
	GameSpawner() : Spawner() {}
	GameSpawner(const GameSpawner &) = delete;
	const GameSpawner &operator=(const GameSpawner &) = delete;
};

class PlayerObj : public Player
{
public:
	static PlayerObj *getInstance()
	{
		return new PlayerObj();
	}
	~PlayerObj()
	{
	}
	void fire()
	{
		Laser *l = Laser::getInstance(rect.x + 45, rect.y - 31);
		addComp(l);

		Mix_PlayChannel(-1, Mix_LoadWAV((resPath + "sounds/laser.wav").c_str()), 0);
	}

private:
	PlayerObj() : Player(screenWidth, screenHeight) {}
	PlayerObj(const PlayerObj &) = delete;
	const PlayerObj &operator=(const PlayerObj &) = delete;
};

class SpaceBarKeybind : public Keybind
{
public:
	static SpaceBarKeybind *getInstance(SDL_Scancode k)
	{
		return new SpaceBarKeybind(k);
	}
	~SpaceBarKeybind()
	{
	}
	void action()
	{
		counter++;
		if (counter > 2)
		{
			std::uniform_int_distribution<int> uni(0, (screenWidth - 60));
			int x = uni(rng);

			Dropper *d = Dropper::getInstance(x);
			addComp(d);
			counter = 0;
		}
	}

private:
	int counter = 0;
	SpaceBarKeybind(SDL_Scancode k) : Keybind(k) {}
	SpaceBarKeybind(const SpaceBarKeybind &) = delete;
	const SpaceBarKeybind &operator=(const SpaceBarKeybind &) = delete;
};

void Component::delComp()
{
	ses.remove(this);
}

void Component::addComp(Component *c)
{
	ses.add(c);
}

int main(int argc, char **argv)
{
	Label *label = Label::getInstance(10, 20, 120, 45, "Score: ", 45, 0);
	PlayerObj *player = PlayerObj::getInstance();
	GameSpawner *spawner = GameSpawner::getInstance();
	SpaceBarKeybind *spacebar = SpaceBarKeybind::getInstance(SDL_SCANCODE_SPACE); // this is purely as a proof of concept, and was very helpful in testing try holding spacebar while playing :)
	ses.setPlayer(player);
	ses.setLabel(label);
	ses.add(spawner);
	ses.add(spacebar);
	ses.run();
	_CrtDumpMemoryLeaks();
	return 0;
}
