#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"
#include "funcoes.h"

// --- DEFINIÇÃO DE CORES E ESTILOS ---
#define RESET   "\033[0m"
#define VERMELHO "\033[31m"
#define VERDE   "\033[32m"
#define AMARELO "\033[33m"
#define AZUL    "\033[34m"
#define MAGENTA "\033[35m"
#define CIANO   "\033[36m"
#define BRANCO  "\033[37m"
#define NEGRITO "\033[1m"

// Detecta sistema operacional para comandos de tela
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf(AMARELO "\n[Pressione ENTER para continuar...]" RESET);
    getchar();
    getchar();
}

void exibirCabecalho() {
    printf(VERDE NEGRITO);
    printf("  _______                              \n");
    printf(" |__   __|                         _   \n");
    printf("    | | ___ _ __ _ __ ___ _ __   _| |_ \n");
    printf("    | |/ _ \\ '__| '__/ _ \\ '_ \\ |_   _|\n");
    printf("    | |  __/ |  | | |  __/ | | |  |_|  \n");
    printf("    |_|\\___|_|  |_|  \\___|_| |_|       \n");
    printf(RESET);
    printf(AMARELO "  >>> GESTAO IMOBILIARIA v2.0 <<<\n" RESET);
    printf(BRANCO "  -------------------------------\n" RESET);
}

int main (int argc, char *argv[]) 
{
    // Verifica argumentos
    if (argc != 2) {
        printf(VERMELHO NEGRITO "ERRO CRITICO:\n" RESET);
        printf(VERMELHO " Voce deve informar o nome do arquivo de dados.\n" RESET);
        printf(AMARELO " Uso correto: %s <banco_de_dados.dat>\n" RESET, argv[0]);
        return 1;
    }

    int opcao, id;
    double valorterreno;
    const char *nomeArquivo = argv[1]; 
    struct Terrenos **terrenos = NULL;

    // Tela de Carregamento
    limparTela();
    printf(AMARELO "Inicializando sistema e carregando dados de '%s'...\n" RESET, nomeArquivo);
    inicializarVetor(&terrenos);
    carregarTerrenos(&terrenos, nomeArquivo);

    do {
        limparTela();
        exibirCabecalho();

        // Menu Organizado por Categorias
        printf("\n" NEGRITO "  [ GESTAO ]" RESET "\n");
        printf("   " VERDE "1." RESET " Criar Terreno\n");
        printf("   " VERDE "2." RESET " Deletar Terreno\n");
        printf("   " VERDE "4." RESET " Editar Terreno\n");
        
        printf("\n" NEGRITO "  [ CONSULTAS ]" RESET "\n");
        printf("   " CIANO "3." RESET " Mostrar Detalhes (ID)\n");
        printf("   " CIANO "5." RESET " Calcular Valor de Venda (ID)\n");
        
        printf("\n" NEGRITO "  [ RELATORIOS ]" RESET "\n");
        printf("   " MAGENTA "6." RESET " Contar Ocupados\n");
        printf("   " MAGENTA "7." RESET " Contar Livres\n");
        printf("   " MAGENTA "8." RESET " Patrimonio Total (Soma Geral)\n");

        printf("\n" NEGRITO "  [ SISTEMA ]" RESET "\n");
        printf("   " AMARELO "9." RESET " Salvar Dados Agora\n");
        printf("   " VERMELHO "0." RESET " Sair e Salvar\n");
        
        printf(AZUL "\n  ______________________________\n" RESET);
        printf(NEGRITO "  > Escolha uma opcao: " RESET);
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            while (getchar() != '\n'); // Limpa buffer se digitar letra
        }

        switch (opcao)
        {
        case 0:
            printf(VERDE "\n  Encerrando programa... Salvando dados!\n" RESET);
            salvarTerrenos(terrenos, nomeArquivo);
            break;

        case 1: // Criar
            printf(VERDE "\n  --- NOVO CADASTRO ---\n" RESET);
            criarTerreno(terrenos);
            pausar();
            break;

        case 2: // Deletar
            printf(VERMELHO "\n  --- REMOVER TERRENO ---\n" RESET);
            deletarTerreno(terrenos);
            pausar();
            break;

        case 3: // Mostrar
            printf(CIANO "\n  --- CONSULTA DETALHADA ---\n" RESET);
            printf("  Informe o ID do terreno: ");
            scanf("%d", &id);
            mostrarTerreno(terrenos, id);
            pausar();
            break;

        case 4: // Editar
            printf(AMARELO "\n  --- EDITAR REGISTRO ---\n" RESET);
            printf("  Informe o ID do terreno: ");
            scanf("%d", &id);
            editarTerreno(terrenos, id);
            pausar();
            break;

        case 5: // Calcular Valor Individual
            printf(CIANO "\n  --- AVALIACAO DE IMOVEL ---\n" RESET);
            printf("  Informe o ID do terreno: ");
            scanf("%d", &id);
            valorterreno = calcularValorTerreno(terrenos, id);
            
            if(valorterreno == -1) 
                printf(VERMELHO "  Erro: Terreno nao encontrado!\n" RESET);
            else 
                printf("  Valor de Mercado: " VERDE "R$ %.2lf\n" RESET, valorterreno);
            
            pausar();
            break;
        
        case 6: // Ocupados
            printf(MAGENTA "\n  --- ESTATISTICAS ---\n" RESET);
            ; // Trigger image to explain occupancy visually if possible, otherwise rely on text.
            printf("  Terrenos Ocupados: " NEGRITO "%d\n" RESET, contarTerrenosOcupados(terrenos));
            pausar();
            break;
            
        case 7: // Livres
            printf(MAGENTA "\n  --- ESTATISTICAS ---\n" RESET);
            printf("  Terrenos Livres (Vagas): " NEGRITO "%d\n" RESET, contarTerrenosLivres(terrenos));
            pausar();
            break;

        case 8: // Total
            printf(MAGENTA "\n  --- FINANCEIRO ---\n" RESET);
            printf("  Valor Somado da Carteira: " VERDE "R$ %.2lf\n" RESET, calcularValorTotal(terrenos));
            pausar();
            break;

        case 9: // Salvar Manual
            printf(AMARELO "\n  Salvando alteracoes no disco...\n" RESET);
            salvarTerrenos(terrenos, nomeArquivo);
            pausar();
            break;

        default:
            printf(VERMELHO "\n  Opcao invalida! Tente novamente.\n" RESET);
            pausar(); // Pausa para ler o erro
        }
    }
    while(opcao != 0);

    // Limpeza de Memória Final
    for (int i = 0; i < 100; i++) {
        if (terrenos[i] != NULL) {
            free(terrenos[i]);
        }
    }
    free(terrenos);
    
    printf(AZUL "  Ate logo!\n" RESET);

    return 0;
}
