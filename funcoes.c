#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"
#include "funcoes.h"

#define MAX_TERRENOS 100

void inicializarVetor(Terrenos **terrenos) {
    for (int i = 0; i < MAX_TERRENOS; i++) {
        terrenos[i] = NULL;
    }
}

void criarTerreno(Terrenos **terrenos) {
    int i;
    int indice_livre = -1;
    Terrenos *novo;

    for (i = 0; i < MAX_TERRENOS; i++) {
        if (terrenos[i] == NULL) {
            indice_livre = i;
            break;
        }
    }

    if (indice_livre == -1) {
        printf("Capacidade Máxima atingida. Não há vagas livres.\n");
        return;
    }

    novo = (Terrenos *)malloc(sizeof(Terrenos));
    if (novo == NULL) {
        perror("Erro ao alocar memória");
        return;
    }

    printf("\n----- Cadastro de Novo Terreno -----\n");
    
    printf("ID do Terreno: ");
    if (scanf("%d", &novo->id) != 1) { free(novo); return; }

    printf("Nome do Dono: ");
    while (getchar() != '\n'); // limpa buffer
    fgets(novo->dono.nome, 100, stdin);
    novo->dono.nome[strcspn(novo->dono.nome, "\n")] = 0; 

    printf("CPF do Dono: ");
    if (scanf("%s", novo->dono.cpf) != 1) { free(novo); return; }
    
    printf("Telefone do Dono: ");
    if (scanf("%s", novo->dono.tel) != 1) { free(novo); return; }

    printf("Data de Nascimento (dd mm aaaa): ");
    if (scanf("%d %d %d", &novo->dono.data_nasc.dia, &novo->dono.data_nasc.mes, &novo->dono.data_nasc.ano) != 3) { free(novo); return; }

    printf("Data de Compra (dd mm aaaa): ");
    if (scanf("%d %d %d", &novo->data_compra.dia, &novo->data_compra.mes, &novo->data_compra.ano) != 3) { free(novo); return; }

    printf("Largura (m): ");
    if (scanf("%f", &novo->largura) != 1) { free(novo); return; }

    printf("Comprimento (m): ");
    if (scanf("%f", &novo->comprimento) != 1) { free(novo); return; }
    
    printf("Preço por m2: R$ ");
    if (scanf("%f", &novo->preco_m2) != 1) { free(novo); return; }

    novo->area = novo->largura * novo->comprimento;

    terrenos[indice_livre] = novo;
    printf("Terreno ID %d cadastrado com sucesso na posição %d.\n", novo->id, indice_livre);
}

void deletarTerreno(Terrenos **terrenos) {
    int id_procurado, i;
    printf("Digite o ID do terreno a ser deletado: ");
    if (scanf("%d", &id_procurado) != 1) return;

    for (i = 0; i < MAX_TERRENOS; i++) {
        if (terrenos[i] != NULL && terrenos[i]->id == id_procurado) {
            free(terrenos[i]);
            terrenos[i] = NULL; 
            printf("Terreno ID %d deletado.\n", id_procurado);
            return;
        }
    }
    printf("Erro: Terreno ID %d não encontrado.\n", id_procurado);
}

void mostrarTerreno(Terrenos **terrenos, int id) {
    int i;
    Terrenos *t = NULL;
    
    for (i = 0; i < MAX_TERRENOS; i++) {
        if (terrenos[i] != NULL && terrenos[i]->id == id) {
            t = terrenos[i];
            break;
        }
    }

    if (t != NULL) {
        printf("\n----- Informações do Terreno ID %d -----\n", t->id);
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
    int i;
    Terrenos *t = NULL;
    
    for (i = 0; i < MAX_TERRENOS; i++) {
        if (terrenos[i] != NULL && terrenos[i]->id == id) {
            t = terrenos[i];
            break;
        }
    }

    if (t != NULL) {
        printf("\n----- Edição de Terreno ID %d -----\n", t->id);
        
        while (getchar() != '\n');
        fgets(t->dono.nome, 100, stdin);
        t->dono.nome[strcspn(t->dono.nome, "\n")] = 0;

        printf("Nova Largura (m) (Atual: %.2f): ", t->largura);
        if (scanf("%f", &t->largura) != 1) return;

        printf("Novo Comprimento (m) (Atual: %.2f): ", t->comprimento);
        if (scanf("%f", &t->comprimento) != 1) return;

        printf("Novo Preço por m2 (Atual: %.2f): R$ ", t->preco_m2);
        if (scanf("%f", &t->preco_m2) != 1) return;

        t->area = t->largura * t->comprimento;

        printf("Terreno ID %d atualizado.\n", id);
    } else {
        printf("Erro: Terreno ID %d não encontrado.\n", id);
    }
}

double calcularValorTerreno(Terrenos **terrenos, int id) {
    int i;
    for(i = 0; i < MAX_TERRENOS; i++) {
        // Verifica se terrenos[i] não é NULL antes de acessar o ID
        if(terrenos[i] != NULL && terrenos[i]->id == id) { 
            return (double)(terrenos[i]->preco_m2 * terrenos[i]->area); 
        }
    }
    return -1.0;
}

int contarTerrenosOcupados(Terrenos **terrenos) {
    int i, terrenos_ocupados = 0;
    
    for(i = 0; i < MAX_TERRENOS; i++) {
       if (terrenos[i] != NULL) {
            terrenos_ocupados++;
        }
    }
    return terrenos_ocupados; 
}

int contarTerrenosLivres(Terrenos **terrenos) {
    int i, terrenos_livres = 0;
    
    for(i = 0; i < MAX_TERRENOS; i++) {
        if(terrenos[i] == NULL) {
            terrenos_livres++;
        }
    }
    return terrenos_livres;
}

double calcularValorTotal(Terrenos **terrenos) {
   int i;
   double valor_total = 0.0;

   for(i = 0; i < MAX_TERRENOS; i++) {
      if (terrenos[i] != NULL) {
          valor_total += (terrenos[i]->area * terrenos[i]->preco_m2);
      }
   }
   return valor_total;
}

void salvarTerrenos(Terrenos **terrenos, const char *dados) {
    FILE *f = fopen(dados, "wb"); 
    int count = contarTerrenosOcupados(terrenos);
    
    if (f == NULL) {
        perror("Erro ao abrir arquivo para salvar");
        return;
    }

    if (fwrite(&count, sizeof(int), 1, f) != 1) {
        perror("Erro ao escrever contador");
        fclose(f);
        return;
    }

    for (int i = 0; i < MAX_TERRENOS; i++) {
        if (terrenos[i] != NULL) {
            if (fwrite(terrenos[i], sizeof(Terrenos), 1, f) != 1) {
                perror("Erro ao salvar terreno");
                fclose(f);
                return;
            }
        }
    }

    fclose(f);
    printf("\nDados de %d terrenos salvos em '%s'.\n", count, dados);
}
void carregarTerrenos(Terrenos **terrenos, const char *dados) {
    FILE *f = fopen(dados, "rb"); 
    int count, i;
    
    if (f == NULL) {
        inicializarVetor(terrenos);
        return;
    }
    for(int k = 0; k < MAX_TERRENOS; k++) {
        if(terrenos[k] != NULL) {
            free(terrenos[k]);
            terrenos[k] = NULL;
        }
    }

    if (fread(&count, sizeof(int), 1, f) != 1) {
        if (!feof(f)) perror("Erro ao ler contador");
        fclose(f);
        return;
    }

    for (i = 0; i < count && i < MAX_TERRENOS; i++) {
        Terrenos *novo = (Terrenos *)malloc(sizeof(Terrenos));
        if (novo == NULL) break; 

        if (fread(novo, sizeof(Terrenos), 1, f) != 1) {
            free(novo);
            break; 
        }
        
        terrenos[i] = novo; 
    }

    fclose(f);
    printf("Dados de %d terrenos carregados.\n", i);
}
