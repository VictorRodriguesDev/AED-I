#include <stdio.h>
#include <stdlib.h>

// função que mantém a propriedade do heap
void heapify(int *vetor, int n, int i){ // vetor: array; n: tamanho; i: índice atual
    int maior = i; // índice do maior elemento
    int esq = 2 * i + 1; // filho esquerdo
    int dir = 2 * i + 2; // filho direito

    if(esq < n && vetor[esq] > vetor[maior]){
        maior = esq;
    }
    if(dir < n && vetor[dir] > vetor[maior]){
        maior = dir;
    }

    if(maior != i){
        int temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;
        heapify(vetor, n, maior);
    }
}

// função de heapsort
void heapsort(int *vetor, int n){ // vetor: array; n: tamanho
    for(int i = n / 2 - 1; i >= 0; i--){ // constrói o heap
        heapify(vetor, n, i);
    }

    for(int i = n - 1; i > 0; i--){ // extrai elementos
        int temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        heapify(vetor, i, 0);
    }
}

int main(){
    int c; // quantidade de casos
    scanf("%d", &c);

    while(c--){
        int n; // quantidade de pessoas
        scanf("%d", &n);

        int *vetor = (int*) malloc(n * sizeof(int)); // vetor de alturas
        if(vetor == NULL){
            return 1;
        }

        for(int i = 0; i < n; i++){
            scanf("%d", &vetor[i]); // lê altura
        }

        heapsort(vetor, n); // ordena usando heapsort

        for(int i = 0; i < n; i++){
            printf("%d", vetor[i]);
            if(i < n - 1){
                printf(" ");
            }
        }
        printf("\n");

        free(vetor); // libera memória
    }

    return 0;
}
