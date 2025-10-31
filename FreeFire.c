#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade;
} Item;

typedef enum {
    NOME,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

void limparTela() {
    for (int i = 0; i < 30; i++) printf("\n");
}

void listarItens(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\n%-20s %-15s %-10s %-10s\n", "NOME", "TIPO", "QTD", "PRIORIDADE");
    for (int i = 0; i < numItens; i++)
        printf("%-20s %-15s %-10d %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
}

void insertionSort(Item mochila[], int numItens, CriterioOrdenacao criterio, int *comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            bool cond = false;
            if (criterio == NOME) cond = strcmp(mochila[j].nome, chave.nome) > 0;
            else if (criterio == TIPO) cond = strcmp(mochila[j].tipo, chave.tipo) > 0;
            else cond = mochila[j].prioridade < chave.prioridade;
            if (!cond) break;
            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }
}

void inserirItem(Item mochila[], int *numItens, bool *ordenadaPorNome) {
    if (*numItens >= MAX) {
        printf("Mochila cheia!\n");
        return;
    }
    printf("Nome: ");
    getchar();
    fgets(mochila[*numItens].nome, 50, stdin);
    mochila[*numItens].nome[strcspn(mochila[*numItens].nome, "\n")] = 0;
    printf("Tipo: ");
    fgets(mochila[*numItens].tipo, 50, stdin);
    mochila[*numItens].tipo[strcspn(mochila[*numItens].tipo, "\n")] = 0;
    printf("Quantidade: ");
    scanf("%d", &mochila[*numItens].quantidade);
    printf("Prioridade (1-5): ");
    scanf("%d", &mochila[*numItens].prioridade);
    (*numItens)++;
    *ordenadaPorNome = false;
    printf("Item adicionado!\n");
}

void removerItem(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nome[50];
    printf("Nome do item para remover: ");
    getchar();
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *numItens - 1; j++)
                mochila[j] = mochila[j + 1];
            (*numItens)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item não encontrado.\n");
}

void buscaBinariaPorNome(Item mochila[], int numItens, bool ordenadaPorNome) {
    if (!ordenadaPorNome) {
        printf("A mochila deve estar ordenada por nome para realizar a busca.\n");
        return;
    }
    char nome[50];
    printf("Nome para buscar: ");
    getchar();
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = 0;
    int ini = 0, fim = numItens - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("\nItem encontrado:\n");
            printf("%-20s %-15s %-10d %-10d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        } else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    printf("Item não encontrado.\n");
}

void menuDeOrdenacao(Item mochila[], int numItens, bool *ordenadaPorNome) {
    if (numItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    int opc, comp;
    printf("\n1 - Ordenar por nome\n2 - Ordenar por tipo\n3 - Ordenar por prioridade\nEscolha: ");
    scanf("%d", &opc);
    if (opc == 1) {
        insertionSort(mochila, numItens, NOME, &comp);
        *ordenadaPorNome = true;
    } else if (opc == 2) {
        insertionSort(mochila, numItens, TIPO, &comp);
        *ordenadaPorNome = false;
    } else if (opc == 3) {
        insertionSort(mochila, numItens, PRIORIDADE, &comp);
        *ordenadaPorNome = false;
    } else return;
    printf("Itens ordenados! Comparações: %d\n", comp);
}

int main() {
    Item mochila[MAX];
    int numItens = 0, opcao;
    bool ordenadaPorNome = false;
    do {
        printf("\n=== CODIGO DA ILHA - NIVEL MESTRE ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar itens\n");
        printf("5 - Buscar item por nome\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: inserirItem(mochila, &numItens, &ordenadaPorNome); break;
            case 2: removerItem(mochila, &numItens); break;
            case 3: listarItens(mochila, numItens); break;
            case 4: menuDeOrdenacao(mochila, numItens, &ordenadaPorNome); break;
            case 5: buscaBinariaPorNome(mochila, numItens, ordenadaPorNome); break;
        }
    } while (opcao != 0);
    return 0;
}
