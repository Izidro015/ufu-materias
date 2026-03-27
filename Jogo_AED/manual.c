#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manual.h"

manlist *createman(){
    manlist *man = (manlist*) malloc(sizeof(manlist));
    man->ini = NULL;
    man->tamanho = 0;
    return man;
}

int insertManpage(manlist *man, int pag){   //inserção no final da lista;
    if(man == NULL) return 2;

    mno *n = (mno*) malloc(sizeof(mno));
    mno *nlist = man->ini;

    strcpy(n->mtxt, manpageList(pag));

    if(nlist == NULL){
        n->next = n;
        n->prev = n;
        man->ini = n;
        man->tamanho++;

        return 0;
    }

    while(nlist->next != man->ini){
        nlist = nlist->next;
    }

    n->next = man->ini;
    man->ini->prev = n;
    nlist->next = n;
    n->prev = nlist;
    man->tamanho++;

    return 0;

    /*
    CÓDIGOS DE RETORNO DA FUNÇÃO:
        2: erro fatal, lista NULA;
        0: item inserido;
    */
}

int removeManpage(manlist *man){    //remoção no início da lista;
    if(man == NULL) return 2;
    if(man->ini == NULL) return 1;

    mno *nlist = man->ini;

    if(man->ini->next == man->ini){
        free(nlist);
        man->ini = NULL;
    }
    else{
        nlist->prev->next = nlist->next;
        nlist->next->prev = nlist->prev;
        man->ini = nlist->next;
        free(nlist);
    }
    man->tamanho--;

    return 0;
}

int clearman(manlist *man){
    if(man == NULL) return 2;
    while(removeManpage(man) == 0)
        ;
    free(man);
    man = NULL;
    return 0;
}

mno *locateManpage(manlist *man, int pag){
    if(man == NULL) return NULL;
    if(man->ini == NULL) return NULL;

    mno *nlist = man->ini;

    for(int i = 1; i < pag; i++){
        nlist = nlist->next;
    }

    return nlist;
}

int browseman(manlist *man, int MODE, int *pag){
    if(man == NULL) return 2;
    if(man->ini == NULL) return 1;

    switch(MODE){
        case 1:
            if(*pag == 1) *pag = man->tamanho;
            else *pag -= 1;
            return 0;
        break;

        case 2:
            if(*pag == man->tamanho) *pag = 1;
            else *pag += 1;
            return 0;
        break;

        default:
            return 3;
        break;
    }
}

void displayManpage(manlist *man, int pag){
    if(man != NULL){
        mno *nlist = locateManpage(man, pag);
        printf("%s", nlist->mtxt);
    }
}

char *manpageList(int pag){
    char *out;
    out = (char*) calloc(5000, sizeof(char));
    switch(pag){
        case 1:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||             Antes de comecar a jogar, eh importante estar ciente de algumas informacoes essenciais:                   |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||        1- Materiais Recomendados                                                                                      |||\n");
            strcat(out, "|||              #Um lapis.                                                                                               |||\n");
            strcat(out, "|||              #Uma borracha.                                                                                           |||\n");
            strcat(out, "|||              #Um caderno ou uma folha de papel em branco.                                                             |||\n");
            strcat(out, "|||                 A recomendacao desses materiais deve-se ao fato de que o jogador nao tem conhecimento                 |||\n");
            strcat(out, "|||                  previo do ambiente em que esta, tornando necessario anotar o caminho para se orientar.               |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||        2- Objetivo do Jogo                                                                                            |||\n");
            strcat(out, "|||             O objetivo principal deste jogo eh explorar uma dungeon desconhecida, enfrentando desafios perigos,       |||\n");
            strcat(out, "|||             a fim de encontrar a [Chave] e, assim, retornar pelo [Portal].                                            |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||        3- Tutorial                                                                                                    |||\n");
            strcat(out, "|||             Movimentacao:                                                                                             |||\n");
            strcat(out, "|||                O jogador pode se locomover nas direcoes Norte, Sul, Leste e Oeste.                                    |||\n");
            strcat(out, "|||                Caso o jogador esteja em um corredor, apenas as possiveis direcoes serao exibidas.                     |||\n");
            strcat(out, "|||             Batalha:                                                                                                  |||\n");
            strcat(out, "|||                Durante um combate, o jogador tem a opcao de atacar a criatura, fugir ou usar o inventario.            |||\n");
            strcat(out, "|||             Inventario:                                                                                               |||\n");
            strcat(out, "|||                No inventario, o jogador pode mudar seus equipamentos e usar itens consumiveis.                        |||\n");
            strcat(out, "|||             Atributos:                                                                                                |||\n");
            strcat(out, "|||                 Vida: O jogador tem um limite maximo de 20 pontos de vida, mas pode aumenta-lo usando consumiveis.    |||\n");
            strcat(out, "|||                 Ataque (ATK): Melhora a chance de vencer um combate.                                                  |||\n");
            strcat(out, "|||                 Defesa (DEF): Reduz o dano que o jogador recebe.                                                      |||\n");
            strcat(out, "|||                 Agilidade (AGI): Usada para fugir e evitar armadilhas.                                                |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;

        case 2:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        1- Humanoides                                                                                                  |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||    Embora o calabouco apeiromorfico tenha origens magicas, eh possivel encontrar humanoides comuns em suas profunde-  |||\n");
			strcat(out, "|||  zas. Alguma influencia desse local fez com que essas almas tenham perdido seus rumos, geralmente patrulhando de for- |||\n");
			strcat(out, "|||  ma obsessiva o labirinto, e atacando tudo que acharem pela frente.                                                   |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    Goblin: criatura pequena de orelhas grandes e pele esverdeada ou azulada. Tambem chamados de orcs, quando crescem. |||\n");
			strcat(out, "|||  Nomades que se hospedam em cavernas e ruinas. Embora seus lares sejam temporarios, eles defendem-os ate a morte.     |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    Fuzileiro: soldado humano vestindo roupas que indicam servitude a algum lorde desconhecido. Patrulha o calabouco.  |||\n");
			strcat(out, "|||  Existem varias razoes que levam homens a realizar tarefas esdruxulas. Talvez ganancia? Fome por poder? Amor?         |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    Conspirador Demonico: humanoide que conspirou com o Abismo, seduzido por promessas de poder e levado ao calabouco. |||\n");
			strcat(out, "|||  Abismo, Caos, Tartaro. Todos nomes para um lugar maldito de onde vem os demonios que espalham desgraca pelo mundo.   |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    Assassino do Labirinto: humanoide fino e delicado, com tracos elficos. Vestia roupas furtivas e carregava uma faca.|||\n");
			strcat(out, "|||  Muito fora de seu elemento, pois assassinos sobrevivem em cortes de intriga e medo. Por que este esta aqui...?       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    Sargento-orc: goblin grande de alta patente, vestido com armadura pesada e decorado com medalhas de honra.         |||\n");
			strcat(out, "|||  Goblins crescem de maneira descomunal, e suas sociedades beligerentes tem refinamento inusitado na arte da guerra.   |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    Cultista do Caos: humanoide afetado por mutacoes bizarras. gasta sua vida dolorosa gritando blasfemias violentas.  |||\n");
			strcat(out, "|||  Ja nao se sabe mais o que essa pobre alma era, pois apos a devocao ao Culto do Caos, se perde toda identidade.       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 3:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        1- Humanoides 2                                                                                                |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    Cavaleiro da Noite: cavaleiro de elite trajado de placas negras, pintadas como o ceu noturno. Empunha uma lanca.   |||\n");
			strcat(out, "|||  A Cavalaria Noturna se dedicou a expurgar demonios do mundo. Mas, afinal, acabaram consumidos por seus inimigos.     |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    Cyborgue: hibridos de humanoide e maquina, armados com feixes de luz incinerante e recobertos de placas de ferro.  |||\n");
			strcat(out, "|||  Cyborgues sao criados por taumaturgos maleficos que apagam as mentes de pessoas moribundas e tornam-as em armas.     |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    Armadilhas: humanoides frequentemente utilizam armadilhas para proteger o calabouco. Essas incluem torretas de de- |||\n");
			strcat(out, "|||  fesa manuseadas por fuzileiros, ou coisas mais simples, como espinhos que saem das paredes, ou pendulos com laminas  |||\n");
			strcat(out, "|||  afiadas em suas extremidades.                                                                                        |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||    RUMOR: dizem que, nas profundezas do calabouco, ha uma criatura vagabunda que protege os artefatos mais ocultos    |||\n");
			strcat(out, "|||  de Apeiromorfo. Quando confrontados por ela, os sobreviventes falaram que viram seus proprios reflexos tomarem vida. |||\n");
			strcat(out, "|||  Somente aqueles que estao prontos para conquistar a si devem entrar no calabouco.                                    |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;

        case 4:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        2- Demonios                                                                                                    |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||    Criaturas nascidas do Caos, encarnacoes de mal e dor. Demonios sao aterrorizados por seus lares, e por isso, uti-  |||\n");
			strcat(out, "|||  lizam suas imortalidades para tentar constantemente fugir do Abismo. Tem poderes elementais, e sao eximios engana-   |||\n");
			strcat(out, "|||  dores. Os demonios em Apeiromorfo devem estar fugindo de casa, ou tornaram o calabouco seu proprio lar.              |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Diabrete: mais baixo dos demonios do Abismo. Magrelos e pequenos, escondem suas expressoes malignas com suas asas.|||\n");
			strcat(out, "|||  Diabretes enganam, mentem, e ludibriam mortais em busca de roubar poder, pois é preciso deste para fugir do Abismo.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Gnoll: um chacal contorcido para forma humanoide. Esses demonios sao ferozes serventes de Yi-noghu, rei do odio.  |||\n");
			strcat(out, "|||  Gnois cacam constantemente, embora nao sintam fome. Simplesmente derivam prazer de perseguir, odiar, e assassinar.   |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Eclipsiana: pequeno demonio que encarna a gula. Essas pequenas sombras aracnideas formam colmeias de milhares.    |||\n");
			strcat(out, "|||  Uma unica eclipsiana eh fraca, mas uma colmeia eh capaz de devorar humanos vivos de forma horripilantemente rapida.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Thalassagon: um demonio maior, encontrado em aguas amaldicoadas. Parecem grandes peixes com pernas de cachorros.  |||\n");
			strcat(out, "|||  O medo das aguas eh mais que justificado na presenca de um Thalassogon, pois estes vivem ate mesmo em pocas.         |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Pesadelo: um cavalo demoniaco de pele cinzenta e crina flamejante. Sao tao rapidos quanto agressivos e sadicos.   |||\n");
			strcat(out, "|||  Cavaleiros cobicam Pesadelos por serem montarias formidaveis. Os cavalos, mesmo domados, tendem a trair seus donos.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Balor: manifestacoes do Caos e das chamas, dados carne. Armados com flagelo de fogo, oculto atras de suas asas.   |||\n");
			strcat(out, "|||  Balores se deleitam na dor e no sofrimento. Por isso carregam consigo armas destinadas nao a batalha, mas a tortura. |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Armadilhas: armadilhas demoniacas consistem do aparecimento subito de almas penadas, ou de portais para o Abismo. |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 5:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        3- Bestas                                                                                                      |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Animais comuns atraidos para as profundezas do calabouco. A influencia do local torna-os insanos e agressivos.    |||\n");
			strcat(out, "|||   Eventualmente, varias dessas bestas se alteram e tornam-se criaturas fantasticas. Alguns dizem ateh que monstros do |||\n");
			strcat(out, "|||   passado distante ainda sobrevivem em Apeiromorfo...                                                                 |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Lobos, Serpentes, Ursos: animais comuns atraidos para o calabouco. Geralmente sao maiores e mais agressivos.      |||\n");
			strcat(out, "|||   Um fenomeno notado em Apeiromorfo eh a adaptacao de bestas para abater presas maiores.                              |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Ratos e Aranhas Gigantes: o apice da transmutacao apeiromorfica. Essas feras minusculas tomaram o tamanho de caes.|||\n");
			strcat(out, "|||   As aparencias deformadas desses animais demonstram um fenomeno perigoso: estao prestes a perder suas mortalidades.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Tigre Dente de Sabre: um predador enorme atestado somente em escritas ancias. De alguma forma, encontrado vivo.   |||\n");
			strcat(out, "|||   A pelagem grossa dessa besta indica que vem de um passado distante, no qual o mundo era congelado. Como sobrevive?  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Velociraptor: lagarto bipede com garras afiadas em seus pes. Geralmente caca como parte de uma manada.            |||\n");
			strcat(out, "|||   O comportamento dessas feras ancias eh similar ao de lobos modernos. Ateh suas penas lembram os pelos dos caes...   |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Caranguejo Gigante: UM CARANGUEJO GIGANTE INIMIGO! ATAQUE SEU PONTO FRACO PARA DAR DANO MASSIVO!                  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Hiena Carniceira: animal ancestral da hiena moderna. Tem a mordida mais forte de todas as feras, capaz de aleijar.|||\n");
			strcat(out, "|||   Em particular, essas bestas parecem se mesclar com chacais. Alguns temem a presenca de Yi-noghu presente nelas.     |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     RUMOR: eh possivel que feras dominem magia pela influencia do calabouco. Relatos de aventureiros que fugiram de   |||\n");
			strcat(out, "|||   Apeiromorfo indicam que um gigante ancestral pode estar devorando os descuidados usando portais. Tome muito cuidado.|||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 6:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        4- Mortos-vivos                                                                                                |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Mortos reanimados por maldicoes. Tanto humanos, quanto feras, ou ateh mesmo seres superiores podem ser afligidos  |||\n");
			strcat(out, "|||   por diversas condicoes que reanimam a carne mesmo na falta de uma alma. Mortos-vivos geralmente sao a praga de cemi-|||\n");
			strcat(out, "|||   terios e campos de batalha... talvez por isso, sejam tao comuns nas profundezas de Apeiromorfo.                     |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Zumbis: os mais tipicos mortos-vivos. Corpos frescos reanimados por uma maldicao, em busca de carne viva.         |||\n");
			strcat(out, "|||   Zumbis nao sao dotados de inteligencia, e sao feitos de diversos corpos, principalmente humanos e cachorros.        |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Esqueletos: restos mortais animados por necromancia forte. Geralmente mais poderosos do que zumbis comuns.        |||\n");
			strcat(out, "|||   Em particular, sao temidos esqueletos com arcos-longos. Dizem que a Morte era uma arqueira, afinal.                 |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Fantasma: espirito vingativo que persiste no plano mortal como sombra incorporea. Atacam a alma de suas vitimas.  |||\n");
			strcat(out, "|||   Ao contrario de mortos-vivos corporeos, fantasmas sao inteligentes e capazes de emocoes. Principalmente o rancor.   |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Dragao Esqueletico: tambem conhecido como dracolich, eh um morto vivo nascido de ritual que ressuscita dragoes.   |||\n");
			strcat(out, "|||   Por serem imortais, dragoes temem morrer mais que mortais. Talvez por isso a desmorte seja tentadora para eles...   |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Dullahan: tambem conhecido descritivamente como cavaleiro-sem-cabeca. Carrega espada feita de espinha humana.     |||\n");
			strcat(out, "|||   A decapitacao de cavaleiros eh um tabu reservado para os desgracados, tal tragedia atrai a maldicao da desmorte.    |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Bolas de Esqueletos e Paredes de Corpos: amontoado de mortos que se movem como um. Nascidos de covas malfeitas.   |||\n");
			strcat(out, "|||   A indignacao dos mortos maltratados eh suficiente para reanimar massas com o objetivo de vingar-se dos vivos.       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Armadilhas: geralmente sao simplesmente mortos-vivos a espreita para emboscar seus alvos. Foque em odores ruins.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 7:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        5- Construtos                                                                                                  |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Seres artificais construidos por taumaturgos: sabios que manipulam materia morta para que se torne como viva.     |||\n");
			strcat(out, "|||   Constructos sao tipicamente feitos de ferro, madeira, rocha, argila, ou outra substancia facilmente maleavel. Podem |||\n");
			strcat(out, "|||   ser minusculos ou massivos, e cumprir diversas funcoes... inclusive o assassinato.                                  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Gargulas Risonhas e Armaduras Animadas: construtos tradicionais feitos principalmente por taumaturgos iniciantes. |||\n");
			strcat(out, "|||   Por serem trabalhos amadores, esses construtos sao mal-programados e tendem a rebelar-se, matando seus criadores.   |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Celeron: uma maquina perdida pelo tempo, feita para a escavacao e exploracao de cavernas perigosas.               |||\n");
			strcat(out, "|||   Equipado para resolver qualquer problema em seu caminho, inclusive removendo aventureiros que o bloqueiem.          |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Yacobot: tambem conhecido como computatorium Yacobis, eh um aparelho esquecido da guarda ana: torreta automatica. |||\n");
			strcat(out, "|||   Alimentado por eletricidade, o Yacobot eh capaz de sobreviver por seculos sem supervisao taumaturgica.              |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Verme mecanico: emulando as antigas minhocas roxas, este instrumento de excavacao tem origem nas sociedades anas. |||\n");
			strcat(out, "|||   Embora tenham sido perdidos eras atras, esses vermes gigantes persistem em Apeiromorfo como uma sombra do passado.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Golens: construtos feitos de diversos materiais. Os mais tipicos sao de argila, feitos por taumaturgos poderosos. |||\n");
			strcat(out, "|||   O golem tipico tem a forca de cinquenta homens. Por isso eram mantidos como guardas-costas de seus criadores.       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Servo de Agor: construto amalgamo com tres bracos. Se rebelou para servir o Falso-Deus Agor.                      |||\n");
			strcat(out, "|||   Esse construto se mutilou e alterou para tomar a imagem de seu novo mestre. O favor de Agor os torna invenciveis.   |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 8:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        5- Construtos   2                                                                                              |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Nanobos: o magnum opus da taumaturgia ancia: minusculas maquinas, cada uma do tamanho de um grao de areia.        |||\n");
			strcat(out, "|||   Nanobos foram criados uma unica vez na historia. Nesse dia, civilizacoes foram devoradas por uma massa cinzenta.    |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Slime metalico: ser unicelular gigante de aspecto metalico. Nascido de uma slime que devorou itens taumaturgicos. |||\n");
			strcat(out, "|||   Tomando o aspecto de construto, slimes metalicos sao irritantemente resilientes, embora fluidos e flexiveis.        |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Armadilhas: armadilhas de origem construta geralmente sao velhas fortificacoes de origem ana ou taumaturgica.     |||\n");
			strcat(out, "|||   Geralmente sao compostas de defesas automaticas que ainda atuam como se estivessem em guerra, incapazes de reconhe- |||\n");
			strcat(out, "|||   cer um fim aos seus milenares conflitos, ou ateh mesmo a mudanca de ambiente.                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     RUMOR: dizem relatos que os construtos tendem as profundezas do calabouco. Uma maquina interrogada aparentemente  |||\n");
			strcat(out, "|||   segue o chamado de um tal Agor, entitulado Falso-Deus por seus servos. Se tal criatura existir e nao for um delirio |||\n");
			strcat(out, "|||   de processadores falhos, Agor eh uma especie de ser divino artificial que pode estar em Apeiromorfo.                |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 9:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        6- Monstruosidades                                                                                             |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Bestas folcloricas ou nascidas de animais alterados por magia. Comuns em Apeiromorfo devido a inexplicavel influ- |||\n");
			strcat(out, "|||   encia do local, que transforma aqueles que entram no calabouco. Monstruosidades tomam diversas formas, podendo ser  |||\n");
			strcat(out, "|||   quase-humanoides, animalescas, ou simplesmente indescritiveis.                                                      |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Slimes: seres unicelulares que formam uma subcategoria de monstruosidades. Espreitam lugares escuros para cacar.  |||\n");
			strcat(out, "|||   Slimes sao extremamente primitivas. Seus instintos se limitam a buscar alimento e se reproduzir.                    |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Harpia: monstruosidade que parece ser metade-humana e metade-ave-de-rapina. Carnivoras e agressivas.              |||\n");
			strcat(out, "|||   Harpias sao comuns em espacos abertos, principalmente regioes montanhosas. Uma em Apeiromorfo estah muito perdida.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Troll das Cavernas: monstro humanoide de pele palida e visao ultrassensivel. Deleitam-se na carne humana.         |||\n");
			strcat(out, "|||   Trolls esperam em lugares escuros e umidos por suas presas. Por isso, teme-se viajar apos o por do sol.             |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Grifos: feras inteligentes e majestosas dotadas de asas e cabeca de aguia, e corpo de leao.                       |||\n");
			strcat(out, "|||   Embora sejam famosos por poderem ser domados pelos bravos, grifos selvagens sao capazes de devorar ate ursos.       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Ent: arvore-sabia, geralmente docil, que protege as florestas e detem conhecimento de magia druidica.             |||\n");
			strcat(out, "|||   Os ents em Apeiromorfo provavelmente foram tirados de seus lugares, e tiveram muito tempo para perderem suas mentes.|||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Amorfo: slime superior que se camufla como limo nas paredes. Toma forma humanoide para devorar suas presas.       |||\n");
			strcat(out, "|||   Certos amorfos sao capazes de imitar objetos para facilitar sua furtividade: esses sao chamados de mimicos.         |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 10:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        6- Monstruosidades 2                                                                                           |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Monstro de Bill Folks: criatura deformada feita de dois corpos humanoides que se fundem no peito. Origem dubia.   |||\n");
			strcat(out, "|||   Batizado pela lenda de uma vila que foi arrasada pelo monstro, com o desmembramento e morte de dezenas em uma noite.|||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Sombras: seres classificados tanto como mortos-vivos como monstruosidades. Sufocam suas vitimas ateh a morte.     |||\n");
			strcat(out, "|||   O simples toque de uma sombra eh capaz de drenar a forca e vitalidade de alguem, alem de serem dificeis de ver.     |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Erros: coisas nascidas de falhas na propria realidade. Conhecidos como NULLs, Strings, ERRs ou outros.            |||\n");
			strcat(out, "|||   As diferentes formas de erros sao causadas por ferimentos no mundo. Alguns dizem que somente humanos causam estes.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Armadilhas: assim como as criaturas, armadilhas derivadas de monstruosidades tomam diversas formas, como chamas   |||\n");
			strcat(out, "|||   que surgem de maneira subita, o aparecimento de erros, ou ateh mesmo simples avisos psiquicos que aterrorizam aven- |||\n");
			strcat(out, "|||   tureiros viajando por Apeiromorfo.                                                                                  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     RUMOR: dizem que slimes mortas, quando perdem suas constituicoes, sao drenadas para bacias onde se acumulam e,    |||\n");
			strcat(out, "|||   possivelmente, renascem. Contam que Apeiromorfo se localiza em uma tal bacia, e que esta tomou consciencia propria  |||\n");
			strcat(out, "|||   apos tantas eras de slimes massacradas em seus entornos.                                                            |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 11:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        7- Dragoes                                                                                                     |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Criaturas majestosas de origem quase-divina. Dragoes sao seres reptilianos dotados de asas e capazes de baforar   |||\n");
			strcat(out, "|||   elementos primordiais de suas bocas. Por sua raridade, poder, e conhecimento, o ato de cacar dragoes eh considerado |||\n");
			strcat(out, "|||   uma tarefa dificil e prestigiosa, para aqueles que voltam vivos.                                                    |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Compsodrago: pequeno dragao subdesenvolvido, tambem chamado de koboldo ou pseudodragao.                           |||\n");
			strcat(out, "|||   Nao se sabe se estes sao dragoes bebes, ou simplesmente criaturas separadas. Levariam milenios para eles crescerem. |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Wyrm: falso-dragao sem membros. Rasteja pelo chao ou voa por magia. Suas mordidas sao extremamente peconhentas.   |||\n");
			strcat(out, "|||   Wyrms sao dragoes degenerados, que crescem muito mais rapidamente que seus primos reais, mas sao mais fracos.       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Dragoes-Verdadeiros: o classico dragao, representante de seu arquetipo. Encarna algum elemento e eh imortal.      |||\n");
			strcat(out, "|||   Os gelados Drogoes e eletrizantes Elektragoes sao encontrados em Apeiromorfo, geralmente deitados sobre seu tesouro.|||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     RUMOR: rugidos das profundezas e outros sinais apontam para a presenca de um aspecto da Rainha dos Dragoes em A-  |||\n");
			strcat(out, "|||   peiromorfo. A enorme Ghodirah, dotada de tres cabecas e poderes incriveis, deve ter decidido que o calabouco per-   |||\n");
			strcat(out, "|||   tence a ela. Aventureiros devem tomar cuidado e prestar atencao em subitas mudancas de gravidade no ambiente.       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 12:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        8- Elementais                                                                                                  |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Seres primordiais compostos de elementos puros, dados vida. Elementais foram fundamentais na criacao da realidade,|||\n");
			strcat(out, "|||   e persistem ateh hoje em planos elementais. As vezes, estes se perdem no mundo, geralmente tornando-se hostis por   |||\n");
			strcat(out, "|||   instinto. Ha grande variancia entre o poder de elementais, que podem ser insignificantes ou opressivos.             |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Ondina: pequeno elemental de agua. Move-se constantemente com a graca de agua fluente.                            |||\n");
			strcat(out, "|||   Embora considerados um bom pressagio de aguas limpas normalmente, as ondinas de Apeiromorfo sao imundas e amargas.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Graboid: um elemental de terra. Toma a forma de uma pedra flutuante com membros aleatorios saindo do corpo.       |||\n");
			strcat(out, "|||   Graboides sao os mais baixos dos elementais de terra. Ainda assim, sua resiliencia descomunal eh bastante notavel.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Silfide: elemental de ar que toma a forma de uma ave transparente, carregando o vento em suas asas.               |||\n");
			strcat(out, "|||   Silfides viajam em bandos, carregando os grandes ventos consigo. Talvez esses sejam a origem do vento no calabouco. |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Salamandra: elemental poderoso de fogo. Tomam a forma de repteis feitos de labaredas e brasas.                    |||\n");
			strcat(out, "|||   As salamandras foram responsaveis pela criacao do sol no passado distante, sendo que os raios deste sao suas lancas.|||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 13:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        1- Itens                                                                                                       |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Entre os varios tesouros que o jogador pode encontrar pelo calabouco, notamos as funcionalidades de itens especi- |||\n");
			strcat(out, "|||   ais com funcoes alem de poderem ser equipados:                                                                      |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Comida Preservada: comida conservada em sal e mel. Recupera uma pequena quantidade de vida.                       |||\n");
			strcat(out, "|||   O momento da alimentacao eh uma das poucas oportunidades de descanso para viajantes, peregrinos, e aventureiros.    |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Pocao de Cura: elixir com ervas aromaticas de aspecto de esmeralda. Recupera uma grande quantidade de vida.       |||\n");
			strcat(out, "|||   As amargas folhas de Estus hierophantica sao o ingrediente principal desse elixir apaziguante.                      |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Elixir Filosofal: pocao aurea, densa, e viscosa. Regenera todos os ferimentos da carne.                           |||\n");
			strcat(out, "|||   Cobicado por todos os alquimistas, a receita desse licor eh desconhecida, embora apareca raramente em ruinas.       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Essencia de Grifo: elixir alcoolico leve que se acumula no topo da garrafa. Permanentemente aumenta agilidade.    |||\n");
			strcat(out, "|||   A alquimia busca reduzir tudo aos seus componentes mais basicos, sendo a Essencia o destilado da propria alma.      |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Essencia de Tita: elixir alcoolico denso e enegrecido de odor terroso. Permanentemente aumenta ataque.            |||\n");
			strcat(out, "|||   A alquimia busca reduzir tudo aos seus componentes mais basicos, sendo a Essencia o destilado da propria alma.      |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Bencao de Dragao: elixir alcoolico que se inflama na presenca do ar. Permanentemente aumenta defesa.              |||\n");
			strcat(out, "|||   A alquimia busca reduzir tudo aos seus componentes mais basicos, sendo a Essencia o destilado da propria alma.      |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Essencia da Vida: elixir alcoolico sanguineo, que pulsa periodicamente. Permanentemente aumenta vitalidade.       |||\n");
			strcat(out, "|||   A alquimia busca reduzir tudo aos seus componentes mais basicos, sendo a Essencia o destilado da propria alma.      |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 14:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        2- Itens  2                                                                                                    |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Granada: explosivo feito de pote de ferro e argila cheio de polvora, aceso por pavio. Explode, causando dano alto.|||\n");
			strcat(out, "|||   Usado por soldados de vanguarda para destruir esquadras inimigas eficientemente, e tambem util contra monstros.     |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Bomba de Trovao: explosivo piromantico poderoso. Causa altissimo dano, mas pode ferir o usuario.                  |||\n");
			strcat(out, "|||   Dizem os mestres da guerra que dez bombas de trovao sao suficientes para incendiar um acampamento militar inteiro.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Vara Polimorfica: artefato arcano com poderes transmutativos. Converte monstros, ou a si mesmo, em um item util.  |||\n");
			strcat(out, "|||   O poder armazenado nessa varinha eh tao grotesco que um unico uso dela eh permitido, antes que desapareca em po.    |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     SCROLL: Maldicao: pergaminho com escrita cuneiforme em nanquim. Enfraquece o inimigo, reduzindo o seu ataque.     |||\n");
			strcat(out, "|||   Pergaminhos armazenam em suas palavras magia. Eles desaparecem apos o uso, a nao ser que um cajado seja utilizado.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     SCROLL: Lentidao: pergaminho coberto com runas douradas. Paralisa o inimigo, reduzindo a sua agilidade.           |||\n");
			strcat(out, "|||   Pergaminhos armazenam em suas palavras magia. Eles desaparecem apos o uso, a nao ser que um cajado seja utilizado.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     SCROLL: Agourar: pergaminho necromantico proibido. Mata uma criatura instantaneamente, mas inflige dano no mago.  |||\n");
			strcat(out, "|||   Pergaminhos armazenam em suas palavras magia. Eles desaparecem apos o uso, a nao ser que um cajado seja utilizado.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     SCROLL: HEMOMANCIA: pergaminho escrito em sangue. Inflige alto dano no inimigo, mas drena os atributos do mago.   |||\n");
			strcat(out, "|||   Pergaminhos armazenam em suas palavras magia. Eles desaparecem apos o uso, a nao ser que um cajado seja utilizado.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     SCROLL: NECROMANCIA: pergaminho palido. Use em uma sala que viu violencia para criar um item, mas tome cuidado.   |||\n");
			strcat(out, "|||   Pergaminhos armazenam em suas palavras magia. Eles desaparecem apos o uso, a nao ser que um cajado seja utilizado.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
        
        case 15:
            strcpy(out, "=============================================================================================================================\n");
            strcat(out, "|||        3- Itens  3                                                                                                    |||\n");
            strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "|||     Cajado Arcano: vara de madeira encantada. Quando nao estah equipado, pode ser usado para invocar scrolls.         |||\n");
			strcat(out, "|||   O item inicial do mago, quando invocado, pode utilizar scrolls sem que esses sejam consumidos, mas drena a sua vida.|||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Mapa Antigo: pergaminho empoeirado, com desenhos angulares sobre ele. Mostra a estrutura de Apeiromorfo.          |||\n");
			strcat(out, "|||   Quando a forma do calabouco muda, todos os mapas conectados a ele desaparecem sem tracos, preservando seu segredo.  |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Bola de Cristal: artefato grande e redondo usado por videntes. Invoque para prever a dificuldade de sala proxima. |||\n");
			strcat(out, "|||   Eh preciso de astucia e conhecimento para reconhecer os vagos sinais devolvidos pela clarividencia.                 |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Bussola Antiga: artefato de vidro empoeirado. Quando usada, magicamente aponta o caminho ateh o seu alvo.         |||\n");
			strcat(out, "|||   As areias douradas que preenchem essa bussola sao provenientes de desejos e sonhos, por isso mostram a verdade.     |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||     Outros itens podem ser encontrados pelo calabouco. Esses sao sempre equipaveis. Quando nao tiver certeza de onde  |||\n");
			strcat(out, "|||   equipar algum item, simplesmente siga os seguintes passos:                                                          |||\n");
			strcat(out, "|||          1. Se estiver nessa lista, eh item usavel.                                                                   |||\n");
			strcat(out, "|||          2. Se nao estiver, tente equipar na mao secundaria, se conseguir, eh item de mao secundaria ou primaria.     |||\n");
			strcat(out, "|||          3. Se nao conseguir, tente equipar na mao primaria, se conseguir, eh item de mao primaria.                   |||\n");
			strcat(out, "|||          4. Se nao conseguir, o item eh uma veste.                                                                    |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                        --BOA SORTE, AVENTUREIRO!--                                                    |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
			strcat(out, "|||                                                                                                                       |||\n");
            strcat(out, "=============================================================================================================================\n");
        break;
		
		default:
        break;
    }

    return out;
}
