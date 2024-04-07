#include <iostream>
#include "STD.h"
#include <SDL.h>

void Init(SDL_Window* &win, SDL_Renderer* &ren, int win_width, int win_height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("Инициализация SDL прошла с ошибками:%s", SDL_GetError());
		exit(-1);
	}

	win = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN);
	if (win == NULL)
	{
		printf("Ошибка создания окна:%s", SDL_GetError());
		DeInit(win, ren, -1);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("Ошибка создания рендера:%s", SDL_GetError());
		DeInit(win, ren, -1);
	}
}

void DeInit(SDL_Window* win, SDL_Renderer* ren, int error)
{
	if (ren) SDL_DestroyRenderer(ren);
	if (win) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);
}

int random(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

double randomd(double a, double b)
{
	return a + (b - a) / RAND_MAX * rand();
}

void WinCoord(SDL_Point coord, SDL_Point coord0, double scale, SDL_Point& rez)
{
	rez = { (int)(coord0.x + coord.x * scale), (int)(coord0.y - coord.y * scale) };
}

bool FPS(int fps)
{
	static int newtime, lasttime = 0, dt;
	newtime = SDL_GetTicks();
	dt = newtime - lasttime;
	if (dt == 0)
		return 0;
	if (1000 / dt <= fps)
	{
		lasttime = newtime;
		return 1;
	}
	else
		return 0;
}