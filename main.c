//librarias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Header Files
#include "game.h"
#include "menus.h"
#include "utils.h"

//funcao que adiciona nós à lista ligada
pMove addLastLinkedList(pMove p, int tab, int y, int x) {
    pMove aux, novo;

    novo = malloc(sizeof(no));

    if (novo == NULL) {
        printf("Erro a alocar memória para a jogada.\n");
        return p;
    }

    novo->tab = tab;
    novo->pos.y = y;
    novo->pos.x = x;

    novo->prox = NULL;

    if(p == NULL) {
        p = novo;
    } else {
        aux = p;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    return p;
}

//limpa nos lista ligada
void freeLinkedList(pMove p) {
    pMove aux;

    while (p != NULL)
    {
        aux = p;
        p = p->prox;
        free(aux);
    }
}

//free boards internos
void freeBoards(miniB *boards){
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            free(boards[i].pos[j]);
        }
        free(boards[i].pos);
    }
    free(boards);
}

//free board externo
void freeBoardExt(miniB board) {
    for (int i = 0; i < 3; i++)
        free(board.pos[i]);
        for (int j = 0; j < 3; j++) {
            free(board.pos[j]);
        }
        
}

//mostra lista ligada
void showList(pMove p) {
    while (p != NULL) {
        printf("TAB: %d | (%d, %d) \n", p->tab, p->pos.y, p->pos.x);
        p = p->prox;
    }
}

//conta os nós existentes na lista ligada com recurso a uma função recursiva
int countMoves(pMove p) {
    if(p == NULL)
        return 0;
    else
        return 1 + countMoves(p->prox); 
}

//funcao que mostra as ultimas jogadas pedidas pelo utilizador
void showLastMoves(pMove p, int *nVezes, int nRondas) {
    if(p == NULL)
        return;
    else {
        showLastMoves(p->prox, nVezes, nRondas);
        if((nRondas+(*nVezes))!=nRondas) {
            if ((*nVezes)%2!=0)
                printf("Jogador 1 - ");
            else 
                printf("Jogador 2 - ");

            printf("TAB: %d | (%d, %d) \n", p->tab, p->pos.y, p->pos.x);
            (*nVezes)--;   
        }
    }
}

//verifica qual foi o ultimo x e y para dar o seguinte tabuleiro a jogar
void showLastTab(pMove p, int *nVezes, int nRondas, int *oldTab, int *x, int *y) {
    if(p == NULL)
        return;
    else {
        showLastTab(p->prox, nVezes, nRondas, oldTab, x, y);
        if((nRondas+(*nVezes))!=nRondas) {
            (*oldTab) = p->tab;
            (*x) = p->pos.x;
            (*y) = p->pos.y;
            (*nVezes)--;   
        }
    }
}

//cria um novo ficheiro através do nome dado pelo operador
FILE *newFile(char Filename[TAMFILE]) {
    FILE * ficheiro = fopen(Filename, "w"); //abre ficheiro

    if (ficheiro == NULL)
    {
        printf("Erro a abrir ficheiro");
    }

    return ficheiro;
}

//apaga binário do jogo
void removeGameFile() {
    if (remove("jogo.bin") == 0)
        //se for igual a 0 é pq o ficheiro não existe
        printf("Jogo anterior apagado.\n");
}

//cria ficheiro .txt
void writeFileTXT(char Filename[TAMFILE], char jogador1[TAMNOME], char jogador2[TAMNOME], pMove p) {
    FILE * ficheiro;
    int cont=0;

    ficheiro = fopen(Filename, "w");

    if (ficheiro == NULL)
    {
        printf("Erro a abrir ficheiro");
    }

    fprintf(ficheiro, "Ultimate Tic-Tac-Toe - Programaçã0 2021/2022\n");
    fprintf(ficheiro, "Tiago Figueiredo - a2020122664@isec.pt\n");
    fprintf(ficheiro, "\n");
    fprintf(ficheiro, "Jogador 1: %s | Jogador 2: %s\n", jogador1, jogador2);
    fprintf(ficheiro, " - Text Game FILE - \n");

    fprintf(ficheiro, "\n");

    while(p != NULL) {
        if (cont%2==0) {
            fprintf(ficheiro, "Ronda %d | Jogador %s | TAB: %d; (%d, %d) \n", cont+1, jogador1, p->tab, p->pos.y, p->pos.x);
        } else {
            fprintf(ficheiro, "Ronda %d | Jogador %s | TAB: %d; (%d, %d) \n", cont+1, jogador2, p->tab, p->pos.y, p->pos.x);
        }
        p = p->prox;
        cont++;
    }

    fprintf(ficheiro, " - END OF FILE - ");

    fclose(ficheiro);
}

//verifica se existe um jogo já existente
bool checkOldGame() {
    FILE * resume;
    resume = fopen("jogo.bin", "rb");

    //se existir ficheiro, resume=1, fecha-o e devolve true
    if (resume) {
        fclose(resume);
        return true;
    } else {
        return false;
    }

}

//guarda binario do jogo
void saveListBin(pMove p, Player joga1, Player joga2){
    FILE * ficheiro;
    
    ficheiro = fopen("jogo.bin", "wb");

    if(ficheiro == NULL){
        printf("Erro a guardar ficheiro.\n");
        return;
    }

    fwrite(&joga1, sizeof(Player), 1, ficheiro);
    fwrite(&joga2, sizeof(Player), 1, ficheiro);

    while (p != NULL)
    {
        fwrite(p, sizeof(no), 1, ficheiro);
        p = p->prox;
    }

    fclose(ficheiro);
}

//imprime binario do jogo
void printFileBin() {
    no p;
    FILE * ficheiro;
    Player joga1, joga2;
    
    ficheiro = fopen("jogo.bin", "rb");
    if (ficheiro == NULL)
    {
        printf("ERRO no acesso ao ficheiro\n");
        return;
    }
    
    fread(&joga1, sizeof(Player), 1, ficheiro);
    printf("Jogador 1: %s - %d\n", joga1.name, joga1.isBot);
    fread(&joga2, sizeof(Player), 1, ficheiro);
    printf("Jogador 2: %s - %d\n", joga2.name, joga2.isBot);

    while (fread(&p, sizeof(no), 1, ficheiro) == 1) {
        printf("TAB: %d | (%d, %d) \n", p.tab, p.pos.y, p.pos.x);
    }
 
    fclose(ficheiro);
}

//recebe binario para o jogo
pMove recoverFromBinToList(Player *Joga1, Player *Joga2) {
    Player J1, J2;
    FILE * ficheiro = NULL;
    pMove list = NULL;
    pMove aux = NULL;
    no changed;

    ficheiro = fopen("jogo.bin", "rb");

    if(ficheiro == NULL){
        printf("Erro a abrir ficheiro.\n");
        return NULL;
    }

    fread(&J1, sizeof(Player), 1, ficheiro);
    fread(&J2, sizeof(Player), 1, ficheiro);

    //guarda jogador 1 no ponteiro
    strcpy(Joga1->name, J1.name);
    Joga1->isBot = J1.isBot;

    //guarda jogador 2 no ponteiro
    strcpy(Joga2->name, J2.name);
    Joga2->isBot = J2.isBot;

    while(fread(&changed, sizeof(no), 1, ficheiro)) {
        list = addLastLinkedList(list, changed.tab, changed.pos.y, changed.pos.x);

    }

    fclose(ficheiro);

    return list;
}

//devolve tabuleiro random
int randomTab() {
    int tabN;

    tabN = intUniformRnd(0,8);

    return tabN;
}

//verificações linhas, colunas, diagonais
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
//fim verificações linhas, colunas, diagonais

//verifica se ganhou o tabuleiro externo
bool endGameExtern(miniB *tabuleiro) {

    if(checkExternLine(tabuleiro)) return true;

    if(checkExternColumn(tabuleiro)) return true;

    if(checkExternDiagonal(tabuleiro)) return true;

    //se nenhum
    return false;
}

//insere vitoria no tabuleiro externo
void moveSetExt(miniB *tabuleiro, int rondas, int tab) {
    //converte o tabuleiro em posicao
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

//insere empate no tabuleiro externo
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

//verificacoes de vitora e final de jogo
bool endGame(miniB *tabuleiros, miniB *tabuleiroEXT, int rondas, int tab) {
    bool controlTable=false;

    if (rondas==0) {
        return false;
    }

    if(checkLine(tabuleiros, tab)) controlTable = true;

    if(checkColumn(tabuleiros, tab)) controlTable = true;

    if(checkDiagonal(tabuleiros, tab)) controlTable = true;

    //se existe vitória no tabuleiro interno
    if(controlTable) {
        //adiciona vitoria no tabuleiro externo
        moveSetExt(tabuleiroEXT, rondas, tab);
        //verifica se há vitoria no tabuleiro externo
        if (endGameExtern(tabuleiroEXT)) 
            return true;
    } else {
    //se não existe vitoria nos tabuleiros internos
    //verifica empate, se sim, coloca carater de empate
        if(checkDraw(tabuleiros, tab)) 
            moveSetDraw(tabuleiroEXT, tab);
    }

    return false;
}

//insere jogada nos tabuleiros
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

//insere jogadas do jogo que vem de fora
//diferente do original porque não mudamos de tabuleiro
void moveSetResume(miniB *tabuleiros, int rondas, int tab, int x, int y) {
    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (x==coluna && y==linha) {
                if(rondas%2==0) {
                    tabuleiros[tab].pos[y][x] = 'X';
                } else {
                    tabuleiros[tab].pos[y][x] = 'O';
                }
            }
        } 
    }
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

//inicia jogo
void newGame(int selec) {
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

            // printf("Jogador 1: %s - %d\n", Jogador1.name, Jogador1.isBot);
            // printf("Jogador 2: %s - %d\n", Jogador2.name, Jogador2.isBot);
            // showList(lista);

            oldRondas = countMoves(lista);
            //devolve a posição do ultimo x e y para sabermos o proximo tabuleiro
            showLastTab(lista, &posResume, oldRondas, &oldTab, &x, &y);
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

            //saber o nRondas do jogo anterior
            nRondas = countMoves(lista);

            //fazer em lista auxiliar

            while (lista != NULL) {
                moveSetResume(tabuleiros, rondasResume, lista->tab, lista->pos.x, lista->pos.y);
                endGame(tabuleiros, &tabuleiroEXT, rondasResume, lista->tab);
                rondasResume++;
                lista = lista->prox;
            }

            //removeGameFile();
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
                //printFileBin();
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

    printf("\nFim do Jogo!\n");

    freeBoards(tabuleiros);
    freeBoardExt(tabuleiroEXT);
    freeLinkedList(lista);

    //exit(0);

    selec = 9;

}

int main() {
    int selec = 0;

    do {
        //verifica se tem ficheiro através da bool resume
        selec = showMenu(checkOldGame());

        if (selec!=9) newGame(selec);

    } while (selec != 9);

    return 0;
}
