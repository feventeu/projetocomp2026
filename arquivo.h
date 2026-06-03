#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "figurinha.h"
void carregarCsv(Album *album);
void salvarBinario(Album *album);
void carregarBinario(Album *album);
void exportarCSV(Album *album);
#endif