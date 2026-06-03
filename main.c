#include <stdio.h>
#include <stdlib.h>
#include "figurinha.h"
#include "arquivo.h"
int main()
{
    Album album;
    album.figurinhas = NULL;
    album.quantidade = 0;
    carregarCsv(&album);
    printf("Quantidade: %d\n", album.quantidade);
    int op;
    do
    {
        printf("\n      ALBUM COPA 2026      \n");
        printf("1 - Inserir figurinha\n");
        printf("2 - Listar figurinhas\n");
        printf("3 - Alterar figurinha\n");
        printf("4 - Excluir figurinha\n");
        printf("0 - Sair.\n");
        printf("Opcao: ");
        scanf("%d", &op);
        
        switch(op)
        {
            case 1:
            inserirFigurinha(&album);
            break;
            case 2:
            listarFigurinhas(&album);
            break;
            case 3:
            alterarFigurinha(&album);
            break;
            case 4:
            excluirFigurinha(&album);
            break;
            case 0:
            salvarBinario(&album);
            printf("Encerrando...\n");
            break;
            default:
            printf("Opcao invalida!\n");
        }
    }while(op != 0);
    liberarAlbum(&album);

    return 0;
}