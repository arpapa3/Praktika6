#include <SDL.h>
#include "STD.h"
#include <iostream>
#include "BackroundColor.h"

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int win_width = 800;
int win_height = 800;

int main(int argc, char** argv)
{
	system("chcp 1251>nul");
	Init(win, ren, win_width, win_height);
	Uint32 time = SDL_GetTicks(), oltime = 0, dltime = 0;
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	color background = { 255, 255, 255 };
	bool run = true, quit = false;
	SDL_Event ev;
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
				if ((ev.key.keysym.scancode != SDL_SCANCODE_F4 && (keyboard[SDL_SCANCODE_LALT] != true || keyboard[SDL_SCANCODE_RALT] != true)))
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
		dltime = time - oltime;
		oltime = time;

		if (!quit)
		{
			/*Сохранение и изменение цвета окна*/
			//Сохраненние цвета окна
			
			if (keyboard[SDL_SCANCODE_1] || keyboard[SDL_SCANCODE_2] || keyboard[SDL_SCANCODE_3])
			{
				if (keyboard[SDL_SCANCODE_1])
					if (keyboard[SDL_SCANCODE_LCTRL] || keyboard[SDL_SCANCODE_RCTRL])
						background = LoadColor(0);
					else
						SaveColor(0, { (unsigned char)background.r, (unsigned char)background.g, (unsigned char)background.b, 255 });
				if(keyboard[SDL_SCANCODE_2])
					if (keyboard[SDL_SCANCODE_LCTRL] || keyboard[SDL_SCANCODE_RCTRL])
						background = LoadColor(1);
					else
						SaveColor(1, { (unsigned char)background.r, (unsigned char)background.g, (unsigned char)background.b, 255 });
				if (keyboard[SDL_SCANCODE_3])
					if (keyboard[SDL_SCANCODE_LCTRL] || keyboard[SDL_SCANCODE_RCTRL])
						background = LoadColor(2);
					else
						SaveColor(2, { (unsigned char)background.r, (unsigned char)background.g, (unsigned char)background.b, 255 });
			}

			//Изменение цвета окна
			BackgroundColor(dltime, background, keyboard);

			SDL_SetRenderDrawColor(ren, background.r, background.g, background.b, 255);
			SDL_RenderClear(ren);
			/*Конец работы с цветом фона*/
		}
		else
		{
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			SDL_RenderClear(ren);
		}
		SDL_RenderPresent(ren);
	}
	DeInit(win, ren, 0);
	return 0;
}