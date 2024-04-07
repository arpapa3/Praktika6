#include <SDL.h>
#include "STD.h"
#include <iostream>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int win_width = 1000;
int win_height = 1000;

int main(int argc, char** argv)
{
	system("chcp 1251>nul");
	Init(win, ren, win_width, win_height);

	int i = 0;
	bool run = true,
		quit = false,
		rectpl = true;
	SDL_Event ev;
	SDL_Rect rect = { 0, 0, 0, win_height };
	while (run)
	{
		//Обработка событий
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
			{
				if (!quit)
					quit = true;
				else
					run = false;
			}
				break;
			//Сейчас продолжает рабоать только при нажатии 0 нужно будет доработать
			case SDL_KEYDOWN:
				if (ev.key.keysym.scancode == SDL_SCANCODE_0)
					quit = false;
				break;
			}
		}
		if (!quit)
		{
			//Если небыло забытия закрытия окна то выполняется это
			printf("Обработка\n");
			if (rectpl)
				if (rect.w < win_width)
					rect.w++;
				else
					rectpl = false;
			else
				if (rect.w > 0)
					rect.w--;
				else
					rectpl = true;

			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
			SDL_RenderClear(ren);
			SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
			SDL_RenderFillRect(ren, &rect);
		}		
		else
		{
			//Если событие было то выполняется это
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			SDL_RenderClear(ren);
		}
		SDL_RenderPresent(ren);
	}
	DeInit(win, ren, 0);
	return 0;
}