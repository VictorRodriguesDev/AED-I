#include <stdio.h>
#include <stdlib.h>

void selectionSort(int *v, int n) {
    int i, j, minIndex, tmp;

    for (i = 0; i < n - 1; i++) {                         
        minIndex = i; // índice do menor elemento

        for (j = i + 1; j < n; j++) {                     
            if (*(v + j) < *(v + minIndex)) { // compara valores via ponteiros 
                minIndex = j; // atualiza índice do mínimo
            }
        }

        // troca o menor com o elemento da posição i
        tmp = *(v + i);
        *(v + i) = *(v + minIndex);
        *(v + minIndex) = tmp;
    }
}

int main() {
    int t;  // número de casos

    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        int *alturas = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            scanf("%d", (alturas + i));
        }

        // ordena usando selection sort
        selectionSort(alturas, n);

        // imprime resultado
        for (int i = 0; i < n; i++) {
            printf("%d", *(alturas + i));
            if (i < n - 1)
                printf(" ");
        }
        printf("\n");

        free(alturas);
    }

    return 0;
}
