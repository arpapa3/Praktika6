#pragma once
#include <SDL.h>
/*�������������� SDL*/
void Init(SDL_Window*& win, SDL_Renderer*& ren, int win_width, int win_height);
/*���������������� SDL, ��������� ��� ������*/
void DeInit(SDL_Window* win, SDL_Renderer* ren, int error);
/*���������� ��������� ����� ����� �� a �� b*/
int random(int, int);
/*���������� ��������� ������������ ����� �� a, b*/
double randomd(double a, double b);
/*������� �������������� ���������� coord, ���������� ������ ������� coord0, ������ scale � � ���������� rez ���������� ���������� � ����*/
void WinCoord(SDL_Point coord, SDL_Point coord0, double scale, SDL_Point& rez);

bool FPS(int fps);