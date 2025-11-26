#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int value;
    struct tree *left;
    struct tree *right;
} tree;

tree* createNo(int valor){
    tree *novo = malloc (sizeof(tree));
    if(novo == NULL){
        //erro de alocação
        exit(1);
    }
    novo->value = valor;
    novo->left = NULL;
    novo->right = NULL;
    return novo;
}

tree* Insert(tree *raiz, int value){
    if (raiz == NULL){
        return createNo(value);
    }if(value < raiz->value){
        raiz->left = Insert(raiz->left, value);
    }else{
        raiz->right = Insert(raiz->right, value);
    }
    return raiz;
}

void Imprimir(tree *raiz, int *primeiro){
    if(raiz == NULL){
        return;
    }
    Imprimir(raiz->left, primeiro);
    if(*primeiro){
        printf("%d", raiz->value);
        *primeiro = 0;
    }else{
        printf(" %d", raiz->value);
    }
    Imprimir(raiz->right, primeiro);
}

void liberarArvore(tree *raiz){
    if(raiz == NULL){
        return;
    }
    liberarArvore(raiz->left);
    liberarArvore(raiz->right);
    free(raiz);
}

int main(){
    int NC, N, Altura, primeiro;
    //leitura da quantidade de casos
    scanf("%d", &NC);
    while(NC--){
        //leitura da quantidade de pessoas
        scanf("%d", &N);
        tree *raiz = NULL;
        for(int i = 0; i < N; i++){
            //leitura das alturas
            scanf("%d", &Altura);
            raiz = Insert(raiz, Altura);
        }
        primeiro = 1;
        Imprimir(raiz, &primeiro);
        printf("\n");

        liberarArvore(raiz);
    }
    return 0;
}