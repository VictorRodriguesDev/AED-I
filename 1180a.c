#include <stdio.h>

int main(){
    int N;
    int Vetor[N];
    int menorValor = 9999999, posicaoMenor = 0;
    printf("Digite o tamanho do vetor: \n");
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        printf("Vetor[%d] = ", i);
        scanf("%d", &Vetor[i]);
    }
    for (int i = 0; i < N; i++)
    {
        if(Vetor[i] < menorValor){
            menorValor = Vetor[i];
            posicaoMenor = i;
        }
    }
    printf("O menor valor do vetor e: %d, e sua posicao %d.\n", menorValor, posicaoMenor);
}