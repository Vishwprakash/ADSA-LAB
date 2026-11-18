#include <stdio.h>

#define INF 9999
#define N 20

void prim(int g[N][N], int n) {
    int selected[N] = {0};
    int i, j, edges = 0;
    int x, y, min, total = 0;

    selected[0] = 1;

    printf("\nEdges in MST:\n");

    while (edges < n - 1) {
        min = INF;
        x = y = -1;

        for (i = 0; i < n; i++) {
            if (selected[i]) {
                for (j = 0; j < n; j++) {
                    if (!selected[j] && g[i][j] &&
                        g[i][j] < min) {
                        min = g[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        if (x == -1) {
            printf("Graph is not connected\n");
            return;
        }

        printf("%d - %d : %d\n", x, y, min);

        total += min;
        selected[y] = 1;
        edges++;
    }

    printf("Minimum cost = %d\n", total);
}

int main() {
    int g[N][N], n;
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    prim(g, n);

    return 0;
}
