#include <stdio.h>
#include <stdlib.h>

#include "figurinha.h"
#include "arquivo.h"


#include "interface.h"

int main() {

    Figurinha *album =
    NULL;

    int total = 0;
    int opcao;

    // tenta carregar dados
    carregarBinario(&album, &total);

   do {
        printf("\n===== ALBUM COPA 2026 =====\n");
        printf("1 - Cadastrar figurinha\n");
        printf("2 - Listar figurinhas\n");
        printf("3 - Buscar figurinha\n");
        printf("4 - Alterar figurinha\n");
        printf("5 - Excluir figurinha\n");
        printf("6 - Salvar dados\n");
        printf("7 - Exportar CSV\n");
        printf("8 - Abrir pacote\n");
        printf("9 - Ver faltantes\n");
        printf("10 - ABRIR INTERFACE GRÁFICA (Raylib) 🚀\n"); // <-- Nova Linha!
        printf("0 - Sair\n");
        printf("Opcao: ");
        
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFigurinha(&album, &total);
                break;

            case 2:
                listarFigurinhas(album, total);
                break;

            case 3: 
                char codigo[20];
                printf("\nCodigo: ");
                scanf("%s", codigo);
                int pos = buscarFigurinha(album, total, codigo);
                if (pos == -1) {
                    printf("Nao encontrada.\n");
                } 
                else {
                    printf("\nEncontrada!\n");
                    printf("Titulo: %s\n", album[pos].titulo);
                }
                break;
                
            case 4:
                alterarFigurinha(album, total);
                break;

            case 5:
                excluirFigurinha(&album, &total);
                break;

            case 6:
                salvarBinario(album, total);
                break;

            case 7:
                exportarCSV(album, total);
                break;

            case 8:
                abrirPacote(album, total);
                break;

            case 9:
                verFaltantes(album, total);
                break;

            case 10:
                printf("Abrindo a janela gráfica... Use o mouse por lá!\n");
                abrir_sistema_grafico(album, total); // <-- Adicione (album, total) aqui!
                break;

            case 0:
                salvarBinario(album, total);
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}