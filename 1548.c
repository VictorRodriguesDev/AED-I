#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// troca dois inteiros
void troca(int *a, int *b) {
    int x = *a;
    *a = *b;
    *b = x;
}

// quicksort 3-way (ordem DECRESCENTE)
void quicksort3(int v[], int p, int r) {
    if (p >= r) return;

    int k = p + rand() % (r - p + 1); // pivô aleatório
    troca(&v[p], &v[k]); // coloca pivô no início

    int pivot = v[p]; // pivô
    int lt = p; // zona de maiores
    int gt = r; // zona de menores
    int i = p + 1; // cursor

    while (i <= gt) {
        if (v[i] > pivot) {       // maior → esquerda
            troca(&v[i], &v[lt]);
            lt++;
            i++;
        } else if (v[i] < pivot) { // menor → direita
            troca(&v[i], &v[gt]);
            gt--;
        } else {
            i++; // igual → passa
        }
    }

    quicksort3(v, p, lt - 1);  // ordena maiores
    quicksort3(v, gt + 1, r);  // ordena menores
}

int main() {
    srand(time(NULL)); // inicializa aleatório

    int t; // quantidade de casos
    scanf("%d", &t);

    while (t--) {
        int n; // quantidade de alunos
        scanf("%d", &n);

        int *orig = malloc(n * sizeof(int)); // vetor original
        int *sorted = malloc(n * sizeof(int)); // cópia para ordenar

        for (int i = 0; i < n; i++) {
            scanf("%d", &orig[i]); // lê nota
            sorted[i] = orig[i];   // copia
        }

        quicksort3(sorted, 0, n - 1); // ordena em ordem DECRESCENTE

        int count = 0; // quantos não mudaram

        for (int i = 0; i < n; i++) {
            if (orig[i] == sorted[i]) // mesma posição?
                count++;
        }

        printf("%d\n", count); // imprime resultado

        free(orig);
        free(sorted);
    }

    return 0;
}
