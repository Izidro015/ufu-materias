#ifndef DUNGROOMS_H

#define DUNGROOMS_H

//begin structs;
typedef struct dungeon{                 //mapa (ponteiro para ponteiro de int), tamanho da dungeon, e coordenadas do spawn do jogador e da chave;
    int **map;
    int MATRIXMAX;
    int spawn[2];
    int keyroom[2];
} dung;

typedef struct sala{                    //conteúdo, dificuldade, e posição (i,j);
    int cont, dif, pos[2], exits;
} room;

typedef struct node{                    //como a lista será implementada de forma encadeada, usaremos nós para armazenar as informações;
    struct node *next;
    struct sala index;
} no;

typedef struct roomlist{                //a lista de salas em si;
    struct node *ini;
} rlist;
//end structs;


//begin DUNGEON.h;
dung *createDungeon(int MATRIXMAX);             //cria uma dungeon;
void MatInit(dung *D, int val);                 //inicializa uma matriz quadrada com o valor val;
int geradorDeDungeon(dung *D, int MODE);        //função responsável por gerar corredores na matriz;
void printar_matriz(dung *D);                   //função de desenvolvedor para imprimir o mapa completo da dungeon;
void printar_matriz2(dung *D, int *pos);        //printa a matriz com a posição do player rastreada;
void room_generator(dung *D);                   //função que preenche as salas com valores aleatórios;
int move(int dir, int *pos, dung *D);           //move uma entidade pela dungeon;
int roomExits(dung *D, int *pos);               //recebe uma posição na dungeon e retorna as saídas possíveis, codificadas como um inteiro;
int clearDung(dung *D);							//desaloca a dungeon;
//end DUNGEON.h;


//begin rooms.h;
rlist *createRL();                          //cria uma lista de salas;
int addRoom(rlist *rl, room input);         //adiciona uma sala ao início da lista;
int testforRoom(rlist *rl, int *pos);       //checa se uma dada sala está na lista, usando sua posição como discriminante;
int remRoom(rlist *rl);                     //remove uma sala do início da lista, basicamente usada somente pela clearrlist();
room *getRoom(rlist *rl, int *pos, int val);//recupera uma sala já existente da lista. É possível alterar o valor de seu cont através do int val;
int clearrlist(rlist *rl);                  //remove todas as salas da lista;
//end rooms.h;

#endif