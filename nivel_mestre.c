#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

// ======================================================
// STRUCT DO COMPONENTE
// ======================================================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ======================================================
// FUNÇÕES DE ORDENAÇÃO + BUSCA + EXIBIÇÃO
// ======================================================
int bubbleSortNome(Componente v[], int n);
int insertionSortTipo(Componente v[], int n);
int selectionSortPrioridade(Componente v[], int n);
int buscaBinariaPorNome(Componente v[], int n, char chave[]);

void mostrarComponentes(Componente v[], int n);
double medirTempo(int (*alg)(Componente[], int), Componente v[], int n);

// ======================================================
// CADASTRO
// ======================================================
void cadastrarComponentes(Componente v[], int *n) {
    printf("\nQuantos componentes deseja cadastrar (1 a 20)? ");
    scanf("%d", n);
    getchar();

    if (*n < 1 || *n > 20) {
        printf("Valor inválido!\n");
        *n = 0;
        return;
    }

    for (int i = 0; i < *n; i++) {
        printf("\n=== Componente %d ===\n", i + 1);

        printf("Nome: ");
        fgets(v[i].nome, 30, stdin);
        v[i].nome[strcspn(v[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(v[i].tipo, 20, stdin);
        v[i].tipo[strcspn(v[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &v[i].prioridade);
        getchar();
    }
}

// ======================================================
// BUBBLE SORT — ordenar por nome (string)
// ======================================================
int bubbleSortNome(Componente v[], int n) {
    int comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
    return comparacoes;
}

// ======================================================
// INSERTION SORT — ordenar por tipo (string)
// ======================================================
int insertionSortTipo(Componente v[], int n) {
    int comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        comparacoes++;
        v[j + 1] = chave;
    }
    return comparacoes;
}

// ======================================================
// SELECTION SORT — ordenar por prioridade (int)
// ======================================================
int selectionSortPrioridade(Componente v[], int n) {
    int comparacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }

        if (min != i) {
            Componente aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
    return comparacoes;
}

// ======================================================
// BUSCA BINÁRIA — somente após ordenar por nome
// ======================================================
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n - 1;
    int comp = 0;

    while (ini <= fim) {
        comp++;
        int meio = (ini + fim) / 2;
        int r = strcmp(chave, v[meio].nome);

        if (r == 0) {
            printf("Comparacoes (busca binária): %d\n", comp);
            return meio;
        } else if (r > 0) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    printf("Comparacoes (busca binária): %d\n", comp);
    return -1;
}

// ======================================================
// EXIBIR COMPONENTES
// ======================================================
void mostrarComponentes(Componente v[], int n) {
    printf("\n=== LISTA DE COMPONENTES ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
            i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// ======================================================
// MEDIR TEMPO
// ======================================================
double medirTempo(int (*alg)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    alg(v, n);
    clock_t fim = clock();

    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// ======================================================
// PROGRAMA PRINCIPAL
// ======================================================
int main() {
    Componente v[MAX], copia[MAX];
    int n = 0, escolha;

    cadastrarComponentes(v, &n);

    if (n == 0) return 0;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Bubble Sort (por nome)\n");
        printf("2 - Insertion Sort (por tipo)\n");
        printf("3 - Selection Sort (por prioridade)\n");
        printf("4 - Busca Binária (por nome)\n");
        printf("5 - Mostrar componentes\n");
        printf("6 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        getchar();

        memcpy(copia, v, sizeof(v)); // manter original

        if (escolha == 1) {
            int comp = bubbleSortNome(copia, n);
            double t = medirTempo(bubbleSortNome, copia, n);
            printf("\nBubble Sort concluído!\n");
            printf("Comparações: %d\nTempo: %.7f s\n", comp, t);
            mostrarComponentes(copia, n);
        }

        else if (escolha == 2) {
            int comp = insertionSortTipo(copia, n);
            double t = medirTempo(insertionSortTipo, copia, n);
            printf("\nInsertion Sort concluído!\n");
            printf("Comparações: %d\nTempo: %.7f s\n", comp, t);
            mostrarComponentes(copia, n);
        }

        else if (escolha == 3) {
            int comp = selectionSortPrioridade(copia, n);
            double t = medirTempo(selectionSortPrioridade, copia, n);
            printf("\nSelection Sort concluído!\n");
            printf("Comparações: %d\nTempo: %.7f s\n", comp, t);
            mostrarComponentes(copia, n);
        }

        else if (escolha == 4) {
            bubbleSortNome(copia, n);  // precisa estar ordenado
            char busca[30];

            printf("Nome para buscar: ");
            fgets(busca, 30, stdin);
            busca[strcspn(busca, "\n")] = '\0';

            int pos = buscaBinariaPorNome(copia, n, busca);

            if (pos != -1)
                printf("Encontrado! Tipo: %s | Prioridade: %d\n",
                       copia[pos].tipo, copia[pos].prioridade);
            else
                printf("Não encontrado!\n");
        }

        else if (escolha == 5) {
            mostrarComponentes(v, n);
        }

    } while (escolha != 6);

    printf("Sistema finalizado!\n");
    return 0;
}