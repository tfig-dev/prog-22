#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

// - INICIO - Criação de Jogadores //
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
    char j1[TAMNOME], j2[TAMNOME];

    printf("|- - NOVO JOGO - - |\n");
    printf("Insira o nome do Jogador 1: ");

    fgets(j1, sizeof(j1), stdin);
    j1[strlen(j1)-1] = '\0';

    (*J1) = CriaJogador(j1, false);

    if (!isBot) {
        printf("Insira o nome do Jogador 1: ");

        fgets(j2, sizeof(j2), stdin);
        j2[strlen(j2)-1] = '\0';

        (*J2) = CriaJogador(j2, false);
    } else {
        (*J2) = CriaJogador("MacBook", true);
    }

    printf("\n");
}
// - FIM - Criação de Jogadores //


//Criação de tabuleiro externo
miniB CriaTabuleiro() {
    miniB board;

    board.pos = malloc(sizeof(char *) * 3);
    for (int i = 0; i < 3; i++) {
        board.pos[i] = (char *) malloc(3);
    }

    for (int i = 0; i < 3; i++) {
        //cria ciclo para o X - coluna
        for (int j = 0; j < 3; j++) {
            board.pos[i][j] = '_';
        }
    }

    
    return board;
}

//Criação dos 9 tabuleiros internos
miniB *CriaTabuleiros() {
    miniB *boards;

    //criamos espaço para 9 tabuleiros do tipo miniB
    boards = malloc(sizeof(miniB) * 9);

    if (boards == NULL) {
        printf("Erro de alocação dos 9 tabuleiros!\n");
        //EXIT_FAILURE é uma flag que avisa o SO que o programa terminou inesperadamente
        exit(EXIT_FAILURE);
    }

    //para cada tabuleiro criado anteriormente
    for (int i = 0; i < 9; i++)
    {
        //cria espaço para 3 linhas
        boards[i].pos = malloc(sizeof(char *) * 3);
        if (boards[i].pos == NULL)
        {
            printf("Erro de alocação de linhas.\n");
            exit(EXIT_FAILURE);
        }
        //cria espaço para 3 colunas
        for (int j = 0; j < 3; j++)
        {
            boards[i].pos[j] = malloc(sizeof(char) * 3);
            if (boards[i].pos[j] == NULL)
            {
                printf("Erro de alocação de colunas.\n");
                exit(EXIT_FAILURE);
            }   
        }
    }

    //incializa tabuleiro com '_'
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            for (int z = 0; z < 3; z++) {
                boards[i].pos[j][z] = '_';
            }         
        }
    }

    return boards;
}