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
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
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
/*
class Score : public Component
{
public:
	static Score *getInstance()
	{
		return new Score();
	}
	Score() : Component(10, 65, 120, 45, 0)
	{
		scoreString = "Score : " + std::to_string(score);
		SDL_Surface *scoreText =
			TTF_RenderText_Solid(TTF_OpenFont((resPath + "fonts/default.ttf").c_str(), 45), scoreString.c_str(), {255, 255, 255});
		texture = SDL_CreateTextureFromSurface(sys.ren, scoreText);
		SDL_FreeSurface(scoreText);
	}
	~Score()
	{
		SDL_DestroyTexture(texture);
	}
	void draw() const
	{
		const SDL_Rect &rect = getRect();
		SDL_RenderCopy(sys.ren, texture, NULL, &rect);
	}
	void tick()
	{
		scoreString = "Score : " + std::to_string(score);
		SDL_DestroyTexture(texture);
		SDL_Surface *surf = TTF_RenderText_Solid(TTF_OpenFont((resPath + "fonts/default.ttf").c_str(), 45),
												 scoreString.c_str(), {255, 255, 255});
		texture = SDL_CreateTextureFromSurface(sys.ren, surf);
		SDL_FreeSurface(surf);
	}

	void collisionHandler(int other) {}
	bool collsionAftermath(int other)
	{
		return false;
	}

private:
	SDL_Texture *texture;
	std::string scoreString;
};

class Ammo : public Component
{
public:
	static Ammo *getInstance()
	{
		return new Ammo();
	}
	Ammo() : Component(10, 10, 120, 45, 0)
	{
		scoreString = "Ammo : " + std::to_string(ammo);
		SDL_Surface *scoreText =
			TTF_RenderText_Solid(TTF_OpenFont((resPath + "fonts/default.ttf").c_str(), 45), scoreString.c_str(), {255, 255, 255});
		texture = SDL_CreateTextureFromSurface(sys.ren, scoreText);
		SDL_FreeSurface(scoreText);
	}
	~Ammo()
	{
		SDL_DestroyTexture(texture);
	}
	void draw() const
	{
		const SDL_Rect &rect = getRect();
		SDL_RenderCopy(sys.ren, texture, NULL, &rect);
	}
	void tick()
	{
		scoreString = "Ammo : " + std::to_string(ammo);
		SDL_DestroyTexture(texture);
		SDL_Surface *surf = TTF_RenderText_Solid(TTF_OpenFont((resPath + "fonts/default.ttf").c_str(), 45),
												 scoreString.c_str(), {255, 255, 255});
		texture = SDL_CreateTextureFromSurface(sys.ren, surf);
		SDL_FreeSurface(surf);
	}

	void collisionHandler(int other) {}
	bool collsionAftermath(int other)
	{
		return false;
	}

private:
	SDL_Texture *texture;
	std::string scoreString;
};


*/
class Laser : public Bullet
{
public:
	static Laser *getInstance(int x, int y)
	{
		return new Laser(x, y);
	}
	~Laser()
	{
		Bullet::~Bullet();
	}
	void action()
	{
		rect.y -= 2;
	}

private:
	Laser(int x, int y) : Bullet(x, y, "images/laser.png") {}
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
		Bullet::~Bullet();
	}
	void action()
	{
		rect.y++;
	}

private:
	Ball(int x, int y) : Bullet(x, y, "images/ball.png") {}
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
		Enemy::~Enemy();
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
				if (rect.x == screenWidth)
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
		Enemy::~Enemy();
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
		Neutral::~Neutral();
	}
	void movement()
	{
		rect.y++;
	}

private:
	Earth(int x) : Neutral(x, "images/earth.png") {}
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
		Spawner::~Spawner();
	}
	void spawnFunc()
	{
		counter++;
		if (counter == 500)
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

		if (counter > 500)
			counter = 0;
	}

private:
	int counter = 0;
	GameSpawner() : Spawner() {}
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
		Player::~Player();
	}
	void fire()
	{
		Laser *l = Laser::getInstance(rect.x + 45, rect.y - 31);
		addComp(l);

		Mix_PlayChannel(-1, Mix_LoadWAV((resPath + "sounds/laser.wav").c_str()), 0);
	}

private:
	PlayerObj() : Player(screenWidth, screenHeight) {}
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
	PlayerObj *player = PlayerObj::getInstance();
	GameSpawner *spawner = GameSpawner::getInstance();
	ses.add(spawner);
	ses.setPlayer(player);
	ses.run();
	_CrtDumpMemoryLeaks();
	return 0;
}
