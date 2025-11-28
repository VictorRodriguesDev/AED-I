#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// troca dois elementos
void troca(int *a, int *b) {
    int x = *a; // guarda a
    *a = *b; // coloca b em a
    *b = x; // coloca a em b
}

// quicksort 3-way (Dijkstra)
void quicksort3(int v[], int p, int r) {
    if (p >= r) return; // caso base

    // escolhe pivô aleatório
    int k = p + rand() % (r - p + 1); // posição aleatória
    troca(&v[p], &v[k]); // coloca pivô na frente

    int x = v[p]; // pivô
    int lt = p; // limite dos menores
    int gt = r; // limite dos maiores
    int i = p + 1; // cursor

    while (i <= gt) { // percorre o intervalo
        if (v[i] < x) { // menor que pivô
            troca(&v[i], &v[lt]); // manda para zona menor
            lt++; // avança lt
            i++;  // avança i
        } else if (v[i] > x) { // maior que pivô
            troca(&v[i], &v[gt]); // manda para zona maior
            gt--; // recua gt
        } else {
            i++; // igual ao pivô
        }
    }

    quicksort3(v, p, lt - 1); // ordena menores
    quicksort3(v, gt + 1, r); // ordena maiores
}

int main() {
    srand(time(NULL)); // inicializa random

    int t; // número de casos
    scanf("%d", &t);

    while (t--) { // processa cada caso
        int n; // quantidade de alturas
        scanf("%d", &n);

        int *v = malloc(n * sizeof(int)); // vetor dinâmico

        for (int i = 0; i < n; i++) { // lê alturas
            scanf("%d", &v[i]);
        }

        quicksort3(v, 0, n - 1); // ordena

        for (int i = 0; i < n; i++) { // imprime ordenado
            printf("%d", v[i]);
            if (i < n - 1) printf(" ");
        }

        printf("\n"); // quebra de linha
        free(v); // libera memória
    }

    return 0;
}
