#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"
#include "funcoes.h"


int main (int argc, char *argv[]) 
{
    if (argc != 2) {
        printf("Erro: Voce deve informar o nome do arquivo como argumento.\n");
        printf("Instrução de uso: %s <nome_do_arquivo_de_dados>\n", argv[0]);
        return 1;
    }

    int opcao, id;
    double valorterreno;
    const char *nomeArquivo = argv[1]; 
    struct Terrenos **terrenos = NULL;

    inicializarVetor(&terrenos);
    carregarTerrenos(&terrenos, nomeArquivo);

    do {
        printf("\n========== MENU ==========\n");
        printf("ESCOLHA A SUA AÇÃO:\n");
        printf("1. Criar Terreno\n");
        printf("2. Deletar Terreno\n");
        printf("3. Mostrar Informações de Terreno\n");
        printf("4. Editar Terreno\n");
        printf("5. Calcular Valor de Terreno\n");
        printf("6. Contar Terrenos Ocupados\n");
        printf("7. Contar Terrenos Livres\n");
        printf("8. Calcular Valor Total dos Terrenos\n");
        printf("9. Salvar Dados\n");
        printf("0. Sair\n");
        printf("==========================\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            while (getchar() != '\n'); 
        }
        printf("\n");

        switch (opcao)
        {
        case 0:
            printf("Encerrando programa… Salvando dados!\n");
            salvarTerrenos(terrenos, nomeArquivo);
            break;

        case 1:
            criarTerreno(terrenos);
            break;

        case 2:
            deletarTerreno(terrenos);
            break;

        case 3:
            printf("Informe o ID do terreno que deseja visualizar: ");
            scanf("%d", &id);
            printf("\n");
            mostrarTerreno(terrenos, id);
            break;

        case 4:
            printf("Informe o ID do terreno que deseja editar: ");
            scanf("%d", &id);
            printf("\n");
            editarTerreno(terrenos, id);
            break;

        case 5:
            printf("Informe o ID do terreno: ");
            scanf("%d", &id);
            printf("\n");
            valorterreno = calcularValorTerreno(terrenos, id);
            if(valorterreno==-1) printf("Terreno inválido!\n");
            else printf("Valor do terreno: %.2lf\n", valorterreno);
            break;
        
        case 6:
            printf("Terrenos ocupados: %d\n", contarTerrenosOcupados(terrenos));
            break;
            
        case 7:
            printf("Terrenos livres: %d\n", contarTerrenosLivres(terrenos));
            break;

        case 8:
            printf("Valor total de todos os terrenos: %.2lf\n", calcularValorTotal(terrenos));
            break;

        case 9:
            salvarTerrenos(terrenos, nomeArquivo);
            break;

        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    }
    while(opcao!=0);

    for (int i = 0; i < 100; i++) {
        if (terrenos[i] != NULL) {
            free(terrenos[i]);
        }
    }
    free(terrenos);

    return 0;
}
