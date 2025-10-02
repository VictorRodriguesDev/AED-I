#include <stdio.h>
#define SIZE 9

int verificaSudoku(int matriz[SIZE][SIZE]);

int main(){
    int totalMatrizes;
    scanf("%d", &totalMatrizes);

    for (int caso = 1; caso <= totalMatrizes; caso++){
        int matriz[SIZE][SIZE];
        //Leitura da matriz
        for (int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                //le os valores da matriz
                scanf("%d", &matriz[i][j]);
            }
        }
        printf("Instancia %d\n", caso);
        if(verificaSudoku(matriz)){
            printf("SIM\n");
        }else{
            printf("NAO\n");
        }
        printf("\n");
    }
    return 0;
}

//verifica se um vetor de 9 numero contem algum numero repetido
int verificaSequencia(int numeros[SIZE]){
    int ocorrencias[SIZE + 1] = {0};
    for (int i = 0; i < SIZE; i++){
        int valor = numeros[i];
        if (valor < 1 || valor > 9 || ocorrencias[valor]){
            return 0;
        }
        ocorrencias[valor] = 1;
    }
    return 1;
}

//verifica se existe um numero repitido na linha
int verificaLinhas(int matriz[SIZE][SIZE]){
    for (int linha = 0; linha < SIZE; linha++){
        int valores[SIZE];
        for (int coluna = 0; coluna < SIZE; coluna++){
            valores[coluna] = matriz[linha][coluna];
        }
        if (!verificaSequencia(valores)){
            return 0;
        }
    }
    return 1;
}

//verifica se existe um numero repitido na coluna
int verificaColuna(int matriz[SIZE][SIZE]){
    for (int coluna = 0; coluna < SIZE; coluna++){
        int valores[SIZE];
        for (int linha = 0; linha < SIZE; linha++){
            valores[linha] = matriz[linha][coluna];
        }
        if (!verificaSequencia(valores)){
            return 0;
        }
    }
    return 1;
}

//verifica todas as matrizes 3x3 dentro do sudoku
int verificaBloco(int matriz[SIZE][SIZE]){
    for (int blocoLinha = 0; blocoLinha < SIZE; blocoLinha += 3){
        for (int blocoColuna = 0; blocoColuna < SIZE; blocoColuna += 3){
            int valores[SIZE], k = 0;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    valores[k++] = matriz[blocoLinha + i][blocoColuna + j];
                }
            }
            if (!verificaSequencia(valores)){
                return 0;
            }
        }
    }
    return 1;
}

int verificaSudoku(int matriz[SIZE][SIZE]){
    return verificaLinhas(matriz) && verificaColuna(matriz) && verificaBloco(matriz);
}