#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10   // Capacidade máxima da mochila

// ----------------------------------------------------
// STRUCT DO ITEM
// ----------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ----------------------------------------------------
// FUNÇÕES DO SISTEMA
// ----------------------------------------------------
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

// ----------------------------------------------------
// FUNÇÃO PRINCIPAL
// ----------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];  // Vetor estático de itens
    int total = 0;            // Número de itens cadastrados
    int opcao;

    do {
        printf("\n========== MENU MOCHILA DO JOGADOR ==========\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch(opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 5:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 5);

    return 0;
}

// ----------------------------------------------------
// FUNÇÃO: INSERIR ITEM NA MOCHILA
// ----------------------------------------------------
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\nA mochila esta cheia (10 itens)!\n");
        return;
    }

    Item novo;

    printf("\n=== Inserir novo item ===\n");

    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item (arma, municao, cura...): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*total] = novo;
    (*total)++;

    printf("\nItem inserido com sucesso!\n");
}

// ----------------------------------------------------
// FUNÇÃO: REMOVER ITEM PELO NOME
// ----------------------------------------------------
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nNome do item que deseja remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // Move os itens da frente para trás (remocao)
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            (*total)--;

            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
}

// ----------------------------------------------------
// FUNÇÃO: LISTAR TODOS OS ITENS
// ----------------------------------------------------
void listarItens(Item mochila[], int total) {
    printf("\n=== ITENS NA MOCHILA ===\n");

    if (total == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

// ----------------------------------------------------
// FUNÇÃO: BUSCAR ITEM PELO NOME (BUSCA SEQUENCIAL)
// ----------------------------------------------------
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
}