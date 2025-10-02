#include <stdio.h>
#include <stdlib.h>
#define SIZE 9

int verificaSudoku(int **matriz);

int main(){
    int totalMatrizes;
    scanf("%d", &totalMatrizes);

    for (int caso = 1; caso <= totalMatrizes; caso++){
        //alocação dinamica da matriz
        int **matriz = (int **) malloc (SIZE * sizeof(int *));
        if(!matriz){
            //printf("Erro de alocacao de linhas.\n");
            return 1;
        }
        for (int i = 0; i < SIZE; i++){
            *(matriz + i) = (int *) malloc (SIZE * sizeof(int));
            if(!*(matriz + i)){
                //printf("Erro de alocacao de colunas.\n");
                return 1;
            }
        }
        //leitura da matriz
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                scanf("%d", (*(matriz + i) + j));
            }
        }

        printf("Instancia %d\n", caso);
        if(verificaSudoku(matriz)){
            printf("SIM\n");
        }else{
            printf("NAO\n");
        }
        printf("\n");

        for (int i = 0; i < SIZE; i++){
        free(*(matriz + i));
    }
    //liberando memoria
    free(matriz);
    }
    return 0;
}

//verifica se um vetor de 9 numero contem algum numero repetido
int verificaSequencia(int *numeros){
    int *ocorrencias = (int *) calloc (SIZE + 1, sizeof (int));
    if (!ocorrencias){
        //printf("Erro de alocacao em ocorrencias.\n");
        exit(1);
    }
    
    for (int i = 0; i < SIZE; i++){
        int valor = *(numeros + i);
        if (valor < 1 || valor > 9 || *(ocorrencias + valor)){
            free(ocorrencias);
            return 0;
        }
        *(ocorrencias + valor) = 1;
    }
    free(ocorrencias);
    return 1;
}

//verifica se existe um numero repitido na linha
int verificaLinhas(int **matriz){
    int *valores = (int *) malloc(SIZE * sizeof(int));
    if (!valores){
        //printf("Erro de alocacao em valores.\n");
        exit(1);
    }
    for (int linha = 0; linha < SIZE; linha++){
        for (int coluna = 0; coluna < SIZE; coluna++){
            *(valores + coluna) = *(*(matriz + linha) + coluna);
        }
        if (!verificaSequencia(valores)){
            free(valores);
            return 0;
        }
    }
    free(valores);
    return 1;
}

//verifica se existe um numero repitido na coluna
int verificaColuna(int **matriz){
    int *valores = (int *) malloc(SIZE * sizeof(int));
    if (!valores){
        //printf("Erro de alocacao em valores.\n");
        exit(1);
    }
    for (int coluna = 0; coluna < SIZE; coluna++){
        for (int linha = 0; linha < SIZE; linha++){
            *(valores + linha) = *(*(matriz + linha) + coluna);
        }
        if (!verificaSequencia(valores)){
            free(valores);
            return 0;
        }
    }
    free(valores);
    return 1;
}

//verifica todas as matrizes 3x3 dentro do sudoku
int verificaBloco(int **matriz){
    int *valores = (int *) malloc(SIZE * sizeof(int));
    if (!valores){
        //printf("Erro de alocacao em valores.\n");
        exit(1);
    }
    for (int blocoLinha = 0; blocoLinha < SIZE; blocoLinha += 3){
        for (int blocoColuna = 0; blocoColuna < SIZE; blocoColuna += 3){
            int k = 0;
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3; j++){
                    *(valores + k++)= *(*(matriz + (blocoLinha + i)) + (blocoColuna + j));
                }
            }
            if (!verificaSequencia(valores)){
                free(valores);
                return 0;
            }
        }
    }
    free(valores);
    return 1;
}

int verificaSudoku(int **matriz){
    return verificaLinhas(matriz) && verificaColuna(matriz) && verificaBloco(matriz);
}