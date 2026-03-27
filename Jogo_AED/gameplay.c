#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "playerFULL.h"
#include "manual.h"
#include "dungrooms.h"
#include "Menulist.h"
#include "gameplay.h"


int enterRoom(rlist *rl, room *r, PLAYER *p, MON *m, TRAP *t, enciclopedia *E, dung *D){
    /*
    0, 1, 2 = combate;
    3, 4, 5 = armadilha;
    6, 7, 8 = item;
          9 = lore/sala vazia;
    */

    int rem = r->cont % 10, encounterres;
    item *X;

    int MODE, continua=1;


    describeRoom(r);

    //chave e spawn;
    if(r->dif == 1000 || r->dif == 3000){
        playerMovHandler(r, p, NULL, D, E);
        return 0;
    }

    //bossssssssss;
    if(r->dif == 20){
        m = createMon(r->cont);
        encounterres = boss(r, p, m, E, D);
        switch(encounterres){
            case -1:
                //game over;
		free(m);
                return -1;
            break;

            case 0:
		p->SCORE += m->SCORE;
                getRoom(rl, p->pos, -4);    //sala setada para -1 para mostrar que houve um combate e foi concluído;
            break;

            case 1:
		p->SCORE += m->SCORE;
                getRoom(rl, p->pos, -4);    //sala setada para -1 para mostrar que houve um combate e foi concluído;
            break;
        }
		free(m);
    }
    
    if(r->cont < 0){ //sala vazia;
        playerMovHandler(r, p, NULL, D, E);
        return 0;
    }


    if(rem < 3){
        //combate;
        m = createMon(r->cont);
        encounterres = treta(p, m, E, r, D);
        switch(encounterres){
            case -1:
                //game over;
				free(m);
                return -1;
            break;

            case 0:
                //Obrigado a mover para outra sala;
				p->SCORE += m->SCORE/6;
                playerMovHandler(r, p, NULL, D, E);
				return 0;
            break;

            case 1:
                //fica na mesma sala;
				p->SCORE += m->SCORE;
                getRoom(rl, p->pos, -1);    //sala setada para -1 para mostrar que houve um combate e foi concluído;
            break;
        }
		free(m);
    }
    else if(rem < 6){
        //armadilha;
        t = createTrap(r->cont);
        encounterres = mardilha(p, t, E, r, D);
        if(encounterres == -1){
			free(t);
            return -1;
        }
        else{
			p->SCORE += t->SCORE;
            getRoom(rl, p->pos, -2);   //sala setada para -2 para mostrar que houve uma armadilha e foi concluída;
        }
		free(t);
    }
    else if(rem < 10){
        //item;
        X = gacha(E);
        printf("                                         ||Em um canto da sala voce ve um pequeno bau.                             ||\n");
        printf("                                         ||Dentro dele ha %s                                      ||\n", X->nome);
        printf("                                         ||Digite 1 para pegar %s                                 ||\n", X->nome);
        printf("                                         ||Digite outro numero para deixar o bau                                   ||\n");
        printf("                                         ============================================================================\n");
        printf("                                         >> ");
        scanf("%d",&MODE);

        if(MODE == 1){
            if(p->inventario->total >= 12){
                while(continua){
                    printf("                                         ============================================================================\n");
                    printf("                                         ||Inventario cheio!                                                       ||\n");
                    printf("                                         ||Deseja Descartar um item para saquear o bau. (1 para confirmar)         ||\n");
                    printf("                                         ============================================================================\n");
                    printf(">>");
                    scanf("%d",&MODE);
                    if(MODE == 1){
                        abrir_inventario(p, m, E, r, D);
                        system("cls");
                        if(p->inventario->total < 12){
                            adicionar_item(p->inventario, X->pos, E);
                            printf("                                         ============================================================================\n");
                            printf("                                         ||%s adicionado ao inventario!                           ||\n", X->nome);
                            continua = 0;
                        
                        }
                        else continua=0;
                    }
                }
            }
            else{
                if(adicionar_item(p->inventario, X->pos, E) != 0){
                printf("                                         ============================================================================\n");
                printf("                                         ||%s adicionado ao inventario!                           ||\n", X->nome);
                }
            }
        }
        printf("                                         ============================================================================\n");
        printf("                                         ||Voce fecha o bau, para nunca mais ser aberto...                         ||\n");

        getRoom(rl, p->pos, -3);    //sala setada para -3 para mostrar que houve item e foi concluída;
    }
    else{
        //lore/sala vazia;
        }
    playerMovHandler(r, p, NULL, D, E);

    return 0;
}

void describeRoom(room *r){
    printf("                                         ============================================================================\n");
    printf("                                         ||Voce entra em uma sala...                                               ||\n");
    if(r->cont < 0){
        switch(r->cont){
            case -1:    //combate concluído;
                printf("                                         ||Odores de suor e sangue ainda permeam o chao manchado...                ||\n");
            break;

            case -2:    //armadilha concluída;
                printf("                                         ||O mecanismo de uma armadilha desativada ainda faz barulhos...           ||\n");
            break;

            case -3:    //item concluído;
                printf("                                         ||O bau que te alegrou ha algum tempo agora so acumula poeira...          ||\n");
            break;

            case -4:    //boss concluído;
                printf("                                         ||Voce ainda se sente observado...                                        ||\n");
            break;
        }
        

        return;
    }
    switch(r->dif){
        case 1000:
            printf("                                         ||Voce se encontra proximo a entrada do calabouco.                        ||\n");
        break;

        case 1:
            printf("                                         ||Musgos e terra se acumulam nos sulcos entre os tijolos de pedra.        ||\n");
        break;

        case 2:
            printf("                                         ||Pingos de agua ecoam pelos corredores.                                  ||\n");
        break;

        case 3:
            printf("                                         ||Um vento misterioso sopra pelos seus cabelos.                           ||\n");
        break;

        case 4:
            printf("                                         ||Os pedregulhos no chao estao rachados.                                  ||\n");
        break;
        
        case 5:
            printf("                                         ||Raizes e plantas estranhas atravessam o teto.                           ||\n");
        break;

        case 6:
            printf("                                         ||O ar esta parado e frio.                                                ||\n");
        break;

        case 7:
            printf("                                         ||Voce sente um odor distante de carnica.                                 ||\n");
        break;

        case 8:
            printf("                                         ||O aspecto das paredes lembra um castelo abandonado.                     ||\n");
        break;

        case 9:
            printf("                                         ||Silencio perdura, permitindo que voce ouca os batimentos de seu coracao.||\n");
        break;

        case 10:
            printf("                                         ||Voce percebe o quao fundo voce esta...                                  ||\n");
        break;

        case 11:
            printf("                                         ||Voce ouve suspiros em suas orelhas, sem fonte perceptivel...            ||\n");
        break;

        case 12:
            printf("                                         ||Voce sente o peso do mundo sobre voce...                                ||\n");
        break;

        case 13:
            printf("                                         ||Risadas esnobantes reverberam pelas paredes...                          ||\n");
        break;

        case 14:
            printf("                                         ||As paredes tem um aspecto similar a obsidiana...                        ||\n");
        break;

        case 15:
            printf("                                         ||Voce se sente observado por algo maligno...                             ||\n");
        break;

        case 16:
            printf("                                         ||Os mortos e os vivos se mesclam em sua visao...                         ||\n");
        break;

        case 17:
            printf("                                         ||Voce se sente como um prisioneiro em direcao a forca...                 ||\n");
        break;
        
        case 18:
            printf("                                         ||Entre as frestas das portas e paredes, o Caos danca por tras.           ||\n");
        break;

        case 19:
            printf("                                         ||Ja nao ha luz em seu torno. Ate sua tocha se apagou...                  ||\n");
        break;

        case 20:
            printf("                                         ||Uma presenca vil se materializa ao seu redor...                         ||\n");
        break;

        case 3000:
            printf("                                         ||Sua alma esta, estranhamente, serena...                                 ||\n");
        break;
    }
}

void playerMovHandler(room *r, PLAYER *p, MON *m, dung *D, enciclopedia *E){
    printf("                                         ||Existem saidas nas seguintes direcoes:                                  ||\n");
    printf("                                         ============================================================================\n");
    printf("\n\n\n\n");
    if(((r->cont < 0) || (r->dif == 1000) || (r->dif == 3000 ) || (r->cont % 10 == 9)) && (r->exits % 2 == 0) ){
	    printf("                                                                              _____  _____\n");
        printf("                                                                             ||   ||||   ||\n");
        printf("                                                                             || W |||| E ||\n");
        printf("                                                                             ||___||||___||\n");
        printf("                                                                             |/___\\||/___\\|\n");
    }
    else 
        if((r->cont < 0 || r->dif == 1000 || r->dif == 3000 || r->cont % 10 == 9) && (r->exits % 2 != 0)  ){
            printf("                                                                                     _____\n");
            printf("                                                                                    ||   ||\n");
            printf("                                                                                    || E ||\n");
            printf("                                                                                    ||___||\n");
            printf("                                                                                    |/___\\|\n");
        }
    if((r->exits % 2 == 0) && ((r->cont > 0) && (r->dif != 1000) && (r->dif != 3000) && (r->cont % 10 != 9)) ){
        printf("                                                                              _____\n");
        printf("                                                                             ||   ||\n");
        printf("                                                                             || W ||\n");
        printf("                                                                             ||___||\n");
        printf("                                                                             |/___\\|\n");
    }
    if(r->exits % 3 == 0 && r->exits % 5 != 0 && r->exits % 7 != 0 ) {
        printf("                                                                                     _____\n");
        printf("                                                                                    ||   ||\n");
        printf("                                                                                    || D ||\n");
        printf("                                                                                    ||___||\n");
        printf("                                                                                    |/___\\|\n");
    }
    if(r->exits % 3 != 0 && r->exits % 5 == 0 && r->exits % 7 != 0){
        printf("                                                                              _____\n");
        printf("                                                                             ||   ||\n");
        printf("                                                                             || S ||\n");
        printf("                                                                             ||___||\n");
        printf("                                                                             |/___\\|\n");
    } 
    if(r->exits % 3 != 0 && r->exits % 5 != 0 && r->exits % 7 == 0){
        printf("                                                                       _____\n");
        printf("                                                                      ||   ||\n");
        printf("                                                                      || A ||\n");
        printf("                                                                      ||___||\n");
        printf("                                                                      |/___\\|\n");        
    }
    if(r->exits % 3 == 0 && r->exits % 5 == 0 && r->exits % 7 == 0){
        printf("                                                                       _____  _____  _____\n");
        printf("                                                                      ||   ||||   ||||   ||\n");
        printf("                                                                      || A |||| S |||| D ||\n");
        printf("                                                                      ||___||||___||||___||\n");
        printf("                                                                      |/___\\||/___\\||/___\\|\n");
    }
    if(r->exits % 3 == 0 && r->exits % 5 != 0 && r->exits % 7 == 0){
        printf("                                                                       _____         _____\n");
        printf("                                                                      ||   ||       ||   ||\n");
        printf("                                                                      || A ||       || D ||\n");
        printf("                                                                      ||___||       ||___||\n");
        printf("                                                                      |/___\\|       |/___\\|\n");
    }
    if(r->exits % 3 == 0 && r->exits % 5 == 0 && r->exits % 7 != 0){
        printf("                                                                              _____  _____\n");
        printf("                                                                             ||   ||||   ||\n");
        printf("                                                                             || S |||| D ||\n");
        printf("                                                                             ||___||||___||\n");
        printf("                                                                             |/___\\||/___\\|\n");
    }
    if(r->exits % 3 != 0 && r->exits % 5 == 0 && r->exits % 7 == 0){
        printf("                                                                       _____  _____\n");
        printf("                                                                      ||   ||||   ||\n");
        printf("                                                                      || A |||| S ||\n");
        printf("                                                                      ||___||||___||\n");
        printf("                                                                      |/___\\||/___\\|\n");
    }

    char dir;
    while(1){
        dir = getch();
        switch(dir){
			case 'E':
			case 'e':
				if(r->cont < 0 || r->dif == 1000 || r->dif == 3000 || r->cont % 10 == 9){
					abrir_inventario(p, m, E, r, D);
					return;
				}
				else printf("Comando invalido.\n");
			break;
			case 'W':
            case 'w':
                dir = 1;
            break;
			case 'D':
            case 'd':
                dir = 2;
            break;
			case 'S':
            case 's':
                dir = 3;
            break;
			case 'A':
            case 'a':
                dir = 4;
            break;
        }
        if(move(dir, p->pos, D) == 0) break;
        printf("Comando invalido.\n");
    }
}

int boss(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D){

    switch (r->cont){
        
        case 200:
        case 201:
            return GHODIRAH(r, p, m, E, D);
        case 202:
        case 203:
            return IMITADOR(r, p, m, E, D);
        case 204:
        case 205:
            return AGOR(r, p, m, E, D);
        case 206:
        case 207:
            return TREX(r, p, m, E, D);
        case 208:
        case 209:
            return BLOB(r, p, m, E, D);
        break;


        default:
            return 0;

    }

}



















int BLOB(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D){
    int MODE,i,j,x;
    int signal1 = 0, signal2 = 0;

    printf("                                         ||   B.L.O.B. - Bacia de residuos limaticos oninucleares bioconscientes   ||\n");
    printf("                                         ============================================================================\n\n");

    while(1){

        if(p->vida == 0) return -1;
        if(m->vida == 0) return 1;

        printf("                                         ============================================================================\n");
        printf("                                         || %s(%d/%d) vs %s", p->nome, p->vida, p->vida_max, m->nome);// /t == 8x" "
        i = strlen(m->nome);
        j = strlen(p->nome);
        x = j+i;
        while(1){
            if(x==58){
                printf("  ||\n");
                break;
            }
            else{
                printf(" ");
                ++x;
            }
        }
        printf("                                         ||------------------------------------------------------------------------||\n");
        printf("                                         || Atributos do Player                                                    ||\n");
        printf("                                         ||                                                                        ||\n");
        printf("                                         ||  ATK:%d",p->atk);
        if(p->atk>9||p->atk<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||  DEF:%d",p->def);
        if(p->def>9||p->def<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||  AGI:%d",p->agi);
        if(p->agi>9||p->agi<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||                                                                        ||\n");
        printf("                                         ||1. Atacar.                                                              ||\n");
        printf("                                         ||2. Item.                                                                ||\n");
        printf("                                         ============================================================================\n");
        printf("                                         >>");
		setbuf(stdin, NULL);
        scanf("%d", &MODE);

        switch (MODE){

            case 1:
                printf("                                         ============================================================================\n");
                MODE = embate (p, m);
                printar_resultado_embate(MODE, m);
                break;
            
            case 2:
                printf("                                         ============================================================================\n");
                escolher_item_para_usar(p, m, E, r, D, &signal2);
                break;

            default:
                printf("                                         ============================================================================\n");
                printf("                                         ||                            Comando invalido.                           ||\n");
                printf("                                         ============================================================================\n");
                break;
        }
            
        /*
        ACOES ESPECIAIS DE BLOB:
        
            1. Se a vida é zerada pela primeira vez, BLOB renasce com outros modificadores
            2. Durante a segunda forma de BLOB, se o Player usar um item, Blob reduzirá o atk do Player em 1 por 1 turno;
        */
        if(signal1 == 0 && m->vida<=0){
            system ("cls");
                //m->SCORE = 2000;
            m->vida = 4;
            m->vida_max = 4;
                //m->pos[0] = 0;
                //m->pos[1] = 0;
            m->mao_principal = 4;
            m->mao_secundaria = 6;
                //m->vestes = 0;
            m->atk = 4;
                //m->def = 0;
                //m->agi = 0;

            signal1 = 1;

            printf("                                         ============================================================================\n");
            printf("                                         ||                       B.L.O.B. nao eh capaz de morrer...               ||\n");
            printf("                                         ============================================================================\n\n\n\n");
        }

        if(signal1 == -1 && signal2 == 0){
            p->atk++;
            signal1 = 1;
        }
        if(signal1 == 1 && signal2 != 0){
            p->atk--;
            signal1 = -1;
        }

        signal2 = 0;
    }

}


int TREX(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D){
    int MODE,i,j,x;
    int signal1 = 0;
	TRAP* t;


	printf("                                         ||                       T-REX - O mestres dos portais                    ||\n");
    printf("                                         ============================================================================\n\n");

    while(1){

        if(p->vida == 0) return -1;
        if(m->vida == 0) return 1;

        printf("                                         ============================================================================\n");
        printf("                                         || %s(%d/%d) vs %s", p->nome, p->vida, p->vida_max, m->nome);// /t == 8x" "
        i = strlen(m->nome);
        j = strlen(p->nome);
        x = j+i;
        while(1){
            if(x==58){
                printf("  ||\n");
                break;
            }
            else{
                printf(" ");
                ++x;
            }
        }
        printf("                                         ||------------------------------------------------------------------------||\n");
        printf("                                         || Atributos do Player                                                    ||\n");
        printf("                                         ||                                                                        ||\n");
        printf("                                         ||  ATK:%d",p->atk);
        if(p->atk>9||p->atk<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||  DEF:%d",p->def);
        if(p->def>9||p->def<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||  AGI:%d",p->agi);
        if(p->agi>9||p->agi<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||                                                                        ||\n");
        printf("                                         ||1. Atacar.                                                              ||\n");
        printf("                                         ||2. Item.                                                                ||\n");
        printf("                                         ============================================================================\n");
        printf("                                         >>");
		setbuf(stdin, NULL);
        scanf("%d", &MODE);

        switch (MODE){

            case 1:
                printf("                                         ============================================================================\n");
                MODE = embate (p, m);
                printar_resultado_embate(MODE, m);
                break;
            
            case 2:
                printf("                                         ============================================================================\n");
                escolher_item_para_usar(p, m, E, r, D, NULL);
                break;

            default:
                printf("                                         ============================================================================\n");
                printf("                                         ||                            Comando invalido.                           ||\n");
                printf("                                         ============================================================================\n");
                break;
        }
		/*
		Acoes Especias do TREX
		1- Quando o T-REX perde metade da vida ele Começa a Lançar Sua Magia de Portal.
		2- Quando o T-REX morre ele lança a sua magia final.
		*/
		
		if(signal1==0 && m->vida==3 ){
			system("cls");
	        printf("                                         ============================================================================\n");
            printf("                                         ||                      T-Rex Comeca a lancar seus feiticos               ||\n");
            printf("                                         ============================================================================\n\n\n\n");  
			m->mao_principal = 2;
			m->mao_secundaria = 4;
			signal1 = 1;
		}
		if(m->vida==0){
			printf("                                         ============================================================================\n");
			printf("                                         ||             Antes de sua morte T-Rex tenta te levar junto              ||\n");
			printf("                                         ============================================================================\n\n\n\n");
			
			t = createTrap(195);
			while(1){
				if(p->vida <= 0) return -1;
				if(t->vida <= 0) break;
				printf("                                         ============================================================================\n");

				printf("                                         || %s(%d/%d)vs %s", p->nome, p->vida, p->vida_max, t->nome);
				i = strlen(t->nome);
				j = strlen(p->nome);
				x = j+i;
				while(1){
					if(x==60){
						printf(" ||\n");
						break;
					}
					else{
						printf(" ");
						++x;
					}
				}
				printf("                                         ||------------------------------------------------------------------------||\n");
				printf("                                         || Atributos do Player                                                    ||\n");
				printf("                                         ||                                                                        ||\n");
				printf("                                         ||  ATK:%d",p->atk);
				if(p->atk>9||p->atk<0){
					printf("                                                                ||\n");
				}
				else{
					printf("                                                                 ||\n");
				}
				printf("                                         ||  DEF:%d",p->def);
				if(p->def>9||p->def<0){
					printf("                                                                ||\n");
				}
				else{
					printf("                                                                 ||\n");
				}
				printf("                                         ||  AGI:%d",p->agi);
				if(p->agi>9||p->agi<0){
					printf("                                                                ||\n");
				}
				else{
					printf("                                                                 ||\n");
				}
				printf("                                         ||                                                                        ||\n");
				printf("                                         ||1. Passar.                                                              ||\n");
				printf("                                         ||2. Item.                                                                ||\n");
				printf("                                         ============================================================================\n");
				printf("                                         >>");
				setbuf(stdin, NULL);
				scanf("%d", &MODE);
				switch(MODE){
					
					case 1:
						switch(actPass(p, t)){

							case 3:
								printf("                                         ============================================================================\n");
								printf("                                         ||                         Voce esquiva da sua morte                      ||\n");
							break;

							case -3:
								printf("                                         ============================================================================\n");
								printf("                                         ||                         o portal te leva ate o Abismo                  ||\n");
							break;

							case 2:
								printf("                                         ============================================================================\n");
								printf("                                         ||                         Voce esquiva da sua morte                      ||\n");
							break;

							case -2:
								printf("                                         ============================================================================\n");
								printf("                                         ||                         o portal te leva ate o Abismo                  ||\n");
							break;
						}
					break;

					case 2:
						escolher_item_para_usar(p, NULL, E, r, D, NULL);
					break;

					default:
						printf("                                         ============================================================================\n");
						printf("                                         ||                            Comando invalido.                           ||\n");
					break;
				}
				printf("                                         ============================================================================\n");
				printf("\n\n");
			}
			free(t);
		}
	
		if(m->vida<=3 && m->vida>0){
			t = createTrap(183);
			printf("                                         ============================================================================\n");
			printf("                                         ||                    Um portal consome a boca do T-Rex                   ||\n");
			printf("                                         ============================================================================\n\n\n\n");
			
			while(1){
				if(p->vida <= 0) return -1;
				if(t->vida <= 0) break;
				printf("                                         ============================================================================\n");

				printf("                                         || %s(%d/%d)vs %s", p->nome, p->vida, p->vida_max, t->nome);
				i = strlen(t->nome);
				j = strlen(p->nome);
				x = j+i;
				while(1){
					if(x==60){
						printf(" ||\n");
						break;
					}
					else{
						printf(" ");
						++x;
					}
				}
				printf("                                         ||------------------------------------------------------------------------||\n");
				printf("                                         || Atributos do Player                                                    ||\n");
				printf("                                         ||                                                                        ||\n");
				printf("                                         ||  ATK:%d",p->atk);
				if(p->atk>9||p->atk<0){
					printf("                                                                ||\n");
				}
				else{
					printf("                                                                 ||\n");
				}
				printf("                                         ||  DEF:%d",p->def);
				if(p->def>9||p->def<0){
					printf("                                                                ||\n");
				}
				else{
					printf("                                                                 ||\n");
				}
				printf("                                         ||  AGI:%d",p->agi);
				if(p->agi>9||p->agi<0){
					printf("                                                                ||\n");
				}
				else{
					printf("                                                                 ||\n");
				}
				printf("                                         ||                                                                        ||\n");
				printf("                                         ||1. Passar.                                                              ||\n");
				printf("                                         ||2. Item.                                                                ||\n");
				printf("                                         ============================================================================\n");
				printf("                                         >>");
				setbuf(stdin, NULL);
				scanf("%d", &MODE);
				switch(MODE){
					
					case 1:
						switch(actPass(p, t)){

							case 3:
								printf("                                         ============================================================================\n");
								printf("                                         ||                       Voce esquiva da boca do T-Rex                    ||\n");
							break;

							case -3:
								printf("                                         ============================================================================\n");
								printf("                                         ||                   A boca do T-Rex te acerta de raspao                  ||\n");
							break;

							case 2:
								printf("                                         ============================================================================\n");
								printf("                                         ||                         Voce Esquiva com facilidade                    ||\n");
							break;

							case -2:
								printf("                                         ============================================================================\n");
								printf("                                         ||               A boca do T-Rex te acerta de maneira inusitada           ||\n");
							break;
						}
					break;

					case 2:
						escolher_item_para_usar(p, NULL, E, r, D, NULL);
					break;

					default:
						printf("                                         ============================================================================\n");
						printf("                                         ||                            Comando invalido.                           ||\n");
					break;
				}
				printf("                                         ============================================================================\n");
				printf("\n\n");
			}
			free(t);
		}
	}
}

int IMITADOR(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D){
    int MODE,i,j,x;
    int signal1 = 0, signal2 = 0;

    printf("                                         ||   Voce se depara diante de um velho espelho cristalino...              ||\n");
	printf("                                         ||                                                                        ||\n");
	printf("                                         ||            Ha uma visao dentro dele. Seu reflexo, tornado sombrio...   ||\n");
	printf("                                         ||                                                                        ||\n");
	printf("                                         ||   Voce pisca... e ele toma um passo...                                 ||\n");
	printf("                                         ||                                                                        ||\n");
	printf("                                         ||                                               . . .                    ||\n");
	printf("                                         ||                                                                        ||\n");
	printf("                                         ||   \"Antes de conquistar a chave, deve, primeiro, conquistar... a si!\"   ||\n");
    printf("                                         ============================================================================\n\n");
	
	m->atk = p->atk;
	m->agi = p->agi;
	
    while(1){

        if(p->vida == 0) return -1;
        if(m->vida == 0) return 1;

        printf("                                         ============================================================================\n");
        printf("                                         || %s(%d/%d) vs %s", p->nome, p->vida, p->vida_max, m->nome);// /t == 8x" "
        i = strlen(m->nome);
        j = strlen(p->nome);
        x = j+i;
        while(1){
            if(x==58){
                printf("  ||\n");
                break;
            }
            else{
                printf(" ");
                ++x;
            }
        }
        printf("                                         ||------------------------------------------------------------------------||\n");
        printf("                                         || Atributos do Player                                                    ||\n");
        printf("                                         ||                                                                        ||\n");
        printf("                                         ||  ATK:%d",p->atk);
        if(p->atk>9||p->atk<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||  DEF:%d",p->def);
        if(p->def>9||p->def<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||  AGI:%d",p->agi);
        if(p->agi>9||p->agi<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||                                                                        ||\n");
        printf("                                         ||1. Atacar.                                                              ||\n");
        printf("                                         ||2. Item.                                                                ||\n");
        printf("                                         ============================================================================\n");
        printf("                                         >>");
		setbuf(stdin, NULL);
        scanf("%d", &MODE);

        switch (MODE){

            case 1:
                printf("                                         ============================================================================\n");
                MODE = embate (p, m);
                printar_resultado_embate(MODE, m);
                break;
            
            case 2:
                printf("                                         ============================================================================\n");
                escolher_item_para_usar(p, m, E, r, D, &signal2);
                break;

            default:
                printf("                                         ============================================================================\n");
                printf("                                         ||                            Comando invalido.                           ||\n");
                printf("                                         ============================================================================\n");
                break;
        }
            
        /*
        ACOES ESPECIAIS DO IMITADOR
		
			0. Os atributos iniciais do Imitador sao identicos aos do player;
		
			1. Quando o jogador se cura, o Imitador também se cura. Ele pode fazer isso enquanto sua defesa for diferente de 0;
			
			2. Quando o Imitador chega à metade de sua vida (3), ele "muda de classe", invertendo agi e atk e recebendo buffs.
        */
        if((signal2 == 171) || (signal2 == 172) || (signal2 == 173)){
            if(m->def > 0){
				system ("cls");
                
				m->def -= 1;

				printf("                                         ============================================================================\n");
				printf("                                         ||     Enquanto voce se cura, voce percebe, no canto de sua visao...      ||\n");
				printf("                                         ||                                                                        ||\n");
				printf("                                         ||                             ...que o Imitador faz o mesmo...           ||\n");
				printf("                                         ============================================================================\n\n\n\n");
				
				adjustHP(m, 1);
			}
			
			else{
				printf("                                         ============================================================================\n");
				printf("                                         ||              Hm... ateh o Imitador tem os seus limites...              ||\n");
				printf("                                         ============================================================================\n\n\n\n");
			}
        }
        signal2 = 0;
		
		if(m->vida <= 3 && signal1 == 0){
			system("cls");
			printf("                                         ============================================================================\n");
			printf("                                         ||         Os cortes sobre a pele falsa do Imitador soltam fumaca...      ||\n");
			printf("                                         ============================================================================\n\n\n\n");
			system("pause");
			system("cls");
			printf("                                         ============================================================================\n");
			printf("                                         ||         EU SOU A SUA SOMBRA.                                           ||\n");
			printf("                                         ||                                                                        ||\n");
			printf("                                         ||                                                                        ||\n");
			printf("                                         ||                                   POR QUE TENTA LUTAR COMIGO?          ||\n");
			printf("                                         ||                                                                        ||\n");
			printf("                                         ||                                                                        ||\n");
			printf("                                         ||         VOCE NAO PODE ME MATAR DE UMA MANEIRA QUE IMPORTA.             ||\n");
            		printf("                                         ||                                                                        ||\n");
			printf("                                         ||                                                                        ||\n");
			printf("                                         ||                         DANCE COMIGO, MEU HOSPEDEIRO...                ||\n");
			printf("                                         ||                                                                        ||\n");
			printf("                                         ||                                                                        ||\n");
			printf("                                         ||          E CAIREMOS JUNTOS NAS PROFUNDEZAS DO ABISMO!                  ||\n");
			printf("                                         ============================================================================\n\n\n\n");
			
			strcpy(m->nome, "Sua Sombra");
			
			m->atk = p->agi;
			m->atk += 2;
			m->agi = p->atk;
			m->agi += 2;
			
			m->mao_principal += 1;
			
			signal1 = 1;
		}
    }

}
int GHODIRAH(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D){
    int MODE,i,j,x;
    int signal1 = 0, signal2 = 0;

    printf("                                         ||               GHODIRAH - A Rainha dos Dragoes despertou!               ||\n");
    printf("                                         ============================================================================\n\n");

    while(1){

        if(p->vida == 0) return -1;
        if(m->vida == 0) return 1;

        printf("                                         ============================================================================\n");
        printf("                                         || %s(%d/%d) vs %s", p->nome, p->vida, p->vida_max, m->nome);// /t == 8x" "
        i = strlen(m->nome);
        j = strlen(p->nome);
        x = j+i;
        while(1){
            if(x==58){
                printf("  ||\n");
                break;
            }
            else{
                printf(" ");
                ++x;
            }
        }
        printf("                                         ||------------------------------------------------------------------------||\n");
        printf("                                         || Atributos do Player                                                    ||\n");
        printf("                                         ||                                                                        ||\n");
        printf("                                         ||  ATK:%d",p->atk);
        if(p->atk>9||p->atk<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||  DEF:%d",p->def);
        if(p->def>9||p->def<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||  AGI:%d",p->agi);
        if(p->agi>9||p->agi<0){
            printf("                                                                ||\n");
        }
        else{
            printf("                                                                 ||\n");
        }
        printf("                                         ||                                                                        ||\n");
        printf("                                         ||1. Atacar.                                                              ||\n");
        printf("                                         ||2. Item.                                                                ||\n");
        printf("                                         ============================================================================\n");
        printf("                                         >>");
		setbuf(stdin, NULL);
        scanf("%d", &MODE);

        switch (MODE){

            case 1:
                if(signal1 == 0){
                    MODE = embate (p, m);
                    printar_resultado_embate(MODE, m);
                }
                else{
                    printf("                                         ============================================================================\n");
                    printf("                                         ||                                                                        ||\n");
                    printf("                                         ||            Voce se levanta, e recupera a postura!                      ||\n");
                    printf("                                         ||                                                                        ||\n");
                    printf("                                         ============================================================================\n\n\n");
                    signal1 = 0;
                }
                break;
            
            case 2:
                printf("                                         ============================================================================\n");
                escolher_item_para_usar(p, m, E, r, D, NULL);
                break;

            default:
                printf("                                         ============================================================================\n");
                printf("                                         ||                            Comando invalido.                           ||\n");
                printf("                                         ============================================================================\n");
                break;
        }
            
            
        /*
        ACOES ESPECIAIS - GHODIRAH

            NOTA: signal1 = 1 guarda quando o player foi derrubado
            NOTA: signal2 = 1 guarda quando o raio de gravidade esta carregando

            1. Ghodirah comeca a carregar o raio de gravidade (salva signal1 = 1 quando está carregando)
	    	Quando Ghodirah começa a carregar o ataque, o player deve rodar agi contra CA 16 para não ser derrubado por 1 turno
                Enquanto o player está derrubado, ele não pode entrar em embate contra Ghodirah.
		Quando o raio carregar, Ghodirah realiza um ataque que da 3d8 - (p->def/2) de dano.
        */
        
        if(signal2 == 0){

            printf("\n\n");
            printf("                                         ============================================================================\n");
            printf("                                         ||                   GHODIRAH COMECA A REUNIR ENERGIAS,                   ||\n");
            printf("                                         ||             E UMA FORCA DE EMPUXO PODEROSA TE AFASTA DELA              ||\n");
            printf("                                         ============================================================================\n");
            printf("                                         ||                    Rode agi para nao ser derubado!                     ||\n");
            printf("                                         ============================================================================\n");
            printf("\n\n");
            system("pause");
            signal2 = 1;

            if(d(20) + p->agi < 16){

                printf("\n\n");
                printf("                                         ============================================================================\n");
                printf("                                         ||              Voce nao foi agil o suficiente, e eh empurrado            ||\n");
                printf("                                         ============================================================================\n");
                printf("\n\n");
                signal1 = 1;
                system("pause");

            }
            else{

                printf("\n\n");
                printf("                                         ============================================================================\n");
                printf("                                         ||           Voce resiste ao empuxo, se equilibra, e se recompoe          ||\n");
                printf("                                         ============================================================================\n");
                printf("\n\n");
                signal1 = 0;
                system("pause");

            }
        }
        else{

            printf("\n\n");
            printf("                                         ============================================================================\n");
            printf("                                         ||                GHODIRAH TERMINA DE REUNIR SUAS FORCAS...               ||\n");
            printf("                                         ||                    UM DISPARO MASSIVO ESTA POR VIR                     ||\n");
            printf("                                         ============================================================================\n");
            printf("                                         ||                                DESVIE!                                 ||\n");
            printf("                                         ============================================================================\n");
            printf("\n\n");
            system("pause");
            signal2 = 1;
        }
        if(d(20) + p->agi < 16){

            printf("\n\n");
            printf("                                         ============================================================================\n");
            printf("                                         ||                     Voce nao foi agil o suficiente...                  ||\n");
            printf("                                         ============================================================================\n");
            printf("\n\n");
            signal1 = XdY(3, 8) - (p->def/2);
            system("pause");
            printf("\n\n");
            printf("                                         ============================================================================\n");
            printf("                                         ||                           Voce levou %d de dano...                     ||\n", signal1);
            printf("                                         ============================================================================\n");
            printf("\n\n");
            adjustHP(p, -1 * signal1);
            system("pause");

        }
        else{

            printf("\n\n");
            printf("                                         ============================================================================\n");
            printf("                                         ||        Voce se desvia do feixe de particulas, e a luta continua!       ||\n");
            printf("                                         ============================================================================\n");
            printf("\n\n");
            system("pause");

        }
    }
}


int AGOR(room *r, PLAYER *p, MON *m, enciclopedia *E, dung *D){

    int MODE,i,j,x;
    int signal1 = 0, signal2 = 0;

    printf("                                         ||                    Agor, o falso-Deus se levanta do po                 ||\n");
    printf("                                         ============================================================================\n\n");

    while(1){

        if(p->vida == 0) return -1;
        if(m->vida == 0) return 1;

        printf("                                         ============================================================================\n");
        printf("                                         || %s(%d/%d) vs %s", p->nome, p->vida, p->vida_max, m->nome);// /t == 8x" "
        i = strlen(m->nome);
        j = strlen(p->nome);
        x = j+i;
        while(1){
            if(x==58){
                printf("  ||\n");
                break;
            }
            else{
                printf(" ");
                ++x;
            }
        }
        printf("                                         ||                                                                        ||\n");
        printf("                                         ||1. Atacar.                                                              ||\n");
        printf("                                         ||2. Item.                                                                ||\n");
        printf("                                         ============================================================================\n\n\n");
        printf("                                         >>");
		setbuf(stdin, NULL);
        scanf("%d", &MODE);

        switch (MODE){

            case 1:
                if(signal2 == 0){
                    MODE = embate (p, m);
                    printar_resultado_embate(MODE, m);
                }
                else{
                    printf("                                         ============================================================================\n");
                    printf("                                         ||                                                                        ||\n");
                    printf("                                         ||            <AGOR> - AINDA NAO TERMINEI!                                ||\n");
                    printf("                                         ||                                                                        ||\n");
                    printf("                                         ============================================================================\n\n\n");
                    signal2 = 0;
                }
                break;
            
            case 2:
                printf("                                         ============================================================================\n");
                escolher_item_para_usar(p, m, E, r, D, NULL);
                break;

            default:
                printf("                                         ============================================================================\n");
                printf("                                         ||                            Comando invalido.                           ||\n");
                printf("                                         ============================================================================\n");
                break;
        }

        /*
        ACOES ESPECIAIS DE AGOR:
        
            1. Quando a vida do Player for zerada pela primeira vez, Agor o ressuscita para continuar a luta (Salva com pos[0]=1 que houve ressurreição)
            2. Agor escaneia o Player, e descobre seu modificador mais baixo (Salva em Signal1)
                Se akt, ent Signal1 = 1;
                Se def, ent Signal1 = 2;
                Se agi, ent Signal1 = 3;
            3. Se já tiver scaneado, Agor obriga o Player a realizar um teste contra Agor no atributo escolhido contra CA 14 para não levar 2d8 de dano.
                Depois disso, se o atributo for menor que 6, Agor dá ao Player um buff de +3 no atributo em questão.
                Agor reseta seu Scan (Signal1 = 0)

                Sempre que não bufar o Player, Agor recebe um "ponto de motivação". Quando tiver acumulado 3 pontos, a ressurreição é permitida novamente.
                A motivação de Agor é salva em pos[1];
        */


        if(p->vida <=0 && m->pos[0] == 0){

            printf("\n\n");
            printf("                                         ============================================================================\n");
            printf("                                         ||                *    Caro Aventureiro, Agor lhe matou...                ||\n");
            printf("                                         ||      -                  Mas sua jornada em Apeiromorfo na-sessdf&/A_S  | |\n");
            printf("                                         ||     0   -      +3)   - ><=g0r>> =  -- -O q pensa estar fazendo...         ||\n");
            printf("                                         ===aa========  - =============0=============== ]q=========================_2==\n\n\n");

            system ("pause");

            printf("\n\n");
            printf("                                         ============================================================================\n");
            printf("                                         ||                                                                        ||\n");
            printf("                                         ||            <AGOR> - TE RESSUCITOU!!! LUTE!!!                          ||\n");
            printf("                                         ||                                                                        ||\n");
            printf("                                         ============================================================================\n\n\n");

            system ("pause");
            p->vida = p->vida_max-1;
            p->atk --;
            p->def --;
            p->agi --;
            p->vida_max --;
		
            m->vida += d(2);
            if(m->vida > m->vida_max) 
		    m->vida = m->vida_max;

		
        }
        else{

            if(rand()%2){

                if(signal1 == 0){
                    if(p->atk <= p->agi && p->atk <= p->def){

                        printf("\n\n");
                        printf("                                         ============================================================================\n");
                        printf("                                         ||                                                                        ||\n");
                        printf("                                         ||            <AGOR> - RECONHECO SUA RESILIENCIA... MAS LHE FALTA FORCA!  ||\n");
                        printf("                                         ||                                                                        ||\n");
                        printf("                                         ============================================================================\n\n\n");
                        signal1 = 1;
                    }
                    else if(p->agi <= p->def && p->agi <= p->atk){

                        printf("\n\n");
                        printf("                                         ============================================================================\n");
                        printf("                                         ||                                                                        ||\n");
                        printf("                                         ||            <AGOR> - VOCE EH FORTE... MAS EH LENTO!                     ||\n");
                        printf("                                         ||                                                                        ||\n");
                        printf("                                         ============================================================================\n\n\n");
                        signal1 = 3;
                    }
                    else{

                        printf("\n\n");
                        printf("                                         ============================================================================\n");
                        printf("                                         ||                                                                        ||\n");
                        printf("                                         ||            <AGOR> - PATETICO...                                        ||\n");
                        printf("                                         ||                                                                        ||\n");
                        printf("                                         ============================================================================\n\n\n");
                        signal1 = 2;

                    }
                }else{

                    printf("\n\n");
                    printf("                                         ============================================================================\n");
                    printf("                                         ||                                                                        ||\n");
                    printf("                                         ||                 <AGOR> - RECEBA A PUNICAO DIVINA, INSOLENTE!           ||\n");
                    printf("                                         ||                                                                        ||\n");
                    printf("                                         ============================================================================\n\n\n");
                    system("pause");

                    if(signal1 == 1){

                        printf("\n\n");
                        printf("                                         ============================================================================\n");
                        printf("                                         ||             <AGOR> invoca um enxame de constructos,                    ||\n");
                        printf("                                         ||                 que se erguem como zumbis do chao                      ||\n");
                        printf("                                         ||                     ATAQUE-OS PARA SOBREVIVER!                         ||\n");
                        printf("                                         ============================================================================\n\n\n");
                        system("pause");

                        if(d(20)+p->atk < 14){
                            
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                 Voce nao tem forca de ataque suficiente...             ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                            signal1 = XdY(2, 8) - p->atk;
                            adjustHP(p, signal1);
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                          Voce levou %d de dano...                      ||\n", signal1);
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                        }
                        else{
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||          Voce combate com vigor, e supera os zangoes de Agor!          ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                        }

                        if(p->atk <6){
                            
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                        <AGOR> - Voce eh patetico...                    ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                            p->atk+=3;
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                     Enquanto voce recupera a postura,                  ||\n");
                            printf("                                         ||                 Uma forca sobrenatural se apodera de voce...           ||\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||               <AGOR> - LUTE COMO UM VERDADEIRO DESAFIANTE!             ||\n", signal1);
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                   Sua arma parece ter sido encantada                   ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");

                        }
                        else{
                            
                            m->pos[1]++;
                            if(m->pos[1] == 3){
                                m->pos[1] = 0;
                                m->pos[0] = 0;
                            }
                        }


                    }
                    if(signal1 == 2){

                        printf("\n\n");
                        printf("                                         ============================================================================\n");
                        printf("                                         ||         <AGOR> comeca a dispara projeteis como uma chuva de fogo!      ||\n");
                        printf("                                         ||                                                                        ||\n");
                        printf("                                         ||                              PROTEJA-SE!!!                             ||\n");
                        printf("                                         ============================================================================\n\n\n");
                        system("pause");

                        if(d(20)+p->def < 14){
                            
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||             Voce nao consegue bloquear todos os projeteis...           ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                            signal1 = XdY(2, 8) - p->def;
                            adjustHP(p, signal1);
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                          Voce levou %d de dano...                      ||\n", signal1);
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                        }
                        else{
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||          Voce se defende com estilo! Nem mesmo foi arranhado!          ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                        }

                        if(p->def <6){
                            
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                        <AGOR> - Voce eh patetico...                    ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                            p->def+=3;
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                     Enquanto voce se levanta no chao,                  ||\n");
                            printf("                                         ||             Voce sente suas pernas gelar, e se paralisar...            ||\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||             <AGOR> - MELHORE SUA POSTURA! A LUTA EXIGE MAIS!           ||\n", signal1);
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||              Suas vestes parecem terem sido encantadas...              ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");

                        }
                        else{
                            m->pos[1]++;
                            if(m->pos[1] == 3){
                                m->pos[1] = 0;
                                m->pos[0] = 0;
                            }
                        }

                    }
                    if(signal1 == 3){

                        printf("\n\n");
                        printf("                                         ============================================================================\n");
                        printf("                                         ||          <AGOR> evoca a arena, e lancas comecam a sair do chao!        ||\n");
                        printf("                                         ||                                                                        ||\n");
                        printf("                                         ||                                DESVIE!!!                               ||\n");
                        printf("                                         ============================================================================\n\n\n");
                        system("pause");

                        if(d(20)+p->agi < 14){
                            
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                    Voce eh atingido por uma lanca...                   ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                            signal1 = XdY(2, 8) - p->agi;
                            adjustHP(p, signal1);
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                          Voce levou %d de dano...                      ||\n", signal1);
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                        }
                        else{
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||         Voce desvia de todas as lancas com destreza e agilidade!       ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                        }

                        if(p->agi <6){

                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                        <AGOR> - Voce eh patetico...                    ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                            p->def+=3;
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||                     Como que pelo sopro de um vento,                   ||\n");
                            printf("                                         ||                   Calafrios tomam conta de seu corpo...                ||\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||             <AGOR> - ESTOU COMECANDO A VER QUALIDADES AQUI...          ||\n", signal1);
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                            printf("\n\n");
                            printf("                                         ============================================================================\n");
                            printf("                                         ||        Voce sente seu corpo mais leve, e recebe a bencao de AGOR       ||\n");
                            printf("                                         ============================================================================\n\n\n");
                            system("pause");
                        }
                        else{
                            
                            m->pos[1]++;
                            if(m->pos[1] == 3){
                                m->pos[1] = 0;
                                m->pos[0] = 0;
                            }
                        }

                    }
                    signal1 = 0;
                }
            }
            else{
                signal2 = 1;
            }
        }
    }
}


