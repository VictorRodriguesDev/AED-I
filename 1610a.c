#include <stdio.h>
#include <stdlib.h>

int **mat;
int *visitado;
int n, m, ciclo;

// percorre o grafo e verifica o processamento dos vertices
void dfs(int v){
    // se ja foi indetificado um ciclo, não precisa continuar
    if (ciclo){
        return;
    }
    // marca o vertice atual como processando
    *(visitado + v) = 1;
    // percorrendo todos os possiveis destinos da linha V
    for (int i = 0; i < n; i++){
        // se esse valor foi 1 significa q tem uma aresta v-> i
        if (*(*(mat + v) + i)){
            // verifica se o destino i esta em processamento, oque significa um ciclo
            if (*(visitado + i) == 1){
                ciclo = 1;
                return;
            }
            // caso o destino i ainda não foi visitado, chamamos a função novamente de maneira recursiva
            else if (*(visitado + i) == 0){
                dfs(i);
            }
        }
    }
    // vamos marcar o vertice v como totalmente processado
    *(visitado + v) = 2;
}

int main(){
    int t;
    // leitura do casos de teste
    scanf("%d", &t);

    while (t--){
        scanf("%d", &n);
        scanf("%d", &m);
        // alocando dinamicamente a matriz, o calloc inicializa todos os valores em zero, ou seja, não ha arestas
        mat = (int **)malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++){
            *(mat + i) = (int *)calloc(n, sizeof(int));
        }
        // alocação do vetor visitado, cada posição desse vetor representa o estado de um vertice:
        // 0 - não visitado
        // 1 - em processamento
        // 2 - processado

        visitado = (int *)calloc(n, sizeof(int));

        // leitura das arestas do grafo
        for (int i = 0; i < m; i++){
            int a, b;
            scanf("%d", &a);
            scanf("%d", &b);
            a--;
            b--;
            // marca que existe uma conexão entre a e b
            *(*(mat + a) + b) = 1;
        }
        // vamos percorrer todos os vertices chamando dfs
        ciclo = 0;
        for (int i = 0; i < n && !ciclo; i++){
            if (*(visitado + i) == 0)
            {
                dfs(i);
            }
        }
        // verificação se há loop ou não
        if (ciclo){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
        //liberando memoria
        for(int i = 0; i < n; i++){
            free(*(mat + i));
        }
        free(mat);
        free(visitado);
    }
    return 0;
}