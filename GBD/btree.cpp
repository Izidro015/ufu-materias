#include <sys/types.h>
#include <sys/stat.h>

#include "btree.h"

#ifndef _BTREE_CPP
#define	_BTREE_CPP

// numero maximo de chaves por pagina (folha ou interna)
static const int MAXCHAVES = ORDEM - 1;

bool fileExists(const char *filename) { struct stat statBuf; if (stat(filename,&statBuf) < 0) return false; return S_ISREG(statBuf.st_mode); }

btree::btree() {
    char nomearquivo[20] = "arvoreb.dat";

    // se arquivo ja existir, abrir e carregar cabecalho
    if (fileExists(nomearquivo)) {
        // abre arquivo (modo binario, para funcionar corretamente tambem no Windows)
        arquivo = fopen(nomearquivo,"rb+");
        leCabecalho();
    }
    // senao, criar novo arquivo e salvar o cabecalho
    else {
        // cria arquivo (modo binario)
        arquivo = fopen(nomearquivo,"wb+");

        // atualiza cabecalho
        cabecalhoArvore.paginaRaiz = -1;
        cabecalhoArvore.alturaArvore = 0;
        cabecalhoArvore.numeroElementos = 0;
        cabecalhoArvore.numeroPaginas = 0;
        salvaCabecalho();
    }
}

btree::~btree() {
    // fechar arquivo
    fclose(arquivo);
}

int btree::computarTaxaOcupacao() {

    if (cabecalhoArvore.paginaRaiz == -1)
        return 0;

    // desce sempre pelo filho mais a esquerda ate encontrar a folha mais a esquerda
    int idPagina = cabecalhoArvore.paginaRaiz;
    pagina *pg = lePagina(idPagina);
    while (!pg->folha) {
        int idFilho = pg->valores[0];
        delete pg;
        pg = lePagina(idFilho);
    }

    // percorre as folhas usando o encadeamento (proximaFolha), somando elementos
    long totalElementos = 0;
    long totalPaginasFolha = 0;

    while (true) {
        totalElementos += pg->numeroElementos;
        totalPaginasFolha++;

        int proxima = pg->proximaFolha;
        delete pg;

        if (proxima == -1)
            break;

        pg = lePagina(proxima);
    }

    if (totalPaginasFolha == 0)
        return 0;

    // taxa de ocupacao (%) = elementos armazenados / capacidade total das paginas folha
    return (int)((totalElementos * 100) / (totalPaginasFolha * MAXCHAVES));
}

void btree::insereChave(int chave, int valor) {

    // caso especial: arvore vazia, cria a primeira pagina (folha) que sera a raiz
    if (cabecalhoArvore.paginaRaiz == -1) {
        int idPagina;
        pagina *pg = novaPagina(&idPagina);

        pg->folha = true;
        pg->numeroElementos = 1;
        pg->chaves[0] = chave;
        pg->valores[0] = valor;
        pg->proximaFolha = -1;
        salvaPagina(idPagina, pg);
        delete pg;

        cabecalhoArvore.paginaRaiz = idPagina;
        cabecalhoArvore.alturaArvore = 1;
    }
    else {
        ResultadoInsercao resultado = insereRecursivo(chave, valor, cabecalhoArvore.paginaRaiz);

        // se a raiz dividiu, cria uma nova raiz (pagina interna) apontando para as duas metades
        if (resultado.houveSplit) {
            int idNovaRaiz;
            pagina *novaRaiz = novaPagina(&idNovaRaiz);

            novaRaiz->folha = false;
            novaRaiz->numeroElementos = 1;
            novaRaiz->chaves[0] = resultado.chavePromovida;
            novaRaiz->valores[0] = cabecalhoArvore.paginaRaiz;
            novaRaiz->valores[1] = resultado.novaPagina;
            salvaPagina(idNovaRaiz, novaRaiz);
            delete novaRaiz;

            cabecalhoArvore.paginaRaiz = idNovaRaiz;
            cabecalhoArvore.alturaArvore++;
        }
    }

    // chave inserida com sucesso, atualiza cabecalho
    cabecalhoArvore.numeroElementos++;
    salvaCabecalho();
}

btree::ResultadoInsercao btree::insereRecursivo(int chave, int valor, int idPagina) {

    pagina *pg = lePagina(idPagina);
    ResultadoInsercao resultado;

    if (pg->folha) {
        // caso base da recursao: chegamos numa folha, inserir aqui
        resultado = insereEmPaginaFolha(pg, idPagina, chave, valor);
    }
    else {
        // pagina interna: descobrir qual filho seguir e descer recursivamente
        int i = 0;
        while (i < pg->numeroElementos && chave >= pg->chaves[i])
            i++;

        int idFilho = pg->valores[i];

        ResultadoInsercao resultadoFilho = insereRecursivo(chave, valor, idFilho);

        if (resultadoFilho.houveSplit) {
            // o filho dividiu: inserir a chave promovida e o ponteiro para a nova pagina aqui
            resultado = insereEmPaginaInterna(pg, idPagina, resultadoFilho.chavePromovida, resultadoFilho.novaPagina);
        }
        else {
            resultado.houveSplit = false;
            resultado.chavePromovida = 0;
            resultado.novaPagina = -1;
        }
    }

    delete pg;
    return resultado;
}

btree::ResultadoInsercao btree::insereEmPaginaFolha(pagina *pg, int idPagina, int chave, int valor) {

    // arrays temporarios: cabem ate MAXCHAVES+1 elementos (overflow temporario antes do split)
    int chavesTemp[ORDEM];
    int valoresTemp[ORDEM];

    int n = pg->numeroElementos;
    for (int i = 0; i < n; i++) {
        chavesTemp[i] = pg->chaves[i];
        valoresTemp[i] = pg->valores[i];
    }

    // encontra posicao ordenada de insercao
    int pos = 0;
    while (pos < n && chavesTemp[pos] < chave)
        pos++;

    // desloca para abrir espaco
    for (int i = n; i > pos; i--) {
        chavesTemp[i] = chavesTemp[i-1];
        valoresTemp[i] = valoresTemp[i-1];
    }
    chavesTemp[pos] = chave;
    valoresTemp[pos] = valor;
    n++;

    ResultadoInsercao resultado;
    resultado.houveSplit = false;
    resultado.chavePromovida = 0;
    resultado.novaPagina = -1;

    if (n <= MAXCHAVES) {
        // sem overflow, apenas grava de volta
        pg->numeroElementos = n;
        for (int i = 0; i < n; i++) {
            pg->chaves[i] = chavesTemp[i];
            pg->valores[i] = valoresTemp[i];
        }
        salvaPagina(idPagina, pg);
    }
    else {
        // overflow: divide a pagina folha em duas
        int meio = n / 2;

        pg->numeroElementos = meio;
        for (int i = 0; i < meio; i++) {
            pg->chaves[i] = chavesTemp[i];
            pg->valores[i] = valoresTemp[i];
        }

        int idNovaPagina;
        pagina *novaPg = novaPagina(&idNovaPagina);
        novaPg->folha = true;
        novaPg->numeroElementos = n - meio;
        for (int i = meio; i < n; i++) {
            novaPg->chaves[i-meio] = chavesTemp[i];
            novaPg->valores[i-meio] = valoresTemp[i];
        }

        // mantem a lista encadeada de folhas
        novaPg->proximaFolha = pg->proximaFolha;
        pg->proximaFolha = idNovaPagina;

        salvaPagina(idPagina, pg);
        salvaPagina(idNovaPagina, novaPg);

        // em arvore B+, a chave que sobe para o pai eh uma COPIA da menor chave
        // da nova pagina (ela continua tambem armazenada na folha)
        resultado.houveSplit = true;
        resultado.chavePromovida = novaPg->chaves[0];
        resultado.novaPagina = idNovaPagina;

        delete novaPg;
    }

    return resultado;
}

btree::ResultadoInsercao btree::insereEmPaginaInterna(pagina *pg, int idPagina, int chave, int idFilhoDireito) {

    // arrays temporarios: cabem ate MAXCHAVES+1 chaves e MAXCHAVES+2 ponteiros (overflow temporario)
    int chavesTemp[ORDEM];
    int valoresTemp[ORDEM+1];

    int n = pg->numeroElementos;
    for (int i = 0; i < n; i++)
        chavesTemp[i] = pg->chaves[i];
    for (int i = 0; i <= n; i++)
        valoresTemp[i] = pg->valores[i];

    // encontra posicao ordenada de insercao da chave
    int pos = 0;
    while (pos < n && chavesTemp[pos] < chave)
        pos++;

    // desloca chaves para abrir espaco
    for (int i = n; i > pos; i--)
        chavesTemp[i] = chavesTemp[i-1];
    chavesTemp[pos] = chave;

    // desloca ponteiros: o novo filho (a direita da chave inserida) vai na posicao pos+1
    for (int i = n+1; i > pos+1; i--)
        valoresTemp[i] = valoresTemp[i-1];
    valoresTemp[pos+1] = idFilhoDireito;

    n++;

    ResultadoInsercao resultado;
    resultado.houveSplit = false;
    resultado.chavePromovida = 0;
    resultado.novaPagina = -1;

    if (n <= MAXCHAVES) {
        // sem overflow, apenas grava de volta
        pg->numeroElementos = n;
        for (int i = 0; i < n; i++)
            pg->chaves[i] = chavesTemp[i];
        for (int i = 0; i <= n; i++)
            pg->valores[i] = valoresTemp[i];
        salvaPagina(idPagina, pg);
    }
    else {
        // overflow: divide a pagina interna em duas. A chave do meio SOBE para o
        // pai (nao fica copiada em nenhuma das duas metades, diferente da folha)
        int meio = n / 2;
        int chaveMeio = chavesTemp[meio];

        pg->numeroElementos = meio;
        for (int i = 0; i < meio; i++)
            pg->chaves[i] = chavesTemp[i];
        for (int i = 0; i <= meio; i++)
            pg->valores[i] = valoresTemp[i];

        int idNovaPagina;
        pagina *novaPg = novaPagina(&idNovaPagina);
        novaPg->folha = false;
        novaPg->numeroElementos = n - meio - 1;
        for (int i = meio+1; i < n; i++)
            novaPg->chaves[i-meio-1] = chavesTemp[i];
        for (int i = meio+1; i <= n; i++)
            novaPg->valores[i-meio-1] = valoresTemp[i];

        salvaPagina(idPagina, pg);
        salvaPagina(idNovaPagina, novaPg);

        resultado.houveSplit = true;
        resultado.chavePromovida = chaveMeio;
        resultado.novaPagina = idNovaPagina;

        delete novaPg;
    }

    return resultado;
}

void btree::removeChave(int chave) {
	// neste trabalho, não é necessário implementar a remoção com rebalanceamento
    // (fusao/redistribuicao de paginas). Aqui localizamos a folha correta e
    // removemos a chave/valor dela, o que já é suficiente para os fins do trabalho.

    if (cabecalhoArvore.paginaRaiz == -1)
        return;

    int idPagina = cabecalhoArvore.paginaRaiz;
    pagina *pg = lePagina(idPagina);

    // desce ate a folha que deveria conter a chave
    while (!pg->folha) {
        int i = 0;
        while (i < pg->numeroElementos && chave >= pg->chaves[i])
            i++;

        int idFilho = pg->valores[i];
        delete pg;
        pg = lePagina(idFilho);
        idPagina = idFilho;
    }

    // procura a chave na folha
    for (int i = 0; i < pg->numeroElementos; i++) {
        if (pg->chaves[i] == chave) {
            // desloca os elementos seguintes uma posicao para tras
            for (int j = i; j < pg->numeroElementos - 1; j++) {
                pg->chaves[j] = pg->chaves[j+1];
                pg->valores[j] = pg->valores[j+1];
            }
            pg->numeroElementos--;
            salvaPagina(idPagina, pg);

            // se remover, atualizar cabecalho
            cabecalhoArvore.numeroElementos--;
            salvaCabecalho();
            break;
        }
    }

    delete pg;
}

int btree::buscaChave(int chave) {

    // se encontrar chave, retornar valor, caso contrário, retornar -1
    if (cabecalhoArvore.paginaRaiz == -1)
        return -1;

    int idPagina = cabecalhoArvore.paginaRaiz;
    pagina *pg = lePagina(idPagina);

    // desce ate a folha que deveria conter a chave
    while (!pg->folha) {
        int i = 0;
        while (i < pg->numeroElementos && chave >= pg->chaves[i])
            i++;

        int idFilho = pg->valores[i];
        delete pg;
        pg = lePagina(idFilho);
    }

    int resultado = -1;
    for (int i = 0; i < pg->numeroElementos; i++) {
        if (pg->chaves[i] == chave) {
            resultado = pg->valores[i];
            break;
        }
    }

    delete pg;
    return resultado;
}

#endif	/* _BTREE_CPP */
