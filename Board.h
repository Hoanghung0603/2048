#ifndef BOARD_H
#define BOARD_H

#include "Draw.h"
#include "SDL.h"

class Board
{
    public:
        Board(int _size){
            size = _size;
            this->tab = createtab();
            this->backTab = createtab();
            copyTab(backTab,tab);
        };
        int** createtab();
        void copyTab(int **&tab1,int **&tab2);
        void remakeTab();
        bool checkWin();
        bool checkLose();
        bool canPut();
        bool checkToRandom();
        void randomOnBoard();
        void move(SDL_Event event);
        void tabtobacktab();
        void cleanTab();

        int** getTab() const;
        int** getbackTab() const;
        unsigned int getScore() const ;
        int size;

    private:
        int** tab;
        int** backTab;
        unsigned int score = 0;
        unsigned int backScore = score;

        void rushBot();
        void rushTop();
        void rushLeft();
        void rushRight();
        void moveBot();
        void moveTop();
        void moveLeft();
        void moveRight();

};

#endif // BOARD_H
