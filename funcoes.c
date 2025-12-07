#include<stdio.h>
#include<stdlib.h>
#include "Structs.h"
#include "funcoes.h"
#include <string.h>
#define TAMANHO_INICIAL 100


void inicializarVetor ( Terrenos **terrenos){
    *terrenos=(Terrenos **)calloc(TAMANHO_INICIAL,sizeof(Terrenos *));
    if (*terrenos == NULL) {
        perror("Erro ao alocar memória para o vetor de terrenos");
        exit(EXIT_FAILURE);
    }
}

void criarTerreno (Terrenos **terrenos) {
    int i;
    int indice_livre = -1;
    Terrenos *novo;

    for (i = 0; i < TAMANHO_INICIAL; i++) {
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
        perror("Erro ao alocar memória para o novo terreno");
        return;
    }

    printf("\n----- Cadastro de Novo Terreno -----\n");
    
    printf("ID do Terreno: ");
    if (scanf("%d", &novo->id) != 1) { free(novo); return; }

    printf("Nome do Dono: ");
    while (getchar() != '\n');
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


void deletarTerreno (Terrenos **terrenos) {
    int id_procurado, i;
    printf("Digite o ID do terreno a ser deletado: ");
    if (scanf("%d", &id_procurado) != 1) return;

    for (i = 0; i < TAMANHO_INICIAL; i++) {
        if (terrenos[i] != NULL && terrenos[i]->id == id_procurado) {
            free(terrenos[i]);
            terrenos[i] = NULL; 
            printf("Terreno ID %d deletado e memória liberada.\n", id_procurado);
            return;
        }
    }
    printf("Erro: Terreno ID %d não encontrado.\n", id_procurado);
}

void mostrarTerreno (Terrenos **terrenos, int id) {
    int i;
    Terrenos *t = NULL;
    
    for (i = 0; i < TAMANHO_INICIAL; i++) {
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

void editarTerreno (Terrenos **terrenos, int id) {
    int i;
    Terrenos *t = NULL;
    
    for (i = 0; i < TAMANHO_INICIAL; i++) {
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

        printf("Terreno ID %d atualizado com sucesso.\n", id);
    } else {
        printf("Erro: Terreno ID %d não encontrado.\n", id);
    }
}
double calcularValorTerreno ( Terrenos **terrenos, int id);

int contarTerrenosOcupados ( Terrenos **terrenos);

int contarTerrenosLivres ( Terrenos **terrenos);

double calcularValorTotal ( Terrenos **terrenos);

void salvarTerrenos(Terrenos **terrenos, const char *dados) {
    FILE *f = fopen(dados, "wb"); 
    int i, count = contarTerrenosOcupados(terrenos);
    if (f == NULL) {
        perror("Erro ao abrir arquivo para salvar");
        return;
    }

    

    if (fwrite(&count, sizeof(int), 1, f) != 1) {
        perror("Erro ao escrever a contagem de terrenos");
        fclose(f);
        return;
    }

    for (i = 0; i < TAMANHO_INICIAL; i++) {
        if (terrenos[i] != NULL) {
            if (fwrite(terrenos[i], sizeof(Terrenos), 1, f) != 1) {
                perror("Erro ao salvar dados do terreno");
                fclose(f);
                return;
            }
        }
    }

    fclose(f);
    printf("\nDados de %d terrenos salvos com sucesso em '%s'.\n", count, dados);
}

void carregarTerrenos(Terrenos ***terrenos_ptr, const char *dados) {
    FILE *f = fopen(dados, "rb"); 
    int count, i;
    if (f == NULL) {
        perror("Erro ao abrir arquivo para carregar (O arquivo pode não existir ainda)");
        
        if (*terrenos_ptr == NULL) {
             inicializarVetor(terrenos_ptr);
        }
        return;
    }

    if (*terrenos_ptr == NULL) {
        inicializarVetor(terrenos_ptr);
    } else {
        for(int k = 0; k < TAMANHO_INICIAL; k++) {
            if((*terrenos_ptr)[k] != NULL) {
                free((*terrenos_ptr)[k]);
                (*terrenos_ptr)[k] = NULL;
            }
        }
    }

    

    if (fread(&count, sizeof(int), 1, f) != 1) {
        if (feof(f)) { 
            printf("Arquivo de dados vazio. Nenhum terreno carregado.\n");
        } else {
            perror("Erro ao ler a contagem de terrenos");
        }
        fclose(f);
        return;
    }

    for (i = 0; i < count && i < TAMANHO_INICIAL; i++) {
        Terrenos *novo = (Terrenos *)malloc(sizeof(Terrenos));
        if (novo == NULL) {
            perror("Erro de alocação de memória ao carregar terreno");
            break; 
        }

        if (fread(novo, sizeof(Terrenos), 1, f) != 1) {
            perror("Erro ao carregar dados do terreno");
            free(novo);
            break; 
        }
        
        (*terrenos_ptr)[i] = novo; 
    }

    fclose(f);
    printf("Dados de %d terrenos carregados com sucesso de '%s'.\n", i, dados);
}
