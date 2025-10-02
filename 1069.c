#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verify(int, char *string);

int main(){
    int N;
    scanf("%d", &N); //leitura da quantidade de casos de teste
    char *string = (char *) malloc (1001 * sizeof (char)); // alocando memoria dinamicamente
    if(string == NULL){ //checa se a alocação funcionou 
        printf("Erro de alocacao!\n");
        return 1;
    }

    verify(N, string);

    free(string);
    return 0;
}
void verify(int N, char *string){
    while(N--){
        scanf("%s", string); //le os valores da string
        int left = 0; //quantidade de < que ainda não foram pareados
        int diamonds = 0; // quantidade de <> formados
        int len = strlen(string); //le o tamanho da string

        //percorrendo a string
        for (int i = 0; i < len; i++){
            if(*(string + i) == '<'){
                //guarda como uma abertura possivel
                left++;
            }else if(*(string + i) == '>' && left > 0){
                //fecha a abertura anterior e forma um diamante
                diamonds++;
                left--;
            }
        }
        printf("%d\n", diamonds);
    }
}