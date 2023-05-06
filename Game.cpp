#include "Game.h"
#include <iostream>

void Game::Initall()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout<<"SDL_Init error: "<< SDL_GetError()<<std::endl;
    }
    if(SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,&window, &renderer)) {
        this->clean();
        std::cout<<"SDL_CreateWindowAndRenderer error: "<<SDL_GetError()<<std::endl;
    }
    SDL_SetWindowTitle(window, "2048 GAME");
    screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
                                  0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STREAMING,
                               SCREEN_WIDTH, SCREEN_HEIGHT);
    charset = SDL_LoadBMP("./cs8x8.bmp");
    if(charset == NULL) {
        std::cout<<"SDL_LoadBMP error: "<< SDL_GetError() <<std::endl;
        this->clean();
    }
    SDL_SetColorKey(charset, true, 0x000000);
    brown = SDL_MapRGB(charset->format, 116,102,59);
    lightyellow = SDL_MapRGB(charset->format, 0xFF, 0xFF, 0xF0);
}

void Game::playing(Board &board)
{
    t2 = SDL_GetTicks();
    delta = (t2 - t1) * 0.001;
    t1 = t2;
    worldTime += delta;

    SDL_FillRect(screen, NULL, brown);
    DrawBoard(screen, board.getTab(), board.size, brown, lightyellow, charset);
    DrawScore(screen, board.getScore(), charset);
    DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, brown, lightyellow);

    sprintf(this->text, "time = %.1lf s ", worldTime);
    DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset,false, true);
    sprintf(text, "Esc - Exit, Arrows - Move, u - Back move, n - New game");
    DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset, false, true);

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        this->quit=true;
                        break;
                    case SDLK_UP:
                    case SDLK_DOWN:
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                        board.move(event);
                        break;
                    case SDLK_u:
                        board.tabtobacktab();
                        break;
                    case SDLK_n:
                        board.cleanTab();
                        board.remakeTab();
                        this->getStart = false;
                        break;
                    case SDLK_r:
                        RankTab ranktab(board.size);
                        ranktab.showRank(event, board, this->quit, screen, charset, scrtex, renderer, brown, lightyellow);
                        update_n_display();
                        ranktab.clean();
                        break;
                }
                break;
            case SDL_KEYUP:
                break;
            case SDL_QUIT:
                this->quit = true;
                break;
        }
    }
}

void Game::choose_size(Board &board)
{
    SDL_FillRect(screen, NULL, brown);
    DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, brown, lightyellow);

    sprintf(text, "Choose size of map: \030 to Bigger, \031 to Smaller     Enter to Start");
    DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 20, text, charset, false, true);

    DrawRectangle(screen, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 36, 200, 36, brown, lightyellow);
    std::stringstream ss;
    ss<<"Size: "<<board.size;
    std::string tempstr = ss.str();
    strcpy(text, tempstr.c_str());
    DrawString(screen, SCREEN_WIDTH/2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset, false, true);
    if (board.size >= 6) board.size = 6;
    if (board.size <= 3) board.size = 3;

    while (SDL_PollEvent(&event)) {
        switch (this->event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) this->quit = true;
                else if (event.key.keysym.sym == SDLK_UP){
                    board.size++;
                    if (board.size>=6) board.size = 6;
                    board.remakeTab();
                }
                else if (event.key.keysym.sym == SDLK_DOWN){
                    board.size--;
                    if(board.size<=3) board.size = 3;
                    board.remakeTab();
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    this->getStart = true;
                    board.cleanTab();
                    board.remakeTab();
                    this->t1 = SDL_GetTicks();
                    this->worldTime = 0;
                }
                board.change_winscore();
                break;
            case SDL_KEYUP:
                break;
            case SDL_QUIT:
                this->quit = true;
                break;
            }
    }
}

void Game::show_lose(const Board &board)
{
    double endTime = this->worldTime;
    while (!quit) {
        SDL_FillRect(screen, NULL, brown);
        DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, brown, lightyellow);
        sprintf(text, "You Lose: esc - quit");
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset, false, true);

        DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, brown, lightyellow);
        sprintf(text, "Your time: %.1lfs  Your score: %u", endTime, board.getScore());
        DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset, false, true);

        update_n_display();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) this->quit = true;
                    break;
                case SDL_QUIT:
                    this->quit = true;
                    break;
            }
        }
    }
}

void Game::show_win(const Board &board)
{
    double endTime = this->worldTime;
    while (!quit) {
        SDL_FillRect(screen, NULL, brown);

        DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, brown, lightyellow);
        sprintf(text, "You Win: s - to save your time, esc -  to quit");
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset, false, true);

        DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, brown, lightyellow);
        sprintf(text, "Your time: %.1lfs  Your score: %u", endTime, board.getScore());
        DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset, false, true);

        update_n_display();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) this->quit = true;
                if (event.key.keysym.sym == SDLK_s) {
                    RankTab ranktab;
                    ranktab.saveToFile(board.getScore(), endTime, board.size);
                    while (!quit) {
                        SDL_FillRect(screen, NULL, brown);
                        DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, brown, lightyellow);
                        sprintf(text, "Score saved!");
                        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset, false, true);
                        sprintf(text, "esc -  close game");
                        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset, false, true);

                        while (SDL_PollEvent(&event)) {
                            switch (event.type) {
                            case SDL_KEYDOWN:
                                if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
                                break;
                            case SDL_QUIT:
                                quit = true;
                                break;
                            }
                        }
                        update_n_display();
                    }
                }
                break;
            case SDL_QUIT:
                this->quit = true;
                break;
            }
        }
    }
}


void Game::update_n_display()
{
    SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, scrtex, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_FreeSurface(charset);
    SDL_FreeSurface(screen);
    SDL_DestroyTexture(scrtex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
