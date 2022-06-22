#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tests.h"
#include "game.h"

//verificações linhas, colunas, diagonais
bool checkLine(miniB *tabuleiros, int tab) {
    for (int linha = 0; linha < 3; linha++) {
        if (tabuleiros[tab].pos[linha][0] != '_') {
            if (tabuleiros[tab].pos[linha][0]==tabuleiros[tab].pos[linha][1] && tabuleiros[tab].pos[linha][1]==tabuleiros[tab].pos[linha][2]) {
                return true;
            }
        }
    }

    return false;
}

bool checkExternLine(miniB *tabuleiro) {
    for (int i = 0; i < 3; i++) {
        if ((*tabuleiro).pos[i][0] != '_') {
            if ((*tabuleiro).pos[i][0]==(*tabuleiro).pos[i][1] && (*tabuleiro).pos[i][1]==(*tabuleiro).pos[i][2]) {
                return true;
            }
        }
    }

    return false;
}

bool checkColumn(miniB *tabuleiros, int tab) {
    for (int coluna = 0; coluna < 3; coluna++) {
        if (tabuleiros[tab].pos[0][coluna] != '_') {
            if (tabuleiros[tab].pos[0][coluna]==tabuleiros[tab].pos[1][coluna] && tabuleiros[tab].pos[1][coluna]==tabuleiros[tab].pos[2][coluna]) {
                return true;
            }
        }
    }

    return false;
}

bool checkExternColumn(miniB *tabuleiro) {
    for (int i = 0; i < 3; i++) {
        if ((*tabuleiro).pos[0][i] != '_') {
            if ((*tabuleiro).pos[0][i]==(*tabuleiro).pos[1][i] && (*tabuleiro).pos[1][i]==(*tabuleiro).pos[2][i]) {
                return true;
            }
        }
    }

    return false;
}

bool checkDiagonal(miniB *tabuleiros, int tab) {
    //diagonal cima esquerda -> baixo direita
    if (tabuleiros[tab].pos[0][0] != '_') {
        if (tabuleiros[tab].pos[0][0] == tabuleiros[tab].pos[1][1] && tabuleiros[tab].pos[1][1] == tabuleiros[tab].pos[2][2]) {
            return true;
        }
    }

    //diagonal baixo esquerda -> cima direita
    if (tabuleiros[tab].pos[2][0] != '_') {
        if (tabuleiros[tab].pos[2][0] == tabuleiros[tab].pos[1][1] && tabuleiros[tab].pos[1][1] == tabuleiros[tab].pos[0][2]) {
            return true;
        }
    }
    return false;
}

bool checkExternDiagonal(miniB *tabuleiro) {
    //diagonal cima esquerda -> baixo direita
    if ((*tabuleiro).pos[0][0] != '_') {
        if ((*tabuleiro).pos[0][0] == (*tabuleiro).pos[1][1] && (*tabuleiro).pos[1][1] == (*tabuleiro).pos[2][2]) {
            return true;
        }
    }

    //diagonal baxio esquerda -> cima direita
    if ((*tabuleiro).pos[2][0] != '_') {
        if ((*tabuleiro).pos[2][0] == (*tabuleiro).pos[1][1] && (*tabuleiro).pos[1][1] == (*tabuleiro).pos[0][2]) {
            return true;
        }
    }

    return false;
}

bool checkDraw(miniB *tabuleiros, int tab) {
    bool checkInt = true;

    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (tabuleiros[tab].pos[linha][coluna] == '_')
            {
                return checkInt = false;   
            }  
        }
    }
    
    return checkInt;
}

bool checkDrawExt(miniB tabuleiro) {
    bool checkExt = true;

    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (tabuleiro.pos[linha][coluna] == '_')
            {
                return checkExt = false;
            }
        }
    }

    return checkExt;   
}
//fim verificações linhas, colunas, diagonais

bool checkTabPlay(miniB *tabuleiro, int tab) {
    //verifica se o tabuleiro está fechado
    int y=(tab/3), x=(tab%3);

    if ((*tabuleiro).pos[y][x] != '_') {
        return true;
    } else {
        return false;
    }
}

