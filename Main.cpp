#include <SDL.h>
#include "STD.h"
#include <iostream>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int win_width = 800;
int win_height = 800;

SDL_Color save_color[3] = { {255, 255, 255, 255}, {255, 255, 255, 255} , {255, 255, 255, 255} };

struct color
{
	float r, g, b;
};

#define COLOR_SPEED 60

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
						background = { (float)save_color[0].r, (float)save_color[0].g, (float)save_color[0].b };
					else
						save_color[0] = { (unsigned char)background.r, (unsigned char)background.g, (unsigned char)background.b, 255 };
				if(keyboard[SDL_SCANCODE_2])
					if (keyboard[SDL_SCANCODE_LCTRL] || keyboard[SDL_SCANCODE_RCTRL])
						background = { (float)save_color[1].r, (float)save_color[1].g, (float)save_color[1].b };
					else
						save_color[1] = { (unsigned char)background.r, (unsigned char)background.g, (unsigned char)background.b, 255 };
				if (keyboard[SDL_SCANCODE_3])
					if (keyboard[SDL_SCANCODE_LCTRL] || keyboard[SDL_SCANCODE_RCTRL])
						background = { (float)save_color[2].r, (float)save_color[2].g, (float)save_color[2].b };
					else
						save_color[2] = { (unsigned char)background.r, (unsigned char)background.g, (unsigned char)background.b, 255 };
			}

			//Изменение цвета окна
			if ((keyboard[SDL_SCANCODE_KP_PLUS] || keyboard[SDL_SCANCODE_KP_MINUS]) && (keyboard[SDL_SCANCODE_R] || keyboard[SDL_SCANCODE_G] || keyboard[SDL_SCANCODE_B]))
			{
				if (keyboard[SDL_SCANCODE_R])
				{
					background.r = background.r + (keyboard[SDL_SCANCODE_KP_PLUS] ? COLOR_SPEED * (dltime / 1000.0) : -COLOR_SPEED * (dltime / 1000.0));
					if (background.r > 255)
						background.r -= 255;
					if (background.r < 0)
						background.r += 255;
				}
				if (keyboard[SDL_SCANCODE_G])
				{
					background.g = background.g + (keyboard[SDL_SCANCODE_KP_PLUS] ? COLOR_SPEED * (dltime / 1000.0) : -COLOR_SPEED * (dltime / 1000.0));
					if (background.g > 255)
						background.g -= 255;
					if (background.g < 0)
						background.g += 255;
				}
				if (keyboard[SDL_SCANCODE_B])
				{
					background.b = background.b + (keyboard[SDL_SCANCODE_KP_PLUS] ? COLOR_SPEED * (dltime / 1000.0) : -COLOR_SPEED * (dltime / 1000.0));
					if (background.b > 255)
						background.b -= 255;
					if (background.b < 0)
						background.b += 255;
				}
			}
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
		printf("R:%f\nG:%f\nB:%f\n\n", background.r, background.g, background.b);
	}
	DeInit(win, ren, 0);
	return 0;
}