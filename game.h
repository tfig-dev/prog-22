#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#define TAMNOME 255

typedef struct Players{
    bool isBot;
    char name[TAMNOME];
}Player;

typedef struct miniBoard{
    char **pos;
}miniB;

char *getUserName (int posPlayer);

Player CriaJogador (char userName[TAMNOME], bool isBot);

void createPlayers(bool isBot, Player *J1, Player *J2);

#endif


