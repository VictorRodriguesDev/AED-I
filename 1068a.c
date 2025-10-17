#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verify(char *vetor);

int main()
{
    //define o vetor
    char *vetor = (char *) malloc (1001 * sizeof(char));
    if(vetor == NULL){ //checa se a alocação funcionou 
        //printf("Erro de alocacao!\n");
        return 1;
    }
    //le o vetor
    while(scanf("%s", vetor) != EOF){
        if(verify(vetor)){
            printf("correct\n");
        }else{
            printf("incorrect\n");
        }
    }
    free(vetor);
    return 0;
}

int verify(char *vetor)
{
    int len = strlen(vetor); // le o tamaho do vetor
    int open = 0; // le as aberturas de parenteses
    for (int i = 0; i < len; i++){
        if(*(vetor + i) == '('){
            //guarda uma possivel abertura
            open++;
        }else if(*(vetor + i) == ')'){
            if(open == 0){
                return 0; //tentou fechar sem abrir
            }
            //contabiliza um fecha e abre
            open--;
        }
    }
    
    return (open == 0);
}
