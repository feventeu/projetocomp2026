#include "raylib.h"
#include "figurinha.h" // Para termos acesso à estrutura Figurinha

#include "interface.h"



void rodar_interface_grafica(Figurinha* album, int total) {

    const int larguraTela = 800;
    const int alturaTela = 600;
    
    InitWindow(larguraTela, alturaTela, "Álbum Copa 2026 - Menu Gráfico");
    SetTargetFPS(60);

    TelaAtual tela = TELA_MENU; // Começa no menu principal gráfico

    while (!WindowShouldClose()) {
        // ==========================================
        // 1. ATUALIZAÇÃO DA LÓGICA (Entradas do usuário)
        // ==========================================
        if (tela == TELA_MENU) {
            // Se clicar no botão ou pressionar '1', vai para as estatísticas
            if (IsKeyPressed(KEY_ONE)) tela = TELA_DASHBOARD;
            if (IsKeyPressed(KEY_TWO)) tela = TELA_ALBUM;
            if (IsKeyPressed(KEY_THREE)) tela = TELA_TROCAS;
        } else {
            // Se estiver em qualquer sub-tela, aperta ESC ou BACKSPACE para voltar ao menu
            if (IsKeyPressed(KEY_BACKSPACE)) tela = TELA_MENU;
        }

        // ==========================================
        // 2. RENDERIZAÇÃO (Desenho na Tela)
        // ==========================================
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (tela) {
            case TELA_MENU:   
                DrawRectangle(0, 0, larguraTela, 80, MAROON);
                DrawText("ÁLBUM COPA 2026 - INTERFACE", 40, 25, 26, WHITE);
                
                DrawText("Pressione [1] para ver Estatísticas (Dashboard)", 50, 180, 20, DARKGRAY);
                DrawText("Pressione [2] para ver Visualizador de Cartas (Álbum)", 50, 240, 20, DARKGRAY);
                DrawText("Pressione [3] para ver Sistema de Trocas", 50, 300, 20, DARKGRAY);
                break;

            case TELA_DASHBOARD:
                // Parte 1 da sua equipe: Estatísticas de preenchimento
                DrawRectangle(0, 0, larguraTela, 80, DARKGREEN);
                DrawText("DASHBOARD DE ESTATÍSTICAS", 40, 25, 26, WHITE);
                DrawText("Pressione [BACKSPACE] para voltar", 40, 550, 16, GRAY);
                
                // [Adicione seus retângulos e barras de progresso aqui!]
                break;

            case TELA_ALBUM:
                // Parte 2 da sua equipe: Visualizador de Cartas
                DrawRectangle(0, 0, larguraTela, 80, BLUE);
                DrawText("VISUALIZADOR DE CARTAS (ÁLBUM)", 40, 25, 26, WHITE);
                DrawText("Pressione [BACKSPACE] para voltar", 40, 550, 16, GRAY);
                
                // [Adicione a lógica para folhear as figurinhas aqui!]
                break;

                // Parte 3 da sua equipe: Sistema de trocas virtuais
            case TELA_TROCAS: {
                int repetida = -1;
                int faltante = -1;

                DrawRectangle(0, 0, larguraTela, 80, ORANGE);
                DrawText("SISTEMA DE TROCAS VIRTUAIS", 40, 25, 26, WHITE);
                DrawText("Pressione [BACKSPACE] para voltar", 40, 550, 16, GRAY);

                for (int i = 0; i < total; i++) {
                    if (album[i].quantidade > 0) {
                        repetida = i;
                        break;
                    }
                }

                for (int i = 0; i < total; i++) {
                    if (album[i].colada == 0) {
                        faltante = i;
                        break;
                    }
                }

                if (repetida == -1) {
                    DrawText("Voce nao possui figurinhas repetidas para trocar.", 120, 250, 22, RED);
                } else if (faltante == -1) {
                    DrawText("Parabens! Album completo!", 240, 250, 28, DARKGREEN);
                } else {
                    DrawText("VOCE ENTREGA", 120, 130, 24, MAROON);
                    DrawRectangle(100, 180, 220, 260, LIGHTGRAY);
                    DrawRectangleLines(100, 180, 220, 260, BLACK);
                    DrawText(album[repetida].codigo, 130, 220, 24, BLACK);
                    DrawText(album[repetida].titulo, 130, 270, 20, BLACK);
                    DrawText("REPETIDA", 140, 370, 22, MAROON);

                    DrawText("VOCE RECEBE", 500, 130, 24, DARKGREEN);
                    DrawRectangle(480, 180, 220, 260, RAYWHITE);
                    DrawRectangleLines(480, 180, 220, 260, BLACK);
                    DrawText(album[faltante].codigo, 510, 220, 24, BLACK);
                    DrawText(album[faltante].titulo, 510, 270, 20, BLACK);
                    DrawText("NOVA FIGURINHA", 500, 370, 20, DARKGREEN);

                    DrawText("Pressione [ENTER] para aceitar a troca", 180, 480, 22, BLACK);

                    if (IsKeyPressed(KEY_ENTER)) {
                        album[repetida].quantidade--;
                        album[faltante].colada = 1;
                    }
                }

                break;
            }

            case TELA_SAIR:
                DrawRectangle(0, 0, larguraTela, 80, WHITE);
                DrawText("SAINDO...", 40, 25, 26, BLACK);
                break;

            default:
                break;
        }

        EndDrawing();
    }

    CloseWindow();
}