#ifndef MENULIST_H_INCLUDED
#define MENULIST_H_INCLUDED

typedef struct lista_manual manlist;
typedef struct dungeon dung;
typedef struct sala room;
typedef struct roomlist rlist;
typedef struct PLAYER PLAYER;
typedef struct PLAYER MON;
typedef struct PLAYER TRAP;
typedef struct Enciclopedia enciclopedia;

int Creditos();
int Manual(manlist *man);
int Jogar(dung *D, room *r_io, rlist *rl, PLAYER *p, MON *m, TRAP *t, enciclopedia *E);
int Menu_final(int i,PLAYER *s);

#endif // MENULIST_H_INCLUDED
