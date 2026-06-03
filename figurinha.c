#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "figurinha.h"
void inserirFigurinha(Album *album){
    album->quantidade++;
    album->figurinhas=realloc(album->figurinhas, album->quantidade *sizeof(Figurinha));
    Figurinha *nova=&album->figurinhas[album->quantidade-1];
    printf("\nCódigo: ");
    scanf("%s", nova->codigo);
    printf("Título: ");
    scanf("%s", nova->titulo);
    printf("Seção: ");
    scanf("%s", nova->secao);
    printf("Grupo: ");
    scanf("%s", nova->grupo);
    printf("Tipo: ");
    scanf("%s", nova->tipo);
    nova->colada=0;
    nova->repetidas=0;
    printf("\nFigurinha cadastrada com sucesso!\n");
}
void listarFigurinhas(Album *album){
    if(album->quantidade==0){
        printf("\nNenhuma figurinha encontrada.\n");
        return;
    }
    for(int i=0; i<album->quantidade; i++){
        printf("\n=======================");
        printf("\nCódigo: %s", album->figurinhas[i].codigo);
        printf("\nTitulo: %s", album->figurinhas[i].titulo);
        printf("\nSeção: %s", album->figurinhas[i].secao);
        printf("\nGrupo: %s", album->figurinhas[i].grupo);
        printf("\nTipo: %s", album->figurinhas[i].tipo);
        printf("\nColada: %d", album->figurinhas[i].colada);
        printf("\nRepetidas: %d", album->figurinhas[i].repetidas);
    }
}
int buscarFigurinha(Album *album, char codigo[]){
    for(int i=0; i<album->quantidade; i++){
        if(strcmp(album->figurinhas[i].codigo, codigo)==0){
            return i;
        }
    }
    return -1;
}
void alterarFigurinha(Album *album){
    char codigo[50];
    printf("\nDigite o código da figurinha: ");
    scanf("%s", codigo);
    int pos;
    pos=buscarFigurinha(album, codigo);
    if(pos==-1){
        printf("\nFigurinha não encontrada!\n");
        return;
    }
    printf("\nNovo titulo: ");
    scanf("%s", album->figurinhas[pos].titulo);
    printf("\nNova seção: ");
    scanf("%s", album->figurinhas[pos].secao);
    printf("\nNovo grupo: ");
    scanf("%s", album->figurinhas[pos].grupo);
    printf("\nNovo tipo: ");
    scanf("%s", album->figurinhas[pos].tipo);
    printf("\nFigurinha alterada com sucesso!\n");
}
void excluirFigurinha(Album *album){
    char codigo[50];
    printf("\nDigite o código da figurinha: ");
    scanf("%s", codigo);
    int pos=buscarFigurinha(album, codigo);
    if(pos==-1){
        printf("\nFigurinha não encontrada!\n");
        return;
    }
    for(int i=pos; i<album->quantidade -1; i++){
        album->figurinhas[i]=album->figurinhas[i+1];
    }
    album->quantidade--;
    album->figurinhas=realloc(album->figurinhas, album->quantidade *sizeof(Figurinha));
    printf("\nFigurinha removida com sucesso!\n");
}
void liberarAlbum(Album *album){
    free(album->figurinhas);
    album->figurinhas = NULL;
    album->quantidade = 0;
}