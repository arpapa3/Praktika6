#pragma once
#include <SDL.h>

struct color
{
	float r, g, b;
};

/*Инициализирует SDL*/
void Init(SDL_Window*& win, SDL_Renderer*& ren, int win_width, int win_height);
/*Деинициализирует SDL, принимает код ошибки*/
void DeInit(SDL_Window* win, SDL_Renderer* ren, int error);
/*Возвращает рандомное целое число от a до b*/
int random(int, int);
/*Возвращает рандомное вещественное число от a, b*/
double randomd(double a, double b);
/*Получет математические координаты coord, координаты центра отсчета coord0, маштаб scale и в переменную rez записывает координаты в окне*/
void WinCoord(SDL_Point coord, SDL_Point coord0, double scale, SDL_Point& rez);