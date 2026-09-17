#ifndef _BTREE_H
#define	_BTREE_H

#include <stdio.h>

/*
 * Definicao da ordem da arvore
 */
#define ORDEM 510

/*
 * Definicao da estrutura de dados do cabecalho.
 * Um objetivo do cabecalho é guardar qual o numero da pagina raiz da arvore
 */
struct cabecalhoB {
    int paginaRaiz; // numero da pagina raiz da arvore
    int alturaArvore; // altura da arvore
    int numeroElementos; // numero de chaves armazenadas na arvore
    int numeroPaginas; // numero de paginas da arvore
	int reservado[ORDEM-2]; //
};
typedef struct cabecalhoB cabecalho;
/*
 * Definicao da estrutura de dados das paginas da arvore
 *
 * Em uma arvore B+, as paginas internas guardam apenas chaves e ponteiros
 * (numeros) para paginas filhas, enquanto as paginas folha guardam as
 * chaves e os valores (offset do registro) de fato. Por isso a struct
 * guarda um indicador "folha" para diferenciar os dois tipos de pagina, e
 * um ponteiro "proximaFolha" para encadear as folhas entre si (permitindo
 * percurso sequencial, tipico de arvores B+).
 *
 * - Se folha == true : valores[i] eh o valor (offset) associado a chaves[i],
 *                       para i em [0, numeroElementos)
 * - Se folha == false: valores[i] eh o numero da pagina filha responsavel
 *                       pelas chaves menores que chaves[i] (e pagina
 *                       valores[numeroElementos] responsavel pelas chaves
 *                       maiores ou iguais a ultima chave da pagina)
 */
struct paginaB {
    int numeroElementos; // numero de elementos na pagina
    int numeroPagina; // vamos guardar o numero da pagina dentro da propria pagina
    bool folha; // true se a pagina eh uma folha, false se eh pagina indice (interna)
    int proximaFolha; // numero da proxima pagina folha (encadeamento), -1 se nao houver (so usado quando folha == true)
    int chaves[ORDEM-1];
    int valores[ORDEM];
};
typedef struct paginaB pagina;

class btree {
public:
    /*
     * Construtor. Abre arquivo de indice.
     */
    btree();

    /*
     * Destrutor. Fecha arquivo de indice.
     */
    virtual ~btree();

    /*
     * Insere par chave e valor para o registro na árvore
     * Tarefas:
     * - localizar pagina para inserir registro
     * - inserir ordenado na pagina
     * - atualizar numeroElementos na pagina
     * - atualizar recursivamente as páginas ancestrais
     */
    void insereChave(int chave, int valor);

    /*
     * Remove par chave e valor.
     * Tarefas:
     * - localizar pagina para remover registro
     * - inserir ordenado na pagina
     * - atualizar numeroElementos na pagina
     * - atualizar recursivamente as páginas ancestrais
     */
    void removeChave(int chave);

    /*
     * Busca chave e retorna o valor. Retorna -1 caso nao encontre a chave
     * Tarefas:
     * - localizar pagina
     * - retorna valor
     */
    int buscaChave(int chave);

    /*
     * Retorna numero de elementos armazenado no cabecalho da arvore
     */
    int getNumeroElementos() { return cabecalhoArvore.numeroElementos; }

    /*
     * Retorna altura da arvore armazenada no cabecalho da arvore
     */
    int getAlturaArvore() { return cabecalhoArvore.alturaArvore; }

    /*
     * Retorna o numero medio de elementos por pagina da arvore. Considerar apenas paginas folha
     */
    int computarTaxaOcupacao();

    /*
     * Depuração: imprime arquivo
     */
    void depuracao() {
        // imprime cabeçalho
        printf("Cabecalho:\n");
        printf("paginaRaiz      = %d\n",cabecalhoArvore.paginaRaiz);
        printf("alturaArvore    = %d\n",cabecalhoArvore.alturaArvore);
        printf("numeroElementos = %d\n",cabecalhoArvore.numeroElementos);
        printf("numeroPaginas   = %d\n",cabecalhoArvore.numeroPaginas);

        if (cabecalhoArvore.paginaRaiz != -1) {
            printf("\nEstrutura da arvore:\n");
            depuracaoRecursiva(cabecalhoArvore.paginaRaiz, 0);
        }
    }

private:
    /*
     * Cabecalho da arvore
     */
    cabecalho cabecalhoArvore;

    /*
     * Instancia para ler uma pagina
     */
    pagina paginaAtual;

    /*
     * Manipulador do arquivo de dados
     */
    FILE *arquivo;

    /*
     * Estrutura auxiliar usada para "propagar" uma divisao (split) de
     * pagina para o nivel acima da arvore durante a insercao.
     */
    struct ResultadoInsercao {
        bool houveSplit;      // indica se a pagina filha dividiu
        int chavePromovida;   // chave que deve subir para o pai
        int novaPagina;       // numero da nova pagina criada pelo split
    };

    /*
     * Criaçao de uma nova pagina. Parametro com numero da pagina deve ser passado por referencia (exemplo: int idpagina;
     * btree->novaPagina(&idpagina);) pois no retorno da funçao o idpagina tera o numero da nova pagina.
     */
    pagina *novaPagina(int *idPagina) {
        pagina *pg = new pagina;
        pg->numeroElementos = 0;
        pg->folha = false;
        pg->proximaFolha = -1;

        cabecalhoArvore.numeroPaginas++;
        pg->numeroPagina = cabecalhoArvore.numeroPaginas;
        *idPagina = cabecalhoArvore.numeroPaginas;

        // grava a pagina na posicao correta do arquivo (baseada no seu id)
        fseek(arquivo, sizeof(cabecalhoArvore) + (pg->numeroPagina-1)*sizeof(pagina), SEEK_SET);
        fwrite(pg,sizeof(pagina),1,arquivo);
        fflush(arquivo);

        salvaCabecalho();

        return pg;
    }

    /*
     * Leitura de uma pagina existente.
     */
    pagina *lePagina(int idPagina) {
        pagina *pg = new pagina;
        fseek(arquivo, sizeof(cabecalhoArvore) + (idPagina-1)*sizeof(pagina), SEEK_SET);
        fread(pg,sizeof(pagina),1,arquivo);
        return pg;
    }

    /*
     * Persistencia de uma pagina.
     */
    void salvaPagina(int idPagina, pagina *pg) {
        fseek(arquivo, sizeof(cabecalhoArvore) + (idPagina-1)*sizeof(pagina), SEEK_SET);
        fwrite(pg,sizeof(pagina),1,arquivo);
    }

    /*
     * Salva o cabecalho
     */
    void salvaCabecalho() {
        fseek(arquivo,0,SEEK_SET);
        fwrite(&cabecalhoArvore,sizeof(cabecalhoArvore),1,arquivo);
    }

    /*
     * Le o cabecalho
     */
    void leCabecalho() {
        fseek(arquivo,0,SEEK_SET);
        fread(&cabecalhoArvore,sizeof(cabecalhoArvore),1,arquivo);
    }

    /*
     * Insere par na árvore, descendo recursivamente ate a folha correta e
     * propagando eventuais splits (divisoes de pagina) de volta para cima.
     */
    ResultadoInsercao insereRecursivo(int chave, int valor, int idPagina);

    /*
     * Insere (chave,valor) em uma pagina folha, dividindo-a caso necessario.
     */
    ResultadoInsercao insereEmPaginaFolha(pagina *pg, int idPagina, int chave, int valor);

    /*
     * Insere (chave, idFilhoDireito) em uma pagina interna (apos um split
     * de um filho), dividindo-a caso necessario.
     */
    ResultadoInsercao insereEmPaginaInterna(pagina *pg, int idPagina, int chave, int idFilhoDireito);

    /*
     * Imprime recursivamente a arvore a partir da pagina informada (usado por depuracao()).
     */
    void depuracaoRecursiva(int idPagina, int nivel) {
        pagina *pg = lePagina(idPagina);

        for (int i = 0; i < nivel; i++) printf("  ");
        printf("[Pagina %d] %s (%d elementos) chaves: ", idPagina, pg->folha ? "FOLHA" : "INTERNA", pg->numeroElementos);
        for (int i = 0; i < pg->numeroElementos; i++)
            printf("%d ", pg->chaves[i]);

        if (pg->folha) {
            printf("| valores: ");
            for (int i = 0; i < pg->numeroElementos; i++)
                printf("%d ", pg->valores[i]);
            printf("| proximaFolha: %d\n", pg->proximaFolha);
        } else {
            printf("\n");
            for (int i = 0; i <= pg->numeroElementos; i++)
                depuracaoRecursiva(pg->valores[i], nivel+1);
        }

        delete pg;
    }
};

#endif	/* _BTREE_H */
