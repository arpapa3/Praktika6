#include <SDL.h>
#include "BackroundColor.h"

#define COLOR_SPEED 60
SDL_Color save_color[3] = { {255, 255, 255, 255}, {255, 255, 255, 255} , {255, 255, 255, 255} };

void BackgroundColor(Uint32 dltime, color& background, const Uint8* keyboard)
{
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
}

void SaveColor(int in, SDL_Color color)
{
	save_color[in] = color;
}

color LoadColor(int in)
{
	return { (float)save_color[in].r, (float)save_color[in].g, (float)save_color[in].b };
}