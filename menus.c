#include <stdio.h>
#include <string.h>
#include "menus.h"

#include "game.h"
//include do game para o TAMNOME
//TF - verificar melhor esta dependencia

#define xMinus "x"
#define xMaius "X"
#define Separator ','

int showMenu() {
    int resume=0, num=0;
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
    //previne o resume se não houver resume game

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
        printf("| -   MENU JOGADAS    - |\n");
        printf("| Y - linha| X - coluna |\n");
        printf("|                       |\n");
        printf("| Y,X |  Format [0-2]   |\n");
        printf("|  X  |  EXIT           |\n");
        printf("- - - - --------- - - - -\n");
        printf("Digite uma opcao: ");

        fgets(output, sizeof(output), stdin);
        output[strlen(output)-1] = '\0';
        printf("\n");

        if ((!strcmp(output,xMinus)) || (!strcmp(output,xMaius)) ) {
            (*valMenu) = 9; 
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
    printf("- - Ronda %d (na verdade %d) - -\n", (nRondas+1), nRondas);
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
        printf("| X | EXIT             |\n");
        printf("- - - - -------- - - - -\n");
        printf("Digite uma opcao: ");

        fgets(output, sizeof(output), stdin);
        output[strlen(output)-1] = '\0';

        printf("\n");

        if ((!strcmp(output,xMinus)) || (!strcmp(output,xMaius)) ) {
            return num = 9; 
        } else if (!strcmp(output, "1")) {
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
