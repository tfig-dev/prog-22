#ifndef MENUS_H
#define MENUS_H

#include "game.h"
//include do game para o TAMNOME

int showMenu();

int showMenuInGame();

void showMenuMoveRepeat(int *valMenu, int *yMenu, int *xMenu);

void printRondas(int nRondas, char jogador[TAMNOME]);

int showMenuResume();

#endif