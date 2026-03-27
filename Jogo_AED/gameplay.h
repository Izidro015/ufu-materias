#ifndef GAMEPLAY_H
#define GAMEPLAY_H

typedef struct lista_manual manlist;
typedef struct dungeon dung;
typedef struct sala room;
typedef struct roomlist rlist;
typedef struct PLAYER PLAYER;
typedef struct PLAYER MON;
typedef struct PLAYER TRAP;
typedef struct Enciclopedia enciclopedia;

int enterRoom(rlist *rl, room *r, PLAYER *p, MON *m, TRAP *t, enciclopedia *E, dung *D);    //função que gerencia o comportamento do jogo quando o player entra em uma sala;
void playerMovHandler(room *r, PLAYER *p, MON *m, dung *D, enciclopedia *E);                        //cuida da movimentação do player;
void describeRoom(room *r);

int boss(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D);


int BLOB(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D);
int TREX(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D);
int IMITADOR(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D);
int GHODIRAH(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D);
int AGOR(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D);

#endif