#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "figurinha.h"


// cadastra figurinha
void cadastrarFigurinha(Figurinha **album, int *total) {

    // aumenta vetor
    *album = realloc(*album, (*total + 1)* sizeof(Figurinha));

    if (*album == NULL) {

        printf("Erro de memoria.\n");
        return;
    }

    Figurinha *nova = &(*album)[*total];

    printf("\nCodigo: ");
    scanf("%s", nova->codigo);

    printf("Titulo: ");
    scanf(" %s", nova->titulo);

    printf("Secao: ");
    scanf(" %s", nova->secao);

    printf("Grupo: ");
    scanf(" %s", nova->grupo);

    printf("Tipo: ");
    scanf(" %s", nova->tipo);

    // comeca sem ter figurinha
    nova->colada = 0;
    nova->quantidade = 0;

    (*total)++;

    printf("\nFigurinha cadastrada!\n");
}


// lista figurinhas
void listarFigurinhas(Figurinha *album, int total) {

    if (total == 0) {

        printf("\nNenhuma figurinha.\n");
        return;
    }

    printf("\n===== FIGURINHAS =====\n");

    for (int i = 0; i < total; i++) {

        printf("\nFigurinha %d\n",i + 1);

        printf("Codigo: %s\n", album[i].codigo);

        printf("Titulo: %s\n", album[i].titulo);

        printf("Secao: %s\n", album[i].secao);

        printf("Grupo: %s\n", album[i].grupo);

        printf("Tipo: %s\n", album[i].tipo);

        printf("Possui: %s\n",album[i].colada ?"Sim" : "Nao");

        printf("Quantidade: %d\n",album[i].quantidade);
    }
}


// busca figurinha
int buscarFigurinha(Figurinha *album, int total, char codigo[]) {

    for (int i = 0; i < total; i++) {

        // compara codigo
        if (strcmp(album[i].codigo, codigo) == 0) {

            return i;
        }
    }

    return -1;
}


// altera
void alterarFigurinha(Figurinha *album, int total) {

    char codigo[20];

    printf("\nDigite codigo: ");
    scanf("%s", codigo);

    int pos = buscarFigurinha(album, total, codigo);

    if (pos == -1) {

        printf("Nao encontrada.\n");
        return;
    }

    printf("Novo titulo: ");
    scanf(" %s", album[pos].titulo);

    printf("Nova secao: ");
    scanf(" %s", album[pos].secao);

    printf("Novo grupo: ");
    scanf(" %s", album[pos].grupo);

    printf("Novo tipo: ");
    scanf(" %s", album[pos].tipo);

    printf("\nAlterada!\n");
}


// excluir figurinha
void excluirFigurinha(Figurinha **album, int *total) {

    char codigo[20];

    printf("\nCodigo: ");
    scanf("%s", codigo);

    int pos = buscarFigurinha(*album, *total, codigo);

    if (pos == -1) {

        printf("Nao encontrada.\n");
        return;
    }

    // move vetor
    for (int i = pos; i < *total - 1; i++) {

        (*album)[i] = (*album)[i + 1];
    }

    // reduz vetor
    *album = realloc(*album, (*total - 1)* sizeof(Figurinha));

    (*total)--;

    printf("\nFigurinha removida.\n");
}


// abre pacote
void abrirPacote(Figurinha *album, int total) {

    if (total == 0) {

        printf("\nAlbum vazio.\n");
        return;
    }

    printf("\n===== PACOTE =====\n");


    for (int i = 0; i < 7; i++) {

        int sorteada = rand() % total;

        int opcao;
        album[sorteada].quantidade++;

        printf("\nFigurinha %d\n", i + 1);
        printf("Codigo: %s\n", album[sorteada].codigo);
        printf("Titulo: %s\n", album[sorteada].titulo);

        printf("\n1 - Colar no album");
        printf("\n2 - Guardar para troca");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        printf("%s\n", album[sorteada].titulo);

        // verifica repetida
        if (album[sorteada].quantidade > 1) {

            printf("repetida!\n");

        } else {

            printf("nova!\n");
        }
        if (opcao == 1) {

        if (album[sorteada].colada == 0) {
            album[sorteada].colada = 1;
            printf("Figurinha colada!\n");
        } else {
            album[sorteada].quantidade++;
            printf("Voce ja tinha essa figurinha. Ela foi para troca.\n");
        }

        } else if (opcao == 2) {

            album[sorteada].quantidade++;
            printf("Figurinha guardada para troca.\n");

        } else {

            printf("Opcao invalida.\n");
        }
    }
}


// mostra faltantes
void verFaltantes(Figurinha *album, int total) {

    int faltam = 0;

    for (int i = 0; i < total; i++) {

        if (album[i].quantidade == 0) {

            faltam++;
        }
    }

    printf("\nFaltam %d figurinhas.\n", faltam);
}