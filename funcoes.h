#ifndef FUNCOES_H
#define FUNCOES_H
#include "Structs.h"


void criarTerreno ( Terrenos **terrenos);

void inicializarVetor ( Terrenos **terrenos);

void deletarTerreno ( Terrenos **terrenos);

void mostrarTerreno ( Terrenos **terrenos, int id);

void editarTerreno ( Terrenos **terrenos, int id);

double calcularValorTerreno ( Terrenos **terrenos, int id);

int contarTerrenosOcupados ( Terrenos **terrenos, int numeros_terrenos);

int contarTerrenosLivres ( Terrenos **terrenos);

double calcularValorTotal ( Terrenos **terrenos);

void salvarTerrenos( Terrenos **terrenos, const char *dados);

void carregarTerrenos( Terrenos ***terrenos, const char *dados);

#endif
