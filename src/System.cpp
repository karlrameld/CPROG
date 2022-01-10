#include "System.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

System::System()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	win = SDL_CreateWindow("Bad Space invaders", 10, 10, screenWidth, screenHeight, 0);
	ren = SDL_CreateRenderer(win, -1, 0);
	bgImage = IMG_LoadTexture(ren, (resPath + "images/bgimage.jpg").c_str());
	Mix_OpenAudio(10050, AUDIO_S16SYS, 2, 4096);
	// Path to your own 'sounds' folder!
	// musik = Mix_LoadWAV("/Users/kjellna/dev/cpp21/f13b/sounds/bgMusic.wav");
	musik = Mix_LoadWAV((resPath + "sounds/background.mp3").c_str());
	Mix_PlayChannel(-1, musik, -1);
}

System::~System()
{
	SDL_DestroyTexture(bgImage);
	Mix_FreeChunk(musik);
	Mix_CloseAudio();
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	TTF_Quit();
	SDL_Quit();
}

System sys;
