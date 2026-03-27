#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "playerFULL.h"
#include "manual.h"
#include "dungrooms.h"
#include "Menulist.h"
#include "gameplay.h"

int main()
{
    //bloco de variáveis da execução principal;
    dung *D;                                    //dungeon;
    PLAYER *jog;                                //player;
    MON *m;                                     //monstro;
    TRAP *t;                                    //armadilha;
    rlist *rl;                                  //salas;
    room *r_io;                                 //sala (entrada e saída);
    enciclopedia *E;                            //enciclopédia de itens;
    manlist *man;                               //manual;

    int i = 1,j,k,p;
    j = 1;// j = 1 serve para colocar o titulo ao centro
    // While utilizado para que o jogador apenas consiga sair quando digitado o numero 6.
    while(i!=4){
            printf("\n\n");
         for(p=0;p<37;p++){ //For utilizado para mover cada linha separadamente.
            for(k=0;k<j;k++){// For utilizado para colocar ao Centro
                printf("\t");
            }
            if(p==0)
                printf("====================================================================================================================================================================================================\n");
            if(p==1)
                printf("|||        ##                ##### ##         ##### ##            #####  #      ##### /##        # ###         #####   ##    ##         # ###         ##### /##       ##### ##          # ###    |||\n");
            if(p==2)
                printf("|||     /####             ######  /###     ######  /### /      ######  /     ######  / ##      /  /###      ######  /#### #####       /  /###      ######  / ##    ######  /### /     /  /###    |||\n");
            if(p==3)
                printf("|||    /  ###            /#   /  /  ###   /#   /  / ###/      /#   /  /     /#   /  /  ##     /  /  ###    /#   /  /  ##### #####    /  /  ###    /#   /  /  ##   /#   /  /  ##/     /  /  ###   |||\n");
            if(p==4)
                printf("|||       /##           /    /  /    ### /    /  /   ##      /    /  /     /    /  /   ##    /  ##   ###  /    /  /   # ##  # ##    /  ##   ###  /    /  /   ##  /    /  /    #     /  ##   ###  |||\n");
            if(p==5)
                printf("|||      /  ##              /  /      ##     /  /                /  /          /  /    /    /  ###    ###     /  /    #     #      /  ###    ###     /  /    /       /  /          /  ###    ### |||\n");
            if(p==6)
                printf("|||      /  ##             ## ##      ##    ## ##               ## ##         ## ##   /    ##   ##     ##    ## ##    #     #     ##   ##     ##    ## ##   /       ## ##         ##   ##     ## |||\n");
            if(p==7)
                printf("|||     /    ##            ## ##      ##    ## ##               ## ##         ## ##  /     ##   ##     ##    ## ##    #     #     ##   ##     ##    ## ##  /        ## ##         ##   ##     ## |||\n");
            if(p==8)
                printf("|||     /    ##          /### ##      /     ## ######         /### ##         ## ###/      ##   ##     ##    ## ##    #     #     ##   ##     ##    ## ###/         ## ######     ##   ##     ## |||\n");
            if(p==9)
                printf("|||    /      ##        / ### ##     /      ## #####         / ### ##         ## ##  ###   ##   ##     ##    ## ##    #     #     ##   ##     ##    ## ##  ###      ## #####      ##   ##     ## |||\n");
            if(p==10)
                printf("|||    /########           ## ######/       ## ##               ## ##         ## ##    ##  ##   ##     ##    ## ##    #     ##    ##   ##     ##    ## ##    ##     ## ##         ##   ##     ## |||\n");
            if(p==11)
                printf("|||   /        ##          ## ######        #  ##          ##   ## ##         #  ##    ##   ##  ##     ##    #  ##    #     ##     ##  ##     ##    #  ##    ##     #  ##          ##  ##     ## |||\n");
            if(p==12)
                printf("|||   #        ##          ## ##               /          ###   #  /             /     ##    ## #      /        /     #      ##     ## #      /        /     ##        #            ## #      /  |||\n");
            if(p==13)
                printf("|||  /####      ##         ## ##           /##/         /  ###    /          /##/      ###    ###     /     /##/      #      ##      ###     /     /##/      ###   /####             ###     /   |||\n");
            if(p==14)
                printf("||| /   ####    ## /       ## ##          /  ##########/    #####/          /  ####    ##      ######/     /  #####           ##      ######/     /  ####    ##   /  #####            ######/    |||\n");
            if(p==15)
                printf("|||/     ##      #/   ##   ## ##         /     ######         ###          /    ##     #         ###      /     ##                      ###      /    ##     #   /    ###               ###      |||\n");
            if(p==16)
                printf("|||#                 ###   #  /          #                                 #                              #                                      #               #                               |||\n");
            if(p==17)
                printf("||| ##                ###    /            ##                                ##                             ##                                     ##              ##                             |||\n");
            if(p==18){
                printf("====================================================================================================================================================================================================\n\n\n");
                j=9; // troca feita para colocar o menu mo centro
            }
            if(p==19){
                printf(" _________________________________\n");
            }
            if(p==20){
                printf("|\\\\_____________________________//|\n");
            }
            if(p==21){
                printf("|//				\\\\|\n");
            }
            if(p==22){
                printf("|||	          		|||\n");
            }
            if(p==23){
                printf("|||	               		|||\n");
            }
            if(p==24){
                printf("|||				|||\n");
            }
            if(p==25){
                printf("|||				|||\n");
            }
            if(p==26){
                printf("|||	1-Jogar.		|||\n");
            }
            if(p==27){
                printf("|||	2-Manual do jogo.       |||\n");
            }
            if(p==28){
                printf("|||	3-Creditos.             |||\n");
            }
            if(p==29){
                printf("|||	4-Sair.      	        |||\n");
            }
            if(p==30){
                printf("|||		           	|||\n");
            }
            if(p==31){
                printf("|||				|||\n");
            }
            if(p==32){
                printf("|||				|||\n");
            }
            if(p==33){
                printf("|||				|||\n");
            }
            if(p==34){
                printf("|||				|||\n");
            }
            if(p==35){
                printf("|\\\\_____________________________//|\n");
            }
            if(p==36){
                printf("|//_____________________________\\\\|\n");
            }

         }
            printf("\n");
            for(k=0;k<j;k++){
                printf("\t");
            }
            printf("\tOpcao >> ");
            scanf("%d",&i);
            printf("\n\n");
            j=1;// Utilizado para se voltar ao Menu print corretamente

    switch(i){
            case 1:
                Jogar(D, r_io, rl, jog, m, t, E);
                break;
            case 2:
                system("cls");
                Manual(man);
                break;
            case 3:
                system("cls");
                Creditos();
                break;
            case 4:
                break;
            default:
                printf("\t\t                                  ============================================================================\n");
                printf("\t\t                                  ||                            Comando invalido.                           ||\n");
                printf("\t\t                                  ============================================================================\n");
                printf("\t\t                                  >>");
                system("pause");
                break;

            }


         }

    return 0;
}
