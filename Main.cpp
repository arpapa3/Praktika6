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

	SDL_Color background = { 255, 255, 255, 255 };
	int i = 0;
	bool run = true,
		quit = false,
		rectpl = true;
	SDL_Event ev;
	SDL_Rect rect = { 0, 0, 0, win_height };
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

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
			//Продолжение работы при нажатии любой клавиши
			case SDL_KEYDOWN:
				if ((ev.key.keysym.scancode != SDL_SCANCODE_F4 && (keyboard[SDL_SCANCODE_LALT] != true || keyboard[SDL_SCANCODE_RALT] != true)))
					quit = false;
				break;
			}
		}

		if (!quit)
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

			SDL_SetRenderDrawColor(ren, background.r, background.g, background.b, 255);
			SDL_RenderClear(ren);
			//SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
			//SDL_RenderFillRect(ren, &rect);
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