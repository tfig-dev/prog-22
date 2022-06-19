#ifndef MENUS_H
#define MENUS_H

#include "game.h"
//include do game para o TAMNOME

int showMenu(bool resume);

int showMenuInGame();

void showMenuMoveRepeat(int *valMenu, int *yMenu, int *xMenu);

void printRondas(int nRondas, char jogador[TAMNOME]);

int showMenuResume();

int showMenuHistory(int jogadas);

int showMenuSave();

void showBoards(miniB *tabuleiros, miniB tabuleiroEXT, int tab);

#endif