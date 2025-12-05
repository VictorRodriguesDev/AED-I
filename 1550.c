#include <stdio.h>; // biblioteca de entrada e saída
#include <stdlib.h>; // biblioteca para malloc, free
#include <string.h>; // biblioteca para funções auxiliares

int inverter_numero(int x) { // função para inverter dígitos do número
    int r = 0; // acumulador do número invertido
    while (x > 0) { // enquanto houver dígitos
        r = r * 10 + (x % 10); // adiciona último dígito ao invertido
        x /= 10; // remove o último dígito de x
    } // fim while
    return r; // retorna número invertido
} // fim função inverter_numero

int bfs(int A, int B) { // BFS para calcular menor número de operações
    int max = 100000; // maior valor permitido pelo problema

    int *visitado = (int*) calloc(max + 1, sizeof(int)); // vetor de visitados
    int *fila = (int*) malloc((max + 1) * sizeof(int)); // fila da BFS
    int *dist = (int*) malloc((max + 1) * sizeof(int)); // distâncias (nº de apertos)

    int ini = 0; // ponteiro do início da fila
    int fim = 0; // ponteiro do fim da fila

    fila[fim++] = A; // coloca A na fila
    visitado[A] = 1; // marca A como visitado
    dist[A] = 0; // distância inicial é zero

    while (ini < fim) { // enquanto a fila não está vazia
        int atual = fila[ini++]; // retira elemento do início

        if (atual == B) { // se encontramos o destino
            int resposta = dist[atual]; // pega distância final

            free(visitado); // libera vetor visitado
            free(fila); // libera fila
            free(dist); // libera distâncias

            return resposta; // retorna o total de apertos
        } // fim if

        if (atual + 1 <= max && !visitado[atual + 1]) { // operação +1
            visitado[atual + 1] = 1; // marca como visitado
            dist[atual + 1] = dist[atual] + 1; // incrementa distância
            fila[fim++] = atual + 1; // adiciona na fila
        } // fim operação +1

        int inv = inverter_numero(atual); // calcula número invertido
        if (inv <= max && !visitado[inv]) { // verifica se pode visitar
            visitado[inv] = 1; // marca como visitado
            dist[inv] = dist[atual] + 1; // incrementa distância
            fila[fim++] = inv; // adiciona na fila
        } // fim operação inverter
    } // fim while BFS

    free(visitado); // libera visitados caso não encontre B
    free(fila); // libera fila
    free(dist); // libera dist

    return -1; // falha (não deve acontecer)
} // fim função bfs

int main() { // função principal
    int T; // número de testes

    if (scanf("%d", &T) != 1) // lê T
        return 0; // caso falhe na leitura

    while (T--) { // para cada teste
        int A, B; // valores A e B
        scanf("%d %d", &A, &B); // leitura da dupla

        int resposta = bfs(A, B); // calcula resultado com BFS
        printf("%d\n", resposta); // imprime resposta
    } // fim while

    return 0; // fim do programa
} // fim main
