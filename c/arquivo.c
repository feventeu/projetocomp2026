#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"


// carrega csv
void carregarCSV(Figurinha **album, int *total) {

    FILE *arquivo;

    arquivo = fopen("figurinhas2026.csv", "r");

    if (arquivo == NULL) {

        printf("Erro ao abrir CSV.\n");
        return;
    }

    char linha[300];

    // pula cabecalho
    fgets(linha, 300, arquivo);

    while (fgets(linha, 300, arquivo)) {

        // aumenta vetor
        *album = realloc(*album,(*total + 1)* sizeof(Figurinha));

        Figurinha *nova = &(*album)[*total];

        // remove quebra linha
        linha[strcspn(linha,"\n")] = 0;

        char *token;

        // separa por virgula
        token = strtok(linha, ",");

        strcpy(nova->codigo,token);

        token = strtok(NULL, ",");

        strcpy(nova->titulo,token);

        token = strtok(NULL, ",");

        strcpy(nova->secao,token);

        token = strtok(NULL, ",");

        strcpy(nova->grupo,token);

        token = strtok(NULL, ",");

        strcpy(nova->tipo, token);

        // album começa vazio
        nova->colada = 0;
        nova->quantidade = 0;

        (*total)++;
    }

    fclose(arquivo);

    printf(
    "CSV carregado!\n");
}


// salva binario
void salvarBinario(
Figurinha *album,
int total) {

    FILE *arquivo;

    arquivo = fopen("album.dat", "wb");

    if (arquivo == NULL) {

        printf("Erro ao salvar.\n");

        return;
    }

    // salva total
    fwrite(&total,sizeof(int), 1, arquivo);

    // salva vetor
    fwrite( album, sizeof(Figurinha),total,arquivo);

    fclose(arquivo);

    printf("Dados salvos!\n");
}


// carrega binario
void carregarBinario(Figurinha **album, int *total) {

    FILE *arquivo;

    arquivo = fopen("album.dat","rb");

    // se nao existir
    if (arquivo == NULL) {

        printf( "Carregando CSV...\n");

        carregarCSV(album,total);

        return;
    }

    // le total
    fread(total, sizeof(int), 1,arquivo);

    // aloca memoria
    *album =  malloc((*total)* sizeof(Figurinha));

    // le vetor
    fread(*album,
    sizeof(Figurinha), *total, arquivo);

    fclose(arquivo);

    printf("Binario carregado!\n");
}


// exporta csv
void exportarCSV(
Figurinha *album,
int total) {

    FILE *arquivo;

    arquivo =fopen("exportado.csv","w");

    if (arquivo == NULL) {

        printf("Erro ao exportar.\n");

        return;
    }

    // cabecalho
    fprintf( arquivo,"codigo,titulo,secao,grupo,tipo\n");

    for (int i = 0; i < total; i++) {

        fprintf(arquivo,"%s,%s,%s,%s,%s\n",

        album[i].codigo,
        album[i].titulo,
        album[i].secao,
        album[i].grupo,
        album[i].tipo);
    }

    fclose(arquivo);

    printf("CSV exportado!\n");
}