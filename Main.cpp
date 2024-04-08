#include <SDL.h>
#include "STD.h"
#include <iostream>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int win_width = 800;
int win_height = 800;

#define FPS 60

int main(int argc, char** argv)
{
	system("chcp 1251>nul");
	Init(win, ren, win_width, win_height);
	SDL_Color background = { 255, 255, 255, 255 };
	int i = 0;
	bool run = true,
		quit = false;
	SDL_Event ev;
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	Uint32 time = SDL_GetTicks(), oltime = 0;
	while (run)
	{
		//Обработка событий
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				if (!quit) quit = true;
				else run = false;
				break;
			//Продолжение работы при нажатии любой клавиши
			case SDL_KEYDOWN:
				if ((ev.key.keysym.scancode != SDL_SCANCODE_F4 && 
					(keyboard[SDL_SCANCODE_LALT] != true || keyboard[SDL_SCANCODE_RALT] != true)))
					quit = false;
				break;
			case SDL_WINDOWEVENT:
				if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					win_width = ev.window.data1;
					win_height = ev.window.data2;
				}
			}
		}
		time = SDL_GetTicks();
		if (!quit)
		{
			if (time - oltime >= 1000 / FPS)
			{
#pragma region 1
				if ((keyboard[SDL_SCANCODE_KP_PLUS] || keyboard[SDL_SCANCODE_KP_MINUS]) &&
					(keyboard[SDL_SCANCODE_R] || keyboard[SDL_SCANCODE_G] || keyboard[SDL_SCANCODE_B]))
				{
					if (keyboard[SDL_SCANCODE_R])
						background.r = background.r + (keyboard[SDL_SCANCODE_KP_PLUS] ? 1 : -1);
					if (keyboard[SDL_SCANCODE_G])
						background.g = background.g + (keyboard[SDL_SCANCODE_KP_PLUS] ? 1 : -1);
					if (keyboard[SDL_SCANCODE_B])
						background.b = background.b + (keyboard[SDL_SCANCODE_KP_PLUS] ? 1 : -1);
				}
#pragma endregion //1
				oltime = time;
			}
			SDL_SetRenderDrawColor(ren, background.r, background.g, background.b, 255);
			SDL_RenderClear(ren);
		}		
		else
		{
			//Если событие было то выполняется это
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			SDL_RenderClear(ren);
		}
		SDL_RenderPresent(ren);
		printf("%dx%d\n", win_width, win_height);
	}
	DeInit(win, ren, 0);
	return 0;
}