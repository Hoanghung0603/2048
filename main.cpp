#include <iostream>
#include "Game.h"
#include "Draw.h"


int main(int argc, char **argv){
    Board board(4);
    Game game;
    game.Initall();
	while(!game.is_quit()){
        if(!game.is_getStart()){
			game.choose_size(board);
            game.update_n_display();
        }
        if(game.is_getStart() && !board.checkLose() && !board.checkWin()){
            game.playing(board);
            game.update_n_display();
        }
        if (board.checkLose()){
            game.show_lose(board);
            game.update_n_display();
        }
        if (board.checkWin()){
            game.show_win(board);
            game.update_n_display();
        }
	}

	board.cleanTab();
    game.clean();
    return 0;
}
