#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

int verificaPilha(char *eq);

typedef struct cel{
    int conteudo;
    struct cel *next;
} cel;

int main(){
    char *eq = (char *) malloc (MAX * sizeof(char));
    if(eq == NULL){
        //erro de alocação
        return 1;   
    }
    while(fgets(eq, MAX, stdin)){
        int len = strlen(eq);
        if (len > 0 && eq[len - 1] == '\n') {
            eq[len - 1] = '\0';
        }
        if(verificaPilha(eq)){
            printf("correct\n");
        }else{
            printf("incorrect\n");
        }
    }
}

void push(int x, cel *p){
    cel *new;
    new = malloc (sizeof(cel));
    if(new == NULL){
        //erro de alocação
        exit(1);
    }
    new->conteudo = x;
    new->next = p->next;
    p->next = new;
}

void pop(cel *p){
    if(p->next == NULL) return;
    cel *trash = p->next;
    p->next = trash->next;
    free(trash);
}

int verificaPilha(char *eq){
    cel *p = (cel *) malloc (sizeof(cel));
    p->next = NULL;
    int i = 0;

    while(*(eq + i) != '\0'){
        if(*(eq + i) == '('){
            push('(', p);
        }else if(*(eq + i) == ')'){
            if(p->next == NULL){
                free(p);
                return 0;
            }
            pop(p);
        }
        i++;
    }
    //se ainda houver ( na pilha
    if(p->next != NULL){
        while(p->next != NULL){
            pop(p);
        }
        return 0;
    }
    free(p);
    return 1;
}