#ifndef FIGURINHA_H
#define FIGURINHA_H
typedef struct{
    char codigo[20];
    char titulo[100];
    char secao[100];
    char grupo[20];
    char tipo[50];
    int colada;
    int repetidas;
}Figurinha;
typedef struct{
    Figurinha *figurinhas;
    int quantidade;
}Album;

void inserirFigurinha(Album *album);
void listarFigurinhas(Album *album);
int buscarFigurinha(
    Album *album,
    char codigo[]
);
void alterarFigurinha(Album *album);
void excluirFigurinha(Album *album);
void liberarAlbum(Album *album);
#endif