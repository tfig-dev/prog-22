#ifndef FILES_H
#define FILES_H

#include "game.h"

pMove addLastLinkedList(pMove p, int tab, int y, int x);

void showList(pMove p);

int countMoves(pMove p);

void showLastMoves(pMove p, int *nVezes, int nRondas);

void showLastTab(pMove p, int *nVezes, int nRondas, int *oldTab, int *x, int *y);

void saveListBin(pMove p, Player joga1, Player joga2);

void printFileBin();

pMove recoverFromBinToList(Player *Joga1, Player *Joga2);

void removeGameFile();

void writeFileTXT(char Filename[TAMFILE], char jogador1[TAMNOME], char jogador2[TAMNOME], pMove p);

bool checkOldGame();

void freeLinkedList(pMove p);

void freeBoards(miniB *boards);

void freeBoardExt(miniB board);

#endif
