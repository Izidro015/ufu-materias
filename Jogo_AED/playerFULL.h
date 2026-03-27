
#ifndef PLAYER_FULL
#define PLAYER_FULL

typedef struct PLAYER TRAP;
typedef struct PLAYER MON;
typedef struct PLAYER PLAYER;

typedef struct dungeon dung;
typedef struct sala room;


struct lista{

    int total;
    int itens[12];
};
typedef struct lista lista;


struct PLAYER{

    char nome[30];

    int SCORE;

    int vida_max;
    int vida;
    int pos[2];
    int mao_principal, mao_secundaria, vestes;

    int atk, def, agi;

    lista *inventario;
};
typedef struct PLAYER PLAYER;




struct Item{

    int pos;
    char nome[21];
    int atk, def, agi;

};
typedef struct Item item;

struct No_item{

    item I;
    struct No_item *prox;
    
};
typedef struct No_item no_item;

struct Enciclopedia{

    no_item *inicio;
    no_item *fim;

    int tamanho;
};
typedef struct Enciclopedia enciclopedia;






int treta(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D);

int embate(PLAYER *p, MON *m);
int fuga(PLAYER *p, MON *m);
void printar_resultado_embate(int MODE, MON *m);
void printar_resultado_fuga(int MODE, MON *m);







/*

    acoes.c:

*/



int usar_item(PLAYER *p, MON *m, int pos, enciclopedia *E, room *r, dung *D);
int usar_scroll(PLAYER *p, MON *m, int pos, enciclopedia *E, room *r, dung *D);



int SCROLL_maldicao(MON *m, room *r);
int SCROLL_lentidao(MON *m, room *r);
int SCROLL_mal_agouro(PLAYER *p, MON *m, room *r);
int SCROLL_hemomancia(PLAYER *p, MON *m, room *r);
int SCROLL_necromancia(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D);
int SCROLL_encantar(PLAYER *p, enciclopedia *E);


int Comida_Preservada(PLAYER *p);
int Pocao_de_Cura(PLAYER *p);
int Elixir_Filosofal(PLAYER *p);

int Essencia_de_Grifo(PLAYER *p);
int Essencia_da_Vida(PLAYER *p);
int Essencia_de_Dragao(PLAYER *p);
int Essencia_de_Tita(PLAYER *p);

int Granada(MON *M);
int Bomba_de_Trovao(MON *M, PLAYER *p);

int Varinha_de_Condao(room *r, MON *m, PLAYER *p, enciclopedia *E);







int Controle_remoto(PLAYER *p, enciclopedia *E);

int Cajado_arcano(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D);
int mapa(dung *D);
int Bola_de_Cristal(room *r, dung *D, PLAYER *p);
int Bussola_Magica(dung *D, PLAYER *p);






int d(int n);
int XdY(int X, int Y);






enciclopedia *iniciar_enciclopedia();
int preencher_com(int pos, char nome[20], int atk, int def, int agi, enciclopedia *E);
int remItem(enciclopedia *E);				//remove um item da enciclopédia;
int clearItemEnc(enciclopedia *E);			//limpa a enciclopédia de itens;
int printar_nome_do_item(int pos, enciclopedia *E);

item *consultar_item(int pos, enciclopedia *E);
item *gacha(enciclopedia *E);





MON *createMon(int monID);                 //cria um monstro, um tipo especial de PLAYER, a partir de uma monID;
int adjustHP(PLAYER *p, int adj);           //muda a vida de um jogador ou monstro, retornando se este está morto, se preciso;
void monsterList(int monID, MON *m);        //armazena dados sobre mais de 2 bilhões monstros (teoricamente);
TRAP *createTrap(int trapID);               //cria uma trap, um tipo especial de PLAYER, a partir de uma monID;
int mardilha(PLAYER *p, TRAP *t, enciclopedia *E, room *r, dung *D);           //a função que gerencia armadilhas;
int actPass(PLAYER *p, TRAP *t);            //tentar passar pela armadilha, arriscando dano;
void trapList(int trapID, TRAP *t);         //armazena dados sobre mais de 2 bilhões de armadilhas (teoricamente);




lista *criar_inventario();

PLAYER *criar_player(int classe, int *spawn, enciclopedia *E);
void abrir_inventario(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D);
void mostrar_inventario(PLAYER *p, enciclopedia *E);
int removerPosicao (lista *l, int pos);
int clearPlayer(PLAYER *p);			//limpa o player;

int adicionar_item(lista *l, int item, enciclopedia *E);
int remover_item(lista *l, int item);

int adicionar_equipamento(PLAYER *p, int pos, enciclopedia *E);
int remover_equipamento(PLAYER *p, int pos, enciclopedia *E);

int escolher_item_para_usar(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D, int *signal);


#endif