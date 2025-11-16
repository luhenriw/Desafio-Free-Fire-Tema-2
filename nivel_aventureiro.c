#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ======================================================
// STRUCT DO ITEM
// ======================================================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ======================================================
// STRUCT DO NÓ — PARA LISTA ENCADEADA
// ======================================================
typedef struct No {
    Item dados;
    struct No* prox;
} No;

// ======================================================
// CONTADORES DE COMPARAÇÃO
// ======================================================
int compSeq = 0;
int compBin = 0;

// ======================================================
// FUNÇÕES PARA O VETOR
// ======================================================
void inserirItemVetor(Item v[], int* total);
void removerItemVetor(Item v[], int* total);
void listarVetor(Item v[], int total);
int buscarSequencialVetor(Item v[], int total, char nome[]);
void ordenarVetor(Item v[], int total);
int buscarBinariaVetor(Item v[], int total, char nome[]);

// ======================================================
// FUNÇÕES PARA A LISTA ENCADEADA
// ======================================================
void inserirItemLista(No** lista);
void removerItemLista(No** lista);
void listarLista(No* lista);
int buscarSequencialLista(No* lista, char nome[]);

// ======================================================
// FUNÇÃO PRINCIPAL
// ======================================================
int main() {
    Item vetor[MAX_ITENS];
    int total = 0;

    No* lista = NULL;

    int opcaoEstrutura, opcao;

    do {
        printf("\n====== SISTEMA DE MOCHILA ======\n");
        printf("1 - Usar Vetor\n");
        printf("2 - Usar Lista Encadeada\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcaoEstrutura);
        getchar();

        if (opcaoEstrutura == 1) {
            // -------------------- MENU DO VETOR --------------------
            do {
                printf("\n--- Mochila com Vetor ---\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar Sequencial\n");
                printf("5 - Ordenar vetor\n");
                printf("6 - Buscar Binária\n");
                printf("7 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();

                if (opcao == 1) inserirItemVetor(vetor, &total);
                if (opcao == 2) removerItemVetor(vetor, &total);
                if (opcao == 3) listarVetor(vetor, total);

                if (opcao == 4) {
                    char nome[30];
                    printf("Nome para busca: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    compSeq = 0;
                    int pos = buscarSequencialVetor(vetor, total, nome);

                    if (pos != -1)
                        printf("Item encontrado no vetor!\n");
                    else
                        printf("Item NAO encontrado.\n");

                    printf("Comparacoes (Busca Sequencial): %d\n", compSeq);
                }

                if (opcao == 5) {
                    ordenarVetor(vetor, total);
                    printf("Vetor ordenado!\n");
                }

                if (opcao == 6) {
                    char nome[30];
                    printf("Nome para busca binaria: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    compBin = 0;
                    int pos = buscarBinariaVetor(vetor, total, nome);

                    if (pos != -1)
                        printf("Item encontrado via busca binaria!\n");
                    else
                        printf("Item NAO encontrado.\n");

                    printf("Comparacoes (Busca Binaria): %d\n", compBin);
                }

            } while (opcao != 7);
        }

        else if (opcaoEstrutura == 2) {
            // ------------------- MENU LISTA -------------------
            do {
                printf("\n--- Mochila com Lista Encadeada ---\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar Sequencial\n");
                printf("5 - Voltar\n");
                printf("Escolha: ");
                scanf("%d", &opcao);
                getchar();

                if (opcao == 1) inserirItemLista(&lista);
                if (opcao == 2) removerItemLista(&lista);
                if (opcao == 3) listarLista(lista);
                if (opcao == 4) {
                    char nome[30];
                    printf("Nome para busca: ");
                    fgets(nome, 30, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    compSeq = 0;
                    int achou = buscarSequencialLista(lista, nome);

                    if (achou)
                        printf("Item encontrado!\n");
                    else
                        printf("Item NAO encontrado!\n");

                    printf("Comparacoes (Busca Sequencial): %d\n", compSeq);
                }

            } while (opcao != 5);
        }

    } while (opcaoEstrutura != 3);

    printf("Sistema finalizado!\n");
    return 0;
}

// ======================================================
// IMPLEMENTAÇÃO VETOR
// ======================================================
void inserirItemVetor(Item v[], int* total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    v[*total] = novo;
    (*total)++;

    printf("Item inserido!\n");
}

void removerItemVetor(Item v[], int* total) {
    char nome[30];
    printf("Nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(v[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++)
                v[j] = v[j + 1];
            (*total)--;
            printf("Removido!\n");
            return;
        }
    }

    printf("Item nao encontrado.\n");
}

void listarVetor(Item v[], int total) {
    if (total == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", v[i].nome);
        printf("Tipo: %s\n", v[i].tipo);
        printf("Qtd: %d\n", v[i].quantidade);
    }
}

int buscarSequencialVetor(Item v[], int total, char nome[]) {
    for (int i = 0; i < total; i++) {
        compSeq++;
        if (strcmp(v[i].nome, nome) == 0) return i;
    }
    return -1;
}

void ordenarVetor(Item v[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Item aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

int buscarBinariaVetor(Item v[], int total, char nome[]) {
    int ini = 0, fim = total - 1;

    while (ini <= fim) {
        compBin++;
        int meio = (ini + fim) / 2;

        int r = strcmp(nome, v[meio].nome);

        if (r == 0)
            return meio;
        else if (r > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// ======================================================
// IMPLEMENTAÇÃO LISTA ENCADEADA
// ======================================================
void inserirItemLista(No** lista) {
    No* novo = (No*)malloc(sizeof(No));

    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->prox = *lista;
    *lista = novo;

    printf("Item inserido na lista!\n");
}

void removerItemLista(No** lista) {
    char nome[30];
    printf("Nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No* atual = *lista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                *lista = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual);
            printf("Item removido!\n");
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Item nao encontrado.\n");
}

void listarLista(No* lista) {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No* aux = lista;
    while (aux != NULL) {
        printf("\nNome: %s\n", aux->dados.nome);
        printf("Tipo: %s\n", aux->dados.tipo);
        printf("Qtd: %d\n", aux->dados.quantidade);
        aux = aux->prox;
    }
}

int buscarSequencialLista(No* lista, char nome[]) {
    No* aux = lista;

    while (aux != NULL) {
        compSeq++;
        if (strcmp(aux->dados.nome, nome) == 0)
            return 1;
        aux = aux->prox;
    }
    return 0;
}