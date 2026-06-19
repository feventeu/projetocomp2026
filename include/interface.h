#ifndef INTERFACE_H
#define INTERFACE_H

#include "figurinha.h" // Para o compilador conhecer a estrutura Figurinha

typedef enum { 
    TELA_MENU = 0, 
    TELA_DASHBOARD, 
    TELA_ALBUM, 
    TELA_TROCAS,
    TELA_SAIR
} TelaAtual;

// Agora a função recebe o ponteiro do álbum e a quantidade de figurinhas
void abrir_sistema_grafico(Figurinha *album, int total);

#endif