#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Menulist.h"
#include "playerFULL.h"
#include "manual.h"
#include "dungrooms.h"
#include "gameplay.h"

// Fun��o que fala sobre o jogo sendo eles as regras e o Objetivo do jogo
int Manual(manlist *man){
    int pag = 1, MODE;
    man = createman();
    for(int i = 1; i <= 15; i++){
        insertManpage(man, i);
    }
    while(1){
        displayManpage(man, pag);
        printf("pag %d/%d\n\n", pag, man->tamanho);
        printf("1 = pagina anterior.\n2 = proxima pagina.\n0 = SAIR.\n>> ");
        setbuf(stdin, NULL);
        scanf("%d", &MODE);
        if(browseman(man, MODE, &pag) != 0){
            if(MODE == 0) break;
            printf("Comando invalido!\n");
        }
        system("cls");
    }
    system("cls");
    clearman(man);
    return 0;
}

int Creditos(){

    int p,j=7,k;
    for(p=0;p<15;p++){
        for(k=0;k<j;k++){
            printf("\t");
        }
        if(p==0)
            printf("=======================================================================\n");
        if(p==1)
            printf("|||                             Creditos                            |||\n");
        if(p==2)
            printf("|||                                                                 |||\n");
        if(p==3)
            printf("|||         Programadores                                           |||\n");
        if(p==4)
            printf("|||             Patrick Gomes de Oliveira                           |||\n");
        if(p==5)
            printf("|||             Diogo Vieira Silva                                  |||\n");
        if(p==6)
            printf("|||             Caio Figueiredo Freitas                             |||\n");
        if(p==7)
            printf("|||             Matheus Izidro Campos dos Santos                    |||\n");
        if(p==8)
            printf("|||                                                                 |||\n");
        if(p==9)
            printf("|||         Players Test                                            |||\n");
        if(p==10)
            printf("|||            Gouzin   pontuacao: 6833 MVP                         |||\n");
        if(p==11)
            printf("|||            Tr3vis4n pontuacao: 0918                             |||\n");
        if(p==12)
            printf("|||            Bernado  pontuacao: 0404                             |||\n");
	 if(p==13)
            printf("|||            Caio H   pontuacao: 0281                             |||\n");
        if(p==14)
            printf("=======================================================================\n");
    }
    printf("\n\n                                                        ");
    return system("pause");
}

int Jogar(dung *D, room *r_io, rlist *rl, PLAYER *p, MON *m, TRAP *t, enciclopedia *E){

    srand(time(NULL));

    int CLASS;

    D = createDungeon(18);
    geradorDeDungeon(D, 80);
    room_generator(D);
    rl = createRL();
    E = iniciar_enciclopedia();
    r_io = (room*) malloc(sizeof(room));
    m = NULL;
    t = NULL;
    char nome[30];
	
	system("cls");
    setbuf(stdin, NULL);
    printf("         ______    ____  ____       __      ___              ______         ________  _______  ____  ____      _____  ___      ______   ___      ___   _______   \n");
    printf("        /      \\  (   _||_   |     /  \\    |   |            /      \\       /        )/       |(   _||_   |    (\\    \\|   \\    /      \\ |   \\    /   | /       |  \n");
    printf("       // ____  \\ |   (  ) : |    /    \\   ||  |           // ____  \\     (:   \\___/(: ______)|   (  ) : |    |.\\\\   \\    |  // ____  \\ \\   \\  //   |(: ______) \n");
    printf("      /  /    )  )(:  |  | . )   /' /\\  \\  |:  |          /  /    ) :)     \\___  \\   \\/    |  (:  |  | . )    |: \\.   \\\\  | /  /    ) :)/\\\\  \\/.    | \\/    |   \n");
    printf("     (: (____/ //  \\\\ \\__/ //   //  __'  \\  \\  |___      (: (____/ //       __/  \\\\  // ___)_  \\\\ \\__/ //     |.  \\    \\. |(: (____/ //|: \\.        | // ___)_     \n");
    printf("      \\         \\  /\\\\ __ //\\  /   /  \\\\  \\( \\_|:  \\      \\        /       /  \\   :)(:       | /\\\\ __ //\\     |    \\    \\ | \\        / |.  \\    /:  |(:       |     \n");
    printf("       \\ ____/\\__\\(__________)(___/    \\___)\\_______)      \\ _____/       (_______/  \\_______)(__________)     \\___|\\____\\)  \\ _____/  |___|\\__/|___| \\_______)     \n\n");
    printf("                      __  ___      ___  _______  _____  ___  ___________  ____  ____   _______    _______   __      _______     ______  ________   \n");
    printf("                     /  \\|   \\    /   |/       |(\\    \\|   \\(      _    )(   _||_   | /       \\  /       | |  \\    /       \\   /      \\(        \\  \n");
    printf("                    /    \\\\   \\  //  /(: ______)|.\\\\   \\    |)__/  \\\\__/ |   (  ) : ||:        |(: ______) ||  |  |:        | // ____  \\\\___/   :) \n");
    printf("                   /' /\\  \\\\\\  \\/. ./  \\/    |  |: \\.   \\\\  |   \\\\_ /    (:  |  | . )|_____/   ) \\/    |   |:  |  |_____/   )/  /    ) :) /  ___/  \n");
    printf("                  //  __'  \\\\.    //   // ___)_ |.  \\    \\. |   |.  |     \\\\ \\__/ //  //      /  // ___)_  |.  |   //      /(: (____/ // //  \\     \n");
    printf("                 /   /  \\\\  \\\\\\   /   (:       ||    \\    \\ |   \\:  |     /\\\\ __ //\\ |:  __   \\ (:       | /\\  |\\ |:  __   \\ \\        / ('___/     \n");
    printf("                (___/    \\___)\\__/     \\_______) \\___|\\____\\)    \\__|    (__________)|__|  \\___) \\_______)(__\\_|_)|__|  \\___) \\ _____/   (___)     \n\n\n\n\n");
    printf("                >>");
    fgets(nome, 30, stdin);
    nome[strlen(nome)-1] = 0;
    system("cls");

    printf("\n\n\n\n\n\n\n\n");
    printf("                                                                       __________________________\n");
    printf("                                                                       ||| Escolha Sua Classe |||\n");
    printf("                                                                       ==========================\n");
    printf("\n\n\n\n\n");
    printf("             _________________________________                     _________________________________                     _________________________________\n");
    printf("            |         1 - Cavaleiro           |                   |           2 - Mago              |                   |         3 - Ladino              |\n");
    printf("            \\_________________________________/                   \\_________________________________/                   \\_________________________________/\n");
    printf("            ||                               ||                   ||                               ||                   ||                               ||\n");
    printf("            ||                               ||                   ||                               ||                   ||                               ||\n");
    printf("            ||                               ||                   ||             _..._             ||                   ||            .-'''-.            ||\n");
    printf("            ||              ___              ||                   ||          .-'_..._''.          ||                   ||           '  ___  '           ||\n");
    printf("            ||             |___|             ||                   ||        .' .'      '.\\         ||                   ||         /  /###  \\  \\         ||\n");
    printf("            ||              | |              ||                   ||       / .'   ___              ||                   ||        .  '##     '  .        ||\n");
    printf("            ||              | |              ||                   ||      . '   .' _ '.            ||                   ||        |  |#      |  |        ||\n");
    printf("            ||          ____|_|____          ||                   ||      | |  /  / \\  \\           ||                   ||        \\  /#      \\  /        ||\n");
    printf("            ||         / _________ \\         ||                   ||      | |  | |   | |           ||                   ||        /`.##       .`\\        ||\n");
    printf("            ||        / / |  |  | \\ \\        ||                   ||      . '  \\  \\_/  /           ||                   ||       '\\  '`\\   /'`  /'       ||\n");
    printf("            ||        \\/ _|__|__|_ \\/        ||                   ||       \\ '. '.___.'  '         ||                   ||      /  \\_ , ||| , _/  \\      ||\n");
    printf("            ||          /   \\|/   \\          ||                   ||        '. '._____.-'/         ||                   ||     / _ \\  /*|||*\\  / _ \\     ||\n");
    printf("            ||     ____/    / \\    \\____     ||                   ||          '-._______/          ||                   ||     |####\\/**|||**\\/####|     ||\n");
    printf("            ||     \\    /\\_/___\\_/\\    /     ||                   ||             |\\\\  |            ||                   ||     |  ###\\_//_\\\\_/###  |     ||\n");
    printf("            ||      |  |           |  |      ||                   ||         /\\  | \\\\ |  /\\        ||                   ||     |    ###########    |     ||\n");
    printf("            ||      |  | _/\\___/\\_ |  |      ||                   ||         \\ \\_|__\\\\|_/ /        ||                   ||     |        ###        |     ||\n");
    printf("            ||      |   \\_________/   |      ||                   ||          | ________ |         ||                   ||     |     /\\     /\\     |     ||\n");
    printf("            ||      \\__  \\/ \\ / \\/  __/      ||                   ||         / / |   \\| \\ \\        ||                   ||     |    /  |   |  \\    |     ||\n");
    printf("            ||         \\    /|\\    /         ||                   ||         \\/  |    |  \\/        ||                   ||     |   .  /     \\  .   |     ||\n");
    printf("            ||          \\_       _/          ||                   ||             |    |            ||                   ||     |  /\\_/       \\_/\\  |     ||\n");
    printf("            ||            \\_   _/            ||                   ||             |    |            ||                   ||     | /-/           \\-\\ |     ||\n");
    printf("            ||            | \\_/ |            ||                   ||             |    |            ||                   ||     |/_/             \\_\\|     ||\n");
    printf("            ||            |  |  |            ||                   ||             |\\   |            ||                   ||     |                   |     ||\n");
    printf("            ||            \\  |  /            ||                   ||             |\\\\  |            ||                   ||     |                   |     ||\n");
    printf("            ||             \\ | /             ||                   ||             | \\\\ |            ||                   ||     |    .\\      /\\     |     ||\n");
    printf("            ||              \\|/              ||                   ||             |  \\\\|            ||                   ||     |   , ;     / /     |     ||\n");
    printf("            ||                               ||                   ||             |___\\|            ||                   ||     |  . .      \\ \\/\\   |     ||\n");
    printf("            ||                               ||                   ||            /______\\           ||                   ||     | .  .       \\   \\  |     ||\n");
    printf("            ||                               ||                   ||            |wwwwww|           ||                   ||     |  \\; '      /    \\ |     ||\n");
    printf("            ||                               ||                   ||                               ||                   ||     |____\\ \\_/\\_/      \\|     ||\n");
    printf("            ||_______________________________||                   ||                               ||                   ||                               ||\n");
    printf("            \\_________________________________/                   \\_________________________________/                   \\_________________________________/\n\n\n");


	while(1){
		printf("\t\t\t>> ");
		setbuf(stdin, NULL);
		scanf("%d", &CLASS);
		if((CLASS < 1 || CLASS > 3) && CLASS != 74){
			printf("\t\t\t>>Selecao invalida.\n");
		}
		else break;
	}
    p = criar_player(CLASS, D->spawn, E);
    strcpy(p->nome, nome);
    
    //LOOP PRINCIPAL DO JOGO;
    //NÃO QUEBRAR;
    while(1){
        system("cls");
        if(testforRoom(rl, p->pos) == 0){
            r_io->dif = D->map[p->pos[0]][p->pos[1]];
            r_io->pos[0] = p->pos[0];
            r_io->pos[1] = p->pos[1];
            r_io->cont = (r_io->dif * 10) + (rand() % 10);
            r_io->exits = roomExits(D, p->pos);
            addRoom(rl, *r_io);
        }

        r_io = getRoom(rl, p->pos, 0);
		if(r_io->dif == 3000){
			system("cls");
            printf("                                         =================================================================================\n");
			printf("                                         ||                 Voce se encontra perante um altar de cristal...             ||\n");
			printf("                                         ||Uma chave brilhante se encontra sobre ele: o artefato que voce buscava...    ||\n");
			printf("                                         ||  Tomando seu trofeu em maos, voce sai do calabouco, sabendo que foi um      ||\n");
			printf("                                         ||                 dos poucos a dominar as ruinas apeiromorficas...            ||\n");
            printf("                                         =============================================================================\n");
            printf("                                       >>");
			system("pause");
			system("cls");
			
			p->SCORE += 3000;
			
			//limpando e desalocando tudo;
			clearrlist(rl);
			free(rl);
			free(r_io);
			clearDung(D);
			free(D);
			clearItemEnc(E);
			free(E);
			return Menu_final(1,p);
		}
        // Debugger
       /*
       printf("\n\nSALA ATUAL:\n");
        printf("  POS: %d/%d\n", r_io->pos[0], r_io->pos[1]);
        printf("  DIFICULDADE: %d\n", r_io->dif);
        printf("  VALOR: %d\n", r_io->cont);
        printf("  SAIDAS: %d\n", r_io->exits);
		
		printf("  ATK %d\n", p->atk);
		printf("  DEF %d\n", p->def);
		printf("  AGI %d\n", p->agi);
        printf("\n\n");
        printar_matriz2(D, p->pos);
        printf("\n\n");
       */ 
        
        if(enterRoom(rl, r_io, p, m, t, E, D) == -1 || p->vida <= 0){
			system("cls");
			
			//limpando e desalocando tudo;
			clearrlist(rl);
			free(rl);
			free(r_io);
			clearDung(D);
			free(D);
			clearItemEnc(E);
			free(E);
			return Menu_final(0,p);
		}
    }



    return system("pause");


}


int Menu_final(int i,PLAYER *s){
int j,p;
printf("\n\n\n\n\n\n");
if(i==0){
    for(j=0;j<5;j++){
        for(p=0;p<3;p++){
            printf("\t\t ");
        }
        if(j==0)
            printf(" @@@@@@@   @@@@@@  @@@@@@@@@@  @@@@@@@@  @@@@@@  @@@  @@@ @@@@@@@@ @@@@@@@ \n");
        if(j==1)
            printf("!@@       @@!  @@@ @@! @@! @@! @@!      @@!  @@@ @@!  @@@ @@!      @@!  @@@\n");
        if(j==2)
            printf("!@! @!@!@ @!@!@!@! @!! !!@ @!@ @!!!:!   @!@  !@! @!@  !@! @!!!:!   @!@!!@!\n");
        if(j==3)
            printf(":!!   !!: !!:  !!! !!:     !!: !!:      !!:  !!!  !: .:!  !!:      !!: :!!\n");
        if(j==4)
            printf(" :: :: :   :   : :  :      :   : :: :::  : :. :     ::    : :: :::  :   : :\n\n\n\n");
    }
    printf("\t\t\t\t\t\t   Infelizmente, para que hajam lendas, devem tambem haver os fracassos...\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t Pontuacao final: %d \n\n\n\n",s->SCORE);
	clearPlayer(s);
	free(s);
    printf("\t\t\t\t\t\t\t\t");
    return system("pause");
}
else{
    for(j=0;j<22;j++){
        for(p=0;p<1;p++){
            if(j>7&&j<15)
                printf("\t");
            printf("\t");
        }
        if(j==0)
            printf("   . .       . .       . .       . .       . .       . .       . .    .       . .       .         . .       . .    .    .       . .       . .       . .    \n");
        if(j==1)
            printf(".+'|=|`+. .+'|=|`+. .+'|=|`+. .+'|=|`+. .+'|=|`+. .+'|=|`+. .+'|=|`+.=|`+. .+'| |`+. .+'|      .+'|=|`+. .+'|=|`+.=|`+. |`+. .+'|=|`+. .+'|=|`+. .+'|=|`+. \n");
        if(j==2)
            printf("|  | `+.| |  | |  | |  | `+ | |  | `+.| |  | |  | |  | |  | |.+' |  | `+.| |  | |  | |  |      |  | |  | |.+' |  | `+.| |  | |  | |  | |  | `+ | |  | `+.| \n");
        if(j==3)
            printf("|  |      |  | |  | |  |  | | |  | .    |  |'. '. |  |=|  |      |  |      |  | |  | |  |      |  |=|  |      |  |      |  | |  | |  | |  |  | | |  | .    \n");
        if(j==4)
            printf("|  |      |  | |  | |  |  | | |  | |`+. |  | |  | |  | |  |      |  |      |  | |  | |  |      |  | |  |      |  |      |  | |  | |  | |  |  | | `+.|=|`+. \n");
        if(j==5)
            printf("|  |    . |  | |  | |  |  | | |  | `. | |  | |  | |  | |  |      |  |      |  | |  | |  |    . |  | |  |      |  |      |  | |  | |  | |  |  | | .    |  | \n");
        if(j==6)
            printf("|  | .+'| |  | |  | |  |  | | |  | .+ | |  | |  | |  | |  |      |  |      |  | |  | |  | .+'| |  | |  |      |  |      |  | |  | |  | |  |  | | |`+. |  | \n");
        if(j==7)
            printf("`+.|=|.+' `+.|=|.+' `+.|  |.| `+.|=|.+' `+.| |.+' `+.| |..|      |.+'      `+.|=|.+' `+.|=|.+' `+.| |..|      |.+'      |.+' `+.|=|.+' `+.|  |.| `+.|=|.+' \n\n\n");
        if(j==8)
            printf(":::   :::  ::::::::  :::    ::: :::::::::       ::::::::::: ::::::::  :::    ::: :::::::::  ::::    ::: :::::::::: :::   :::\n");
        if(j==9)
            printf(":+:   :+: :+:    :+: :+:    :+: :+:    :+:          :+:    :+:    :+: :+:    :+: :+:    :+: :+:+:   :+: :+:        :+:   :+:\n");
        if(j==10)
            printf(" +:+ +:+  +:+    +:+ +:+    +:+ +:+    +:+          +:+    +:+    +:+ +:+    +:+ +:+    +:+ :+:+:+  +:+ +:+         +:+ +:+ \n");
        if(j==11)
            printf("  +#++:   +#+    +:+ +#+    +:+ +#++:++#:           +#+    +#+    +:+ +#+    +:+ +#++:++#:  +#+ +:+ +#+ +#++:++#     +#++:  \n");
        if(j==12)
            printf("   +#+    +#+    +#+ +#+    +#+ +#+    +#+          +#+    +#+    +#+ +#+    +#+ +#+    +#+ +#+  +#+#+# +#+           +#+   \n");
        if(j==13)
            printf("   #+#    #+#    #+# #+#    #+# #+#    #+#      #+# #+#    #+#    #+# #+#    #+# #+#    #+# #+#   #+#+# #+#           #+#   \n");
        if(j==14)
            printf("   ###     ########   ########  ###    ###       #####      ########   ########  ###    ### ###    #### ##########    ###   \n\n");
        if(j==15)
            printf(":::::::::  ::::::::::     :::      ::::::::  :::    ::: :::::::::: :::::::::        ::::::::::: ::::::::::: ::::::::        :::::::::: ::::    ::: :::::::::\n");
        if(j==16)
            printf(":+:    :+: :+:          :+: :+:   :+:    :+: :+:    :+: :+:        :+:    :+:           :+:         :+:    :+:    :+:       :+:        :+:+:   :+: :+:    :+:\n");
        if(j==17)
            printf("+:+    +:+ +:+         +:+   +:+  +:+        +:+    +:+ +:+        +:+    +:+           +:+         +:+    +:+              +:+        :+:+:+  +:+ +:+    +:+ \n");
        if(j==18)
            printf("+#++:++#:  +#++:++#   +#++:++#++: +#+        +#++:++#++ +#++:++#   +#+    +:+           +#+         +#+    +#++:++#++       +#++:++#   +#+ +:+ +#+ +#+    +:+\n");
        if(j==19)
            printf("+#+    +#+ +#+        +#+     +#+ +#+        +#+    +#+ +#+        +#+    +#+           +#+         +#+           +#+       +#+        +#+  +#+#+# +#+    +#+\n");
        if(j==20)
            printf("#+#    #+# #+#        #+#     #+# #+#    #+# #+#    #+# #+#        #+#    #+#           #+#         #+#    #+#    #+#       #+#        #+#   #+#+# #+#    #+# \n");
        if(j==21)
            printf("###    ### ########## ###     ###  ########  ###    ### ########## #########        ###########     ###     ########        ########## ###    #### ######### \n\n\n\n\n");
    }
    printf("\t\t\t\t\t      Celebre sua vitoria, pois, hoje, voce se tornou parte da historia.\n\n\n");
    printf("\t\t\t\t\t\t\t             Pontuacao final: %d \n\n\n",s->SCORE);
	clearPlayer(s);
	free(s);
    printf("\t\t\t\t\t\t\t       ");
    return system("pause");
}



}
