#include <stdio.h>

int main() {
    int x, y;
    scanf("%d%d\n", &x, &y);

    char map[100][100];
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            scanf("%c", &map[i][j]);
        }
        getchar(); // lê o '\n'
    }

    // Direções: 0 = direita, 1 = esquerda, 2 = baixo, 3 = cima
    int dir = 0;
    int r = 0, c = 0;

    int visited[100][100] = {0};

    while (1) {
        // Se já visitou essa posição, ciclo detectado
        if (visited[r][c]) {
            printf("!\n");
            break;
        }
        visited[r][c] = 1;

        char cell = map[r][c];

        if (cell == '*') {
            printf("*\n");
            break;
        }

        // Atualiza direção se for seta
        if (cell == '>') dir = 0;
        else if (cell == '<') dir = 1;
        else if (cell == 'v') dir = 2;
        else if (cell == '^') dir = 3;

        // Move para próxima posição
        if (dir == 0) c++;
        else if (dir == 1) c--;
        else if (dir == 2) r++;
        else if (dir == 3) r--;

        // Verifica limites do mapa
        if (r < 0 || r >= y || c < 0 || c >= x) {
            printf("!\n");
            break;
        }
    }

    return 0;
}
