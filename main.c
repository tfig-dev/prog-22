//librarias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header Files
#include "game.h"
#include "menus.h"
#include "utils.h"
#include "files.h"
#include "tests.h"

//insere vitoria no tabuleiro externo
void moveSetExt(miniB *tabuleiro, int rondas, int tab) {
    //converte o tabuleiro em posicao
    int y=((tab)/3), x=((tab)%3);

    if(rondas%2==0) (*tabuleiro).pos[y][x] = 'X';
    else (*tabuleiro).pos[y][x] = 'O';
}

//insere empate no tabuleiro externo
void moveSetDraw(miniB *tabuleiro, int tab) {
    int y=(tab/3), x=(tab%3);

    (*tabuleiro).pos[y][x] = '.';
}

//insere jogada nos tabuleiros
void moveSet(miniB *tabuleiros, int rondas, int *tab, int x, int y) {
    if(rondas%2==0) tabuleiros[(*tab)].pos[y][x] = 'X';
    else tabuleiros[(*tab)].pos[y][x] = 'O';
    //novo tabuleiro
    (*tab) = y*3+x;
}

//insere jogadas do jogo que vem de fora diferente do original porque não mudamos de tabuleiro
void moveSetResume(miniB *tabuleiros, int rondas, int tab, int x, int y) {
    if(rondas%2==0) tabuleiros[tab].pos[y][x] = 'X';
    else tabuleiros[tab].pos[y][x] = 'O';
}

//verifica se ganhou o tabuleiro externo
bool endGameExtern(miniB *tabuleiro) {

    if(checkExternLine(tabuleiro)) return true;

    if(checkExternColumn(tabuleiro)) return true;

    if(checkExternDiagonal(tabuleiro)) return true;

    //se nenhum
    return false;
}

//verificacoes de vitora e final de jogo
bool endGame(miniB *tabuleiros, miniB *tabuleiroEXT, int rondas, int tab) {
    bool controlTable=false;

    if (rondas==0) return false;

    if(checkLine(tabuleiros, tab)) controlTable = true;

    if(checkColumn(tabuleiros, tab)) controlTable = true;

    if(checkDiagonal(tabuleiros, tab)) controlTable = true;

    //se existe vitória no tabuleiro interno
    if(controlTable) {
        //adiciona vitoria no tabuleiro externo
        moveSetExt(tabuleiroEXT, rondas, tab);
        //verifica se há vitoria no tabuleiro externo
        if (endGameExtern(tabuleiroEXT)) return true;
    } else {
    //se não existe vitoria nos tabuleiros internos
    //verifica empate, se sim, coloca carater de empate
        if(checkDraw(tabuleiros, tab)) moveSetDraw(tabuleiroEXT, tab);
    }

    return false;
}

//verifica se jogada a inserir é possivel
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

//pede jogada ao utilizador
void moveRequest(miniB *tabuleiros, miniB *tabuleiroEXT, int nRondas, int *atualTab, bool isBot, bool *viewMove, bool *end, bool *save, int *xPos, int *yPos) {
    bool request=false, viewM=false;
    int valorMenu=0, valorMenuSave=0, x=0, y=0, seeMoves=0, oldTab=0;

    oldTab = (*atualTab);

    do {
        //se for a vez do bot a jogar não apresenta tabuleiros
        //faz random de jogadas até uma ser possivel
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
            //se não for bot pede valores ao utilizador
            showMenuMoveRepeat(&valorMenu, &y, &x);
        }

        //Play
        if (valorMenu==1)
        {
            //verifica jogada
            //se jogada for possivel -> move check = 1 (true)
            if (moveCheck(tabuleiros, atualTab, x, y)) {
                moveSet(tabuleiros, nRondas, atualTab, x, y);

                request=true;
            } else {
                printf("Jogada Inválida! - Tente Novamente!\n");
                continue;
            }
        //verifica jogadas anteriores
        } else if (valorMenu==2) {
            //se houver jogadas verifica
            if (nRondas!=0) {
                (*viewMove) = true;
                request = true;
            } else {
                printf("Não existem jogadas a verificar!\n");
                continue;
            }
        //exit
        } else {
            if(nRondas!=0) {
                valorMenuSave = showMenuSave();
                
                (*end) = true;

                //verfica se quer gravar
                if (valorMenuSave==1) {
                    (*save) = true;
                } else {
                    (*save) = false;
                }
            } else {
                (*end) = true;
                (*save) = false;
            }
            request=true;
        }
        
    } while (!request);

    //atualiza ponteiros de x e y para a seguir verificar se o tabuleiro seguinte é possivel
    (*xPos) = x;
    (*yPos) = y;
}

//le lista ligada para colocar jogadas no tabuleiro
void readLinkedList(miniB *tabuleiros, miniB tabuleiroEXT, pMove p) {
    pMove aux;
    int rondasResume=0;

    if(p == NULL) {
        printf("Erro na lista ligada!\n");
    } else {
        aux = p;
        while (aux != NULL)
        {
            moveSetResume(tabuleiros, rondasResume, aux->tab, aux->pos.x, aux->pos.y);
            showBoards(tabuleiros, tabuleiroEXT, aux->tab);
            endGame(tabuleiros, &tabuleiroEXT, rondasResume, aux->tab);
            rondasResume++;
            aux = aux->prox;
        }   
    }
}

//inicia jogo
int newGame(int selec) {
    Player Jogador1, Jogador2;
    miniB *tabuleiros = CriaTabuleiros();
    miniB tabuleiroEXT = CriaTabuleiro();
    pMove lista = NULL;
    char nomeFicheiro[TAMFILE];
    
    int continueGame=0, rondasResume=0, nRondas=0, oldRondas=0, tab=0, oldTab=0, winner=0, x=0, y=0, posResume=1, jogadas=0, viewOldMoves=0;
    bool finished = false, tabulNext=false, tabulNextResume=false, end=false, save=false, viewM=false;

    if (selec == 1) {
        //newgame multiplayer
        removeGameFile();
        createPlayers(false, &Jogador1, &Jogador2);
        initRandom();
        tab = intUniformRnd(0,8);
    } else if (selec == 2) {
        //newgame bot
        removeGameFile();
        createPlayers(true, &Jogador1, &Jogador2);
        initRandom();
        tab = intUniformRnd(0,8);
    } else if (selec == 0) {
        continueGame = showMenuResume();
        if (continueGame==1) {

            //recebe na lista o ficheiro binario previamente criado e atualiza jogadores
            lista = recoverFromBinToList(&Jogador1, &Jogador2);

            nRondas = countMoves(lista);
            //devolve a posição do ultimo x e y para sabermos o proximo tabuleiro
            showLastTab(lista, &posResume, nRondas, &oldTab, &x, &y);
            //converte o x,y para tabuleiro
            tab = y*3+x;

            //verifica se tabuleiro anterior é possivel para jogar
            do {
                //se true está fechado, tem que mudar
                //se false pode jogar
                if (!checkTabPlay(&tabuleiroEXT, tab)) {
                    tabulNextResume = true;
                } else {
                    tab = randomTab();
                    tabulNextResume = false;
                }
            } while (!tabulNextResume);

            readLinkedList(tabuleiros, tabuleiroEXT, lista);
            removeGameFile();

        } else {
            printf("O jogo anterior será eliminado.\n");
            removeGameFile();
            printf("A criar novo jogo ... \n");

            createPlayers(false, &Jogador1, &Jogador1);
            initRandom();
            tab = intUniformRnd(0,8);
        }
    }

    do {

        oldTab = tab;
        oldRondas = nRondas;

        //pedidos de jogadas
        if(nRondas%2==0) {
            printRondas(nRondas, Jogador1.name);
            showBoards(tabuleiros, tabuleiroEXT, tab);
            moveRequest(tabuleiros, &tabuleiroEXT, nRondas, &tab, false, &viewM, &end, &save, &x, &y);
        } else {
            if (!Jogador2.isBot) {
                printRondas(nRondas, Jogador2.name);
                showBoards(tabuleiros, tabuleiroEXT, tab);
                moveRequest(tabuleiros, &tabuleiroEXT, nRondas, &tab, false, &viewM, &end, &save, &x, &y);
            } else {
                printRondas(nRondas, Jogador2.name);
                moveRequest(tabuleiros, &tabuleiroEXT, nRondas, &tab, true, &viewM, &end, &save, &x, &y);
            }
        }

        //se acaba
        if (end) {
            if(save) {
                //pergunta se quer guardar
                saveListBin(lista, Jogador1, Jogador2);
            }

            finished = true;

        } else {
            if (viewM) {
                //se é para verificar, pede jogadas a verificar e confirma se existem
                jogadas = countMoves(lista);
                viewOldMoves = showMenuHistory(jogadas);

                printf("Ultimas %d jogadas:\n", viewOldMoves);
                showLastMoves(lista, &viewOldMoves, jogadas);

                viewM = false;
            } else {
                //verificação de jogadas
                //add jogada link list
                lista = addLastLinkedList(lista, oldTab, y, x);

                if (endGame(tabuleiros, &tabuleiroEXT, nRondas, oldTab)) {
            
                    showBoards(tabuleiros, tabuleiroEXT, -1);

                    if  (nRondas%2 == 0) {
                        printf("Ganhou à %d ronda o Jogador 1 -> %s\n", (nRondas+1), Jogador1.name);
                    } else {
                        if (Jogador2.isBot) {
                            printf("Ganhou o bot à %d ronda! AHAHAHAH!\n", (nRondas+1));
                        } else {
                            printf("Ganhou à %d ronda o Jogador 2 -> %s\n", (nRondas+1), Jogador2.name);
                        }
                    }

                    printf("Qual vai ser o nome do ficheiro?\n> ");
                    fgets(nomeFicheiro, sizeof(nomeFicheiro), stdin);
                    nomeFicheiro[strlen(nomeFicheiro)-1] = '\0';

                    strcat(nomeFicheiro, ".txt");

                    writeFileTXT(nomeFicheiro, Jogador1.name, Jogador2.name, lista);

                    finished = true;

                } else if (checkDrawExt(tabuleiroEXT)) {

                    printf("Todos os tabuleiros preenchidos.\n");
                    printf("Jogo Empatado\n");

                    printf("Qual vai ser o nome do ficheiro?\n> ");
                    fgets(nomeFicheiro, sizeof(nomeFicheiro), stdin);
                    nomeFicheiro[strlen(nomeFicheiro)-1] = '\0';

                    strcat(nomeFicheiro, ".txt");

                    writeFileTXT(nomeFicheiro, Jogador1.name, Jogador2.name, lista);

                    finished = true;

                } else {
                    //jogada seguinte
                    nRondas++;
                    do {
                        //se true está fechado, tem que mudar
                        //se false pode jogar
                        if (!checkTabPlay(&tabuleiroEXT, tab)) {
                            tabulNext = true;
                        } else {
                            tab = randomTab();
                            tabulNext = false;
                        }
                    } while (!tabulNext);
                }
            }
        }
    } while (!finished);

    freeBoards(tabuleiros);
    freeBoardExt(tabuleiroEXT);
    freeLinkedList(lista);

    return 9;
}

//main
int main() {
    int selec = 0;

    do {
        //verifica se tem ficheiro através da bool resume
        selec = showMenu(checkOldGame());

        if (selec!=9) selec = newGame(selec);

    } while (selec != 9);

    printf("END\n");

    return 0;
}
