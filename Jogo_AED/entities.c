#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playerFULL.h"


//essas funções foram colocadas em outro arquivo para fins de organização;
//os protótipos delas estão em playerFULL.h
void monsterList(int monID, MON *m){
    /*
    ATRIBUTOS DE UM PLAYER/MONSTRO
    char nome[30];      << nome, normal;
    int SCORE;          << pontuação adicionada ao jogador quando o monstro for derrotado;
    int vida_max;       << NECESSÁRIO;
    int vida;           << vida, normal;
    int pos[2];         << com certeza podem ser usados para outra coisa;
    char mao_principal, mao_secundaria, vestes; << mao_principal e mao_secundaria estão sendo usados para armazenar dano: mp = 2, ms = 8, -> 2d8 de dano;
    int atk, def, agi;  << usados normalmente mas defesa pode ser reciclada para outra coisa;
    lista inventario;   << com certeza não será usada, pelo menos em primeiro momento;

    IDS DE MONSTROS USADAS:
        --FÁCIL (10-92)--
            10
            11
            12
            20
            21
	        22
            30
            31
	        32
     	    40
	        41
     	    42
            50
	        51
            52
	        60
     	    61
	        62
     	    70
	        71
     	    72
	        80
     	    81
	        82
     	    90
	        91
	        92
        --MÉDIO (100-142)--
            100
	        101
     	    102
            110
            111
            112
            120
            121
	        122
            130
            131
	        132
            140
            141
	        142
        --DIFÍCIL (150-192)--
	        150
     	    151
	        152
            160
            161
	        162
            170
            171
	        172
            180
	        181
     	    182
            190
	        191
     	    192
    */
    switch(monID){
	case 90:
	    strcpy(m->nome,"Gnoll");
	    m->SCORE = 75;
	    m->vida = 3;
	    m->vida_max = 3;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 3;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 4;
	break;
	    
	case 82:
	    strcpy(m->nome,"Cyborgue");
	    m->SCORE = 69;
	    m->vida = 3;
	    m->vida_max = 3;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 4;
        m->mao_secundaria = 2;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 4;
	break;
	    
	case 81:
	    strcpy(m->nome,"Slime Eletrico");
	    m->SCORE = 45;
	    m->vida = 2;
	    m->vida_max = 2;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 2;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 2;
        m->def = 0;
        m->agi = 4;
	break;
	    
	case 80:
	    strcpy(m->nome,"Slime Metalico");
	    m->SCORE = 45;
	    m->vida = 2;
	    m->vida_max = 2;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 2;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 2;
	break;
	    
	case 72:
	    strcpy(m->nome,"Slime");
	    m->SCORE = 45;
	    m->vida = 2;
	    m->vida_max = 2;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 2;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 3;
        m->def = 0;
        m->agi = 3;
	break;
	    
	case 71:
	    strcpy(m->nome,"Morcego Gigante");
	    m->SCORE = 42;
	    m->vida = 2;
	    m->vida_max = 2;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 3;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 2;
        m->def = 0;
        m->agi = 4;
	break;
	case 91:
	    strcpy(m->nome,"Harpia");
	    m->SCORE = 60;
	    m->vida = 3;
	    m->vida_max = 3;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 2;
        m->mao_secundaria = 6;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 3;
	break;
	    
	case 70:
	    strcpy(m->nome,"Esqueleto de Lanceiro");
	    m->SCORE = 45;
	    m->vida = 1;
	    m->vida_max = 1;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 1;
        m->mao_secundaria = 8;
        m->vestes = 0;
        m->atk = 3;
        m->def = 0;
        m->agi = 2;
    break;
	    
	case 62:
	    strcpy(m->nome,"Golem de Madeira");
	    m->SCORE = 50;
	    m->vida = 4;
	    m->vida_max = 4;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 1;
        m->mao_secundaria = 1;
        m->vestes = 0;
        m->atk = 0;
        m->def = 0;
        m->agi = 4;
    break;
	    
	 case 61:
	    strcpy(m->nome,"Hiena Carniceira");
	    m->SCORE = 47;
	    m->vida = 2;
	    m->vida_max = 2;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 3;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 2;
    break;
	    
	case 60:
	    strcpy(m->nome,"Rato de Pedra");
	    m->SCORE = 40;
	    m->vida = 3;
	    m->vida_max = 3;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 1;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 1;
    break;
	    
	case 52:
	    strcpy(m->nome,"Escorpiao Gigante");
	    m->SCORE = 33;
	    m->vida = 1;
	    m->vida_max = 1;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 2;
        m->mao_secundaria = 6;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 1;
    break;
	    
	case 51:
		
	    strcpy(m->nome,"Caranguejo Gigante");
	    m->SCORE = 30;
	    m->vida = 1;
	    m->vida_max = 1;
	    m->pos[0] = 0;
	    m->pos[1] = 0;
	    m->mao_principal = 3;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 3;
        m->def = 0;
        m->agi = 2;
    break;
	    
	case 182: //n. Monstro de Bill Folks - dificil;
            
        strcpy(m->nome, "Monstro de Bill Folks");
        m->SCORE = 260;
        m->vida = 6;
        m->vida_max = 6;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 2;
        m->mao_secundaria = 12;
        m->vestes = 0;
        m->atk = 6;
        m->def = 0;
        m->agi = 4;
    break;

// Um garoto contava todos os dias para seus pais sobre o monstro da janela, um grande homem gordo, com um pequeno homem magro no peito.
// Ele nunca foi ouvido, até o dia da catástrofe... 42 aldeões foram mortos e desmembrados no ataque.
	case 162: //n. Amorfo - dificil;
            
        strcpy(m->nome, "Amorfo");
        m->SCORE = 200;
        m->vida = 5;
        m->vida_max = 5;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 4;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 6;
    break;

// Uma massa cinzenta que se move como um limo começa a se juntar, e forma uma grande figura humanoide.
// A lama escorre, revelando partes de ossos e crânios que se movem num emaranhado mortal. Ele te quer na coleção

	case 152: //n. Ent - dificil;
            
        strcpy(m->nome, "Ent");
        m->SCORE = 120;
        m->vida = 5;
        m->vida_max = 5;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 3;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 5;
        m->def = 0;
        m->agi = 5;
        break;

// Ents eram conhecidos como guardiões da sabedoria e da magia driade.
// Entretanto, tiveram séculos para enlouquecer em Apeiromorfo. Agora são gigantes violentos que matarão sem piedade.
	case 151: // grifo;
            
        strcpy(m->nome, "Grifo");
        m->SCORE = 105;
        m->vida = 4;
        m->vida_max = 4;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 4;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 3;
        m->def = 0;
        m->agi = 6;
    break;

// Majestosos e imponentes, os grifos eram o sonho de consumo de muitos magos antigos.
// Ainda sim, são criaturas perigosas quando não-domesticados. Geralmente caçam alces, bisões, e até ursos na natureza.
	    
	case 150: // Akon-Haie;
            
        strcpy(m->nome, "Akon-Haie");
        m->SCORE = 100;
        m->vida = 4;
        m->vida_max = 4;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 3;
        m->mao_secundaria = 6;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 4;
    break;

// É uma cobra gigante que costumava habitar regiões tropicais.
// Essa espécie em particular foi extinta há centenas de anos...

	case 92: //n. troll das cavernas - medio;
            
        strcpy(m->nome, "Troll das Cavernas");
        m->SCORE = 69;
        m->vida = 3;
        m->vida_max = 3;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 3;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 3;
    break;

// Um gigantesco humanóide de pele pálida e feições tortas e distorcidas;
// Conhecido como devorador de homens, os trolls eram os motivos de aldeões não viajarem à noite.
	    
	case 181: //n. Golem de ferro - dificil ;
            
        strcpy(m->nome, "Golem de ferro");
        m->SCORE = 230;
        m->vida = 9;
        m->vida_max = 9;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 4;
        m->mao_secundaria = 1;
        m->vestes = 0;
        m->atk = 8;
        m->def = 0;
        m->agi = 0;
    break;

// É o ápice da taumaturgia antiga, é o mais poderoso dos golens, impenetrável e forte como 100 homens.
// Era usado como um demolidor de muralhas e aplanainador de terreno nas grandes guerras entre impérios.
	    
	case 172: //n. Servo de Agor - dificil ;
            
        strcpy(m->nome, "Servo de Agor");
        m->SCORE = 230;
        m->vida = 4;
        m->vida_max = 4;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 3;
        m->mao_secundaria = 8;
        m->vestes = 0;
        m->atk = 7;
        m->def = 0;
        m->agi = 5;
    break;

// Um constructo de 3 braços que serve ao Falso-Deus Agor. Quando Agor caiu no esquecimento, seus servos cairam com ele
// Agora resta apenas a sombra de suas existências nas profundezas do Apeiromorfo.
	    
	case 102: //n. Golem - medio;
            
        strcpy(m->nome, "Golem");
        m->SCORE = 78;
        m->vida = 5;
        m->vida_max = 5;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 2;
        m->mao_secundaria = 1;
        m->vestes = 0;
        m->atk = 5;
        m->def = 0;
        m->agi = 0;
    break;

// Moldado pelas mãos de antigos magos de Apeiromorfo, os golens são os maiores dentre todos os constructos.
// Com a força de 50 homens, são openentes formidáveis para qualquer guerreiro experiênte.
	    
	case 122: //n. Verme mecanico - medio ;
            
        strcpy(m->nome, "Verme Mecanico");
        m->SCORE = 88;
        m->vida = 3;
        m->vida_max = 3;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 2;
        m->mao_secundaria = 6;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 6;
    break;

// É um grande constructo dos anões que, a princípio, tinha a função de escavar as profundezas buscando minérios.
// A sombra de tais máquinas antigas ainda persiste em Apeiromorfo, mesmo estas já terem se perdido há séculos.
	    
	case 101: //n. Yacobot - Medio;
            
        strcpy(m->nome, "Yacobot");
        m->SCORE = 76;
        m->vida = 1;
        m->vida_max = 1;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 1;
        m->mao_secundaria = 8;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = -1;
    break;

// Um esquecido aparelho da guarda-anã, o Yacob Computatorium é uma torreta elétrica fixa, que
// atacará qualquer criatura não autorizada que entrar em seu alcance.
	    
	case 42: // celeron - facil;
            
        strcpy(m->nome, "Celeron");
        m->SCORE = 29;
        m->vida = 2;
        m->vida_max = 2;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 3;
        m->mao_secundaria = 3;
        m->vestes = 0;
        m->atk = 3;
        m->def = 0;
        m->agi = 2;
    break;

// Uma máquina perdida pelo tempo, o celeron é um antigo aparelho de exploração de cavernas perigosas,
// e é equipado para conseguir resolver qualquer problema que encontre em seu caminho.
	    
	case 132:// um dragão menos desenvolivdo 
	    strcpy(m->nome, "Wyrm");
        m->SCORE = 87;
        m->vida = 4;
        m->vida_max = 4;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 3;
        m->mao_secundaria = 6;
        m->vestes = 0;
        m->atk = 4;
        m->def = 0;
        m->agi = 2;
    break;
	    
	case 41:// "Dragoes bebes"
	    strcpy(m->nome, "Compsodragus");
        m->SCORE = 32;
        m->vida = 2;
        m->vida_max = 2;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 2;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 3;
        m->def = 0;
        m->agi = 3;
    break;
	    
	case 192://Dragão de Raio
	    strcpy(m->nome, "Elektragon");
        m->SCORE = 385;
        m->vida = 8;
        m->vida_max = 8;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 4;
        m->mao_secundaria = 6;
        m->vestes = 0;
        m->atk = 8;
        m->def = 0;
        m->agi = 5;
    break;
	    
	case 191:// Dragão de Gelo
	    strcpy(m->nome, "Drogon");
        m->SCORE = 385;
        m->vida = 8;
        m->vida_max = 8;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 6;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 5;
        m->def = 0;
        m->agi = 8;
    break;
	    
	case 40:// Elementais de Vento
	    strcpy(m->nome, "Bando de Silfides");
        m->SCORE = 19;
        m->vida = 2;
        m->vida_max = 2;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 2;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 3;
        m->def = 0;
        m->agi = 3;
	break;

	case 32: // Uma Pedra com Pernas
	    strcpy(m->nome, "Graboid");
        m->SCORE = 17;
        m->vida = 2;
        m->vida_max = 2;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 3;
        m->mao_secundaria = 1;
        m->vestes = 0;
        m->atk = 2;
        m->def = 0;
        m->agi = 1;
    break;
	    
	case 142: // Reptil Flamejante!!!!
    	strcpy(m->nome, "Salamandra de Fogo");
        m->SCORE = 120;
        m->vida = 6;
        m->vida_max = 6;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 2;
        m->mao_secundaria = 8;
        m->vestes = 0;
        m->atk = 6;
        m->def = 0;
        m->agi = 5;
    break;
	    
	case 22: // Elemental de onda
    	strcpy(m->nome, "Ondina");
        m->SCORE = 7;
        m->vida = 2;
        m->vida_max = 2;
        m->pos[0] = 0;
        m->pos[1] = 0;
        m->mao_principal = 2;
        m->mao_secundaria = 4;
        m->vestes = 0;
        m->atk = 3;
        m->def = 0;
        m->agi = 2;
    break;
	    
        case 10:    //Goblin;
            strcpy(m->nome, "Goblin");
            m->SCORE = 10;
            m->vida = 1;
            m->vida_max = 1;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 1;
            m->mao_secundaria = 6;
            m->vestes = 0;
            m->atk = 2;
            m->def = 0;
            m->agi = 3;
        break;
//        Uma pequena criatura de orelhas grandes e proporções magras, geralmente de pele esverdeada ou azulada. Fracos e comuns em espaços escuros.
//        Embora sejam nômades que se hospedam em lugares como cavernas e ruínas, goblins defendem seus lares temporários até a morte.

        case 20:    //Fuzileiro;
            strcpy(m->nome, "Fuzileiro");
            m->SCORE = 10;
            m->vida = 2;
            m->vida_max = 2;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 1;
            m->mao_secundaria = 12;
            m->vestes = 0;
            m->atk = 1;
            m->def = 0;
            m->agi = 2;
        break;
//        Soldado humano, servente a algum lorde desconhecido. Inusitadamente patrulham os corredores do calabouço apeiromorfo.
//        Várias razões existem que levam homens a realizar tarefas esdrúxulas. Talvez fome por poder? Ganância? Amor?

        case 100:    //Assassino do Labirinto;
            strcpy(m->nome, "Assassino do Labirinto");
            m->SCORE = 95;
            m->vida = 4;
            m->vida_max = 4;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 3;
            m->mao_secundaria = 6;
            m->vestes = 0;
            m->atk = 3;
            m->def = 0;
            m->agi = 5;
        break;
//        Humanoide fino e delicado, identificado como elfo. Esse foi encontrado com vestimentas típicas de assassinos profissionais.
//        Absolutamente fora de seu elemento, pois assassinos vivem em cortes com intriga e desconfiança. Por que um estaria tão isolado?

        case 110:    //Sargento-Orc;
            strcpy(m->nome, "Sargento-Orc");
            m->SCORE = 75;
            m->vida = 3;
            m->vida_max = 3;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 2;
            m->mao_secundaria = 6;
            m->vestes = 0;
            m->atk = 5;
            m->def = 0;
            m->agi = 2;
        break;
//        Orc trajado com armadura pesada decorada com medalhas de honra. Equipado com machado de cabo longo.
//        As sociedades beligerentes dos vários clãs de orcs alcançam um grau único de refinamento na arte da guerra.

        case 160:    //Cultista do Caos;
            strcpy(m->nome, "Cultista do Caos");
            m->SCORE = 125;
            m->vida = 5;
            m->vida_max = 5;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 1;
            m->mao_secundaria = 8;
            m->vestes = 0;
            m->atk = 5;
            m->def = 0;
            m->agi = 6;
        break;
//        Humanoide afetado por mutações bizarras. Usava suas incontáveis bocas para gritar cacofonias e blasfêmias em sua dolorosa vida.
//        Já não se sabe o que essa maldita alma era, pois, após a dedicação ao Culto do Caos, é perdida a identidade e o desejo de viver.


        case 170:    //Cavaleiro da Noite;
            strcpy(m->nome, "Cavaleiro da Noite");
            m->SCORE = 200;
            m->vida = 4;
            m->vida_max = 4;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 2;
            m->mao_secundaria = 8;
            m->vestes = 0;
            m->atk = 6;
            m->def = 0;
            m->agi = 3;
        break;
//        Cavaleiro de elite trajado em placas negras tingidas com as estrelas e a lua. Montava um cavalo negro e empunhava uma lança.
//        A Cavalaria Noturna era uma ordem de inquisidores dedicada à expurgação de demônios. Afinal, foram consumidos por seus inimigos.

        case 50:    //Diabrete;
            strcpy(m->nome, "Diabrete");
            m->SCORE = 15;
            m->vida = 2;
            m->vida_max = 2;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 1;
            m->mao_secundaria = 8;
            m->vestes = 0;
            m->atk = 2;
            m->def = 0;
            m->agi = 2;
        break;
//        Mais baixo dos demônios do Abismo. Altos mas magrelos, portados de garras afiadas e expressões maléficas, ocultas por asas faciais.
//        Diabretes enganam, mentem, e ludibriam mortais em busca de poder, pois é preciso deste para fugir do Abismo.

        case 30:    //Conspirador Demonico;
            strcpy(m->nome, "Conspirador Demonico");
            m->SCORE = 20;
            m->vida = 2;
            m->vida_max = 2;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 1;
            m->mao_secundaria = 10;
            m->vestes = 0;
            m->atk = 2;
            m->def = 0;
            m->agi = 3;
        break;
//        Humano que conspirou com o Abismo. Parecia perdido quando foi encontrado nas profundezas do calabouço.
//        "Inevitavelmente, pactos com criaturas malignas levam à desgraça," uma máxima carregada pelos mais sensatos.

        case 120:    //Colmeia de Eclipsianas;
            strcpy(m->nome, "Colmeia de Eclipsianas");
            m->SCORE = 90;
            m->vida = 2;
            m->vida_max = 2;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 4;
            m->mao_secundaria = 4;
            m->vestes = 0;
            m->atk = 4;
            m->def = 0;
            m->agi = 1;
        break;
//        Colmeia de eclipsianas, criaturas semelhantes às sombras de aranhas. Camuflam-se na escuridão, à espreita.
//        Uma única eclipsiana é fraca quando sozinha. Juntas, elas encarnam a fome, sendo capazes de devorar homens vivos.

        case 130:    //Thalassagon;
            strcpy(m->nome, "Thalassagon");
            m->SCORE = 105;
            m->vida = 4;
            m->vida_max = 4;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 6;
            m->mao_secundaria = 3;
            m->vestes = 0;
            m->atk = 4;
            m->def = 0;
            m->agi = 5;
        break;
//        Demônio maior das águas. Thalassagões são grandes peixes que podem ser encontrados em poças de água no calabouço.
//        O medo das águas é mais do que justificado quanto a presença de um thalassogon é verificada. Até mesmo rasas manchas são perigosas.

        case 161:    //Pesadelo;
            strcpy(m->nome, "Pesadelo");
            m->SCORE = 210;
            m->vida = 4;
            m->vida_max = 4;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 1;
            m->mao_secundaria = 6;
            m->vestes = 0;
            m->atk = 7;
            m->def = 0;
            m->agi = 8;
        break;
//        Cavalo demoníaco marcado pela pelagem cinzenta e crina em labaredas. Possuem temperamento agressivo e são dotados de alta velocidade.
//        Pesadelos são cobiçados por cavaleiros por serem as mais formidáveis montarias. Mal sabem que o leal cavalo planeja traí-los no pior dos momentos.

        case 190:    //Balor;
            strcpy(m->nome, "Balor");
            m->SCORE = 250;
            m->vida = 6;
            m->vida_max = 6;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 2;
            m->mao_secundaria = 8;
            m->vestes = 0;
            m->atk = 7;
            m->def = 0;
            m->agi = 3;
        break;
//        Manifestações do caos e das chamas, dados carne. Armados com um tradicional flagelo flamejante, oculto por trás de suas asas. 
//        Balores se deleitam no sofrimento, por isso carregam consigo algo destinado não para a batalha, mas para a tortura.

        case 21:// Facil
            strcpy(m->nome, "Lobo");
            m->SCORE = 10;
            m->vida = 2;
	        m->vida_max = 2;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 1;
            m->mao_secundaria = 4;
            m->vestes = 0;
            m->atk = 1;
            m->def = 0;
            m->agi = 3;
        break;

	    case 11:// facil
            strcpy(m->nome, "Serpente");
            m->SCORE = 16;
            m->vida = 1;
	        m->vida_max = 1;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 2;
            m->mao_secundaria = 2;
            m->vestes = 0;
            m->atk = 1;
            m->def = 0;
            m->agi = 1;
        break;

	    case 121:// Medio
            strcpy(m->nome, "Urso Marrom");
            m->SCORE = 67;
            m->vida = 3;
	        m->vida_max = 3;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 2;
            m->mao_secundaria = 6;
            m->vestes = 0;
            m->atk = 5;
            m->def = 0;
            m->agi = 3;
        break;

	    case 131://Medio
            strcpy(m->nome, "Tigre Dente de Sabre");
            m->SCORE = 98;
            m->vida = 2;
	        m->vida_max =2;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 4;
            m->mao_secundaria = 4;
            m->vestes = 0;
            m->atk = 4;
            m->def = 0;
            m->agi = 6;
        break;

	    case 111:// Medio
            strcpy(m->nome, "Aranha Gigante");
            m->SCORE = 67;
            m->vida = 3;
	        m->vida_max =3;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 3;
            m->mao_secundaria = 4;
            m->vestes = 0;
            m->atk = 5;
            m->def = 0;
            m->agi = 3;
        break;

	    case 140:// Medio
            strcpy(m->nome, "Velociraptor");
            m->SCORE = 76;
            m->vida = 2;
	        m->vida_max =2;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal =5;
            m->mao_secundaria = 2;
            m->vestes = 0;
            m->atk = 4;
            m->def = 0;
            m->agi = 6;
        break;


	    case 31: // Facil
            strcpy(m->nome, "Zumbi");
            m->SCORE = 17;
            m->vida = 2;
	        m->vida_max = 2;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 1;
            m->mao_secundaria = 8;
            m->vestes = 0;
            m->atk = 3;
            m->def = 0;
            m->agi = 1;
        break;
//	Mortos-vivos comuns, vindos de humanoides amaldiçoados. Esse, em particular, era um aventureiro que falhou ao desbravar o calabouço.
//	Comuns em regiões de praga, que atraem os maus presságios e as maldições. Por isso, é tradicional queimar os corpos nessas situações.

	    case 12: // Facil
            strcpy(m->nome, "Cachorro Zumbi");
            m->SCORE = 5;
            m->vida = 1;
	        m->vida_max =1;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 2;
            m->mao_secundaria = 4;
            m->vestes = 0;
            m->atk = 1;
            m->def = 0;
            m->agi = 1;
        break;
//	Mortos-vivos comuns, vindos de cachorros amaldiçoados. Talvez um animal selvagem, ou o companheiro de algum bravo guerreiro.
//	Gemem de dor para atrair os descuidados. Esses monstros parecem ser mais inteligentes do que logicamente deveriam.

	    case 141: //Medio
            strcpy(m->nome, "Arqueiro Longo Esqueletico");
            m->SCORE = 58;
            m->vida = 2;
	        m->vida_max = 2;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 2;
            m->mao_secundaria = 8;
            m->vestes = 0;
            m->atk = 6;
            m->def = 0;
            m->agi = 4;
        break;
//	Morto-vivo ósseo, antes um arqueiro em vida. Seu braço direito é mais longo que o esquerdo, adaptado aos movimentos de um arco.
//	Dizem que a Morte é uma arqueira. Ceifar almas manualmente deve ser difícil. Independentemente, esse monstro herdou suas habilidades.

	    case 112: //Medio
            strcpy(m->nome, "Fantasma");
            m->SCORE = 80;
            m->vida = 3;
	        m->vida_max =3;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 2;
            m->mao_secundaria = 6;
            m->vestes = 0;
            m->atk = 3;
            m->def = 0;
            m->agi = 5;
        break;
//	Espectros perpétuos motivados pela vingança. Nascidos quando uma alma morre por traição.
//	Pelo aspecto de suas rasgadas vestes, era um simples civil arrastado para dentro do calabouço amaldiçoado.

	    case 180: //Dificil
            strcpy(m->nome, "Dragao Esqueletico");
            m->SCORE = 205;
            m->vida = 6;
	        m->vida_max = 6;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 2;
            m->mao_secundaria = 12;
            m->vestes = 0;
            m->atk = 6;
            m->def = 0;
            m->agi = 4;
        break;
//	Também conhecido como draco-lich, são mortos-vivos nascidos de um ritual que ressuscita um dragão moribundo.
//	Os dragões que escolhem esse caminho são desesperados, ou talvez sedentos por poder. A vida após a morte é tentadora para tais criaturas.

	    case 171: //Dificil
            strcpy(m->nome, "Dullahan");
            m->SCORE = 185;
            m->vida = 4;
	        m->vida_max = 4;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 3;
            m->mao_secundaria = 8;
            m->vestes = 0;
            m->atk = 5;
            m->def = 0;
            m->agi = 6;
        break;
//	Sombra de um cavaleiro decapitado, também chamado, descritivamente, de Cavaleiro-Sem-Cabeça. Portado de uma espada longa, feita de uma espinha.
//	Esses guerreiros são, por motivo de tradição, decapitados somente ao morrerem em desgraça. Tal maldição facilmente leva à vida apos a morte.







                        /*
                        
                        
                        BOSSES:
                        
                        
                        */


        
	    case 200: //Rainha Ghodirah
	    case 201: //Rainha Ghodirah
	    	    strcpy(m->nome, "Rainha Ghodirah");
	            m->SCORE = 2000;
	            m->vida = 7;
		    m->vida_max = 7;
	            m->pos[0] = 0;
	            m->pos[1] = 0;
	            m->mao_principal = 2;
	            m->mao_secundaria = 8;
	            m->vestes = 0;
	            m->atk = 6;
	            m->def = 0;
	            m->agi = 0;
	    break;
	    
	    case 202: //O IMITADOR
	    case 203: //O IMITADOR
	    	    strcpy(m->nome, "O Imitador");
	            m->SCORE = 2000;
	            m->vida = 6;
		    m->vida_max = 6;
	            m->pos[0] = 0;
	            m->pos[1] = 0;
	            m->mao_principal = 4;
	            m->mao_secundaria = 4;
	            m->vestes = 0;
	            m->atk = 0;
	            m->def = 3;
	            m->agi = 0;
	    break;
	    
	    case 204: //AGOR
	    case 205: //AGOR
		    strcpy(m->nome,"AGOR");
		    m->SCORE = 2000;
		    m->vida = 5;
		    m->vida_max = 5;
		    m->pos[0] = 0;
		    m->pos[1] = 0;
		    m->mao_principal = 3;
	            m->mao_secundaria = 6;
	            m->vestes = 0;
	            m->atk = 4;
	            m->def = 0;
	            m->agi = 0;
	    break;
	    
	    case 206: //TREX
	    case 207: //TREX
		    strcpy(m->nome,"T-Rex");
		    m->SCORE = 2000;
		    m->vida = 6;
		    m->vida_max = 6;
		    m->pos[0] = 0;
		    m->pos[1] = 0;
		    m->mao_principal = 3;
	            m->mao_secundaria = 6;
	            m->vestes = 0;
	            m->atk = 6;
	            m->def = 0;
	            m->agi = 0;
	break;
	    
	    case 208: //BLOB
	    case 209: //BLOB
	            strcpy(m->nome, "B.L.O.B.");
	            m->SCORE = 2000;
	            m->vida = 6;
		    m->vida_max = 6;
	            m->pos[0] = 0;
	            m->pos[1] = 0;
	            m->mao_principal = 2;
	            m->mao_secundaria = 4;
	            m->vestes = 0;
	            m->atk = 5;
	            m->def = 0;
	            m->agi = 0;
        break;








        default:
            strcpy(m->nome, "NULL");
            m->SCORE = 0;
            m->vida = 0;
            m->vida_max = 0;
            m->pos[0] = 0;
            m->pos[1] = 0;
            m->mao_principal = 0;
            m->mao_secundaria = 1;
            m->vestes = 0;
            m->atk = 0;
            m->def = 0;
            m->agi = 0;
        break;
    }
}















void trapList(int trapID, TRAP *t){
    /*
    ATRIBUTOS DE UM PLAYER/MONSTRO
    char nome[30];      << nome, normal;
    int SCORE;          << pontuação adicionada ao jogador quando a armadilha for passada;
    int vida_max;       << NECESSÁRIO;
    int vida;           << vida, normal;
    int pos[2];         << com certeza podem ser usados para outra coisa;
    char mao_principal, mao_secundaria, vestes; << mao_principal e mao_secundaria estão sendo usados para armazenar dano: mp = 2, ms = 8, -> 2d8 de dano;
    int atk, def, agi;  << def é a DC da armadilha (valor necessário para passá-la), atk e agi definem qual atributo é testado para passar a armadilha;
    lista inventario;   << com certeza não será usada, pelo menos em primeiro momento;

    IDS DE ARMADILHAS USADAS:
        --FÁCIL (13-95)--
            13
            14
	        15
            23
	        24
            25
            33
	        34
     	    35
	        43
	        44
     	    45
     	    53
	        54
            55
	        63
     	    64
	        65
            73
	        74
            75
            83
	        84
     	    85
            93
     	    94
	        95
        --MÉDIO (103-145)--
            103
	        104
       	    105
            113
	        114
            115
            123
	        124
     	    125
            133
	        134
            135
	        143
            144
     	    145
        --DIFÍCIL (153-195)--
            153
	        154
     	    155
            163
	        164
     	    165
            173
	        174
	        175
            183
	        184
     	    185
	        193
     	    194
            195
            
    */
    switch(trapID){
	case 75:

            strcpy(t->nome, "Acidos fluem da parede");
            t->SCORE = 49;
            t->vida = 3;
            t->vida_max = 3;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 1;
            t->def = 16;
            t->agi = 0;
        break;
	    
	case 74:

            strcpy(t->nome, "Um bode corre em sua direcao");
            t->SCORE = 40;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 1;
            t->def = 13;
            t->agi = 0;
        break;
	    
	case 73:

            strcpy(t->nome, "Uma gosma verde te prende");
            t->SCORE = 43;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 2;
            t->vestes = 0;
            t->atk = 1;
            t->def = 12;
            t->agi = 0;
        break;
	    
	case 83:

            strcpy(t->nome, "Pedras voam em sua direcao!");
            t->SCORE = 52;
            t->vida = 3;
            t->vida_max = 3;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 3;
            t->vestes = 0;
            t->atk = 0;
            t->def = 14;
            t->agi = 1;
        break;
	    
	case 84:

            strcpy(t->nome, "P -> Q");// ;-;
            t->SCORE = 60;
            t->vida = 1;
            t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 16;
            t->agi = 1;
        break;
	    
	case 65:

            strcpy(t->nome, "Hiena tenta te morder");
            t->SCORE = 67;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 0;
            t->def = 13;
            t->agi = 1;
        break;
	    
	case 64:

            strcpy(t->nome, "A sala esta congelando!");
            t->SCORE = 54;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 0;
            t->def = 14;
            t->agi = 1;
        break;
	    
	case 55:

            strcpy(t->nome, "Errrr$$###@*****```ooooo"); // apenas para dar medo aos jogadores
            t->SCORE = 0;
            t->vida = 0;
            t->vida_max = 0;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 0;
            t->mao_secundaria = 1;
            t->vestes = 0;
            t->atk = 1;
            t->def = 0;
            t->agi = 0;
        break;
	    
	case 54:

            strcpy(t->nome, "Teias saem da parede");
            t->SCORE = 50;
            t->vida = 1;
            t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 2;
            t->vestes = 0;
            t->atk = 1;
            t->def = 16;
            t->agi = 0;
        break;
	    
	case 45:

            strcpy(t->nome, "Que sorte, nada acontece");
            t->SCORE = 30;
            t->vida = 0;
            t->vida_max = 0;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 0;
            t->mao_secundaria = 1;
            t->vestes = 0;
            t->atk = 1;
            t->def = 0;
            t->agi = 0;
        break;
	    
	case 85:

            strcpy(t->nome, "Placas tentam te prender");
            t->SCORE = 70;
            t->vida = 3;
            t->vida_max = 3;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 1;
            t->def = 13;
            t->agi = 0;
        break;
	    
	case 94:

            strcpy(t->nome, "Esta chovendo fogo!");
            t->SCORE = 61;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 1;
            t->def = 12;
            t->agi = 0;
        break;
	    
	case 144:

            strcpy(t->nome, "Estacas de gelo caem do teto");
            t->SCORE = 84;
            t->vida = 1;
            t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 4;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 0;
            t->def = 15;
            t->agi = 1;
        break;
	    
	case 194:

            strcpy(t->nome, "ERRE E TOME 30 DE DANO"); // Sim Apenas isso mesmo
            t->SCORE = 230;
            t->vida = 1;
            t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 30;
            t->mao_secundaria = 1;
            t->vestes = 0;
            t->atk = 1;
            t->def = 16;// Qual sera em ?, Apenas quem leu o codigo sabe HEHE e claro aquele que ja passou pela armadilha
            t->agi = 1;
        break;
	    
	case 193:

            strcpy(t->nome, "Sombras tentam te matar");
            t->SCORE = 167;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 1;
            t->def = 16;
            t->agi = 0;
        break;
	    
	case 174:

            strcpy(t->nome, "Labaredas surgem do chao");
            t->SCORE = 110;
            t->vida = 3;
            t->vida_max = 3;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 0;
            t->def = 16;
            t->agi = 1;
        break;
	    
	case 175:

            strcpy(t->nome, "CORRA, NAO HA COMO EXPLICAR");
            t->SCORE = 114;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 8;
            t->vestes = 0;
            t->atk = 0;
            t->def = 15;
            t->agi = 1;
        break;
	    
	case 185:

            strcpy(t->nome, "O CHAO EH LAVA!");
            t->SCORE = 182;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 14;
            t->agi = 1;
        break;
	    
	case 145:

            strcpy(t->nome, "Laminhas voam em sua direcao");
            t->SCORE = 100;
            t->vida = 1;
            t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 15;
            t->agi = 1;
        break;
	    
	case 165:

            strcpy(t->nome, "UM DRAGAO VEM EM SUA DIRECAO");
            t->SCORE = 130;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 8;
            t->vestes = 0;
            t->atk = 0;
            t->def = 13;
            t->agi = 1;
        break;
	    
	case 93:

            strcpy(t->nome, "StRiNg MaLuCa TeNtA tE MaTaR");
            t->SCORE = 78;
            t->vida = 1;
            t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 7; // a string Maluca da 7 de dano por causa do /0
            t->mao_secundaria = 1;
            t->vestes = 0;
            t->atk = 0;
            t->def = 11;
            t->agi = 1;
        break;
	    
	case 155:

            strcpy(t->nome, "Uma estatua tenta de pegar!");
            t->SCORE = 114;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 1;
            t->def = 14;
            t->agi = 0;
        break;
	    
	case 143: //Monstro enjaulada

            strcpy(t->nome, "Um monstro enjaulado fugiu");
            t->SCORE = 88;
            t->vida = 3;
            t->vida_max = 3;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 1;
            t->def = 13;
            t->agi = 0;
        break;
    
// Eh uma armadilha simples e de facil manutencao. Classica e previsível? Talvez... Mas mortal.
// Um poco de jacares eh a forma mais eficiente de desmembrar convidados indesejados em castelos, fortalezas e masmorras.
	    
	case 43: //Poço de jacarés

            strcpy(t->nome, "Um poco com jacares se abre");
            t->SCORE = 40;
            t->vida = 1;
            t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 1;
            t->def = 13;
            t->agi = 0;
        break;
    
// Eh uma armadilha simples e de facil manutencao. Classica e previsível? Talvez... Mas mortal.
// Um poco de jacares eh a forma mais eficiente de desmembrar convidados indesejados em castelos, fortalezas e masmorras.

	case 25: //Ratos gigantes

            strcpy(t->nome, "Ratos gigantes surgem do chao");
            t->SCORE = 35;
            t->vida = 1;
            t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 1;
            t->def = 10;
            t->agi = 0;
        break;
    
// De não tão pequenos buracos nas paredes começam a emergir roedores imensos evoluidos especialmente para habitar Apeiromorfo
// Uma possível explicação para seu tamanho é a necessidade de abater criaturas maiores para se alimentar de seus cadaveres
	case 24: //Monstro de lago

            strcpy(t->nome, "Monstro de lago");
            t->SCORE = 20;
            t->vida = 3;
            t->vida_max = 3;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 1;
            t->def = 13;
            t->agi = 0;
        break;
    
// Um corredor repleto de vinhas do chão ao teto guarda um segredo obscuro.
// A falta de nutrientes forçou essas plantas a evoluirem para fixiar suas raízes na carne.
	case 15: //Planta carnívora

            strcpy(t->nome, "Uma planta carnivora brotou");
            t->SCORE = 17;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 1;
            t->def = 11;
            t->agi = 0;
        break;
    
// Um corredor repleto de vinhas do chão ao teto guarda um segredo obscuro.
// A falta de nutrientes forçou essas plantas a evoluirem para fixiar suas raízes na carne.
	    
	case 135: //Incinerador

            strcpy(t->nome, "Incinerador");
            t->SCORE = 84;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 10;
            t->agi = 1;
        break;
    
// Um antigo mecanismo de proteção que, simplesmente, cozinha os invasores em suas armaduras.
// Eram usados em salas-fortes dos antigos reinos anões. Porque haveria um em Apeiromorfo?

	case 125: //(Sala de treinamento abandonada) ERRO
		// Torretas Atiram em Você CORRETO

            strcpy(t->nome, "Torretas atiram em voce!");
            t->SCORE = 67;
            t->vida = 4;
            t->vida_max = 4;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 14;
            t->agi = 1;
        break;
    
// É uma sala com escudos de metal espalhados pelo chão e pelas paredes.
// Torretas mecânicas surgem e comaçam a disparar contra quem estiver na sala, para simular um combate real.

	case 154: //Enxame de nanobôs

            strcpy(t->nome, "Enxame de nanobos");
            t->SCORE = 135;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 0;
            t->def = 17;
            t->agi = 1;
        break;
    
//  Fino pó acinzentado, que se move de maneira inusitada no vento. Emitem um som quase imperceptível. 
//  Nanobôs são o magnum opus dos taumaturgos. Porém, raramente ficam sob seus controles, consumindo tudo em uma simples missão de auto-replicação.
	    
	case 115: //Sala da Gárgula risonha

            strcpy(t->nome, "A gargula de pedra da risadas");
            t->SCORE = 60;
            t->vida = 2;
            t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 4;
            t->mao_secundaria = 2;
            t->vestes = 0;
            t->atk = 1;
            t->def = 13;
            t->agi = 0;
        break;
    
// Um espírito maligno permeia uma estátua de pedra de uma antiga catedral.
// Ele gosta de brincar os vivos, e gosta ainda mais de brincar com seus cadáveres.
	    
	    case 105: //Corredor de Armaduras

            strcpy(t->nome, "Corredor de armaduras");
            t->SCORE = 50;
            t->vida = 3;
            t->vida_max = 3;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 14;
            t->agi = 1;
        break;
    
// É um corredor de pedra decorado com as armaduras de antigos guerreiros lendários.
// Alguns morrerem com glória, outros tiveram seus espíritos acorrentados ao ferro e sangue.
	    
	case 184:
            strcpy(t->nome, "O Caos tenta te imolar!");
            t->SCORE = 0;
            t->vida = 2;
	        t->vida_max = 2;
            t->pos[0] = 1;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 16;
            t->agi = 1;
        break;
	    
	case 173:
            strcpy(t->nome, "O Caos tenta te sequestrar!");
            t->SCORE = 0;
            t->vida = 3;
	        t->vida_max = 3;
            t->pos[0] = 1;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 1;
            t->def = 14;
            t->agi = 0;
        break;
	    
	case 164:
            strcpy(t->nome, "Explosivos desmoronam o teto");
            t->SCORE = 0;
            t->vida = 1;
		    t->vida_max = 1;
            t->pos[0] = 1;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 8;
            t->vestes = 0;
            t->atk = 1;
            t->def = 15;
            t->agi = 0;
        break;
	    
	case 134:
            strcpy(t->nome, "Uma torreta vigia o corredor");
            t->SCORE = 0;
            t->vida = 5;
		    t->vida_max = 5;
            t->pos[0] = 1;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 13;
            t->agi = 1;
        break;
	    
	case 124:
            strcpy(t->nome, "Um portal infernal! Feche-o");
            t->SCORE = 0;
            t->vida = 3;
		    t->vida_max = 3;
            t->pos[0] = 1;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 10;
            t->vestes = 0;
            t->atk = 1;
            t->def = 15;
            t->agi = 0;
        break;
	
	case 114:
            strcpy(t->nome, "A sala conflagra-se!");
            t->SCORE = 0;
            t->vida = 3;
		    t->vida_max = 3;
            t->pos[0] = 1;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 8;
            t->vestes = 0;
            t->atk = 0;
            t->def = 15;
            t->agi = 1;
        break;
	    
	case 104:
            strcpy(t->nome, "Minas terrestres!!");
            t->SCORE = 0;
            t->vida = 1;
		    t->vida_max = 1;
            t->pos[0] = 1;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 8;
            t->vestes = 0;
            t->atk = 0;
            t->def = 14;
            t->agi = 1;
        break;
	    
	case 53:
            strcpy(t->nome, "Manada de almas penadas");
            t->SCORE = 0;
            t->vida = 1;
		    t->vida_max = 1;
            t->pos[0] = 1;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 8;
            t->vestes = 0;
            t->atk = 1;
            t->def = 12;
            t->agi = 0;
        break;
	    
        case 44:
            strcpy(t->nome, "Glifos de dor infernais!!");
            t->SCORE = 0;
            t->vida = 2;
		    t->vida_max = 2;
            t->pos[0] = 4;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 12;
            t->agi = 1;
        break;
	    
	case 63:
            strcpy(t->nome, "Almas penadas te estrangulam");
            t->SCORE = 0;
            t->vida = 2;
            t->pos[0] = 2;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 10;
            t->vestes = 0;
            t->atk = 1;
            t->def = 12;
            t->agi = 0;
        break;

	case 35:
            strcpy(t->nome, "Um pendulo laminado!!");
            t->SCORE = 0;
            t->vida = 1;
		    t->vida_max = 1;
            t->pos[0] = 1;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 11;
            t->agi = 1;
        break;

	case 95:
            strcpy(t->nome, "Uma camara de gas corrosivo");
            t->SCORE = 0;
            t->vida = 4;
		    t->vida_max = 4;
            t->pos[0] = 4;
            t->pos[1] = 0;
            t->mao_principal = 5;
            t->mao_secundaria = 1;
            t->vestes = 0;
            t->atk = 0;
            t->def = 8;
            t->agi = 1;
        break;

	case 34:
            strcpy(t->nome, "Espinhos saindo do chao");
            t->SCORE = 0;
            t->vida = 2;
		    t->vida_max = 2;
            t->pos[0] = 3;
            t->pos[1] = 0;
            t->mao_principal = 4;
            t->mao_secundaria = 1;
            t->vestes = 0;
            t->atk = 0;
            t->def = 10;
            t->agi = 1;
        break;
	    
        case 13: // Facil
            strcpy(t->nome, "Armadilha de urso acionada");
            t->SCORE = 67;
            t->vida = 1;
	        t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 10;
            t->agi = 1;
        break;

	case 33:// Facil
            strcpy(t->nome, "Bestas correm em sua direcao");
            t->SCORE = 56;
            t->vida = 2;
	        t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 8;
            t->vestes = 0;
            t->atk = 0;
            t->def = 12;
            t->agi = 1;
        break;


	case 23: //Facil
            strcpy(t->nome, "Maos surgem do chao!");
            t->SCORE = 10;
            t->vida = 1;
	        t->vida_max =1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 0;
            t->def = 12;
            t->agi = 1;
        break;

	case 14: // facil
            strcpy(t->nome, "Um zumbi cai em voce!!");
            t->SCORE = 18;
            t->vida = 1;
	        t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 1;
            t->def = 11;
            t->agi = 0;
        break;
 
	case 103: // Medio
            strcpy(t->nome, "Uma horda te emboscou");
            t->SCORE = 25;
            t->vida = 2;
	        t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 1;
            t->mao_secundaria = 10;
            t->vestes = 0;
            t->atk = 0;
            t->def = 15;
            t->agi = 1;
        break;

	case 113: // Medio
            strcpy(t->nome, "Bola de esqueletos famintos");
            t->SCORE =87;
            t->vida = 1;
	        t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 1;
            t->def = 13;
            t->agi = 0;
        break;

	case 123:// Medio
            strcpy(t->nome, "Parede de corpos esmagadora");
            t->SCORE = 67;
            t->vida = 2;
	        t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 3;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 1;
            t->def = 15;
            t->agi = 0;
        break;

	case 133:// Medio
            strcpy(t->nome, "Um laco espinhoso te prende");
            t->SCORE = 50;
            t->vida = 1;
	        t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 6;
            t->vestes = 0;
            t->atk = 1;
            t->def = 16;
            t->agi = 0;
        break;

	case 153: // dificil
            strcpy(t->nome, "Um fantasma tenta te possuir");
            t->SCORE = 120;
            t->vida = 1;
	        t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 4;
            t->mao_secundaria = 3;
            t->vestes = 0;
            t->atk = 0;
            t->def = 18;
            t->agi = 1;
        break;

	case 163: // dificil
            strcpy(t->nome, "Uma jaula de ossos te prende");
            t->SCORE =130;
            t->vida = 2;
	        t->vida_max = 2;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 2;
            t->mao_secundaria = 4;
            t->vestes = 0;
            t->atk = 1;
            t->def = 17;
            t->agi = 0;
        break;

	case 183: //dificil
            strcpy(t->nome, "A boca de um T-Rex aparece!");
            t->SCORE = 90;
            t->vida = 1;
	        t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 12;
            t->mao_secundaria = 1;
            t->vestes = 0;
            t->atk = 0;
            t->def = 17;
            t->agi = 1;
        break;

	case 195: // dificil
            strcpy(t->nome, "Um portal se abre no chao");
            t->SCORE = 999;
            t->vida = 1;
	        t->vida_max = 1;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 666;
            t->mao_secundaria = 1;
            t->vestes = 0;
            t->atk = 0;
            t->def = 6;
            t->agi = 1;
        break;

        default:
            strcpy(t->nome, "NULL");
            t->SCORE = 0;
            t->vida = 0;
            t->pos[0] = 0;
            t->pos[1] = 0;
            t->mao_principal = 0;
            t->mao_secundaria = 1;
            t->vestes = 0;
            t->atk = 0;
            t->def = 0;
            t->agi = 0;
        break;
   }
}
