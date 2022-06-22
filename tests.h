#ifndef TESTS_H
#define TESTS_H

#include "game.h"

bool checkLine(miniB *tabuleiros, int tab);

bool checkExternLine(miniB *tabuleiro);

bool checkColumn(miniB *tabuleiros, int tab);

bool checkExternColumn(miniB *tabuleiro);

bool checkDiagonal(miniB *tabuleiros, int tab);

bool checkExternDiagonal(miniB *tabuleiro);

bool checkDraw(miniB *tabuleiros, int tab);

bool checkDrawExt(miniB tabuleiro);

bool checkTabPlay(miniB *tabuleiro, int tab);

#endif
