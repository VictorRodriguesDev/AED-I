#include <stdio.h>

#define MAX 1000000

int freq[10001];

int main() {
    int n, x;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        freq[x]++;
    }

    for (int i = 0; i <= 10000; i++) {
        if (freq[i] > 0) {
            printf("%d aparece %d vez(es)\n", i, freq[i]);
        }
    }

    return 0;
}
