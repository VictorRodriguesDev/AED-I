#include <stdio.h>
#include <stdlib.h>

void insertion(int, int *height);

int main(){
    int N, numberofPeople;
    //le a quantidade de casos
    scanf("%d", &N);
    while (N--){
        //le o numero de pessoas
        scanf("%d", &numberofPeople);
        int *height = (int *) malloc (numberofPeople * sizeof(int));
        if(height == NULL){ //checa se a alocação funcionou 
        //printf("Erro de alocacao!\n");
        return 1;
    }
        //leitura do vetor
        for (int i = 0; i < numberofPeople; i++){
            scanf("%d", &*(height + i));
        }
        
        insertion(numberofPeople, height);
        printf("\n");
        free(height);
    }
    return 0;
}

void insertion(int numberofPeople, int *height){
    int i, j, x;
    for  (j = 1; j < numberofPeople; j++){
        x = height[j];
        for  (i = j - 1; i >= 0 && *(height + i) > x; i--){
            *(height + (i + 1)) = *(height + i);
        }
        height[i + 1] = x;
    }

    for (int i = 0; i < numberofPeople; i++){
        if(i == numberofPeople - 1){
            printf("%d", *(height + i));
        }else{
            printf("%d ", *(height + i));
        }
    }
}