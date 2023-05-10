#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <ctime>

#include "Draw.h"
#include "Board.h"
#include "RankTab.h"

#include "SDL.h"
#include "SDL_image.h"

class Game
{
    public:
        Game(){};
        void Initall();
        bool is_getStart(){return this->getStart;}
        bool is_quit(){return this->quit;}
        void playing(Board &board);
        void choose_size(Board &board);
        void show_lose(const Board &board);
        void show_win(const Board &board);
        void update_n_display();
        void display_gamestart();
        void clean();
    private:
        char text[128];
        int t1, t2;
        Uint32 brown, lightyellow;
        double delta;
        double worldTime = 0;
        bool quit= false;
        bool getStart = false;

        SDL_Rect start_imageRect;
        SDL_Surface* start_imageSurface;
        SDL_Texture* start_imageTexture;

        SDL_Event event;
        SDL_Surface *screen = nullptr;
        SDL_Surface *charset = nullptr;
        SDL_Texture *scrtex = nullptr;
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
};

#endif // GAME_H
