#include <stdio.h>
#include <windows.h>
#include <string.h>

#define MAX_LETRAS 200
#define MAX_LINHAS 50

struct Produto {
    char nome[50];
    int quantidade;
    char localizacao[50];
    float valor_unitario;
};
int main() {
    SetConsoleOutputCP(CP_UTF8);
    struct Produto inventario[MAX_LINHAS];
    int total_produtos = 0;
    int qtdLinhas = 0;

    FILE *arquivo = fopen("inventario.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    char linha[MAX_LETRAS];

    while (fgets(linha, sizeof(linha), arquivo) != NULL && qtdLinhas < MAX_LINHAS) {
        linha[strcspn(linha, "\n")] = '\0';
        qtdLinhas++;

        if (qtdLinhas > 1) {
            char loc1[25] = {0};
            char loc2[25] = {0};
            
            sscanf(linha, "%49[^;];%d;%24[^;];%24[^;];%f",
                   inventario[total_produtos].nome,
                   &inventario[total_produtos].quantidade,
                   loc1,
                   loc2,
                   &inventario[total_produtos].valor_unitario);
                   
            snprintf(inventario[total_produtos].localizacao, 50, "%s%s", loc1, loc2);
            total_produtos++;
        }
    }
    fclose(arquivo);
    printf("========================================================================\n");
    printf("                       RELATÓRIO DE INVENTÁRIO                          \n");
    printf("========================================================================\n");
    printf("%-15s | %-12s | %-15s | %-20s\n", "Produto", "Quantidade", "Localização   ", "Valor Total");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < total_produtos; i++) {
        float valor_total = inventario[i].quantidade * inventario[i].valor_unitario;
        printf("%-15s | %-12d | %-15s | R$ %-17.2f\n",
               inventario[i].nome,
               inventario[i].quantidade,
               inventario[i].localizacao,
               valor_total);
    }
    printf("========================================================================\n");
    return 0;
}
