#ifndef FIGURINHA_H
#define FIGURINHA_H

// estrutura da figurinha
typedef struct {

    char codigo[20];
    char titulo[100];
    char secao[100];
    char grupo[100];
    char tipo[50];

    // 0 = nao tem
    // 1 = ja conseguiu
    int colada;

    // quantidade da figurinha
    int quantidade;

} Figurinha;


// cadastra nova figurinha
void cadastrarFigurinha(Figurinha **album, int *total);


// lista todas
void listarFigurinhas(Figurinha *album, int total);


// busca pelo codigo
int buscarFigurinha(Figurinha *album, int total, char codigo[]);


// altera figurinha
void alterarFigurinha(Figurinha *album, int total);


// remove figurinha
void excluirFigurinha(Figurinha **album, int *total);


// abre pacote de 5 figurinhas
void abrirPacote(Figurinha *album, int total);


// mostra faltantes
void verFaltantes(Figurinha *album, int total);

#endif