
char showMenuHistory(int jogadastab) {
    //deve passar o numero de jogadas já jogadas e colocar em limite
    char jogadas[2];
    int num;
    do {
        printf("Prima ESC se quiser voltar ao menu de jogo.\n");
        printf("\nInsira o nº de jogadas que deseja ver.");
        scanf("%c", jogadas);

    } while (num>jogadastab || num<=0);

    return jogadas;
}


void newGame(Player Jogador1, Player Jogador2) {
    miniB *tabuleiros = CriaTabuleiros();
    miniB tabuleiroEXT = CriaTabuleiro();
    int nRondas=0, winner=0, tab=0;
    bool finished = false;

    initRandom();
    tab = intUniformRnd(0,8);

    //falta o empate
    //TF
    do {
        //verifica se podes jogar e não a jogada, 
        //acho q é redundante porque no moverequest ele verifica se pode jogar atraves do checkTabPlay
        if(!endGame(tabuleiros, &tabuleiroEXT, &nRondas, tab) && !Jogador1.isBot) {
            printf("não há end game 1\n");
            printRondas(nRondas, Jogador1.name);
            showBoards(tabuleiros);
            moveRequest(tabuleiros, &tabuleiroEXT, &nRondas, &tab, false, &controlRandom);
        } 

        if(!endGame(tabuleiros, &tabuleiroEXT, &nRondas, tab) && !Jogador2.isBot) {
            printf("não há end game 2\n");
            printRondas(nRondas, Jogador2.name);
            showBoards(tabuleiros);
            moveRequest(tabuleiros, &tabuleiroEXT, &nRondas, &tab, false, &controlRandom);
        }

        if(!endGame(tabuleiros, &tabuleiroEXT, &nRondas, tab) && Jogador2.isBot) {
            printf("não há end game bot\n");
            printRondas(nRondas, Jogador2.name);
            moveRequest(tabuleiros, &tabuleiroEXT, &nRondas, &tab, true, &controlRandom);
        }

        printf("entras sempre aqui ao fim da jogada, certo e antes de jogar de novo?\n");

        if (endGame(tabuleiros, &tabuleiroEXT, &nRondas, tab)) {
            printf("há end game\n");
            showBoards(tabuleiros);

            nRondas--;

            if  (nRondas%2 == 0) {
                winner = 1;
            } else {
                winner = 2;
            }

            if (winner == 1) {
                printf("Ganhou à %d ronda o Jogador %d -> %s", nRondas, winner, Jogador1.name);
            } else {
                if (Jogador2.isBot) {
                    printf("Ganhou o bot à %d ronda! AHAHAHAH!\n", nRondas);
                } else {
                    printf("Ganhou à %d ronda o Jogador %d -> %s", nRondas, winner, Jogador2.name);
                }
            }

            finished = true;

        } else if (nRondas==81){
            printf("EMPATE\n");
            finished = true;
        }

    //while enquanto for diferente de 1 (true)
    } while (!finished);
}



bool endGame(miniB *tabuleiros, miniB *tabuleiroEXT, int *rondas, int tab) {
    if ((*rondas)==0) {
        return false;
    }

    if(checkLine(tabuleiros, tab)) {
        if (!checkTab(tabuleiroEXT, tab)) {
            moveSetExt(tabuleiroEXT, rondas, tab);
            printf("Tabuleiro %d fechado! c/linha\n", tab);
        }
    } else if(checkColumn(tabuleiros, tab)) {
        if (!checkTab(tabuleiroEXT, tab)) {
            moveSetExt(tabuleiroEXT, rondas, tab);
            printf("Tabuleiro %d fechado! c/coluna\n", tab);
        }
    } else if(checkDiagonal(tabuleiros, tab)) {
        if (!checkTab(tabuleiroEXT, tab)) {
            moveSetExt(tabuleiroEXT, rondas, tab);
            printf("Tabuleiro %d fechado! c/diagonal\n", tab);
        }
    } else if(checkDraw(tabuleiros, tab)) {
        if (!checkTab(tabuleiroEXT, tab)) {
            moveSetDraw(tabuleiroEXT, tab);
            printf("Tabuleiro %d fechado c/empate\n", tab);
        }
    }

    if (endGameExtern(tabuleiroEXT)) {
        return true;
    } else {
        return false;
    }

}
// FIM verificações endGame
