#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"
#include "funcoes.h"

#define MAX_TERRENOS 100

int calcularHash(int id){
    return abs(id % MAX_TERRENOS);
}

int buscarIndicePorId(Terrenos **terrenos, int id){
    int pos = calcularHash(id);
    int inicio = pos;

    while (terrenos[pos] != NULL) {
        if (terrenos[pos]->id == id){
            return pos;
        }

        pos = (pos + 1) % MAX_TERRENOS;

        if (pos == inicio) {
            return -1;
        }
    }
    return -1;
}

void inicializarVetor(Terrenos **terrenos) {
    for (int i = 0; i < MAX_TERRENOS; i++) {
        terrenos[i] = NULL;
    }
}

void criarTerreno(Terrenos **terrenos) {
    Terrenos *novo = (Terrenos *)malloc(sizeof(Terrenos));

    if (novo == NULL) {
        perror("Erro de memoria");
        return;
    }

    printf("\n----- Cadastro de Novo Terreno -----\n");
    
    printf("ID do Terreno: ");
    if (scanf("%d", &novo->id) != 1) { free(novo); return; }

    int pos = calcularHash(novo->id);
    int inicio = pos;
    int inserido = 0;

    while (terrenos[pos] != NULL) {
        if (terrenos[pos]->id == novo->id) {
            printf("Erro: ID %d ja existe na posicao %d.\n", novo->id, pos);
            free(novo);
            return;
        }

        pos = (pos + 1) % MAX_TERRENOS;

        if (pos == inicio) {
            printf("Erro: Capacidade maxima atingida (Vetor Cheio).\n");
            free(novo);
            return;
        }
    }

    printf("Nome do Dono: ");
    scanf(" %[^\n]", novo->dono.nome);

    printf("CPF do Dono: ");
    scanf(" %[^\n]", novo->dono.cpf);
    
    printf("Telefone do Dono: ");
    scanf(" %[^\n]", novo->dono.tel);

    printf("Data de Nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &novo->dono.data_nasc.dia, &novo->dono.data_nasc.mes, &novo->dono.data_nasc.ano);

    printf("Data de Compra (dd mm aaaa): ");
    if (scanf("%d %d %d", &novo->data_compra.dia, &novo->data_compra.mes, &novo->data_compra.ano) != 3);

    printf("Largura (m): ");
    scanf("%f", &novo->largura);

    printf("Comprimento (m): ");
    scanf("%f", &novo->comprimento);
    
    printf("Preço por m2: R$ ");
    scanf("%f", &novo->preco_m2);

    novo->area = novo->largura * novo->comprimento;

    terrenos[pos] = novo;
    printf("Terreno ID %d cadastrado com sucesso na posição %d.\n", novo->id, pos);
}

void deletarTerreno(Terrenos **terrenos) {
    int id;
    printf("Digite o ID do terreno a ser deletado: ");
    if (scanf("%d", &id) != 1) return;

    int pos = buscarIndicePorId(terrenos, id);

    if (pos != -1) {
        free(terrenos[pos]);
        terrenos[pos] = NULL;
        printf("Terreno ID %d removido da posicao %d.\n", id, pos);
    } else {
        printf("Erro: ID %d nao encontrado.\n", id);
    }
}

void mostrarTerreno(Terrenos **terrenos, int id) {
    int pos = buscarIndicePorId(terrenos, id);

    if (pos != NULL) {
        Terrenos *t = terrenos[pos];
        printf("\n----- Informações do Terreno ID %d -----\n", pos);
        printf("Dono: %s\n", t->dono.nome);
        printf("CPF: %s | Telefone: %s\n", t->dono.cpf, t->dono.tel);
        printf("Data Compra: %d/%d/%d\n", t->data_compra.dia, t->data_compra.mes, t->data_compra.ano);
        printf("Dimensões: %.2f m x %.2f m\n", t->largura, t->comprimento);
        printf("Área Total: %.2f m²\n", t->area);
        printf("Preço por m²: R$ %.2f\n", t->preco_m2);
        printf("Valor Estimado: R$ %.2f\n", calcularValorTerreno(terrenos, id));
    } else {
        printf("Erro: Terreno ID %d não encontrado.\n", id);
    }
}

void editarTerreno(Terrenos **terrenos, int id) {
    int pos = buscarIndicePorId(terrenos, id);

    if (pos != -1) {
        Terrenos *t = terrenos[pos];
        printf("Editando ID %d (Indice %d).\n", id, pos);
        
        // Aqui também usamos scanf direto
        printf("Novo Nome (Atual: %s): ", t->dono.nome);
        scanf(" %[^\n]", t->dono.nome);

        printf("Novo Preco m2 (Atual %.2f): ", t->preco_m2);
        scanf("%f", &t->preco_m2);
        
        printf("Sucesso. Dados atualizados.\n");
    } else {
        printf("Erro: ID %d nao encontrado.\n", id);
    }
}

double calcularValorTerreno(Terrenos **terrenos, int id) {
    int pos = buscarIndicePorId(terrenos, id);

    if (pos != -1) {
        return (double)(terrenos[pos]->area * terrenos[pos]->preco_m2);
    }
    return -1.0;
}

int contarTerrenosOcupados(Terrenos **terrenos) {
    int count = 0;
    for(int i = 0; i < MAX_TERRENOS; i++) {
       if (terrenos[i] != NULL) count++;
    }
    return count; 
}

int contarTerrenosLivres(Terrenos **terrenos) {
    return MAX_TERRENOS - contarTerrenosOcupados(terrenos);
}

double calcularValorTotal(Terrenos **terrenos) {
   double total = 0.0;
   for(int i = 0; i < MAX_TERRENOS; i++) {
      if (terrenos[i] != NULL) {
          total += (terrenos[i]->area * terrenos[i]->preco_m2);
      }
   }
   return total;
}

void salvarTerrenos(Terrenos **terrenos, const char *dados) {
    FILE *f = fopen(dados, "wb"); 
    int count = contarTerrenosOcupados(terrenos);
    
    if (!f) return;
    fwrite(&count, sizeof(int), 1, f);

    for (int i = 0; i < MAX_TERRENOS; i++) {
        if (terrenos[i] != NULL) {
            fwrite(terrenos[i], sizeof(Terrenos), 1, f);
        }
    }
    fclose(f);
    printf("\nSalvo com sucesso.\n");
}
void carregarTerrenos(Terrenos **terrenos, const char *dados) {
    FILE *f = fopen(dados, "rb"); 
    if (!f) { inicializarVetor(terrenos); return; }

    inicializarVetor(terrenos);

    int count;
    if (fread(&count, sizeof(int), 1, f) != 1) { fclose(f); return; }

    for (int i = 0; i < count; i++) {
        Terrenos *temp = (Terrenos *)malloc(sizeof(Terrenos));
        if (fread(temp, sizeof(Terrenos), 1, f) == 1) {
            
            // Reinsere com Hash
            int pos = calcularHash(temp->id);
            int inicio = pos;
            
            while (terrenos[pos] != NULL) {
                pos = (pos + 1) % MAX_TERRENOS;
                if (pos == inicio) break; 
            }
            
            if (terrenos[pos] == NULL) {
                terrenos[pos] = temp;
            } else {
                free(temp);
            }
        } else {
            free(temp);
        }
    }
    fclose(f);
    printf("Dados de %d terrenos carregados.\n", count);
}
