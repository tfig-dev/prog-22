#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "menus.h"
#include "utils.h"

typedef struct move no, *pMove;
struct move {
    int tab;
    int x, y;
    pMove prox;
}
//gcc *.c -o run
//dashboard trabalho P

//Criação de tabuleiros
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

int randomTab() {
    int tabN;

    tabN = intUniformRnd(0,8);

    return tabN;
}

//futuramente para o menus.c
void showBoardv3(miniB tabuleiro) {
    printf("|-------------|\n");
    printf("|- 0 - 1 - 2 X|\n");
    printf("Y|- --- --- --|\n");

    for (int i = 0; i < 3; i++)
    {
        printf("%d| ", i);
        for (int j = 0; j < 3; j++)
        {
            if(j==2) {
                printf("%c  |\n", tabuleiro.pos[i][j]);
            } else {
                printf("%c | ", tabuleiro.pos[i][j]);
            }
        }
        if (i<=1) {
            printf("| ----------- |\n");
        }
    }
    printf("|-------------|\n");
}

void showBoardsv1(miniB *tabuleiros) {
    int control = 0;

    for (int i = 0; i < 3; ++i) {
        //contrução nº tabuleiros
        printf("-------------------------------------------------------\n");
        printf("|   ||");
        for (int nTab = control; nTab < control+3; nTab++)
        {
            if ((nTab+1)%3==0) {
                printf("|     %d     |", nTab);
            } else {
                printf("|     %d     |", nTab);
                printf(" ||| ");
            }
        }
        printf("\n");
        printf("-------------------------------------------------------\n");
        //fim contrução nº tabuleiros

        //construção linhas X
        printf("| - ||");
        for (int j = 0; j < 3; j++)
        {
            printf("| 0   1   2 ");
            if(j==2) {
                printf("|");
                printf("\n");
            } else {
                printf("| ||| ");
            }
        }
        printf("-------------------------------------------------------\n");
        //fim construção linhas X

        //construção tabuleiros
        for (int linha = 0; linha < 3; linha++)
        {
            printf("| %d ||", linha);
            for (int nTab = control; nTab < (control+3); nTab++)
            { 
                for (int coluna = 0; coluna < 3; coluna++)
                {
                    printf("| %c ", tabuleiros[nTab].pos[linha][coluna]);
                }
                if(nTab==(control+2)) {
                    printf("|");
                    printf("\n");
                } else {
                    printf("| ||| ");
                }
            }
        }
        //fim construção tabuleiros

       control += 3;
    }
    printf("-------------------------------------------------------\n");
}

void showBoards(miniB *tabuleiros, miniB tabuleiroEXT, int tab) {
    int control = 0;

    for (int i = 0; i < 3; ++i) {
        //contrução nº tabuleiros
        printf("-------------------------------------------------------\n");
        printf("|   ||");
        for (int nTab = control; nTab < control+3; nTab++)
        {
            if ((nTab+1)%3==0) {
                if(tab==nTab) {
                    printf("|  -> %d <-  |", nTab);
                } else {
                    printf("|     %d     |", nTab);
                }
            } else {
                if(tab==nTab) {
                    printf("|  -> %d <-  |", nTab);
                } else {
                    printf("|     %d     |", nTab);
                }
                printf(" ||| ");
            }
        }
        printf("\n");
        printf("-------------------------------------------------------\n");
        //fim contrução nº tabuleiros

        //construção linhas X
        printf("|   ||");
        for (int j = 0; j < 3; j++)
        {
            printf("| 0   1   2 ");
            if(j==2) {
                printf("|");
                printf("\n");
            } else {
                printf("| ||| ");
            }
        }
        printf("-------------------------------------------------------\n");
        //fim construção linhas X

        //construção tabuleiros
        int y=0, x=0;
        for (int linha = 0; linha < 3; linha++)
        {
            printf("| %d ||", linha);
            for (int nTab = control; nTab < (control+3); nTab++)
            { 
                for (int coluna = 0; coluna < 3; coluna++)
                {
                    y=(nTab/3); 
                    x=(nTab%3);

                    if(linha==1 && coluna==1) {
                        if(tabuleiroEXT.pos[y][x] != '_') {
                            printf("| %c ", tabuleiroEXT.pos[y][x]);
                        } else {
                            printf("| %c ", tabuleiros[nTab].pos[linha][coluna]);
                        }
                    } else {
                        if(tabuleiroEXT.pos[y][x] != '_') {
                            printf("|   ");
                        } else {
                            printf("| %c ", tabuleiros[nTab].pos[linha][coluna]);
                        }
                    }
                
                }
                if(nTab==(control+2)) {
                    printf("|");
                    printf("\n");
                } else {
                    printf("| ||| ");
                }
            }
        }
        //fim construção tabuleiros

       control += 3;
    }
    printf("-------------------------------------------------------\n");
}

//verificações endGame - passar para game
bool checkTabPlay(miniB *tabuleiro, int tab) {
    //verifica se o tabuleiro está fechado
    int y=(tab/3), x=(tab%3);

    if ((*tabuleiro).pos[y][x] != '_') {
        return true;
    } else {
        return false;
    }
}

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

bool endGameExtern(miniB *tabuleiro) {

    if(checkExternLine(tabuleiro)) return true;

    if(checkExternColumn(tabuleiro)) return true;

    if(checkExternDiagonal(tabuleiro)) return true;

    //se nenhum
    return false;
}

void moveSetExt(miniB *tabuleiro, int rondas, int tab) {
    int y=((tab)/3), x=((tab)%3);

    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (x==coluna && y==linha) {
                if(rondas%2==0) {
                    (*tabuleiro).pos[y][x] = 'X';
                } else {
                    (*tabuleiro).pos[y][x] = 'O';
                }
            }
        } 
    }
}

void moveSetDraw(miniB *tabuleiro, int tab) {
    int y=(tab/3), x=(tab%3);

    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (x==coluna && y==linha) {
                (*tabuleiro).pos[y][x] = '.';
            }
        } 
    }
}

bool endGame(miniB *tabuleiros, miniB *tabuleiroEXT, int rondas, int tab) {
    bool controlTable=false;

    if (rondas==0) {
        return false;
    }

    if(checkLine(tabuleiros, tab)) controlTable = true;

    if(checkColumn(tabuleiros, tab)) controlTable = true;

    if(checkDiagonal(tabuleiros, tab)) controlTable = true;

    if(controlTable) {
        moveSetExt(tabuleiroEXT, rondas, tab);
        if (endGameExtern(tabuleiroEXT)) 
            return true;
    } else {
        if(checkDraw(tabuleiros, tab)) 
            moveSetDraw(tabuleiroEXT, tab);
    }

    return false;
}

void moveSet(miniB *tabuleiros, int rondas, int *tab, int x, int y) {
    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (x==coluna && y==linha) {
                if(rondas%2==0) {
                    tabuleiros[(*tab)].pos[y][x] = 'X';
                } else {
                    tabuleiros[(*tab)].pos[y][x] = 'O';
                }
            }
        } 
    }

    //novo tabuleiro
    (*tab) = y*3+x;
}

bool moveCheck(miniB *tabuleiros, int *tab, int x, int y) {
    bool moveOK;

    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (x==coluna && y==linha) {
                if (tabuleiros[(*tab)].pos[linha][coluna] != '_') {
                    return moveOK = false;
                }
            }
        } 
    }

    return moveOK = true;
}

void moveRequest(miniB *tabuleiros, miniB *tabuleiroEXT, int nRondas, int *atualTab, bool isBot) {
    bool request=false;
    int valorMenu=0, x=0, y=0;

    do {
        if (isBot) {
            do {
                x = intUniformRnd(0,2);
                y = intUniformRnd(0,2);

            } while(!moveCheck(tabuleiros, atualTab, x, y));

            printf("Jogador 2 -> Tabuleiro: %d | %d, %d \n", *atualTab, y, x);

            moveSet(tabuleiros, nRondas, atualTab, x, y);
            request=true;
            break;
        } else {
            printf("TABULEIRO EM JOGO: %d\n", *atualTab);
            //se não for bot pede valores ao utilizador
            showMenuMoveRepeat(&valorMenu, &y, &x);
        }

        //Play
        if (valorMenu==1)
        {
            //verifica jogada
            //se move check = 1 (true)
            if (moveCheck(tabuleiros, atualTab, x, y)) {
                moveSet(tabuleiros, nRondas, atualTab, x, y);
                request=true;
            } else {
                printf("Jogada Inválida! - Tente Novamente!\n");
                continue;
            }
        } else {
            //TF
            request=true;
            printf("EXIT\n");
        }
        
    } while (!request);
}

void newGame(Player Jogador1, Player Jogador2) {
    miniB *tabuleiros = CriaTabuleiros();
    miniB tabuleiroEXT = CriaTabuleiro();
    pMove lista = NULL;
    
    int nRondas=0, oldRondas=0, tab=0, oldTab=0, winner=0;
    bool finished = false, tabulNext=false;

    initRandom();
    tab = intUniformRnd(0,8);

    do {

        oldTab = tab;
        oldRondas = nRondas;

        if(nRondas%2==0) {
            printRondas(nRondas, Jogador1.name);
            //TF
            //no showboard passa o tab e sinaliza qual é que está a ser jogado
            //quando fechado um tabuleiro externo atualiza no showboards e assim o showboard(tabuleiro) pode desaparecer
            showBoards(tabuleiros, tabuleiroEXT, tab);
            moveRequest(tabuleiros, &tabuleiroEXT, nRondas, &tab, false);
        } else {
            if (!Jogador2.isBot) {
                printRondas(nRondas, Jogador2.name);
                showBoards(tabuleiros, tabuleiroEXT, tab);
                moveRequest(tabuleiros, &tabuleiroEXT, nRondas, &tab, false);
            } else {
                printRondas(nRondas, Jogador2.name);
                moveRequest(tabuleiros, &tabuleiroEXT, nRondas, &tab, true);
            }
        }

        if (endGame(tabuleiros, &tabuleiroEXT, oldRondas, oldTab)) {
            showBoards(tabuleiros, tabuleiroEXT, -1);

            if  (oldRondas%2 == 0) {
                printf("Ganhou à %d ronda o Jogador 1 -> %s\n", oldRondas+1, Jogador1.name);
            } else {
                if (Jogador2.isBot) {
                    printf("Ganhou o bot à %d ronda! AHAHAHAH!\n", oldRondas+1);
                } else {
                    printf("Ganhou à %d ronda o Jogador 2 -> %s\n", oldRondas+1, Jogador2.name);
                }
            }
            finished = true;

        //TF
        //testa empate
        } else if (checkDrawExt(tabuleiroEXT)) {
            printf("Todos os tabuleiros preenchidos.\n");
            printf("Empate\n");
            finished = true;
            break;

        } else {
            //jogada seguinte
            nRondas++;
            do {
                //se true está fechado, tem que mudar
                //se false pode jogar
                if (!checkTabPlay(&tabuleiroEXT, tab)) {
                    tabulNext = true;
                } else {
                    printf("Tabuleiro anterior: %d\n", oldTab);
                    tab = randomTab();
                    printf("Tabuleiro novo: %d\n", tab);
                    tabulNext = false;
                }
            } while (!tabulNext);
        }

    } while (!finished);
}

int main() {
    int selec = 0, continueGame = 0, rondas = 0;
    Player jogador1, jogador2;
    bool teste = true;

    do {
        selec = showMenu();

        if (selec==0) {
            continueGame = showMenuInGame();

            if (continueGame) {
                //restoreGame
            } else if (continueGame==2) {
                printf("O jogo guardado será eliminado.\n");
                printf("A criar novo jogo ... \n");
                //remover ficheiro 
                selec = 1;
            } else {
                selec = 9;
                continue;
            }
        } else if (selec==1) {
            //Multi
            createPlayers(false, &jogador1, &jogador2);
            //TF
            newGame(jogador1, jogador2);
        } else if (selec==2) {
            //bot
            createPlayers(true, &jogador1, &jogador2);
            newGame(jogador1, jogador2);
        }

    } while (selec == 9);

    printf("\nFim do Jogo!\n");

    return 0;
}
