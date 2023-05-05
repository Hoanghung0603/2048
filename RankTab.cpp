#include "RankTab.h"
void RankTab::sortByScore()
{
    for(int i=0; i < amount-1; i++){
        for(int j=i+1; j < amount; j++){
            if(tab[i].endScore<tab[j].endScore){
                std::swap(tab[i], tab[j]);
            }
        }
    }
}

void RankTab::sortByTime()
{
    playerResult temp;
    for(int i=0; i < amount-1; i++){
        for(int j = i + 1; j < amount; j++){
            if(tab[i].endTime > tab[j].endTime){
                std::swap(tab[i],tab[j]);
            }
        }
    }
}

playerResult* RankTab::createRanking()
{
    playerResult *ranktab = new playerResult[amount];
    int x=0;
    for(int i=0; i<this->fileSize; i++){
        if(winnerList[i].endSize==size){
            ranktab[x].endScore=winnerList[i].endScore;
            ranktab[x].endTime=winnerList[i].endTime;
            ranktab[x].endSize=winnerList[i].endSize;
            ++x;
        }
    }
    return ranktab;
}

void RankTab::saveToFile(int score, double time, int size)
{
    std::ofstream file("winnerList.txt", std::ios::app);
    file<<score<<' '<<time<<' '<<size<<'\n';
    file.close();
}

playerResult* RankTab::openFile()
{
    std::ifstream file("winnerList.txt");
    if(!file){
        std::cout<<"cannot open winnerList"<<std::endl;
        return nullptr;
    }

    std::string temp="";
    while(std::getline(file,temp)){
        ++this->fileSize;
    }

    playerResult*list = new playerResult[fileSize];

    file.clear();  //xóa các flag lỗi
    file.seekg(0, std::ios::beg); //đưa con trỏ đọc đến đầu file
    for(int i=0; i<this->fileSize; i++){
        file>>list[i].endScore>>list[i].endTime>>list[i].endSize;
    }
    file.close();
    return list;
}

void RankTab::clean()
{
    delete[] tab;
    delete[] winnerList;
}

void RankTab::showRank(SDL_Event &event, const Board &board, bool &quit, SDL_Surface *&screen, SDL_Surface *&charset, SDL_Texture *&scrtex, SDL_Renderer *renderer, const int &black, const int&lightblue)
{
    char text[128];
    while(!showRanking){
        SDL_FillRect(screen, NULL, black);
        DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, black, lightblue);
        sprintf(text, "Winner list for %dx%d", board.size, board.size);
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset, false, true);
        sprintf(text, "esc -  go back, press t to sort by time and p to sort by points");
        DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset, false, true);

        int startShow=0;
        int limit = 10;
        if (startShow <= 0) startShow = 0;
        if (startShow >= amount - 10) startShow = amount - 10;
        if (amount <= 10) {
            startShow = 0;
            limit = amount;
        }
        if (fileSize == 0 || limit == 0) {
            sprintf(text, "Winner list is empty");
            DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8, SCREEN_HEIGHT / 2 -8 , text, charset, true);
        }

        for (int i = startShow, placeShow=0; placeShow < limit; i++) {
            DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 190 + placeShow * 40, 400, 40, black, lightblue);
            sprintf(text, "%d. Your time: %.1lfs Your score: %d",startShow + placeShow + 1, tab[i].endTime, tab[i].endScore);
            DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 200 + 26 + placeShow * 40, text, charset, false, true);
            placeShow++;
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) showRanking = true;
                if (event.key.keysym.sym == SDLK_t) this->sortByTime();
                if (event.key.keysym.sym == SDLK_p) this->sortByScore();
                else if (event.key.keysym.sym == SDLK_UP) startShow++;
                else if (event.key.keysym.sym == SDLK_DOWN) startShow--;
                break;
            case SDL_QUIT:
                quit = true;
                showRanking=true;
                break;
            }
        }
        SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, scrtex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}
