#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    lista *l = criar();
    if (l == NULL){
        printf("\nErro.");
        exit(1);
    }
    leitura(l);
    busca(l);
    exibe(l);
    free(l);
    return 0;
}
