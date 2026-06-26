#include "raylib.h"
#include "interface.h"

// Controle do tema: 0 = Escuro, 1 = Claro
static int modoClaro = 0; 

// Controle de paginação do álbum
static int paginaAtual = 0;
const int FIGURINHAS_POR_PAGINA = 6;

/**
 * Desenha o botão de alternar tema no canto superior direito
 */
static void desenhar_botao_tema(int larguraTela) {
    Vector2 posicaoMouse = GetMousePosition();
    Rectangle btnTema = { larguraTela - 130, 25, 110, 35 };

    if (CheckCollisionPointRec(posicaoMouse, btnTema)) {
        DrawRectangleRec(btnTema, LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            modoClaro = !modoClaro; 
        }
    } 
    else {
        DrawRectangleRec(btnTema, modoClaro ? DARKGRAY : RAYWHITE);
    }
    DrawRectangleLinesEx(btnTema, 1, BLACK);
    
    if (modoClaro) {
        DrawText("Modo Escuro", btnTema.x + 8, btnTema.y + 10, 14, WHITE);
    } 
    else {
        DrawText("Modo Claro", btnTema.x + 12, btnTema.y + 10, 14, BLACK);
    }
}

/**
 * Desenha o Menu Principal e gerencia os cliques
 */
static TelaAtual gerenciar_cliques_menu(int larguraTela) {
    Vector2 posicaoMouse = GetMousePosition();

    Rectangle btnEstatisticas = { 150, 180, 500, 60 };
    Rectangle btnAlbum = { 150, 270, 500, 60 };
    Rectangle btnTrocas = { 150, 360, 500, 60 };
    Rectangle btnSair = { 150, 450, 500, 60 };

    TelaAtual proximaTela = TELA_MENU;

    DrawRectangle(0, 0, larguraTela, 90, BLUE);
    DrawText("ÁLBUM COPA 2026", larguraTela / 2 - MeasureText("ÁLBUM COPA 2026", 32) / 2, 15, 32, YELLOW);
    DrawText("Menu de Opções Gráficas", larguraTela / 2 - MeasureText("Menu de Opções Gráficas", 16) / 2, 55, 16, LIGHTGRAY);

    desenhar_botao_tema(larguraTela);

    Color corFundoBotao = modoClaro ? RAYWHITE : BLACK;
    Color corTextoBotao = modoClaro ? BLACK : WHITE;
    Color corBordaBotao = modoClaro ? DARKGRAY : WHITE;

    // Botão 1: Estatísticas
    if (CheckCollisionPointRec(posicaoMouse, btnEstatisticas)) {
        DrawRectangleRec(btnEstatisticas, YELLOW); 
        DrawRectangleLinesEx(btnEstatisticas, 2, YELLOW);
        DrawText("1. Ver Estatísticas (Dashboard)", btnEstatisticas.x + 30, btnEstatisticas.y + 18, 20, BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) proximaTela = TELA_DASHBOARD;
    } else {
        DrawRectangleRec(btnEstatisticas, corFundoBotao);
        DrawRectangleLinesEx(btnEstatisticas, 2, corBordaBotao);
        DrawText("1. Ver Estatísticas (Dashboard)", btnEstatisticas.x + 30, btnEstatisticas.y + 18, 20, corTextoBotao);
    }   

    // Botão 2: Álbum
    if (CheckCollisionPointRec(posicaoMouse, btnAlbum)) {
        DrawRectangleRec(btnAlbum, YELLOW);
        DrawRectangleLinesEx(btnAlbum, 2, YELLOW);
        DrawText("2. Folhear Álbum (Visualizador)", btnAlbum.x + 30, btnAlbum.y + 18, 20, BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) proximaTela = TELA_ALBUM;
    } else {
        DrawRectangleRec(btnAlbum, corFundoBotao);
        DrawRectangleLinesEx(btnAlbum, 2, corBordaBotao);
        DrawText("2. Folhear Álbum (Visualizador)", btnAlbum.x + 30, btnAlbum.y + 18, 20, corTextoBotao);
    }

    // Botão 3: Trocas
    if (CheckCollisionPointRec(posicaoMouse, btnTrocas)) {
        DrawRectangleRec(btnTrocas, YELLOW);
        DrawRectangleLinesEx(btnTrocas, 2, YELLOW);
        DrawText("3. Abrir Pacotes / Trocas Virtuais", btnTrocas.x + 30, btnTrocas.y + 18, 20, BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            proximaTela = TELA_TROCAS;
        }
    } else {
        DrawRectangleRec(btnTrocas, corFundoBotao);
        DrawRectangleLinesEx(btnTrocas, 2, corBordaBotao);
        DrawText("3. Abrir Pacotes / Trocas Virtuais", btnTrocas.x + 30, btnTrocas.y + 18, 20, corTextoBotao);
    }

    // Botão 4: Sair
    if (CheckCollisionPointRec(posicaoMouse, btnSair)) {
        DrawRectangleRec(btnSair, RED);
        DrawRectangleLinesEx(btnSair, 2, RED);
        DrawText("0. Fechar Interface Gráfica", btnSair.x + 30, btnSair.y + 18, 20, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            proximaTela = TELA_SAIR;
        }
    } else {
        DrawRectangleRec(btnSair, corFundoBotao);
        DrawRectangleLinesEx(btnSair, 2, corBordaBotao);
        DrawText("0. Fechar Interface Gráfica", btnSair.x + 30, btnSair.y + 18, 20, corTextoBotao);
    }

    return proximaTela;
}

/**
 * Função principal do sistema gráfico
 */
void abrir_sistema_grafico(Figurinha *album, int total) { 
    const int larguraTela = 800;
    const int alturaTela = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
    InitWindow(larguraTela, alturaTela, "Álbum Copa 2026 - UTFPR");
    SetTargetFPS(60);

    TelaAtual telaAtual = TELA_MENU;

    while (!WindowShouldClose() && telaAtual != TELA_SAIR) {
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        BeginDrawing();
        ClearBackground(modoClaro ? RAYWHITE : BLACK); 

        Color corTextoGeral = modoClaro ? BLACK : WHITE;
        Color corBordaCaixa = modoClaro ? DARKGRAY : WHITE;

        switch (telaAtual) {
            case TELA_MENU:
                telaAtual = gerenciar_cliques_menu(larguraTela);
                break;

            case TELA_DASHBOARD: {
                int coladas = 0;
                for (int i = 0; i < total; i++) {
                    if (album[i].colada == 1) { 
                        coladas++;
                    }
                }
                float porcentagemGeral = (total > 0) ? ((float)coladas / total) * 100.0f : 0.0f;

                DrawRectangle(0, 0, larguraTela, 90, BLUE);
                DrawText("DASHBOARD DE ESTATÍSTICAS", 40, 20, 28, YELLOW);
                DrawText("Progresso de Preenchimento do seu Álbum", 40, 55, 16, LIGHTGRAY);
                
                desenhar_botao_tema(larguraTela);

                DrawRectangle(50, 130, 700, 100, modoClaro ? LIGHTGRAY : BLACK);
                DrawRectangleLinesEx((Rectangle){50, 130, 700, 100}, 2, corBordaCaixa);
                
                DrawText(TextFormat("Total de Espaços no Álbum: %d", total), 80, 150, 20, corTextoGeral);
                DrawText(TextFormat("Figurinhas Coladas: %d", coladas), 80, 190, 20, LIME);
                DrawText(TextFormat("%.1f%%", porcentagemGeral), 620, 155, 36, YELLOW);
                DrawText("Concluído", 620, 195, 14, LIGHTGRAY);

                DrawText("Barra de Progresso Geral:", 50, 270, 18, corTextoGeral);
                DrawRectangle(50, 300, 700, 40, DARKGRAY);
                
                int larguraProgresso = (int)((porcentagemGeral / 100.0f) * 692);
                if (larguraProgresso > 0) {
                    DrawRectangle(54, 304, larguraProgresso, 32, LIME);
                }
                DrawRectangleLinesEx((Rectangle){50, 300, 700, 40}, 2, corBordaCaixa);

                if (porcentagemGeral == 100.0f) {
                    DrawText("Parabéns! Você completou o álbum!", 50, 370, 20, GOLD);
                } 
                else if (porcentagemGeral > 50.0f) {
                    DrawText("Mais da metade já foi! Continue abrindo pacotes!", 50, 370, 18, LIME);
                } 
                else {
                    DrawText("Seu álbum está no começo. Rumo ao Hexa!", 50, 370, 18, LIGHTGRAY);
                }

                DrawRectangle(0, 540, larguraTela, 60, modoClaro ? LIGHTGRAY : DARKGRAY);
                DrawText("Pressione [BACKSPACE] para retornar ao Menu Principal", 40, 560, 16, corTextoGeral);
                
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    telaAtual = TELA_MENU;
                }
                break;
            }

            case TELA_ALBUM: {
                DrawRectangle(0, 0, larguraTela, 90, BLUE);
                DrawText("VISUALIZADOR DO ÁLBUM", 40, 20, 28, YELLOW);
                DrawText("Use as setas [←] e [→] para folhear as páginas", 40, 55, 16, LIGHTGRAY);
                desenhar_botao_tema(larguraTela);

                int totalPaginas = (total + FIGURINHAS_POR_PAGINA - 1) / FIGURINHAS_POR_PAGINA;

                if (IsKeyPressed(KEY_RIGHT) && paginaAtual < totalPaginas - 1) paginaAtual++;
                if (IsKeyPressed(KEY_LEFT) && paginaAtual > 0) paginaAtual--;

                int inicioIndice = paginaAtual * FIGURINHAS_POR_PAGINA;
                
                for (int i = 0; i < FIGURINHAS_POR_PAGINA; i++) {
                    int indiceFigurinha = inicioIndice + i;
                    if (indiceFigurinha >= total){
                        break; 

                    }
                    int coluna = i % 3;
                    int linha = i / 3;
                    int x = 60 + (coluna * 240);
                    int y = 130 + (linha * 190);

                    Rectangle card = { x, y, 200, 160 };

                    //Sincronizado com os campos exatos do seu figurinha.h
                    if (album[indiceFigurinha].colada == 1) {
                        DrawRectangleRec(card, modoClaro ? LIGHTGRAY : DARKGRAY);
                        DrawRectangleLinesEx(card, 3, LIME);
                        
                        // string
                        DrawText(TextFormat("Cód: %s", album[indiceFigurinha].codigo), x + 15, y + 15, 20, YELLOW);
                        DrawText(album[indiceFigurinha].titulo, x + 15, y + 50, 16, corTextoGeral);
                        DrawText(album[indiceFigurinha].secao, x + 15, y + 80, 14, LIGHTGRAY);
                        
                        // Mostra a quantidade de repetidas caso tenha mais de 1
                        if (album[indiceFigurinha].quantidade > 1) {
                            DrawText(TextFormat("Repetidas: %d", album[indiceFigurinha].quantidade - 1), x + 15, y + 105, 14, ORANGE);
                        }
                        
                        DrawText("COLADA!", x + 15, y + 130, 16, LIME);
                    } 
                    else {
                        DrawRectangleRec(card, modoClaro ? RAYWHITE : BLACK);
                        DrawRectangleLinesEx(card, 1, GRAY);
                        
                        DrawText(TextFormat("Cód: %s", album[indiceFigurinha].codigo), x + 15, y + 15, 20, GRAY);
                        DrawText("FALTANDO", x + 15, y + 70, 18, RED);
                    }
                }

                // Número da Página ou mensagem de aviso
                if (totalPaginas == 0) {
                    DrawText("Nenhuma figurinha cadastrada no sistema.", larguraTela / 2 - 170, 300, 18, RED);
                } 
                else {
                    DrawText(TextFormat("Página %d de %d", paginaAtual + 1, totalPaginas), larguraTela / 2 - 50, 510, 16, corTextoGeral);
                }

                DrawRectangle(0, 540, larguraTela, 60, modoClaro ? LIGHTGRAY : DARKGRAY);
                DrawText("Pressione [BACKSPACE] para retornar ao Menu Principal", 40, 560, 16, corTextoGeral);
                
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    telaAtual = TELA_MENU;
                }
                break;
            }

            case TELA_TROCAS: {
                int repetida = -1;
                int faltante = -1;

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

                DrawRectangle(0, 0, larguraTela, 90, ORANGE);
                DrawText("SISTEMA DE TROCAS", 40, 25, 28, WHITE);
                DrawText("Pressione [BACKSPACE] para voltar", 40, 560, 16, corTextoGeral);

                if (repetida == -1) {
                    DrawText("Voce nao possui figurinhas repetidas.", 130, 260, 24, RED);
                } else if (faltante == -1) {
                    DrawText("Parabens! Album completo!", 220, 260, 28, LIME);
                } else {
                    DrawText("VOCE ENTREGA", 120, 130, 24, MAROON);
                    DrawRectangle(100, 180, 220, 260, modoClaro ? LIGHTGRAY : DARKGRAY);
                    DrawRectangleLines(100, 180, 220, 260, BLACK);
                    DrawText(album[repetida].codigo, 130, 220, 24, BLACK);
                    DrawText(album[repetida].titulo, 130, 270, 18, BLACK);
                    DrawText("REPETIDA", 135, 370, 22, MAROON);

                    DrawText("VOCE RECEBE", 500, 130, 24, DARKGREEN);
                    DrawRectangle(480, 180, 220, 260, modoClaro ? RAYWHITE : DARKGRAY);
                    DrawRectangleLines(480, 180, 220, 260, BLACK);
                    DrawText(album[faltante].codigo, 510, 220, 24, BLACK);
                    DrawText(album[faltante].titulo, 510, 270, 18, BLACK);
                    DrawText("NOVA", 555, 370, 22, DARKGREEN);

                    DrawText("Pressione [ENTER] para aceitar a troca", 170, 480, 22, corTextoGeral);

                    if (IsKeyPressed(KEY_ENTER)) {
                        album[repetida].quantidade--;
                        album[faltante].colada = 1;
                    }
                }   

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    telaAtual = TELA_MENU;
                }

                break;
            }

            default:
                break;
        }

        EndDrawing();
    }

    CloseWindow();
}