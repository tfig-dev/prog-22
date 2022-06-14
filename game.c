#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

// - INICIO - Criação de Jogadores //
char *getUserName (int posPlayer) {
    char nome[2][TAMNOME];
    printf("Insira o nome do Jogador %d: ", posPlayer);
    fgets(nome[0], sizeof(nome[0]), stdin);
    nome[0][strlen(nome[0]) - 1] = '\0';
    
    return nome;
}

Player CriaJogador (char userName[TAMNOME], bool isBot) {
    Player Jogador;
    strcpy(Jogador.name, userName);

    if (!isBot) {
        Jogador.isBot = false;
    } else {
        Jogador.isBot = true;
    }

    return Jogador;
}

void createPlayers(bool isBot, Player *J1, Player *J2) {

    printf("|- - NOVO JOGO - - |\n");

    (*J1) = CriaJogador(getUserName(1), false);

    if (!isBot) {
        (*J2) = CriaJogador(getUserName(2), false);
    } else {
        (*J2) = CriaJogador("MacBook", true);
    }

    printf("\n");
}
// - FIM - Criação de Jogadores //

