#pragma once
#include <SDL.h>
#include "STD.h"

void BackgroundColor(Uint32 dltime, color& background, const Uint8* keyboard);

void SaveColor(int in, SDL_Color color);

color LoadColor(int in);