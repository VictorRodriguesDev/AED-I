#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int Vetor[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &Vetor[i]);
    }

    int menorValor = Vetor[0];
    int posicaoMenor = 0;

    for (int i = 1; i < N; i++) {
        if (Vetor[i] < menorValor) {
            menorValor = Vetor[i];
            posicaoMenor = i;
        }
    }

    printf("Menor valor: %d\n", menorValor);
    printf("Posicao: %d\n", posicaoMenor);

    return 0;
}
