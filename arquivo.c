#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"


// carrega as figurinhas do csv
void carregarCSV(Figurinha **album,
                 int *total) {

    FILE *arquivo;

    // abre o csv para leitura
    arquivo = fopen("figurinhas2026.csv", "r");

    // verifica se conseguiu abrir
    if (arquivo == NULL) {

        printf("Erro ao abrir CSV.\n");
        return;
    }

    char linha[300];

    // ignora o cabecalho
    fgets(linha, 300, arquivo);

    // le linha por linha
    while (fgets(linha,
                 300,
                 arquivo)) {

        // aumenta o vetor dinamicamente
        *album = realloc(*album,
                        (*total + 1) *
                        sizeof(Figurinha));

        // pega a posicao da nova figurinha
        Figurinha *nova =
        &(*album)[*total];

        // remove quebra de linha
        linha[strcspn(linha,
                      "\n")] = 0;

        char *token;

        // separa os dados pela virgula
        token = strtok(linha, ",");
        strcpy(nova->codigo,
               token);

        token = strtok(NULL, ",");
        strcpy(nova->titulo,
               token);

        token = strtok(NULL, ",");
        strcpy(nova->secao,
               token);

        token = strtok(NULL, ",");
        strcpy(nova->grupo,
               token);

        token = strtok(NULL, ",");
        strcpy(nova->tipo,
               token);

        // valores iniciais
        nova->colada = 0;
        nova->quantidade = 1;

        // aumenta quantidade total
        (*total)++;
    }

    fclose(arquivo);

    printf("CSV carregado com sucesso!\n");
}


// salva as figurinhas no binario
void salvarBinario(Figurinha *album,
                   int total) {

    FILE *arquivo;

    // abre arquivo binario
    arquivo = fopen("album.dat",
                     "wb");

    // verifica erro
    if (arquivo == NULL) {

        printf("Erro ao salvar.\n");
        return;
    }

    // salva quantidade de figurinhas
    fwrite(&total,
           sizeof(int),
           1,
           arquivo);

    // salva vetor inteiro
    fwrite(album,
           sizeof(Figurinha),
           total,
           arquivo);

    fclose(arquivo);

    printf("Dados salvos!\n");
}


// carrega o arquivo binario
void carregarBinario(Figurinha **album,
                     int *total) {

    FILE *arquivo;

    // tenta abrir o arquivo salvo
    arquivo = fopen("album.dat",
                     "rb");

    // se nao existir, carrega csv
    if (arquivo == NULL) {

        printf("Arquivo binario nao encontrado.\n");
        printf("Carregando CSV...\n");

        carregarCSV(album,
                    total);

        return;
    }

    // le total de figurinhas
    fread(total,
          sizeof(int),
          1,
          arquivo);

    // aloca memoria
    *album = malloc((*total) *
                    sizeof(Figurinha));

    // le todas as figurinhas
    fread(*album,
          sizeof(Figurinha),
          *total,
          arquivo);

    fclose(arquivo);

    printf("Binario carregado!\n");
}


// exporta as figurinhas para csv
void exportarCSV(Figurinha *album,
                 int total) {

    FILE *arquivo;

    // cria arquivo csv
    arquivo = fopen("exportado.csv",
                     "w");

    // verifica erro
    if (arquivo == NULL) {

        printf("Erro ao exportar.\n");
        return;
    }

    // escreve cabecalho
    fprintf(arquivo,
    "codigo,titulo,secao,grupo,tipo\n");

    // percorre todas as figurinhas
    for (int i = 0;
         i < total;
         i++) {

        // escreve no csv
        fprintf(arquivo,
        "%s,%s,%s,%s,%s\n",

        album[i].codigo,
        album[i].titulo,
        album[i].secao,
        album[i].grupo,
        album[i].tipo);
    }

    fclose(arquivo);

    printf("CSV exportado com sucesso!\n");
}