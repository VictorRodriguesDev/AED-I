#include <stdio.h>
#include <stdlib.h>

int main() {
    int *v = (int*) malloc(sizeof(int)); // ponteiro para velocidade
    int *t = (int*) malloc(sizeof(int)); // ponteiro para tempo

    while (scanf("%d %d", v, t) != EOF) { // lê até acabar o arquivo
        long long *d = (long long*) malloc(sizeof(long long)); // ponteiro para distância
        *d = (long long) (*v) * (*t) * 2; // cálculo do deslocamento
        printf("%lld\n", *d); // imprime resultado
        free(d); // libera distância
    }

    free(v); // libera velocidade
    free(t); // libera tempo

    return 0;
}
