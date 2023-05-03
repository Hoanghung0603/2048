#ifndef DRAW_H
#define DRAW_H

#include <string>
#include <cstring>
#include <sstream>
#include <bitset>

#include "Setting.h"
#include "Board.h"
#include "SDL.h"
#include "SDL_image.h"

void DrawPixel(SDL_Surface *screen, int x, int y, Uint32 color);
void DrawLine(SDL_Surface *screen,int x, int y, int l, int dx, int dy, Uint32 color);
void DrawString(SDL_Surface *screen,int x, int y, const char *text,SDL_Surface *charset, bool check= false, bool bold= false);
void DrawPoint(SDL_Surface *screen,int x, int y, int width, const char* number,SDL_Surface *charset, bool check = true);
void DrawRectangle(SDL_Surface *screen,int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
void DrawBoard(SDL_Surface *screen, int** tab, const int &size, Uint32 outlineColor, Uint32 fillColor,SDL_Surface *charset);
void DrawScore(SDL_Surface *screen, unsigned int score, SDL_Surface *charset);
Uint32 pick_color(SDL_Surface *screen, const int &id);

#endif // DRAW_H
