#include <stdio.h>

int main(){
    int N, menorValor = 0, posicaoMenor = 0;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &N);
    int Vetor[N];
    int *p = Vetor;
    for (int i = 0; i < N; i++)
    {
        printf("Vetor[%d] = ", i);
        scanf("%d", &*(p + i));
    }
    menorValor = *Vetor;
    for (int i = 0; i < N; i++)
    {
        if(*(Vetor + i) < menorValor){
            menorValor = *(Vetor + i);
            posicaoMenor = i;
        }
    }
    printf("Menor valor: %d\n", menorValor);
    printf("Posicao: %d\n", posicaoMenor);
    return 0;
}