#include "Board.h"
#include <iostream>

int** Board::createtab()
{
	int **temtab;
	temtab = new int *[size];
	for (int i = 0; i < size; i++) temtab[i] = new int[size] {0};

	int X = rand() % size;
	int Y = rand() % size;
	temtab[X][Y] = 2;

	return temtab;
}

void Board::copyTab(int **&tab1,int **&tab2)
{
    for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) tab1[i][j] = tab2[i][j];
	}
}

void Board::remakeTab()
{
    tab=createtab();
    backTab=createtab();
    copyTab(backTab, tab);
    this->backScore = 0;
    this->score = 0;
}


bool Board::checkWin()
{
    for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tab[i][j] == 2048) return true;
		}
	}
	return false;
}

bool Board::checkLose()
{
    for (int i = 0; i < size-1; i++) {
		for (int j = 0; j < size - 1; j++) {
			if ((this->tab[i][j] == this->tab[i][j + 1])||(this->tab[i][j] == this->tab[i + 1][j])) return false;
		}
	}

	if(tab[size-2][size-1]==tab[size-1][size-1]) return false;
	else if (tab[size-1][size-2]==tab[size-1][size-1]) return false;
	if (this->canPut()) return false;

	return true;
}

bool Board::canPut()
{
    for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->tab[i][j] == 0) return true;
		}
	}
	return false;
}

bool Board::checkToRandom()
{
    for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (this->tab[i][j] != this->backTab[i][j]) return true;
		}
	}
	return false;
}

void Board::randomOnBoard()
{
    if (this->canPut()) {
        int X,Y;
        do{
            X = rand() % size;
            Y = rand() % size;
        } while (this->tab[X][Y] != 0);

        this->tab[X][Y]=2;
	}
}

void Board::moveBot()
{
    this->rushBot();

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (this->tab[j][i] != 0) {
				if (tab[j][i] == tab[j + 1][i]) {
					tab[j + 1][i] += tab[j][i];
					this->score += tab[j + 1][i];
					tab[j][i] = 0;
				}
			}
		}
	}

	this->rushBot();
}

void Board::moveTop()
{
    this->rushTop();

	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->tab[i][j] != 0) {
				if (tab[i - 1][j] == tab[i][j]) {
					tab[i - 1][j]+= tab[i][j];
					this->score += tab[i - 1][j];
					tab[i][j] = 0;

				}
			}
		}
	}

	this->rushTop();
}

void Board::moveLeft()
{
    this->rushLeft();

	for(int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (this->tab[i][j] != 0) {
				if (tab[i][j] == tab[i][j - 1]) {
					tab[i][j - 1] += tab[i][j];
					this->score += tab[i][j - 1];
					tab[i][j] = 0;
				}
			}
		}
	}

	this->rushLeft();
}

void Board::moveRight()
{
    this->rushRight();

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (this->tab[i][j] != 0) {
				if (tab[i][j] == tab[i][j + 1]) {
					tab[i][j + 1] += tab[i][j];
					this->score += tab[i][j + 1];
					tab[i][j] = 0;
				}
			}
		}
	}

	this->rushRight();
}

void Board::move(SDL_Event event)
{
    int **checkTab = createtab();
	int checkScore = this->backScore;
	copyTab(checkTab, this->backTab);
	copyTab(backTab, this->tab);
	this->backScore = this->score;

	// sửa thành dùng switch case
	if (event.key.keysym.sym == SDLK_UP) moveTop();
	else if (event.key.keysym.sym == SDLK_DOWN) moveBot();
	else if (event.key.keysym.sym == SDLK_LEFT) moveLeft();
	else if (event.key.keysym.sym == SDLK_RIGHT) moveRight();

	if (this->checkToRandom()) {
		this->randomOnBoard();
	}
	// có thể phần else này thừa
	else {
		copyTab(backTab, checkTab);
		backScore = checkScore;
	}

	for (int i = 0; i < size; ++i)
		delete[] checkTab[i];
	delete[] checkTab;
}

void Board::rushBot()
{
    for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (this->tab[j][i] != 0) {
				for (int k = j; k < size - 1; ++k) {
					if (tab[k + 1][i] == 0) {
						tab[k + 1][i] = tab[k][i];
						tab[k][i] = 0;
					}
				}
			}
		}
	}
}

void Board::rushTop()
{
    for (int i = 1; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->tab[i][j] != 0) {
				for (int k = i; k > 0; --k) {
					if (tab[k - 1][j] == 0) {
						tab[k - 1][j] = tab[k][j];
						tab[k][j] = 0;
					}
				}
			}
		}
	}
}

void Board::rushLeft()
{
    for (int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (this->tab[i][j] != 0) {
				for (int k = j; k > 0; --k) {
					if (tab[i][k - 1] == 0) {
						tab[i][k - 1] = tab[i][k];
						tab[i][k] = 0;
					}
				}
			}
		}
	}
}

void Board::rushRight()
{
    for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (this->tab[i][j] != 0) {
				for (int k = j; k < size - 1; ++k) {
					if (tab[i][k + 1] == 0) {
						tab[i][k + 1] = tab[i][k];
						tab[i][k] = 0;
					}
				}
			}
		}
	}
}

void Board::tabtobacktab()
{
    copyTab(tab,backTab);
    score=backScore;
}


int** Board::getTab() const
{
    return this->tab;
}

int** Board::getbackTab() const
{
    return this->backTab;
}

unsigned int Board::getScore() const
{
    return score;
}

void Board::cleanTab()
{
    for (int i = 0; i < size; ++i){
		delete[] this->tab[i];
		delete[] this->backTab[i];
    }
	delete[] tab;
	delete[] backTab;
}

