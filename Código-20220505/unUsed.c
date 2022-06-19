

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


//TF funfa
pMove addLastLinkedList(pMove p, int tab, int y, int x) {
    pMove aux, novo;

    novo = malloc(sizeof(no));

    if (novo == NULL) return p;

    novo->tab = tab;
    novo->pos.x = x;
    novo->pos.y = y;

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

void showList2(pMove *p) {
    while (*p != NULL) {
        printf("TAB: %d | (%d, %d) \n", (*p)->tab, (*p)->pos.y, (*p)->pos.x);
        *p = (*p)->prox;
    }
}

//TF funfa
void saveListBin(pMove p, char jogador1[TAMNOME], char jogador2[TAMNOME], bool isBot){
    FILE * ficheiro;
    
    ficheiro = fopen("jogo.bin", "wb");

    if(ficheiro == NULL){
        printf("Erro a guardar ficheiro.\n");
        return;
    }

    printf("inicio guarda bin lista\n"); 
    fwrite(jogador1, sizeof(char), TAMNOME, ficheiro);
    fwrite(jogador2, sizeof(char), TAMNOME, ficheiro);
    fwrite(&isBot, sizeof(bool), 1, ficheiro);

    while (p != NULL)
    {
        fwrite(&p, sizeof(pMove), 1, ficheiro);
        p = p->prox;
    }
    printf("fim guarda bin lista\n"); 

    fclose(ficheiro);
}



void saveListBin3(pMove *p, Player joga1, Player joga2){
    FILE * ficheiro;
    
    ficheiro = fopen("jogo.bin", "wb");

    if(ficheiro == NULL){
        printf("Erro a guardar ficheiro.\n");
        return;
    }

    printf("inicio guarda bin lista\n"); 
    fwrite(&joga1, sizeof(Player), 1, ficheiro);
    fwrite(&joga2, sizeof(Player), 1, ficheiro);

    while ((*p) != NULL)
    {
        fwrite(&p, sizeof(pMove), 1, ficheiro);
        p = (*p)->prox;
    }
    printf("fim guarda bin lista\n"); 

    fclose(ficheiro);
}

//TF funfa funcao teste para verificar ficheiro BIN
void printFileBin() {
    pMove p;
    FILE * ficheiro;
    char jogador[TAMNOME];
    bool isBot;
    
    ficheiro = fopen("jogo.bin", "rb");
    if (ficheiro == NULL)
    {
        printf("ERRO no acesso ao ficheiro\n");
        return;
    }
    
    printf("inicio print bin lista\n");
    fread(jogador, sizeof(char), TAMNOME, ficheiro);
    printf("Jogador 1: %s\n", jogador);
    fread(jogador, sizeof(char), TAMNOME, ficheiro);
    printf("Jogador 2: %s\n", jogador);
    fread(&isBot, sizeof(bool), 1, ficheiro);
    printf("%d\n", isBot);

    while (fread(&p, sizeof(pMove), 1, ficheiro) == 1) {
        printf("TAB: %d | Y: %d - X: %d \n", p->tab, p->pos.y, p->pos.x);
        p = p->prox;
    }
    printf("fim print bin lista\n");

    fclose(ficheiro);
}



//1 warning
//tirei o ponteiro de p
pMove addLastLinkedList(pMove p, int tab, int y, int x) {
    pMove aux, novo;

    novo = malloc(sizeof(no));

    if (novo == NULL) return p;

    novo->tab = tab;
    novo->pos.x = x;
    novo->pos.y = y;

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


pMove addLastLinkedList(pMove *p, int tab, int y, int x) {
    pMove aux, novo;

    novo = malloc(sizeof(no));

    if (novo == NULL) return *p;

    novo->tab = tab;
    novo->pos.x = x;
    novo->pos.y = y;

    novo->prox = NULL;

    if(*p == NULL) {
        *p = novo;
    } else {
        aux = *p;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    return *p;
}


int countMoves(pMove *p) {
    if(*p == NULL)
        return 0;
    else
        return 1 + countMoves((*p)->prox); 
}




void newGame(int selec) {
    Player Jogador1, Jogador2;
    miniB *tabuleiros = CriaTabuleiros();
    miniB tabuleiroEXT = CriaTabuleiro();
    pMove *lista = NULL;
    char nomeFicheiro[TAMFILE];
    
    int nRondas=0, oldRondas=0, tab=0, oldTab=0, winner=0, x=0, y=0, posResume=1, jogadas=0, viewOldMoves=0;
    bool finished = false, tabulNext=false, end=false, save=false, viewM=false;

    int continueGame=0;

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
            //TF
            //restoreGame
            pMove *lista2 = NULL;
            printFileBin();
            lista2 = recoverFromBinToList(&Jogador1, &Jogador2);

            printf("Jogador 1: %s - %d\n", Jogador1.name, Jogador1.isBot);
            printf("Jogador 2: %s - %d\n", Jogador2.name, Jogador2.isBot);

            printf("lista after receive in\n");
            showList(lista2);
            printf("\n");
            removeGameFile();
            //TF estas rondas são as corretas ou tem que ser menos 1?

            oldRondas = countMoves(lista);
            showLastTab(lista, &posResume, &oldRondas, &oldTab, &x, &y);
            tab = y*3+x;
            oldRondas = countMoves(lista);
            oldRondas--;
        } else {
            printf("O jogo anterior será eliminado.\n");
            removeGameFile();
            printf("A criar novo jogo ... \n");
            //TF
            //apagar lista
            createPlayers(false, &Jogador1, &Jogador1);
            initRandom();
            tab = intUniformRnd(0,8);
        }
    }

    do {
        if (continueGame!=1) {

            oldTab = tab;
            oldRondas = nRondas;

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
        }

        continueGame = 0;

        if (end) {
            if(save) {
                printf("verificações end save! showList\n");
                showList(lista);
                printf("save list to bin\n");
                //TF
                //só este é que fica
                saveListBin(lista, Jogador1, Jogador2);
                printf("print bin\n");
                printFileBin();

                freeLinkedList(lista);
                
                pMove *lista2 = NULL;

                Player jogador3, jogador4;

                printf("Recover\n");
                lista2 = recoverFromBinToList(&jogador3, &jogador4);
                
                printf("Jogador 1: %s - %d\n", jogador3.name, jogador3.isBot);
                printf("Jogador 2: %s - %d\n", jogador4.name, jogador4.isBot);

                showList(lista2);
            }

            finished = true;

        } else {
            if (viewM) {
                //TF 
                //está okay, apenas mostra é o menu 2x
                printf("nRondas = %d\n", nRondas);

                jogadas = countMoves(lista);

                printf("tes = %d\n", jogadas);

                if (jogadas == nRondas) {
                    printf("é igual\n");
                } else {
                    printf("não é igual\n");
                }
                viewOldMoves = showMenuHistory(jogadas);

                printf("Ultimas %d jogadas:\n", viewOldMoves);
                showLastMoves(lista, &viewOldMoves, jogadas);

                viewM = false;

            } else {

                //add jogada link list
                addLastLinkedList(lista, oldTab, y, x);

                printf("lista in\n");
                showList(lista);
                printf("\n");

                if (endGame(tabuleiros, &tabuleiroEXT, oldRondas, oldTab)) {
            
                    showBoards(tabuleiros, tabuleiroEXT, -1);

                    if  (oldRondas%2 == 0) {
                        printf("Ganhou à %d ronda o Jogador 1 -> %s\n", (oldRondas+1), Jogador1.name);
                    } else {
                        if (Jogador2.isBot) {
                            printf("Ganhou o bot à %d ronda! AHAHAHAH!\n", (oldRondas+1));
                        } else {
                            printf("Ganhou à %d ronda o Jogador 2 -> %s\n", (oldRondas+1), Jogador2.name);
                        }
                    }

                    printf("Qual vai ser o nome do ficheiro?\n> ");
                    scanf("%s", nomeFicheiro);
                    sprintf(nomeFicheiro, "%s.txt", nomeFicheiro);

                    writeFileTXT(nomeFicheiro, Jogador1.name, Jogador2.name, lista);

                    finished = true;

                } else if (checkDrawExt(tabuleiroEXT)) {
                    //TF
                    //testa empate

                    printf("Todos os tabuleiros preenchidos.\n");
                    printf("Jogo Empatado\n");

                    printf("Qual vai ser o nome do ficheiro?\n> ");
                    scanf("%s", nomeFicheiro);
                    sprintf(nomeFicheiro, "%s.txt", nomeFicheiro);

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
                            printf("Tabuleiro novo: %d\n", tab);
                            tabulNext = false;
                        }
                    } while (!tabulNext);
                }
            }
        }
    } while (!finished);

    //TF
    //limparMemoriaTab(tabuleiros);
    //printf("\nMemoria limpa.");

}
