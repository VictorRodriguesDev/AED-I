#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, menorNumero, posicaoMenor = 0;
    int *Vetor;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    //Alocação dinâmica
    Vetor  = (int *) malloc(n * sizeof(int));
    if (Vetor == NULL){
        printf("Erro de alocação!\n");
        return 1;
    }
    for (int i = 0; i < n; i++){
        printf("Vetor[%d] = ",i);
        scanf("%d", &*(Vetor + i));
    }
    menorNumero = *Vetor;
    for (int i = 0; i < n; i++){
        if (*(Vetor + i) < menorNumero){
            menorNumero = *(Vetor + i);
            posicaoMenor = i;
        }
    }
    printf("Menor valor: %d\n", menorNumero);
    printf("Posicao: %d", posicaoMenor);
    free(Vetor);
    return 0;
}