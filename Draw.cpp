#include "Draw.h"
#include "SDL.h"
#include "SDL_image.h"
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8 *)surface->pixels + y * (surface->pitch) + x * bpp;
	*(Uint32 *)p = color;
}

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color)
{
    for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
}

void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset, bool check, bool bold)
{
    if(bold) SDL_SetSurfaceColorMod(charset, 0, 0, 0);
    else SDL_SetSurfaceColorMod(charset, 255, 255, 255);
    int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	if(!check){
        while(*text) {
            c = *text & 255;
            px = (c % 16) * 8;
            py = (c / 16) * 8;

            s.x = px;
            s.y = py;
            d.x = x;
            d.y = y;

            SDL_BlitSurface(charset, &s, screen, &d);
            x += 8;
            text++;
        }
	}
	else
    {
        int scale=2;
        d.w = 8*scale;
        d.h = 8*scale;
        while(*text) {
            c = *text & 255;
            px = (c % 16) * 8;
            py = (c / 16) * 8;

            s.x = px;
            s.y = py;
            d.x = x;
            d.y = y;

            SDL_BlitScaled(charset, &s, screen, &d);
            x += 8*scale;
            text++;
        }
    }
}

void DrawPoint(SDL_Surface* screen, int x, int y, int width, const char* number, SDL_Surface* charset, bool check)
{
    int length = strlen(number);
    if(length==1)
        DrawString(screen, (x + width / 2) - length*4 , y + width / 2 - 4, number, charset, check, true);
    else if(length ==2)
        DrawString(screen, (x + width / 2) - length*4 - 4, y + width / 2 - 4, number, charset, check);
    else if(length==3)
        DrawString(screen, (x + width / 2) - length*4 - 8, y + width / 2 - 4, number, charset, check);
    else
        DrawString(screen, (x + width / 2) - length*4 - 12, y + width / 2 - 4, number, charset, check);


}

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor)
{
    int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
}

void DrawBoard(SDL_Surface* screen, int** tab, const int &size, Uint32 outlineColor, Uint32 fillColor, SDL_Surface* charset)
{
    int width = (BOARD_WIDTH / size) - 2;
	int X, Y;
	int id;
	char number[5];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			X = BOARD_X + (BOARD_WIDTH / size)*i;
			Y = BOARD_Y + (BOARD_WIDTH / size)*j;
			id=tab[i][j];
			DrawRectangle(screen, Y, X, width, width, outlineColor, pick_color(screen,id));
			if(tab[i][j] == 0) strcpy(number, "");
			else {
                std::stringstream ss;
                std::string temp;
                ss << tab[i][j];
                ss>>temp;
                strcpy(number, temp.c_str());
            }
			DrawPoint(screen, Y, X, width, number, charset);
		}
	}
}

void DrawScore(SDL_Surface* screen, unsigned int score, SDL_Surface* charset)
{
    int X = BOARD_X;
	int Y = BOARD_Y + BOARD_WIDTH + 100;
	int width = 40;
	char number[18];

	std::stringstream ss;
    ss << "score: " << score;
    std::string temp = ss.str();
    strncpy(number, temp.c_str(), sizeof(number)-1);
    number[sizeof(number)-1] = '\0';

	DrawPoint(screen, Y, X, width, number, charset, false);
}

Uint32 pick_color(SDL_Surface* screen, const int& id)
{
    switch(id){
        case 0: return SDL_MapRGB(screen->format, 169, 169, 169);
        case 2: return SDL_MapRGB(screen->format, 238, 228, 218);
        case 4: return SDL_MapRGB(screen->format, 237, 224, 200);
        case 8: return SDL_MapRGB(screen->format, 242, 177, 121);
        case 16: return SDL_MapRGB(screen->format, 245, 149, 99);
        case 32: return SDL_MapRGB(screen->format, 246, 124, 95);
        case 64: return SDL_MapRGB(screen->format, 246, 94, 59);
        case 128: return SDL_MapRGB(screen->format, 237, 207, 114);
        case 256: return SDL_MapRGB(screen->format, 237, 204, 97);
        case 512: return SDL_MapRGB(screen->format, 237, 200, 80);
        case 1024: return SDL_MapRGB(screen->format, 237, 197, 63);
        case 2048: return SDL_MapRGB(screen->format, 237, 194, 46);
    }
}
