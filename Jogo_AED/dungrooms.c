#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dungrooms.h"

//-----------------------------------------------begin DUNGEONFUNC.c----------------------------------------------------------//
dung *createDungeon(int MATRIXMAX){    //função responsável por gerar um ponteiro alocado para uma dungeon;
                                       //o que permite a passagem eficiente dessa como parâmetro;
    dung *D = (dung*) calloc(1, sizeof(dung));
    if(D == NULL) return NULL;
    D->MATRIXMAX = MATRIXMAX;

    int i;

    D->map = (int**) calloc(D->MATRIXMAX, sizeof(int*));
    for(i = 0; i < D->MATRIXMAX; i++){
        D->map[i] = (int*) calloc(D->MATRIXMAX, sizeof(int));
        if(D->map[i] == NULL) return NULL;
    }

    return D;
}

void printar_matriz(dung *D){    //função de desenvolvedor responsável por imprimir um mapa;
                                 //para motivos de debugging e teste;
    for(int i = 0; i < D->MATRIXMAX; i++){
        printf("\t\t");
        for(int j = 0; j < D->MATRIXMAX; j++){
            if(D->map[i][j]){
                if(i == D->spawn[0] && j == D->spawn[1]){
                    printf("@ ");
                }
                else if(i == D->keyroom[0] && j == D->keyroom[1]){
                    printf("? ");
                }
                else if(D->map[i][j] < 10){
                    printf("%d ", D->map[i][j]);
                }
                else if(D->map[i][j] < 15){
                    printf("T ");
                }
                else if(D->map[i][j] < 20){
                    printf("V ");
                }
                else{
                    printf("X ");
                }
            }
            else printf("  ");
        }
        printf("\n");
    }

}

void printar_matriz2(dung *D, int *pos){

    for(int i = 0; i < D->MATRIXMAX; i++){
        printf("\t\t");
        for(int j = 0; j < D->MATRIXMAX; j++){
            if(D->map[i][j]){
                if(pos[0] == i && pos[1] == j){
                    printf("@ ");
                }
                else if(i == D->spawn[0] && j == D->spawn[1]){
                    printf("! ");
                }
                else if(i == D->keyroom[0] && j == D->keyroom[1]){
                    printf("? ");
                }
                else if(D->map[i][j] < 10){
                    printf("%d ", D->map[i][j]);
                }
                else if(D->map[i][j] < 15){
                    printf("T ");
                }
                else if(D->map[i][j] < 20){
                    printf("V ");
                }
                else{
                    printf("X ");
                }
            }
            else printf("  ");
        }
        printf("\n");
    }

}

void MatInit(dung *D, int val){    //inicializa um mapa com um valor;
    int i, j;
    for(i = 0; i < D->MATRIXMAX; i++){
        for(j = 0; j < D->MATRIXMAX; j++){
            D->map[i][j] = val;
        }
    }
}

/*
    COMO A FUNÇÃO "gerdorDeDungeon" OPERA:

        1. inicializa o 'MOUSE' em D->map[5][6];

        2. sorteia uma direção ao acaso para 'MOUSE' se mover, sendo:
            '0' para "Sul", incrementando i;
            '1' para "Norte", decrementando i;
            '2' para "Leste", incrementando j;
            '3' para "Oeste", decrementando j;

        3. testa se 'MOUSE' pode se mover 1 casa para a direção selecionada pelos seguintes aspectos:
            'MOUSE' está suficientemente afastado ad borda do D->mapa
            Representando 'MOUSE' como 'M' e a casa para onde ele quer se mover como 'x', é feito um teste para reconhecer o seguinte padrão:

                1 x 2
                1 m 2
                # # #

                Se as 2 casas marcadas como '1' forem salas do labirinto, ou as 2 casas marcadas como '2' forem salas do labirinto, 'MOUSE' não se move, e o contador 'k' decresce 1 unidade;
                Além disso, o teste é feito apenas para a direção em que 'MOUSE' está apontado.
            
        4. Se MOUSE puder se mover, ele se move uma casa na direção selecionada;

        5. A casa de D->map[][] onde 'MOUSE' se encontra é incrementada em 1;
            (assim as casas por onde 'MOUSE' se mover ficam marcadas como >0)

        NOTA:
        ADIÇÃO ESPECIAL AO PROGRAMA:

            Se o teste 3. permitir a 'MOUSE' que ele se mova, acontece o seguinte:
                1. Além de 4. e 5. se realizarem uma vez, o programa entra em um loop, em que há uma chance de 'MOUSE' continuar se movendo na direção selecionada.
                2. A cada vez que o loop é executado, p teste 3. é realizado novamente, assim como o um teste que confere ao loop uma chance de se encerrar.
                3. Se qualquer um desses testes retornar 'FALSE', ou '0', o loop se encerra imediatamente;
                4. Mas se qualquer um deles retornar TRUE, os passos 4. e 5. são realizados novamente, até que o loop se encerre.
                
                Obs. A chance de o loop encerrar é determinada por K, o "coeficiente de comprimento de corredor", de modo que quanto maior K, maior será o corredor, sendo K>0
                Deste modo, se K=1, o loop nunca se inicia, e o movimento de MOUSE é sorteado novamente.
                Assim, se K=2, o loop tem 50% de chance de se encerrar por execução, se K=3, a chance cai pra 33%, se K=4, a chance é de 25%, e assim sucessivamente.
                Vale ressaltar que K é uma variável de desenvolvedor, e não é enquanto o programa está rodando.

    SEGUE O ALGORITMO BASE DA FUNCAO:

        inicia MOUSE em D->map[5][6];

        Realiza (MODE) vezes:
        {
            sorteia uma direção pra MOUSE ir;
            se MOUSE não está indo de encontro a um possivel corredor paralelo, então:
            {
                MOUSE se move uma casa nessa direção;
                a casa de D->map[][] onde MOUSE está é incrementada em 1;

                ENQUANTO o caminho para onde MOUSE está destinado a ir ainda livre, então:
                {
                    se (rand()%K == 0), então esse loop se encerra imediatamente;
                    MOUSE se move mais uma casa nessa direção;
                    a casa de D->map[][] onde MOUSE está é incrementada em 1;
                }
            }
        }

    FIM DA DOCUMENTACAO DA FUNÇÃO "geradorDeDungeon";

*/

int geradorDeDungeon(dung *D, int MODE){

    int i, j, k;                //A variável MODE está relacionada ao tamanho da Dungeon
                                //de modo que MODE indica quantas vezes MOUSE mudará de direção
    //int K=1;
        //Testes indicam que K=1 cria uma Dungeon mais caótica e bagunçada,
        //enquanto valores maiores criam uma Dungeon com corredores longos e fáceis de lembrar

    i= rand() % (D->MATRIXMAX - 2) + 1;        //1.
    j= rand() % (D->MATRIXMAX - 2) + 1;

    MatInit(D, 0);

    for(k=0; k<MODE; ){
        //a maior parte do código relaciona-se à verificações feitas pelo MOUSE, para garantir;
        //que está seguindo direções válidas de geração;
        switch (rand()%4){      //2.
        case 0:
            if(i<(D->MATRIXMAX-2) && !( (D->map[i+1][j+1] && D->map[i][j+1]) || (D->map[i+1][j-1] && D->map[i][j-1]) )){   //3.
                i++;                //4.
                if(D->map[i][j] == 0) k++;
                D->map[i][j]++;        //5.
            }
            break;
        case 1:
            if(i>1 && !( (D->map[i-1][j+1] && D->map[i][j+1]) || (D->map[i-1][j-1] && D->map[i][j-1]) )){   //3.
                i--;                //4.
                if(D->map[i][j] == 0) k++;
                D->map[i][j]++;        //5.
            }
            break;
        case 2:
            if(j<(D->MATRIXMAX-2) && !( (D->map[i+1][j] && D->map[i+1][j+1]) || (D->map[i-1][j] && D->map[i-1][j+1]) )){   //3.
                j++;                //4.
                if(D->map[i][j] == 0) k++;
                D->map[i][j]++;        //5.

            }
            break;
        case 3:
            if(j>1 && !( (D->map[i+1][j] && D->map[i+1][j-1]) || (D->map[i-1][j] && D->map[i-1][j-1]) )){   //3.
                j--;                //4.
                if(D->map[i][j] == 0) k++;
                D->map[i][j]++;        //5.

            }
            break;
        }
    }

    return 0;

}

void room_generator(dung *D){    //atribui valor às salas;
    int i, j, dir, diffmod, differ;

    dir = rand() % 4;   //define a direção a partir da qual as salas serão geradas;
    D->keyroom[0] = -1;
    D->keyroom[1] = -1;
    D->spawn[0] = -1;
    D->spawn[1] = -1;


    //esse primeiro switch define qual será o D->keyroom, a sala onde o item-chave que o jogador busca será colocado;
    switch(dir){
        case 0: //sup. esquerdo;
            for(i = 0; i < D->MATRIXMAX-1; i++){
                for(j = 0; j < D->MATRIXMAX-1; j++){
                    if(D->map[i][j] != 0){
                        D->keyroom[0] = i;
                        D->keyroom[1] = j;
                    }
                }
                if(D->keyroom[0] != -1) break;
            }
            break;

        case 1: //sup. direito;
            for(i = 0; i < D->MATRIXMAX-1; i++){
                for(j = D->MATRIXMAX-2; j > 0; j--){
                    if(D->map[i][j] != 0){
                        D->keyroom[0] = i;
                        D->keyroom[1] = j;
                    }
                }
                if(D->keyroom[0] != -1) break;
            }
            break;
            
        case 2: //inf. direito;
            for(i = D->MATRIXMAX-2; i > 0; i--){
                for(j = D->MATRIXMAX-2; j > 0; j--){
                    if(D->map[i][j] != 0){
                        D->keyroom[0] = i;
                        D->keyroom[1] = j;
                    }
                }
                if(D->keyroom[0] != -1) break;
            }
            break;
            
        case 3: //inf. esquerdo;
            for(i = D->MATRIXMAX-2; i > 0; i--){
                for(j = 0; j < D->MATRIXMAX-1; j++){
                    if(D->map[i][j] != 0){
                        D->keyroom[0] = i;
                        D->keyroom[1] = j;
                    }
                }
                if(D->keyroom[0] != -1) break;
            }
            break;
            
    }

    //esse segundo switch define onde está o D->spawn, a sala onde o jogador começa o jogo;
    switch(dir){
        case 0: //key: sup. esquerdo;
            for(i = D->MATRIXMAX-2; i > 0; i--){
                for(j = D->MATRIXMAX-2; j > 0; j--){
                    if(D->map[i][j] != 0){
                        D->spawn[0] = i;
                        D->spawn[1] = j;
                    }
                }
                if(D->spawn[0] != -1) break;
            }
            break;

        case 1: //key: sup. direito;
            for(i = D->MATRIXMAX-2; i > 0; i--){
                for(j = 0; j < D->MATRIXMAX-1; j++){
                    if(D->map[i][j] != 0){
                        D->spawn[0] = i;
                        D->spawn[1] = j;
                    }
                }
                if(D->spawn[0] != -1) break;
            }
            break;
            
        case 2: //key: inf. direito;
            for(i = 0; i < D->MATRIXMAX-1; i++){
                for(j = 0; j < D->MATRIXMAX-1; j++){
                    if(D->map[i][j] != 0){
                        D->spawn[0] = i;
                        D->spawn[1] = j;
                    }
                }
                if(D->spawn[0] != -1) break;
            }
            break;
            
        case 3: //key: inf. esquerdo;
            for(i = 0; i < D->MATRIXMAX-1; i++){
                for(j = D->MATRIXMAX-2; j > 0; j--){
                    if(D->map[i][j] != 0){
                        D->spawn[0] = i;
                        D->spawn[1] = j;
                    }
                }
                if(D->spawn[0] != -1) break;
            }
            break;
            
    }


    //a partir da key, agora será feita a atribuição de valores à partir da distância de uma dada sala até a key.
    diffmod = D->MATRIXMAX - 2;

    /*
    diffmod = 15;
    differ_MAX = 14 (15 - 1);
    map[i][j]_min = 1 (15 - 14);
    */
    
    //esses loops percorrem o mapa e, usando a posição da chave como referência, conferem níveis de dificuldade baseados em sua distância da chave;
    //o resultado é a formação de zonas em formato de quadrado com centro na chave, da seguinte forma:
    /*
    
                            1 1 1 1 1
                            1 2 2 2 1
                            1 2 ? 2 1
                            1 2 2 2 1
                            1 1 1 1 1
    
    */
    //a matriz de dificuldade base é, em seguida, alterada de maneira aleatória para deixar o jogo mais... engraçado;
    for(i = 1; i < D->MATRIXMAX; i++){
        for(j = 1; j < D->MATRIXMAX; j++){
            if(D->map[i][j] > 0){
                differ = i - D->keyroom[0];
                if(differ < 0) differ *= -1;
                D->map[i][j] = diffmod - differ;
            }
        }
    }
    for(j = 1; j < D->MATRIXMAX; j++){
        for(i = 1; i < D->MATRIXMAX; i++){
            if(D->map[i][j] > 0){
                differ = j - D->keyroom[1];
                if(differ < 0) differ *= -1;
                if(D->map[i][j] > diffmod - differ){
                    D->map[i][j] = diffmod - differ;
                }
            }
        }
    }
    for(i = 1; i < D->MATRIXMAX; i++){
        for(j = 1; j < D->MATRIXMAX; j++){
            if(D->map[i][j] > 0){
                D->map[i][j] += (rand() % 4) - (rand() % 4);
                if(D->map[i][j] == 0) D->map[i][j] += 1;
                if(D->map[i][j] < 0) D->map[i][j] *= -1;
            }
        }
    }
    
    //inicializando as posições adjacentes ao jogador como 1, à chave como 20, e a posição da chave como 1000;
    for(i = -1; i < 2; i++){
        for(j = -1; j < 2; j++){
            if(D->map[D->spawn[0]+i][D->spawn[1]+j] != 0){
                D->map[D->spawn[0]+i][D->spawn[1]+j] = 1;
            }
            if(D->map[D->keyroom[0]+i][D->keyroom[1]+j] != 0 && i != j && i != -j){
                D->map[D->keyroom[0]+i][D->keyroom[1]+j] = 20;
            }
        }
    }
    D->map[D->keyroom[0]][D->keyroom[1]] = 3000;
    D->map[D->spawn[0]][D->spawn[1]] = 1000;
}

int move(int dir, int *pos, dung *D){
    switch(dir){
        case 1: //NORTE;
            if(pos[0] == 0 || D->map[pos[0]-1][pos[1]] == 0) return 1;
            else{
                pos[0]--;
                return 0;
            }
            break;
        case 2: //LESTE;
            if(pos[1] == D->MATRIXMAX-1 || D->map[pos[0]][pos[1]+1] == 0) return 1;
            else{
                pos[1]++;
                return 0;
            }
            break;
        case 3: //SUL;
            if(pos[0] == D->MATRIXMAX-1 || D->map[pos[0]+1][pos[1]] == 0) return 1;
            else{
                pos[0]++;
                return 0;
            }     
            break;   
        case 4: //OESTE;
            if(pos[1] == 0 || D->map[pos[0]][pos[1]-1] == 0) return 1;
            else{
                pos[1]--;
                return 0;
            }     
            break;
        default: return 1;   
    }
}

int roomExits(dung *D, int *pos){
    //saídas simples;
    if(D == NULL) return -1;
    if(D->map[pos[0]][pos[1]] == 0) return 0;

    int out = 1;
    //testando as salas adjacentes à posição;
    if(D->map[pos[0]-1][pos[1]] != 0) out *= 2; //norte;
    if(D->map[pos[0]][pos[1]+1] != 0) out *= 3; //leste;
    if(D->map[pos[0]+1][pos[1]] != 0) out *= 5; //oeste;
    if(D->map[pos[0]][pos[1]-1] != 0) out *= 7; //sul;

    return out;

    /*
    CÓDIGOS DE RETORNO DA FUNÇÃO:
        - -1: erro fatal: dungeon NULA;
        - 0 : erro: posição fechada;
        - 1 : sala isolada;
        out : saídas codificadas usando o produto de valores primos, gerando um inteiro único que mostra a quantidade de saídas da sala e quais são elas;
    */
}

int clearDung(dung *D){
	if(D == NULL) return 2;

	int i;
	for(i = 0; i < D->MATRIXMAX; i++){
		free(D->map[i]);
	}
	free(D->map);
	
	return 0;
	
	/*
    CÓDIGOS DE RETORNO DA FUNÇÃO:
        - 2 : erro fatal: dungeon NULA;
        - 0 : dungeon limpada com sucesso;    
	*/
}
//-----------------------------------------------end DUNGEONFUNC.c------------------------------------------------------------//


//-----------------------------------------------begin rlist.c----------------------------------------------------------------//
rlist *createRL(){    //cria uma lista de salas;
    rlist *rl = (rlist*) calloc(1, sizeof(rlist));
    if(rl != NULL){
        rl->ini = NULL;
    }
    return rl;
}

int addRoom(rlist *rl, room input){    //adiciona uma sala ao início da lista;
    if(rl == NULL) return 2;
    if(testforRoom(rl, input.pos)) return 1;
    
    no *n = (no*) calloc(1, sizeof(no));
    if(n != NULL){
        n->index = input;
        n->next = rl->ini;
        rl->ini = n;

        return 0;
    }
    else return -1;

    /*
    Códigos de retorno da função:
        - 2:    erro fatal: lista NULA;
        - 1:    a sala já existe;
        - -1:   erro: falha ao alocar sala;
        - 0:    operação realizada com sucesso;
    */
}
     
int testforRoom(rlist *rl, int *pos){    //testa se uma sala está na lista;
    if(rl == NULL) return 2;             //usando sua posição como discriminante;
    if(rl->ini == NULL) return 0;

    no *nlist = rl->ini;

    while(nlist != NULL){
        if(pos[0] == nlist->index.pos[0] && pos[1] == nlist->index.pos[1]){
            if(nlist->index.cont < 0) return -1;
            else return 1;
        }
        nlist = nlist->next;
    }

    return 0;

    /*
    Códigos de retorno da função:
        - 2:    erro fatal: lista NULA;
        - 1:    sala já existe e NÃO foi concluída;
        - -1:   sala já existe e foi concluída;
        - 0:    sala não existe;
    */
}
   
int remRoom(rlist *rl){    //remove a primeira sala da lista;
    if(rl == NULL) return 2;
    if(rl->ini == NULL) return 1;

    no *nlist = rl->ini;

    rl->ini = nlist->next;
    free(nlist);
    return 0;

    /*
    Códigos de retorno da função:
        - 2:    erro fatal: lista NULA;
        - 1:    erro: lista vazia;
        - 0:    sala removida com sucesso;
    */
}

room *getRoom(rlist *rl, int *pos, int val){    //retorna um ponteiro para uma sala da lista;
    if(rl == NULL) return NULL;                 //usando a posição como discriminante;
    if(rl->ini == NULL) return NULL;

    no *nlist = rl->ini;

    while(nlist != NULL){
        if(pos[0] == nlist->index.pos[0] && pos[1] == nlist->index.pos[1]){
            if(val != 0){    //se val == 0, o cont da sala não é alterado;
                nlist->index.cont = val;
            }

            room *out = (room*) calloc(1, sizeof(room));

            *out = nlist->index;

            return out;
        }
        nlist = nlist->next;
    }

    return NULL;

    /*
    Códigos de retorno da função:
        - NULL:     alguma falha;
        - out:      a sala desejada é retornada;
    */
}
                 
int clearrlist(rlist *rl){    //apaga todos os itens da lista;
    if(rl == NULL) return 2;
    while(rl->ini != NULL){
        remRoom(rl);
    }
    return 0;

    /*
    Códigos de retorno da função:
        - 2:    erro fatal: lista NULA;
        - 0:    lista esvaziada com sucesso;
    */
}            
//-----------------------------------------------end rlist.c------------------------------------------------------------------//