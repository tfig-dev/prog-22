#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

void initRandom(){
    srand(time(NULL));
}

int intUniformRnd(int a, int b){
    return a + rand()%(b-a+1);
}

//devolve tabuleiro random
int randomTab() {
    int tabN;

    tabN = intUniformRnd(0,8);

    return tabN;
}
