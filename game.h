#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#define TAMNOME 255
#define TAMFILE 255

typedef struct Players{
    char name[TAMNOME];
    bool isBot;
} Player;

typedef struct miniBoard{
    char **pos;
}miniB;

typedef struct move no, *pMove;

typedef struct {
    int y, x;
} coord;

struct move {
    int tab;
    coord pos;
    pMove prox;
};

Player CriaJogador (char userName[TAMNOME], bool isBot);

void createPlayers(bool isBot, Player *J1, Player *J2);

miniB CriaTabuleiro();

miniB *CriaTabuleiros();
#endif


