#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "game.h"

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
    free(board.pos);
}

