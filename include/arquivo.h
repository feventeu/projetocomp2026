#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "figurinha.h"


// carrega csv
void carregarCSV(Figurinha **album, int *total);


// salva binario
void salvarBinario(Figurinha *album, int total);


// carrega binario
void carregarBinario(Figurinha **album, int *total);


// exporta csv
void exportarCSV(Figurinha *album, int total);

#endif