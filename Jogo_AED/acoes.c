#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#include "manual.h"
#include "dungrooms.h"
#include "Menulist.h"
#include "gameplay.h"

#include "playerFULL.h"



int usar_item(PLAYER *p, MON *m, int pos, enciclopedia *E, room *r, dung *D){

    system("cls");
    switch (pos){



        case 999:
            return Controle_remoto(p, E);

                        //ITENS NAO CONSUMIVEIS:


        case 51:
            return Cajado_arcano(p, m, E, r, D);

        case 151:
            return mapa(D);

        case 152:
            return Bola_de_Cristal(r, D, p);

        case 153:
            return Bussola_Magica(D, p);
			
		case 154:
			return Varinha_de_Condao(r, m, p, E);

                        //ITENS CONSUMIVEIS:


        case 171:
            return Comida_Preservada(p);
        case 172:
            return Pocao_de_Cura(p);
        case 173:
            return Elixir_Filosofal(p);

        case 174:
            return Essencia_de_Grifo(p);
        case 175:
            return Essencia_da_Vida(p);
        case 176:
            return Essencia_de_Dragao(p);
        case 177:
            return Essencia_de_Tita(p);

        case 178:
            return Granada(m);
        case 179:
            return Bomba_de_Trovao(m, p);







        default:
            break;
    }

    if(pos > 200) return usar_scroll(p, m, pos, E, r, D);

    return 0;
}




int usar_scroll(PLAYER *p, MON *m, int pos, enciclopedia *E, room *r, dung *D){

    switch(pos){
        
        case 201:
            return SCROLL_maldicao(m, r);
        case 202:
            return SCROLL_lentidao(m, r);
        case 203:
            return SCROLL_mal_agouro(p, m, r);
        case 204:
            return SCROLL_hemomancia(p, m, r);
        case 205:
            return SCROLL_necromancia(p, m, E, r, D);
    }

    return 0;
}


int SCROLL_maldicao(MON *m, room *r){

    if(r->cont < 0 || m==NULL){
        printf("\n\n              Nao ha monstros a serem amaldicoados aqui...\n\n");
        return 0;
    }

    printf("\n\n              A maldicao se apodera do inimimgo, e o enfraquece...\n\n");
    m->atk-=2;
    printf("\n\n              O ataque do inimigo diminuiu\n\n");
    printf("              ");
    system ("pause");
    return 0;
}
int SCROLL_lentidao(MON *m, room *r){

    if(r->cont < 0 || m==NULL){
        printf("\n\n              Nao ha monstros a serem amaldicoados aqui...\n\n");
        return 0;
    }

    printf("\n\n              A maldicao se apodera do inimimgo, e o enfraquece...\n\n");
    m->agi-=2;
    printf("\n\n              O inimigo esta mais lento\n\n");
    printf("              ");
    system ("pause");
    return 0;
}
int SCROLL_mal_agouro(PLAYER *p, MON *m, room *r){

    int MODE;
    if(r->cont < 0 || m==NULL){
        printf("\n\n              Nao ha monstros a serem amaldicoados aqui...\n\n");
        return 0;
    }
    if(r->dif == 20){
        printf("\n\n              %s eh poderoso demais para o feitico!!!\n\n", m->nome);
        return 0;
    }

    printf("\n\n              Uma fumaca rodeia o inimigo... e ele, gritando, desaparece nas sombras\n\n");
    m->vida = 0;
    printf("\n\n              O fantasma de sua antiga presenca persiste a maldicao, e te ataca!\n\n\n");

    p->atk -=20;
    printf("                                         ============================================================================\n\n");
    MODE = embate (p, m);
    printar_resultado_embate(MODE, m);
    p->atk +=20;
    printf("              ");
    system("pause");
    if(p->vida <=0 )return 1;
    else return 0;
}

int SCROLL_hemomancia(PLAYER *p, MON *m, room *r){

    if(r->cont < 0 || m==NULL){
        printf("\n\n              Nao ha monstros a serem amaldicoados aqui...\n\n");
        return 0;
    }

    printf("\n\n              VOce faz um pequeno corte no seu braco, do qual surge uma nevoa e rodeia o inimigo\n\n");
    m->vida -= 3;
    printf("\n\n              Voce comeca a sentir no seu corpo os efeitos dessa magia poderosa:\n\n\n");

    for(int i=0; i<2; i++){

        switch(rand()%3){

            case 0:
                p->agi--;
                printf("              Voce perdeu 1 de agilidade\n");
                break;
            case 1:
                p->atk--;
                printf("              Voce perdeu 1 de ataque\n");
                break;
            case 2:
                p->def--;
                printf("              Voce perdeu 1 de defesa\n");
                break;
        }
    }
    printf("              ");
    system ("pause");
    return 0;
}

int SCROLL_necromancia(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D){

    int MODE, continua = 1;
    item *X = gacha(E);
    if(r->cont != -1){              //Caso o player nao esteja numa sala onde um combate contra monstro foi concluido
        printf("              O feitico falhou...\n");
        return 0;
    }

    printf("              Voce recita o antigo encantamento...\n\n");
    printf("              Uma presenca vil se ergue do chao...\n\n");
    printf("              ");
    system ("pause");
    system ("cls");

    m = createMon(112); //m eh um fantasma
    MODE = treta(p, m, E, r, D);
	
	if(MODE == -1) return -1;

    system ("cls");
    printf("              O fantasma se desfaz...\n\n");
    printf("              No seu lugar, apenas fica um item:\n\n");
    printf("\t>>%s\n\n\n", X->nome);

    printf("                                         ============================================================================\n");
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
                printf("                                         ||Descarte um item para saquear o bau (pressione 1).                      ||\n");
                printf("                                         ============================================================================\n");
                printf("                                         >>");
                scanf("%d",&MODE);
                if(MODE == 1){
                    abrir_inventario(p, m, E, r, D);
                    system("cls");
                    if(p->inventario->total < 12){
                        adicionar_item(p->inventario, X->pos, E);
                        printf("                                         ============================================================================\n");
                        printf("                                         ||%s adicionado ao inventario!                           ||\n", X->nome);
                        printf("                                         ============================================================================\n\n\n");
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
            printf("                                         ============================================================================\n\n\n");
            }
        }
    }
    printf("                                         ============================================================================\n");
    printf("                                         ||Um item largado por uma entidade das trevas pode ser perigoso...        ||\n");
    printf("                                         ============================================================================\n");
  
    return 0;

}






















int Controle_remoto(PLAYER *p, enciclopedia *E){

    int pos;
    item *X;
    p->vida = 99;
    p->vida_max = 99;

    printf("              Digite um item a ser adicionado (pos do item):\n\n>>");
    scanf("%d", &pos);

    X = consultar_item(pos, E);
    if(X != NULL && p->inventario->total <= 12){
        p->inventario->itens[p->inventario->total] = X->pos;
        p->inventario->total++;
    }
    return 0;
}

int Comida_Preservada(PLAYER *p){

    int random = d(6)+2;
    printf("              Voce se alimenta e descansa...\n\n");
    printf("              Voce recuperou %d HP!\n\n", random);
    adjustHP(p, random);
    printf("              ");
    system("pause");

    return 0;
}
int Pocao_de_Cura(PLAYER *p){

    int random = d(10)+2;
    printf("              A magia te envolve, e voce se sente revigorado\n\n");
    printf("              Voce recuperou %d HP!\n\n", random);
    adjustHP(p, random);
    printf("              ");
    system("pause");

    return 0;
}
int Elixir_Filosofal(PLAYER *p){

    int random = 999;
    printf("              Os Deuses abencoaram sua jornada, corajoso aventureiro!\n\n");
    printf("              Voce recuperou %d HP!\n\n", random);
    adjustHP(p, random);
    printf("              ");
    system("pause");

    return 0;
}


int Essencia_de_Grifo(PLAYER *p){

    printf("              O tempo se passa mais devagar, sua adrenalina dispara, e a força do vento flui nas suas veias...\n\n");
    printf("              Voce ganhou +1 de agilidade!\n\n");
    p->agi++;
    printf("              ");
    system("pause");

    return 0;
}
int Essencia_da_Vida(PLAYER *p){

    printf("              A natureza lhe concede suas bencaos, e voce ouve o barulho das aves, ha muito esquecido no calabouco...\n\n");
    printf("              Sua vida aumentou em +5 HP!\n\n");
    p->vida_max+=5;
    p->vida+=5;
    printf("              ");
    system("pause");

    return 0;
}
int Essencia_de_Dragao(PLAYER *p){

    printf("              Uma furia invade sua mente, e a coragem dos reis seu coracao!\n\n");
    printf("              Voce ganhou +1 de defesa!\n\n");
    p->def++;
    printf("              ");
    system("pause");

    return 0;
}
int Essencia_de_Tita(PLAYER *p){

    printf("              Voce sente seu corpo se fortalecer, como se uma magia antiga lhe encantasse\n\n");
    printf("              Voce ganhou +1 de ataque!\n\n");
    p->atk++;
    printf("              ");
    system("pause");

    return 0;
}

int Granada(MON *m){

    if(m == NULL){
        printf("              Voce causa um grande estrondo na sala...\n\n");
        printf("              ...Voca gastou uma Granada...\n\n");
        printf("              ");
        system("pause");
        return 0;
    }

    int random = d(4);
    printf("              Voce lanca o dispositivo no inimigo\n\n");

    if(random <2) printf("              A explosao o acerta com sucesso!\n\n");
    else printf("              O lancamento foi preciso, e o inimigo sofre um dano consideravel!\n\n");
    m->vida-=random;
    printf("              ");
    system("pause");

    return 0;
}
int Bomba_de_Trovao(MON *m, PLAYER *p){

    int random = d(4), teste;
    if(m == NULL){
        printf("              Uma bola de fogo preenche a sala...\n\n");
        printf("              A Explosao eh muito poderosa! Rode um teste de agilidade:\n\n");
        printf("              ");
        system("pause");
    
        teste = d(20)+p->agi;

        printf("\n\n\t\t[%d]\n\n\n", teste);

        if(teste<14){
            printf("              Voce eh envolto pelas chamas da explosa...\n\n");
            random = XdY(2, 4);
            printf("              Voce levou %d de dano!\n\n", random);
            printf("              ");
            p->vida-=random;
            system("pause");
            return 0;
        }
        else{
            printf("              Voce se esquiva com destreza das chamas e se protege atras duma rocha!\n\n");
            printf("              Foi a explosao mais epica da sua vida!\n\n");
            printf("              ");
            system("pause");
            return 0;
        }
    }

    printf("              Voce lanca o dispositivo no inimigo\n\n");

    printf("              A Explosao eh muito poderosa! Rode um teste de agilidade:\n\n");
    printf("              ");
    system("pause");
    
    teste = d(20)+p->agi;

    printf("\n\n\t\t[%d]\n\n\n", teste);

    if(teste<14){
        printf("              A explosao preenche toda a sala, e voce tambem eh atingido!\n\n");
        random = XdY(2, 4);
        printf("              Voce e o inimigo levaram %d de dano!\n\n", random);
        printf("              ");
        p->vida-=random;
        m->vida-=random;
        system("pause");
        return 0;
    }
    else{
        
        if(random <3) printf("              A explosao inflinge grande dano ao inimigo, mas voce sobrevive!\n\n");
        else printf("              A explosao dilacera o inimigo! Agora ele esta a beira da morte...\n\n");
        m->vida-=random;
        printf("              ");
        system("pause");
        return 0;

    }
}

int Varinha_de_Condao(room *r, MON *m, PLAYER *p, enciclopedia *E){

    if(r->dif == 20){
        printf("              %s eh poderoso demais para a Varinha!!!\n\n", m->nome);
        printf("              A varinha se desfaz em suas maos...\n\n");
        printf("             ");
		remover_item(p->inventario, 154);
        system("pause");
        return 0;
    }

    item *X=gacha(E);

    printf("\n\n              Pifhit Paphit PHUM!!!\n\n");
    printf("              Convoco a magia de Ontum!\n\n");
    printf("             ");
	remover_item(p->inventario, 154);

    system("pause");

    if(m == NULL){
        printf("\n\n              Apos dizer as palavras magicas, a varinha se converte em po e brilho...\n\n");
        printf("              No chao, uma pequena caixinha se forma...\n");
        printf("              Dentro dela, voce encontra um item, e o pega:\n\n\t>>%s\n\n", X->nome);
        p->inventario->itens[p->inventario->total] = X->pos;
        p->inventario->total++;
        printf("             ");
        system("pause");
        return 0;
    }
    else{
        printf("              Apos dizer as palavras magicas, a varinha se converte em po e brilho...\n\n");
        printf("              O monstro se desfaz em cinzas e, no meio delas, uma pequena caixa aparece\n");
        printf("              Dentro dela, voce encontra um item, e o pega:\n\n\t>>%s\n\n", X->nome);
        printf("             ");
		p->inventario->itens[p->inventario->total] = X->pos;
        p->inventario->total++;
        system("pause");
        m->vida = 0;
        return 0;
    }
}




int Cajado_arcano(PLAYER *p, MON *m, enciclopedia *E, room *r, dung *D){

    int n, random = d(6);

    mostrar_inventario(p, E);

    printf("\n\n\n\n\t\t         >> Selecione o encantamento (digita a casas dele)");
    printf("\n\t\t         >> -1 desativara o cajado");
    
    while(1){

        printf("\n\n\t>> ");
        scanf("%d", &n);

        if(n == -1) return 0;

        if(p->inventario->itens[n]<200) printf("\n              Isso nao eh um feitico");
        else {
            if(n<0 || n>=p->inventario->total) printf("\n              Selecao invalida");
            else break;
        }
    }

    system("cls");

    printf("\n\n\t         O CAJADO ARCANO FOI ATIVADO!\n\n");

    printf("\t         A magia consome sua forca vital\n\n");

    printf("\t         Voce perdeu %d HP!\n\n", random);
    p->vida-=random;
    printf("\t         ");
    system("pause");

    printf("\n\n\t         A conjuracao termina, e o feitico esta ativo.\n\n");

    printf("\t         ");
    system("pause");

    if(p->vida<=0){

        printf("\n\n\n\t         A magia era poderosa demais para um iniciante como voce...\n\n");
        printf("\n\n\n\t         ");       
        system("pause");
        return 1;
    }

    system("cls");

    return usar_scroll(p, m, p->inventario->itens[n], E, r, D);
}

int mapa(dung *D){

    printf("\n\n");
    for(int i=0; i<D->MATRIXMAX; i++){
        printf("\t\t");
        for(int j=0; j<D->MATRIXMAX; j++){

            if(D->map[i][j]>0) printf(". ");
            else printf("# ");
                    
        }
        printf("\n");
    }
    printf("\n\n");
    printf("\t\t>>");
    system("pause");
    return 0;
}

int Bola_de_Cristal(room *r, dung *D, PLAYER *p){
     
    printf("\t         Um feitico de clarividencia foi ativado, e a bola de cristal comeca a sussurrar...\n\n");
    printf("\t         ");
    system("pause");
    printf("\n\n\t         Escolha uma direcao para conjurar a magia:\n\n");

    int pos[2];
    pos[0] = p->pos[0];
    pos[1] = p->pos[1];

    if(r->exits % 2 == 0){
        printf("\t                 _____\n");
        printf("\t                ||   ||\n");
        printf("\t                || W ||\n");
        printf("\t                ||___||\n");
        printf("\t                |/___\\|\n");
    }
    if(r->exits % 3 == 0 && r->exits % 5 != 0 && r->exits % 7 != 0 ) {
        printf("\t                        _____\n");
        printf("\t                       ||   ||\n");
        printf("\t                       || D ||\n");
        printf("\t                       ||___||\n");
        printf("\t                       |/___\\|\n");
    }
    if(r->exits % 3 != 0 && r->exits % 5 == 0 && r->exits % 7 != 0){
        printf("\t                 _____\n");
        printf("\t                ||   ||\n");
        printf("\t                || S ||\n");
        printf("\t                ||___||\n");
        printf("\t                |/___\\|\n");
    } 
    if(r->exits % 3 != 0 && r->exits % 5 != 0 && r->exits % 7 == 0){
        printf("\t          _____\n");
        printf("\t         ||   ||\n");
        printf("\t         || A ||\n");
        printf("\t         ||___||\n");
        printf("\t         |/___\\|\n");        
    }
    if(r->exits % 3 == 0 && r->exits % 5 == 0 && r->exits % 7 == 0){
        printf("\t          _____  _____  _____\n");
        printf("\t         ||   ||||   ||||   ||\n");
        printf("\t         || A |||| S |||| D ||\n");
        printf("\t         ||___||||___||||___||\n");
        printf("\t         |/___\\||/___\\||/___\\|\n");
    }
    if(r->exits % 3 == 0 && r->exits % 5 != 0 && r->exits % 7 == 0){
        printf("\t          _____         _____\n");
        printf("\t         ||   ||       ||   ||\n");
        printf("\t         || A ||       || D ||\n");
        printf("\t         ||___||       ||___||\n");
        printf("\t         |/___\\|       |/___\\|\n");
    }
    if(r->exits % 3 == 0 && r->exits % 5 == 0 && r->exits % 7 != 0){
        printf("\t                 _____  _____\n");
        printf("\t                ||   ||||   ||\n");
        printf("\t                || S |||| D ||\n");
        printf("\t                ||___||||___||\n");
        printf("\t                |/___\\||/___\\|\n");
    }
    if(r->exits % 3 != 0 && r->exits % 5 == 0 && r->exits % 7 == 0){
        printf("\t          _____  _____\n");
        printf("\t         ||   ||||   ||\n");
        printf("\t         || A |||| S ||\n");
        printf("\t         ||___||||___||\n");
        printf("\t         |/___\\||/___\\|\n");
    }
    char dir;
    while(1){
        dir = getch();
        if(p->pos[0]!= pos[0]||p->pos[1]!= pos[1]){
            break;
        }
        switch(dir){

			case 'W':
            case 'w':
                pos[0]--;
            break;

			case 'D':
            case 'd':
                pos[1]++;
            break;

			case 'S':
            case 's':
                pos[0]++;
            break;

			case 'A':
            case 'a':
                pos[1]--;
            break;

            default:
            printf("\t         Comando invalido.\n");
            break;
        }
    }
    printf("\n\n\n\n\n");

    if(D->map[pos[0]][pos[1]] < 3){
        printf("\t         Um caminho tranquilo o aguarda.\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if(D->map[pos[0]][pos[1]] < 7){
        printf("\t         A magia antiga de Apeiromorfo comeca a afetar-te. Cuidado.\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if(D->map[pos[0]][pos[1]] < 12){
        printf("\t         Sombras percorrem a escuridao. Um antigo horror dorme. Nao o acorde.\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if(D->map[pos[0]][pos[1]] < 16){
        printf("\t         Algo espreita as sombras. Seu caminho eh violento e desafiador. Tenha coragem.\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if(D->map[pos[0]][pos[1]] < 19){
        printf("\t         Teu caminho te levara as profundezas do Tartaro. A batalha sera dificl e desgastante.\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if(D->map[pos[0]][pos[1]] == 20){
        printf("\t         O mal dorme nessa sala... A sombra de um antigo horror, uma presenca maligna se ergue e cai, esperando a quem devorar.\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    return 1;
}

int Bussola_Magica(dung *D, PLAYER *p){

    printf("\t         Voce chacoalha um pequeno recipiente d'agua\n\n");
    printf("\t         ");
    system("pause");
    printf("\n\n\t        Uma pequena seta dourada se forma dos sedimentos dentro da esfera:\n\n\n\n");

    int dif_vertical = D->keyroom[0] - p->pos[0];
    int dif_horizontal = D->keyroom[1] - p->pos[1];
    

    if(dif_horizontal==0 && dif_vertical==0){

        printf("\t         A seta comeca a rodopiar... Parece que algo deu errado.");

        printf("\n\n\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if((dif_vertical <3) && (dif_vertical >-3) && (dif_horizontal > 0)){

        printf("\t                                                                                 |\\\\   \n");
        printf("\t                                                                         #=======##\\\\  \n");
        printf("\t                                                                         |########## * \n");
        printf("\t                                                                         #=======##//  \n");
        printf("\t                                                                                 |//   \n");

        printf("\n\n\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if((dif_vertical <3) && (dif_vertical >-3) && (dif_horizontal < 0)){

        printf("\t                                                                          //|            \n");
        printf("\t                                                                        //##=======#    \n");
        printf("\t                                                                        * ##########|    \n");
        printf("\t                                                                         \\\\##=======#    \n");
        printf("\t                                                                          \\\\|            \n");

        printf("\n\n\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if((dif_vertical >=0) && (dif_horizontal >=0)){

        printf("\t                                                                             /###\\\\        \n");
        printf("\t                                                                             \\\\###\\\\      \n");
        printf("\t                                                                              \\\\###\\\\//   \n");
        printf("\t                                                                               \\\\###//    \n");
        printf("\t                                                                              ---- *      \n");

        printf("\n\n\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if((dif_vertical >=0) && (dif_horizontal <=0)){

        printf("\t                                                                                //###\\\\   \n");
        printf("\t                                                                               //###//    \n");
        printf("\t                                                                            \\\\//###//     \n");
        printf("\t                                                                             \\\\###//      \n");
        printf("\t                                                                               * ----     \n");

        printf("\n\n\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if((dif_vertical <=0) && (dif_horizontal <=0)){

        printf("\t                                                                          * ----        \n");
        printf("\t                                                                         //###\\\\      \n");
        printf("\t                                                                        //\\\\###\\\\     \n");
        printf("\t                                                                           \\\\###\\\\    \n");
        printf("\t                                                                            \\\\###//      \n");

        printf("\n\n\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    if((dif_vertical >=0) && (dif_horizontal <=0)){
 
        printf("\t                                                                              ---- *      \n");
        printf("\t                                                                               //###\\\\   \n");
        printf("\t                                                                              //###//\\\\   \n");
        printf("\t                                                                             //###//      \n");
        printf("\t                                                                            \\\\###//      \n");

        printf("\n\n\n");
        printf("\t         ");
        system("pause");
        return 0;
    }
    return 1;
}






























