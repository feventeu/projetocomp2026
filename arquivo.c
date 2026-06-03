#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "figurinha.h"
void carregarCsv(Album *album){
    FILE *arq;
    arq=fopen("figurinhas2026.csv", "r");
    if(arq==NULL){
        printf("Erro ao abrir!\n");
        return;
    }
    char linha[300];
    fgets(linha, 300, arq);
    while(fgets(linha, 300, arq)!=NULL){
        album->quantidade++;
        album->figurinhas=realloc(album->figurinhas, album->quantidade *sizeof(Figurinha));
        Figurinha *f=&album->figurinhas[album->quantidade-1];
        sscanf(linha, "%s, %s, %s, %s, %s", f->codigo, f->titulo, f->secao, f->grupo, f->tipo);
        f->colada=0;
        f->repetidas=0;
    }
    fclose(arq);
    printf("\ncsv carregado com sucesso!\n");
}
void salvarBinario(Album *album)
{
    FILE *arq = fopen("album.bin", "wb");
    if(arq == NULL){
        printf("Erro ao salvar binario!\n");
        return;
    }
    fwrite(&album->quantidade, sizeof(int), 1, arq);
    fwrite(album->figurinhas, sizeof(Figurinha), album->quantidade, arq);
    fclose(arq);
    printf("Album salvo!\n");
}
void carregarBinario(Album *album)
{
    FILE *arq = fopen("album.bin", "rb");
    if(arq == NULL){
        printf("Binario nao encontrado!\n");
        return;
    }
    fread(&album->quantidade, sizeof(int), 1, arq);
    album->figurinhas = malloc(album->quantidade * sizeof(Figurinha));
    fread(album->figurinhas, sizeof(Figurinha), album->quantidade, arq);
    fclose(arq);
    printf("Album carregado!\n");
}