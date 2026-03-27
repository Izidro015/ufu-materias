#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*
#include "dados.h"
#include "itens.h"
#include "player.h"

#include "acoes.h"
*/

#include "playerFULL.h"


int treta(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D){
    int MODE,i,j,x;

    printf("                                         ||Voce entra em combate contra %s!", m->nome);
    i = strlen(m->nome);
    while(1){
        if(i==29){
            printf("             ||\n");
            break;
        }
        else{
            printf(" ");
            i++;
        }
    }

    while(1){
        if(p->vida <= 0) return -1;
        if(m->vida <= 0) return 1;

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
        printf("                                         ||3. Fugir.                                                               ||\n");
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
                
            case 3:
                MODE = fuga(p, m);
                printf("                                         ============================================================================\n");
                printar_resultado_fuga(MODE, m);
                if(MODE > 0) return 0;
                break;

            default:
                printf("                                         ============================================================================\n");
                printf("                                         ||                            Comando invalido.                           ||\n");
                printf("                                         ============================================================================\n");
                break;
        }
        printf("                                         ============================================================================\n");
    }
    system("cls");


    system("cls");

}








int embate(PLAYER *p, MON *m){
    int playerRoll, monsterRoll;
    playerRoll = d(20);
    monsterRoll = d(20);

    int dano_monstro = (XdY(m->mao_principal, m->mao_secundaria)) -p->def;
    if(dano_monstro < 0) dano_monstro = 0;

    //crítico do monstro;
    if((playerRoll == 1 || monsterRoll == 20) && playerRoll != monsterRoll){

        adjustHP(p, -dano_monstro);
        if((d(20) + m->atk) > (10 + p->atk)){
            adjustHP(p, -dano_monstro);
        }
        return -2;
    }
    //crítico do player;
    else if((playerRoll == 20 || monsterRoll == 1) && playerRoll != monsterRoll){
        adjustHP(m, -1);
        if((d(20) + p->atk) > (10 + m->atk)){
            adjustHP(m, -1);
        }
        return 2;
    }
    //combate normal;
    else{
        playerRoll += p->atk;
        monsterRoll += m->atk;

        if(playerRoll > monsterRoll){
            adjustHP(m, -1);
            return 1;
        }
        else if(playerRoll < monsterRoll){
            adjustHP(p, -dano_monstro);
            return -1;
        }
        else{
            return 0;
        }
    }
    /*
    CÓDIGOS DE RETORNO DA FUNÇÃO:
        -2: acerto crítico do monstro;
        -1: acerto do monstro;
        0:  empate;
        1:  acerto do player;
        2:  acerto crítico do player;
    */
}


int fuga(PLAYER *p, MON *m){
    int playerRoll = d(20);
    int monsterRoll = d(20);

    int dano_monstro = (XdY(m->mao_principal, m->mao_secundaria)) -p->def;
    if(dano_monstro < 0) dano_monstro = 0;

    //crítico do monstro;
    if((playerRoll == 1 || monsterRoll == 20) && playerRoll != monsterRoll){
        
        adjustHP(p, -dano_monstro);
        if((d(20) + m->atk) > (10 + p->atk)){
            adjustHP(p, -dano_monstro);
        }
        return -2;
    }
    //crítico do player;
    else if((playerRoll == 20 || monsterRoll == 1) && playerRoll != monsterRoll){
        return 2;
    }
    //fuga normal;
    else{
        playerRoll += p->agi;
        monsterRoll += m->agi;

        if(playerRoll > monsterRoll){
            return 1;
        }
        else if(playerRoll < monsterRoll){
            adjustHP(p, -dano_monstro);
            return -1;
        }
        else{
            return 0;
        }
    }
    /*
    CÓDIGOS DE RETORNO DA FUNÇÃO:
        -2: acerto crítico do monstro;
        -1: acerto do monstro;
        0:  empate;
        1:  fuga do player;
        2:  fuga crítica(?) do player;
    */

}









void printar_resultado_embate(int MODE, MON *m){
   int i;
    
    switch(MODE){

        case -2:
            printf("                                         ||%s te atinge brutalmente     ", m->nome);
            i = strlen(m->nome);
            while(1){
                if(i==29){
                    printf("                ||\n");
                    break;
                }
                else{
                    printf(" ");
                    i++;
                }
            }
            break;

        case -1:
            printf("                                         ||Voce se engalfinha com %s,recebendo um ataque", m->nome);
            i = strlen(m->nome);
            while(1){
                if(i==29){
                    printf("||\n");
                    break;
                }
                else{
                    printf(" ");
                    i++;
                }
            }
            break;

        case 0:
            printf("                                         ||Voce troca golpes com %s, ninguem recebe dano", m->nome);
            i = strlen(m->nome);
            while(1){
                if(i==29){
                    printf("||\n");
                    break;
                }
                else{
                    printf(" ");
                    i++;
                }
            }
            break;

        case 1:
            printf("                                         ||Voce engalfinha com %s, acertando um ataque  ", m->nome);
            i = strlen(m->nome);
            while(1){
                if(i==29){
                    printf("||\n");
                    break;
                }
                else{
                    printf(" ");
                    i++;
                }
            }
            break;

        case 2:
            printf("                                         ||Voce golpeia %s de maneira excelente ", m->nome);
            i = strlen(m->nome);
            while(1){
                if(i==29){
                    printf("        ||\n");
                    break;
                }
                else{
                    printf(" ");
                    i++;
                }
            }
            break;
    }
    printf("                                         ============================================================================\n");
}

void printar_resultado_fuga(int MODE, MON *m){
    int i;
    switch(MODE){
        case -2:
            printf("                                         ||Voce tenta fugir, e %s te ataca, brutalmente ", m->nome);
            i = strlen(m->nome);
            while(1){
                if(i==29){
                    printf("||\n");
                    break;
                }
                else{
                    printf(" ");
                    i++;
                }
            }
            break;

        case -1:
            printf("                                         ||Voce tenta fugir, e %s te ataca, atingindo   ", m->nome);
            i = strlen(m->nome);
            while(1){
                if(i==29){
                    printf("||\n");
                    break;
                }
                else{
                    printf(" ");
                    i++;
                }
            }
            break;

        case 0:
            printf("                                         ||Voce tenta fugir, e %s te ataca... mas erra  ", m->nome);
            i = strlen(m->nome);
            while(1){
                if(i==29){
                    printf("||\n");
                    break;
                }
                else{
                    printf(" ");
                    i++;
                }
            }
            break;

        case 1:

        case 2:
            printf("                                         ||Voce foge, deixando %s para tras             ", m->nome);
            i = strlen(m->nome);
            while(1){
                if(i==29){
                    printf("||\n");
                    break;
                }
                else{
                    printf(" ");
                    i++;
                }
            }
            break;

    }
    printf("                                         ============================================================================\n");
}



















/*

INICIO DE dados.h


*/

int d(int n){
    return (rand()%n)+1;
}

int XdY(int X, int Y){

    int retorno=0;

    while(X>0){
        retorno += d(Y);
        X--;
    }

    return retorno;
}



/*

FIM DE dados.h

















INICIO DE itens.h


*/



enciclopedia *iniciar_enciclopedia(){

    /*
    A variável pos guarda a seguinte informação:
        Se pos < 50: O item só pode ser equipado na mão principal;
        Se 50 < pos < 100: O item pode ser equipado em qualquer mão;
        Se 100 < pos < 150: O item é uma veste;
        Se 150 < pos < 170: O item é um item especial não-consumível;
        Se 170 < pos < 200: O item é um item especial consumível;
        Se 200 < pos: O item é um feitiço, e é consumido ao ser usado, a não ser se for usado com o cajado de feiticeiro;
    */

    enciclopedia *E=NULL;
    E = (enciclopedia*) calloc(1, sizeof(enciclopedia));

    if(E==NULL) return NULL;

    E->inicio = NULL;
    E->fim = NULL;
    E->tamanho = 0;

	int i;

	/*	template de item;
	preencher_com(XYZ,"[NOME]             ", 0, 0, 0, E);
	*/
	//os itens mundanos foram duplicados para que a probabilidade de serem selecionados pelo gacha() seja maior;
	//itens totais: 157;

    //Itens de classe
    preencher_com(2,  "[Escudo Real]      ", 0, 3, 0, E);
    preencher_com(51, "[Cajado Arcano]    ", 2, 0, 0, E);
    preencher_com(101,"[Capa de ladino]   ", 0, 0, 2, E);

	//mão principal: mundanos;
	for(i = 0; i < 2; i++){
    	preencher_com(3,  "[Espada Longa]     ", 3, 0, 0, E);
	    preencher_com(4,  "[Machado Grande]   ", 4, 0, -1, E);
		preencher_com(5,  "[Florete]          ", 2, 1, 0, E);
		preencher_com(6,  "[Montante]         ", 5, 0, -2, E);
		preencher_com(7,  "[Maca]             ", 4, -1, 0, E);
		preencher_com(8,  "[Alabarda]         ", 3, 1, -1, E);
		preencher_com(9,  "[Kriegsmesser]     ", 2, 0, 1, E);
		preencher_com(10, "[Uchigatana]       ", 2, -1, 2, E);
		preencher_com(11, "[Bardiche]         ", 4, 1, -2, E);
		preencher_com(12, "[Labris]           ", 2, 1, 0, E);
		preencher_com(13, "[Pique]            ", 2, 2, -1, E);
		preencher_com(14, "[Naginata]         ", 3, -1, 1, E);
		preencher_com(15, "[Arco Longo]       ", 4, -2, 1, E);
		preencher_com(16, "[Arco Composto]    ", 1, 1, 1, E);
		preencher_com(17, "[Mosquete]         ", 5, -1, -1, E);
		preencher_com(18, "[Carabina]         ", 5, -2, 0, E);
	}
	//mágicos;
	preencher_com(19, "[Mata-Dragoes]     ", 4, 2, 0, E);
	preencher_com(20, "[Marreta Executora]", 7, 0, -1, E);
	preencher_com(21, "[Sabre de Maria]   ", 3, 1, 2, E);
	preencher_com(22, "[Artilheiro]       ", 7, -1, 0, E);
	preencher_com(23, "[Pridwen]          ", 0, 6, 0, E);
	preencher_com(24, "[Presa Negra]      ", 5, 0, 1, E);
	preencher_com(25, "[Cutelo Serrilhado]", 4, 0, 2, E);
	preencher_com(26, "[Muramasa]         ", 3, 0, 3, E);
	preencher_com(27, "[Lanca de Raios]   ", 2, 0, 4, E);
	preencher_com(28, "[Maca Solar]       ", 3, 2, 1, E);
	preencher_com(29, "[Dente de Dragao]  ", 3, 3, 0, E);
	preencher_com(30, "[Tridente Venenoso]", 2, 2, 2, E);

	//mão secundária: mundanos;
	for(i = 0; i < 2; i++){
	    preencher_com(52, "[Escudo Triangular]", 0, 3, 0, E);
		preencher_com(53, "[Broquel]          ", 0, 2, 1, E);
		preencher_com(54, "[Escudo Torre]     ", 0, 4, -1, E);
		preencher_com(55, "[Adaga de Guarda]  ", 1, 1, 1, E);
		preencher_com(56, "[Faca]             ", 1, 0, 0, E);
		preencher_com(57, "[Espada Armada]    ", 2, 0, 0, E);
		preencher_com(58, "[Espada de Lado]   ", 2, 1, -1, E);
		preencher_com(59, "[Martelo de Guerra]", 3, 0, -1, E);
		preencher_com(60, "[Misericorde]      ", 4, -2, 0, E);
		preencher_com(61, "[Chicote]          ", 0, 0, 2, E);
		preencher_com(62, "[Funda]            ", 3, -1, 0, E);
		preencher_com(63, "[Pistola]          ", 4, -1, -1, E);
		preencher_com(64, "[Arco Curto]       ", 2, -1, 1, E);
		preencher_com(65, "[Escudo de Couro]  ", 0, 2, 0, E);
		preencher_com(66, "[Escudo Pequeno]   ", 0, 1, 1, E);
		preencher_com(67, "[Manopla]          ", 1, 1, 0, E);
		preencher_com(68, "[Escudo Grande]    ", 0, 5, -2, E);
		preencher_com(69, "[Bengala]          ", -2, 1, -2, E);
	}
	//mágicos;
	preencher_com(70, "[Excalibur]        ", 4, 0, 0, E);
	preencher_com(71, "[Mao Sombria]      ", 3, 0, 1, E);
	preencher_com(72, "[Pistola de Caca]  ", 1, 0, 3, E);
	preencher_com(73, "[Chikarasu]        ", 2, 0, 2, E);
	preencher_com(74, "[Escudo de Rocha]  ", 0, 5, -1, E);
	preencher_com(75, "[Manopla do Vento] ", 0, 0, 4, E);
	preencher_com(76, "[Escudo de Farpas] ", 2, 2, 0, E);
	preencher_com(77, "[Anel Serpentino]  ", 0, 2, 2, E);
	preencher_com(78, "[Mjolnir]          ", 2, 1, 1, E);
	preencher_com(79, "[Martelo do Sol]   ", 1, 2, 1, E);
	preencher_com(80, "[Faca de Mythril]  ", 1, 1, 2, E);
	preencher_com(81,"[Anel da Fome]     ", 6, -2, 0, E);
	
	
	//vestes: mundanos;
	for(i = 0; i < 2; i++){
		    preencher_com(102,"[Colete de Couro]  ", 0, 1, 0, E);
			preencher_com(103,"[Perponte]         ", 0, 1, 1, E);
			preencher_com(104,"[Peles Barbaricas] ", 1, 1, 0, E);
			preencher_com(105,"[Tunica Elfica]    ", 0, 0, 2, E);
			preencher_com(106,"[Carapaca de Anao] ", 2, 0, 0, E);
			preencher_com(107,"[Malha Escamada]   ", -1, 2, 1, E);
			preencher_com(108,"[Cota de Malha]    ", 0, 3, -1, E);
			preencher_com(109,"[Lorica Segmentada]", 1, 2, -1, E);
			preencher_com(110,"[Armadura de Placa]", 0, 4, -1, E);
			preencher_com(111,"[Placas Goticas]   ", 1, 3, -2, E);
			preencher_com(112,"[Panoplia Palatina]", -1, 5, -1, E);
	}
	//mágicos;
	preencher_com(113,"[Malha de Cruzador]", 1, 3, 0, E);
	preencher_com(114,"[Vestido Gotico]   ", 2, 0, 2, E);
	preencher_com(115,"[Casaco de Cacador]", 1, 0, 3, E);
	preencher_com(116,"[Dai-maou Yoroi]   ", 1, 2, 1, E);
	preencher_com(117,"[Botas de Tornado] ", 0, 0, 4, E);
	preencher_com(118,"[Manto da Protecao]", 0, 3, 1, E);
	preencher_com(119,"[Armadura de Rocha]", 0, 4, 0, E);
	preencher_com(120,"[Malha Peconhenta] ", 0, 2, 2, E);
	preencher_com(121,"[Escamas de Dragao]", 2, 2, 0, E);
	preencher_com(122,"[Coroa de Iulian]  ", 4, 0, 0, E);
	preencher_com(123,"[Venda de Tornado] ", 0, -2, 6, E);
	preencher_com(124,"[Elmo da Paciencia]", -2, 6, 0, E);
	
    
	//itens usáveis;
	for(i = 0; i < 10; i++){
		preencher_com(151,"[Mapa antigo]      ", 0, 0, 0, E);
		preencher_com(152,"[Bola de Cristal]  ", 0, 0, 0, E);
		preencher_com(153,"[Bussola Antiga]   ", 0, 0, 0, E);
		preencher_com(154,"[Vara Polimorfica] ", 0, 0, 0, E);
		
		preencher_com(174,"[Essencia de Grifo]", 0, 0, 0, E);
		preencher_com(175,"[Essencia da Vida] ", 0, 0, 0, E);
		preencher_com(176,"[Bencao do Dragao] ", 0, 0, 0, E);
		preencher_com(177,"[Essencia de Tita] ", 0, 0, 0, E);
		preencher_com(178,"[Granada]          ", 0, 0, 0, E);
		preencher_com(179,"[Bomba de trovao]  ", 0, 0, 0, E);

		preencher_com(201,"[SCROLL: Maldicao] ", 0, 0, 0, E);
		preencher_com(202,"[SCROLL: Lentidao] ", 0, 0, 0, E);
		preencher_com(203,"[SCROLL: Agourar]  ", 0, 0, 0, E);
		preencher_com(204,"[HEMOMANCIA]       ", 0, 0, 0, E);
		preencher_com(205,"[NECROMANCIA]      ", 0, 0, 0, E);
	}

	//itens consumíveis;
	for(int i = 0; i < 30; i++){
    		preencher_com(171,"[Comida preservada]", 0, 0, 0, E);
	}
	for(int i = 0; i < 20; i++){
    		preencher_com(172,"[Pocao de cura]    ", 0, 0, 0, E);
	}

	for(int i = 0; i < 10; i++){
    		preencher_com(173,"[Elixir Filosofal] ", 0, 0, 0, E);
	}
	
	
	preencher_com(999,"[Controle Remoto]  ", 0, 0, 0, E);


    return E;
}

int preencher_com(int pos, char nome[20], int atk, int def, int agi, enciclopedia *E){

    if(E == NULL) return 3;

    no_item *no = (no_item*) malloc (sizeof(no_item));
    no_item *p = E->fim;

    E->tamanho ++;

    item *x = &no->I;

    x->pos = pos;

    x->atk = atk;
    x->def = def;
    x->agi = agi;

    for(int i=0; i<21; i++){
        x->nome[i] = nome[i];
    }

    if(E->inicio == NULL) E->inicio = no;
    else p->prox = no;
    no->prox = NULL;

    E->fim = no;

    return 0;
}

int remItem(enciclopedia *E){
	if(E == NULL) return 2;
    if(E->inicio == NULL) return 1;

    no_item *nlist = E->inicio;

    E->inicio = nlist->prox;
	free(nlist);
    return 0;
	/*
	CÓDIGOS DE RETORNO DA FUNÇÃO:
		2: ERRO FATAL: enciclopédia NULA;
		1: ERRO: enciclopédia vazia;
		0: item removido com sucesso;
	*/
}

int clearItemEnc(enciclopedia *E){
    if(E == NULL) return 2;
    while(E->inicio != NULL){
        remItem(E);
    }
    return 0;
	/*
	CÓDIGOS DE RETORNO DA FUNÇÃO:
		2: ERRO FATAL: enciclopédia NULA;
		0: enciclopédia limpada com sucesso;
	*/
}

int printar_nome_do_item(int pos, enciclopedia *E){

    no_item *p = E->inicio;

    while (p !=NULL){

        if(p->I.pos == pos){
            printf("%s", p->I.nome);
            return 0;
        }
        p=p->prox;
    }
    return 1;
}
/*
void printar_item(int pos, enciclopedia *E){

    item *I = consultar_item(pos, E);
    printf("[%d]", )
    for(int i=0; i<E->tamanho; i++){

        if(E->I[i][0].pos == pos){
            printf("%s", E->I[i][0].nome);
            break;
        }
    }

    printf("")
}
*/
item *consultar_item(int pos, enciclopedia *E){

    no_item *p = E->inicio;

    while (p != NULL){
        if(p->I.pos == pos) return &p->I;
        p=p->prox;
    }

    return NULL;
    
}

item *gacha(enciclopedia *E){

    int random = d(E->tamanho-4)+3;
    no_item *p = E->inicio;

    while (random > 0){
        p=p->prox;
		random--;
    }
    return &p->I;
}


/*

FIM DE itens.h

















INICIO DE montrap.h


*/


MON *createMon(int monID){
    MON *m = (MON*) malloc(sizeof(MON));

    monsterList(monID, m);
    return m;
}


int adjustHP(PLAYER *p, int adj){
    if(p == NULL) return 2;
    if(adj == 0) return 1;
    p->vida += adj;
    if(p->vida > p->vida_max){
        p->vida = p->vida_max;
    }
    if(p->vida < 0){
        p->vida = 0;
        return -1;
    }

    return 0;
    /*
    CÓDIGOS DE RETORNO DA FUNÇÃO:
        -1: operação normal && p está morto;
        0:  operação normal;
        1:  ajuste zero;
        2:  jogador nulo;
    */
}

TRAP *createTrap(int trapID){
    TRAP *t = (TRAP*) malloc(sizeof(TRAP));

    trapList(trapID, t);
    return t;
}   

int mardilha(PLAYER *p, TRAP *t, enciclopedia *E, room *r, dung *D){
    int MODE,i,j,x;
    
    printf("                                         ||Voce acionou uma armadiha! %s!", t->nome);
    i = strlen(t->nome);
    while(1){
        if(i==29){
            printf("               ||\n");
            break;
        }
        else{
            printf(" ");
            i++;
        }
    }
    while(1){
        if(p->vida <= 0) return -1;
        if(t->vida <= 0) return 1;

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
                    case 1:
                        printf("                                         ============================================================================\n");
                        printf("                                         ||Voce utiliza sua forca para parar a armadilha                           ||\n");
                    break;

                    case -1:
                        printf("                                         ============================================================================\n");
                        printf("                                         ||A armadilha supera a forca de seus musculos                             ||\n");
                    break;

                    case 3:
                        printf("                                         ============================================================================\n");
                        printf("                                         ||Voce esquiva da armadilha com destreza                                  ||\n");
                    break;

                    case -3:
                        printf("                                         ============================================================================\n");
                        printf("                                         ||A armadilha te atinge quando voce tenta desviar                         ||\n");
                    break;

                    case 2:
                        printf("                                         ============================================================================\n");
                        printf("                                         ||Voce supera a armadilha com facilidade                                  ||\n");
                    break;

                    case -2:
                        printf("                                         ============================================================================\n");
                        printf("                                         ||A armadilha te pega de maneira inusitada                                ||\n");
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
        printf("                                         ============================================================================\n");
    }
}   

int actPass(PLAYER *p, TRAP *t){
    int playerRoll = d(20);
    int dano_monstro = (XdY(t->mao_principal, t->mao_secundaria)) -p->def;
    if(dano_monstro < 0) dano_monstro = 0;
    if(playerRoll == 20){   //teste crítico;
        adjustHP(t, -2);
        return 2;
    }
    else if(playerRoll == 1){   //falha crítica;
        adjustHP(p, (-2 * dano_monstro));
        return -2;
    }
    else{
        if(t->atk){        //teste normal;
            playerRoll += p->atk;
            if(playerRoll > t->def){
                adjustHP(t, -1);
                return 1;
            }
            else{
                adjustHP(t, -1);
                adjustHP(p, (-1 * dano_monstro));
                return -1;
            }
        }
        else{
            playerRoll += p->agi;
            if(playerRoll > t->def){
                adjustHP(t, -1);
                return 3;
            }
            else{
                adjustHP(t, -1);
                adjustHP(p, (-1 * dano_monstro));
                return -3;
            }
        }
    }
    /*
    CÓDIGOS DE RETORNO DA FUNÇÃO:
        1:  TESTE DE FORÇA: sucesso; 
        -1: TESTE DE FORÇA: falha;
        3:  TESTE DE AGILIDADE: sucesso;
        -3: TESTE DE AGILIDADE: falha;
        2:  sucesso crítico;
        -2: falha crítica;
    */
}   



/*

FIM DE montrap.h

















INICIO DE player.h


*/

lista *criar_inventario(){

    lista *inventario = (lista*) calloc (1, sizeof(lista));
    return inventario;
}

int adicionar_item(lista *l, int item, enciclopedia *E){

    if(l == NULL) return 2;
    if(l->total >= 12) return 1;

    if(consultar_item(item, E) == NULL) return 3;
    l->itens[l->total] = item;
    l->total++;

    return 0;

}
int remover_item(lista *l, int item){

    if(l == NULL) return 2;
    for(int i=0; i<l->total; i++){
        if(l->itens[i] == item){

            if(removerPosicao (l, i) != 0) return 3;
            return 0;
        }
    }
    return 1;
}
int removerPosicao (lista *l, int pos){

    if(l == NULL) return 2;
    if(pos >= l->total || pos < 0) return 1;
    for(int i=pos; i<=l->total; i++){
        l->itens[i] = l->itens[i+1];
    }
    l->total--;
    return 0;
}

int clearPlayer(PLAYER *p){
	if(p == NULL) return 2;
	free(p->inventario);
	return 0;
	/*
	CÓDIGOS DE RETORNO DA FUNÇÃO:
		2: ERRO FATAL: player NULO;
		0: player limpado com sucesso;
	*/
}


PLAYER *criar_player(int classe, int *spawn, enciclopedia *E){

    PLAYER *p = (PLAYER*) malloc (sizeof(PLAYER));
    
    p->inventario = criar_inventario(20);

    p->inventario->total = 2;
    p->inventario->itens[0] = 171;
    p->inventario->itens[1] = 171;

    p->SCORE = 0;

    p->vida_max = 20;
    p->vida = 20;
    p->pos[0] = spawn[0];
    p->pos[1] = spawn[1];
    p->mao_principal = 0;
    p->mao_secundaria = 0;
    p->vestes = 0;

    if(classe == 1){
        p->atk = 1;
        p->def = 2;
        p->agi = 1;

        adicionar_equipamento(p, 56, E);
        p->mao_secundaria = 56;

		adicionar_equipamento(p, 102, E);
		adicionar_equipamento(p, 2, E);
        p->mao_principal = 2;
        p->vestes = 102;
    }
    if(classe == 2){
        p->atk = 2;
        p->def = 1;
        p->agi = 1;

        
		adicionar_equipamento(p, 105, E);
        p->vestes = 105;

		adicionar_equipamento(p, 51, E);
        p->mao_secundaria = 51;
    }
    if(classe == 3){
        p->atk = 1;
        p->def = 1;
        p->agi = 2;

        adicionar_equipamento(p, 56, E);
        p->mao_principal = 56;
        adicionar_equipamento(p, 56, E);
        p->mao_secundaria = 56;

		adicionar_equipamento(p, 101, E);
        p->vestes = 101;
    }
    if(classe == 74){
        p->atk = 10;
        p->def = 10;
        p->agi = 10;

        p->inventario->itens[2] = 999;
        p->inventario->itens[3] = 151;
		adicionar_equipamento(p, 999, E);
		adicionar_equipamento(p, 151, E);
        p->inventario->total+=2;
    }

    return p;
}


void abrir_inventario(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D){


    int n, continua=1;
    int c;


    while (continua){

        system ("cls");
        printf("\t\t\n\n\n--------------------------------------------------------------------------------------------------");
        printf("\n\n\t\t                AVENTUREIRO: %s\n\n\n", p->nome);

        printf("\t              HP: %d/%d\n\n", p->vida, p->vida_max);

        printf("\t              ATK: %d\n", p->atk);
        printf("\t              DEF: %d\n", p->def);
        printf("\t              AGI: %d\n", p->agi);
           
        mostrar_inventario(p, E);

        printf("\n\n                  Mao principal: "); printar_nome_do_item(p->mao_principal, E);
        printf("\n                  Mao secundaria: "); printar_nome_do_item(p->mao_secundaria, E);
        printf("\n                  Equipamento: "); printar_nome_do_item(p->vestes, E);
        printf("\n\n");
       
        printf("                Escolha uma opcao:\n\n");
        printf("\t          1. Equipar item na mao principal\n");
        printf("\t          2. Equipar item na mao secundaria\n");
        printf("\t          3. Equipar vestes\n\n");

        printf("\t          4. Desequipar item na mao principal\n");
        printf("\t          5. Desequipar item na mao secundaria\n");
        printf("\t          6. Desequipar vestes\n\n");

        printf("\t          7. Usar item\n");
        printf("\t          8. Descartar item\n");
        printf("\t          9. sair\n");
		setbuf(stdin, NULL);
        printf("\t\t>>");
        scanf("%d", &n);

        system ("cls");

        switch(n){


            case 1:

                mostrar_inventario(p, E);

                printf("\n                 Escolha o item a ser equipado (digite a casa dele): ");
				setbuf(stdin, NULL);
                scanf("%d", &n);

                if(p->inventario->itens[n]>=100){
                    printf("\n\t         O item ");
                    printar_nome_do_item(p->inventario->itens[n], E);
                    printf("nao pode ser equipado na mao principal\n\n");
                    break;
                }
                if(n>=p->inventario->total){
                    printf("                 Selecao invalida\n\n");
                    break;
                }
                
                c = p->inventario->itens[n];
                removerPosicao(p->inventario, n);

                adicionar_equipamento(p, c, E);

                if(p->mao_principal == 0) p->mao_principal = c;
                else{
                    remover_equipamento(p, p->mao_principal, E);
                    adicionar_item(p->inventario, p->mao_principal, E);
                    p->mao_principal = c;
                }
                break;


            case 2:

                mostrar_inventario(p, E);
                
                printf("\n                 Escolha o item a ser equipado (digite a casa dele): ");
				setbuf(stdin, NULL);
                scanf("%d", &n);

                if(n>=p->inventario->total){
                    printf("                 Selecao invalida\n\n");
                    break;
                }

                if(p->inventario->itens[n]<50 || p->inventario->itens[n]>100){
                    printf("\n\t         O item ");
                    printar_nome_do_item(p->inventario->itens[n], E);
                    printf("nao pode ser equipado na mao secundaria\n\n");
                    break;
                }

                c = p->inventario->itens[n];
                removerPosicao(p->inventario, n);

                adicionar_equipamento(p, c, E);

                if(p->mao_secundaria == 0) p->mao_secundaria = c;
                else{
                    remover_equipamento(p, p->mao_secundaria, E);
                    adicionar_item(p->inventario, p->mao_secundaria, E);
                    p->mao_secundaria = c;
                }
                break;


            case 3:

                mostrar_inventario(p, E);

                printf("\n                 Escolha o item a ser equipado (digite a casa dele): ");
				setbuf(stdin, NULL);
                scanf("%d", &n);

                if(n>=p->inventario->total){
                    printf("                 Selecao invalida\n\n");
                    break;
                }

                if(p->inventario->itens[n]<100 || p->inventario->itens[n]>150){
                    printf("\n\t         O item ");
                    printar_nome_do_item(p->inventario->itens[n], E);
                    printf("O equipamento nao pode ser vestido\n\n");
                    break;
                }


                c = p->inventario->itens[n];
                removerPosicao(p->inventario, n);

                adicionar_equipamento(p, c, E);

                if(p->vestes == 0) p->vestes = c;
                else{
                    remover_equipamento(p, p->vestes, E);
                    adicionar_item(p->inventario, p->vestes, E);
                    p->vestes = c;
                }
                break;

            case 4:
                if(p->inventario->total>=20) {
                    printf("\n                        Inventario Cheio\n");
                    break;
                }
                if(p->mao_principal == 0){
                    printf("\n                        Nao ha nada equipado na mao principal\n");
                }
                else{
                    remover_equipamento(p, p->mao_principal, E);
                    adicionar_item(p->inventario, p->mao_principal, E);
                    p->mao_principal = 0;
                }
                break;

            case 5:
                if(p->inventario->total>=20) {
                    printf("\n                        Inventario Cheio\n");
                    break;
                }
                if(p->mao_secundaria == 0){
                    printf("\n                        Nao ha nada equipado na mao secundaria\n");
                }
                else{
                    remover_equipamento(p, p->mao_secundaria, E);
                    adicionar_item(p->inventario, p->mao_secundaria, E);
                    p->mao_secundaria = 0;
                }
                break;

            case 6:
                if(p->inventario->total>=20) {
                    printf("\n                        Inventario Cheio\n");

                    break;
                }
                if(p->vestes == 0){
                    printf("\n                        Nao ha uma veste equipada\n");

                }
                else{
                    remover_equipamento(p, p->vestes, E);
                    adicionar_item(p->inventario, p->vestes, E);
                    p->vestes = 0;
                }
                break;

            case 7:
                escolher_item_para_usar(p, m, E, r, D, NULL);
                break;

            case 8:

                mostrar_inventario(p, E);
                
                printf("\n              Escolha o item a ser descartado (digite a casa dele): ");
				setbuf(stdin, NULL);
                scanf("%d", &n);
                n = removerPosicao(p->inventario, n);
                if(n == 1) printf("\n               posicao invalida\n\n");
                if(n == 0) printf("\n\n              item Descartado\n\n");

                break;

            case 9:
                continua=0;
                break;


            default:
                printf("\n\n\t                  OPCAO INVALIDA\n\n");

               
        }
    }
}


void mostrar_inventario(PLAYER *p, enciclopedia *E){

    int i=0;
    item *X;
    printf("\t\t\n\n\n--------------------------------------------------------------------------------------------------\n");
    for(int j=0; j<5; j++){

        printf(" {{ ");

        for(int k=0; k<4; k++){

            if(i >= p->inventario->total){
                j=5; break;
            }
            
            X = consultar_item(p->inventario->itens[i], E);
            if(X != NULL) printf("[%d]", i);
                printf("%s", X->nome);
                if(i<10) printf(" ");
                i++;
        }
        printf(" }}\n");
    }

    printf("\t\t\n\n\n--------------------------------------------------------------------------------------------------");


}


int adicionar_equipamento(PLAYER *p, int pos, enciclopedia *E){

    item *X = consultar_item(pos, E);

    p->agi += X->agi;
    p->atk += X->atk;
    p->def += X->def;

    return 0;

}
int remover_equipamento(PLAYER *p, int pos, enciclopedia *E){

    item *X=consultar_item(pos, E);
    
    p->agi -= X->agi;
    p->atk -= X->atk;
    p->def -= X->def;

    return 0;

}




int escolher_item_para_usar(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D, int *signal){

    int i=0;
    item *X;

    system ("cls");
    printf("\t\t\n\n\n--------------------------------------------------------------------------------------------------");
    printf("\n\n\t\t                AVENTUREIRO: %s\n\n\n", p->nome);
        printf("\t              HP: %d/%d\n\n", p->vida, p->vida_max);
        printf("\t              ATK: %d\n", p->atk);
        printf("\t              DEF: %d\n", p->def);
        printf("\t              AGI: %d\n", p->agi);
           
    printf("\t\t\n\n\n--------------------------------------------------------------------------------------------------\n");
    for(int j=0; j<5; j++){
        for(int k=0; k<4; k++){

            if(i >= p->inventario->total){
                j=5; break;
            }
            if(consultar_item(p->inventario->itens[i], E) != NULL) printf("[%d]", i);
            printar_nome_do_item(p->inventario->itens[i], E);
            if(i<10) printf(" ");
            i++;
        }
        printf("\n");
    }

    printf("\t\t\n\n\n--------------------------------------------------------------------------------------------------");

    printf("\n\n                  Mao principal: "); printar_nome_do_item(p->mao_principal, E);
    printf("\n                  Mao secundaria: "); printar_nome_do_item(p->mao_secundaria, E);
    printf("\n                  Equipamento: "); printar_nome_do_item(p->vestes, E);
    printf("\n\n");
 
    printf("\n                 Escolha o item a ser usado (digite a casa dele): ");
    scanf("%d", &i);

    if(i>=p->inventario->total){
        printf("                 Selecao invalida\n\n");

        }
    else{

        X = consultar_item(p->inventario->itens[i], E);
        if(X == NULL) return 0;

        if(X->pos<150 && X->pos!=51){ 
            printf("\n                  Esse item nao eh usavel\n\n");
            }
        else{
            usar_item(p, m, X->pos, E, r, D);
            if(signal != NULL) *signal = X->pos;
            if(X->pos > 170 && X->pos !=999) removerPosicao(p->inventario, i);
        }
    }
    if(p->vida<0) return -1;
    else return 0;
}


