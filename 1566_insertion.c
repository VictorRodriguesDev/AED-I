#include <stdio.h>

void insertion(int, int, int height[]);

int main(){
    int N, numberofPeople;
    //le a quantidade de casos
    scanf("%d", &N);
    while (N--){
        //le o numero de pessoas
        scanf("%d", &numberofPeople);
        int height[numberofPeople];
        //leitura do vetor
        for (int i = 0; i < numberofPeople; i++){
            scanf("%d", &height[i]);
        }
        
        insertion(N, numberofPeople, height);
        printf("\n");
    }
}

void insertion(int N, int numberofPeople, int height[]){
    int i, j, x;
    for  (j = 1; j < numberofPeople; j++){
        x = height[j];
        for  (i = j - 1; i >= 0 && height[i] > x; i--){
            height[i + 1] = height[i];
        }
        height[i + 1] = x;
    }

    for (int i = 0; i < numberofPeople; i++){
        printf("%d ", height[i]);
    }
}