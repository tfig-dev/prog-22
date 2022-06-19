#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"

#include "game.h"
//include do game para o TAMNOME

#define xMinus "x"
#define xMaius "X"
#define mMinus "m"
#define mMaius "M"
#define Separator ','

int showMenu(bool resume) {
    int num=0;
    char output[255];
    //ver se consigo ir buscar a data de criação do ficheiro
    //verifica se tem ficheiro

    do {
        printf("| - - - MENU - - - |\n");
        printf("|                  |\n");

        if (resume) {
            printf("| 0 | Resume Game  |\n");
            printf("|                  |\n");
            printf("| - - New Game - - |\n");
            printf("|                  |\n");
        }

        printf("| 1 | Multiplayer  |\n");
        printf("| 2 | Singleplayer |\n");
        printf("| X | Exit         |\n");
        printf("- - - - ---- - - - -\n");
        printf("Digite uma opcao: ");

        fgets(output, sizeof(output), stdin);
        output[strlen(output)-1] = '\0';

        printf("\n");

        if ( (!strcmp(output,xMinus)) || (!strcmp(output,xMaius)) ) {
            return num = 9; 
        } else if (!strcmp(output, "0")) {
            num = 0;
        } else if (!strcmp(output, "1")){
            return num = 1;
        } else if (!strcmp(output, "2")){
            return num = 2;
        }  else {
            //considerado ERRO
            num = 7;
        }
       
    } while (num==0 && resume==0 || num==7);
    //previne menor 0
    //previne o 0 se não houver resume game

    return num;
}

int showMenuInGame() {
    int num=0;
    char output[255];
    
    do {
        printf("| - MENU IN GAME - |\n");
        printf("|                  |\n");
        printf("| 1 | Play         |\n");
        printf("| 2 | History      |\n");
        printf("| 8 | Save & Exit  |\n");
        printf("| X | Exit         |\n");
        printf("- - - - ---- - - - -\n");
        printf("Digite uma opcao: ");

        fgets(output, sizeof(output), stdin);
        output[strlen(output)-1] = '\0';

        printf("\n");

        if ( (!strcmp(output,xMinus)) || (!strcmp(output,xMaius)) ) {
            return num = 9; 
        } else if (!strcmp(output, "1")) {
            num = 1;
        } else if (!strcmp(output, "2")){
            return num = 2;
        } else if (!strcmp(output, "8")){
            return num = 8;
        }  else {
            //considerado ERRO
            num = 7;
        }
    } while (num==7);

    return num;
}

void showMenuMoveRepeat(int *valMenu, int *yMenu, int *xMenu) {
    char output[255];

    do {
        printf("| -    MENU JOGADAS   - |\n");
        printf("| Y - linha| X - coluna |\n");
        printf("|      Format [0-2]     |\n");
        printf("|                       |\n");
        printf("| Y,X |  JOGAR          |\n");
        printf("|  M  |  VER JOGADAS    |\n");
        printf("|  X  |  EXIT           |\n");
        printf("- - - - --------- - - - -\n");
        printf("Digite uma opcao: ");

        fgets(output, sizeof(output), stdin);
        output[strlen(output)-1] = '\0';
        printf("\n");

        if ((!strcmp(output,xMinus)) || (!strcmp(output,xMaius)) ) {
            (*valMenu) = 9; 
            return;
        } else if ((!strcmp(output,mMinus)) || (!strcmp(output,mMaius))) {
            (*valMenu) = 2;
            return;
        } else if ((output[1]==Separator) && (strlen(output)==3)) {
            if (output[0]-48>=0 && output[0]-48<=2) {
                if (output[2]-48>=0 && output[2]-48<=2) {
                    (*yMenu) = output[0]-48;
                    (*xMenu) = output[2]-48;
                    (*valMenu) = 1;
                    return;
                }
            }
        }
        
        (*valMenu) = 7;
        
    } while ((*valMenu)==7);
}

void printRondas(int nRondas, char jogador[TAMNOME]) {
    printf("- - Ronda %d - -\n", (nRondas+1));
    if(nRondas%2==0) {
        printf("Jogador 1: %s -> X\n", jogador);
    } else {
        printf("Jogador 2: %s -> O\n", jogador);
    }
    printf("- - - - - - - - -\n");
}

int showMenuResume() {
    int num=0;
    char output[255];
    
    do {
        printf("| - -  RESUME GAME - - |\n");
        printf("| Tem um jogo guardado.|\n");
        printf("| Deseja retoma-lo?    |\n");
        printf("|                      |\n");
        printf("| 1 | SIM              |\n");
        printf("| 2 | NÃO              |\n");
        printf("- - - - -------- - - - -\n");
        printf("Digite uma opcao: ");

        fgets(output, sizeof(output), stdin);
        output[strlen(output)-1] = '\0';

        printf("\n");

        if (!strcmp(output, "1")) {
            num = 1;
        } else if (!strcmp(output, "2")){
            return num = 2;
        } else {
            //considerado ERRO
            num = 7;
        }
    } while (num==7);

    return num;
}

int showMenuHistory(int jogadas) {
    //deve passar o numero de jogadas já jogadas e colocar em limite
    int num;
    char output[255];

    do {
        printf("Insira o nº de jogadas que deseja ver.\n");
        fgets(output, sizeof(output), stdin);
        
        num = atoi(output);

        if(num>jogadas)
            printf("Numero superior às rondas do jogo. Tente outra vez!\n");

    } while (num>jogadas || num<=0);

    return num;
}

int showMenuSave() {
    int num=0;
    char output[255];
    
    do {
        printf("| - -  LEAVE GAME  - - |\n");
        printf("|    Deseja guardar    |\n");
        printf("|    o jogo atual?     |\n");
        printf("|                      |\n");
        printf("| 1 | SIM              |\n");
        printf("| 2 | NÃO              |\n");
        printf("- - - - -------- - - - -\n");
        printf("Digite uma opcao: ");

        fgets(output, sizeof(output), stdin);
        output[strlen(output)-1] = '\0';

        printf("\n");

        if (!strcmp(output, "1")) {
            return num = 1;
        } else if (!strcmp(output, "2")){
            return num = 2;
        }  else {
            //considerado ERRO
            num = 7;
        }
    } while (num==7);

    return num;
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
