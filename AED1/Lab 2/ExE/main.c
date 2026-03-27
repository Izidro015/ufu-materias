#include <stdio.h>
#include <stdlib.h>

struct Cliente{
    char cpf[12];
    char estadoCivil[20];
    char **filhos;
    int numFilhos;
};

void inserirCliente(struct Cliente *clientes, int *numClientes) {
    printf("CPF: ");
    scanf("%s", clientes[*numClientes].cpf);
    printf("Estado Civil: ");
    scanf("%s", clientes[*numClientes].estadoCivil);
    printf("Quantidade de filhos: ");
    scanf("%d",&clientes[*numClientes].numFilhos);
    if (clientes[*numClientes].numFilhos>0) {
        clientes[*numClientes].filhos = (char **)malloc(clientes[*numClientes].numFilhos * sizeof(char *));
        printf("Nomes dos filhos:\n");
        for (int i=0;i<clientes[*numClientes].numFilhos;i++) {
            clientes[*numClientes].filhos[i]=(char *)malloc(50 * sizeof(char));
            printf("Filho %d: ", i + 1);
            scanf("%s", clientes[*numClientes].filhos[i]);
        }
    } else {
        clientes[*numClientes].filhos = NULL;
    }
    (*numClientes)++;
}
void removerCliente(struct Cliente *clientes, int *numClientes, int posicao) {
    if (posicao>=0&&posicao<*numClientes) {
        free(clientes[posicao].filhos);
        for (int i=posicao;i<*numClientes-1;i++) {
            clientes[i] = clientes[i + 1];
        }
        (*numClientes)--;
        printf("Cliente removido.\n");
    } else {
        printf("Posicao invalida.\n");
    }
}
void mostrarCPFs(struct Cliente *clientes, int numClientes) {
    printf("CPFs dos clientes:\n");
    for (int i=0;i<numClientes;i++) {
        printf("%s\n", clientes[i].cpf);
    }
}
int main() {
    int tamanhoVetor;
    printf("Digite o tamanho do vetor de clientes: ");
    scanf("%d",&tamanhoVetor);
    struct Cliente *clientes = (struct Cliente *)malloc(tamanhoVetor * sizeof(struct Cliente));
    int numClientes=0;
    int opcao;
    do {
        printf("\nOpções:\n");
        printf("1. Inserir cliente\n");
        printf("2. Remover cliente (por posicao)\n");
        printf("3. Mostrar CPFs dos clientes\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d",&opcao);
        switch (opcao){
            case 1:inserirCliente(clientes,&numClientes);break;
            case 2:
                if (numClientes > 0) {
                    int posicao;
                    printf("Digite a posicao do cliente a ser removido: ");
                    scanf("%d", &posicao);
                    removerCliente(clientes, &numClientes, posicao);
                } else {
                    printf("Nenhum cliente para remover.\n");
                }
                break;
            case 3:
                if (numClientes > 0) {
                    mostrarCPFs(clientes, numClientes);
                } else {
                    printf("Nenhum cliente cadastrado.\n");
                }
                break;
            case 0:
                break;
            default:printf("Opcao invalida.\n");
        }
    } while (opcao!=0);
    for (int i=0;i<numClientes;i++) {
        free(clientes[i].filhos);
    }
    free(clientes);
    return 0;
}
