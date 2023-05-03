#ifndef RANKTAB_H
#define RANKTAB_H

#include <iostream>
#include <fstream>
#include <string>

#include "Board.h"
struct playerScore{
    int endScore;
    double endTime;
    int endSize;
};

class RankTab
{
    public:
        RankTab(){};
        RankTab(int _size){
            size=_size;
            winnerList = openFile();
            for(int i=0; i<fileSize; i++){
                if(size==winnerList[i].endSize) ++amount;
            }
            tab = createRanking();
        }
        void showRank(SDL_Event &event, const Board &board, bool &quit, SDL_Surface *&screen, SDL_Surface *&charset, SDL_Texture *&scrtex, SDL_Renderer *renderer, const int &black, const int &lightblue);
        void clean();
        void saveToFile(int score, double time, int _size);


    private:
        playerScore *tab;
        bool showRanking = false;
        int size;
        int amount=0;
        int fileSize=0; //file có bao nhiêu dòng
        playerScore *winnerList;
        void sortByScore();
        void sortByTime();
        playerScore *createRanking();
        playerScore *openFile();

};

#endif // RANKTAB_H
