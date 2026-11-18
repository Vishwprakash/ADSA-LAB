#include <stdio.h>

#define N 20

int g[N][N];
int color[N];
int tin[N], tout[N];
int timer;

void dfs(int u, int n) {
    int v;

    color[u] = 1;
    tin[u] = ++timer;

    for (v = 0; v < n; v++) {

        if (!g[u][v])
            continue;

        if (color[v] == 0) {
            printf("%d -> %d : Tree Edge\n", u, v);
            dfs(v, n);
        }
        else if (color[v] == 1) {
            printf("%d -> %d : Back Edge\n", u, v);
        }
        else {
            if (tin[u] < tin[v])
                printf("%d -> %d : Forward Edge\n", u, v);
            else
                printf("%d -> %d : Cross Edge\n", u, v);
        }
    }

    color[u] = 2;
    tout[u] = ++timer;
}

int main() {
    int n, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter directed adjacency matrix:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    for (i = 0; i < n; i++)
        color[i] = 0;

    timer = 0;

    printf("\nDFS Edge Classification:\n");

    for (i = 0; i < n; i++) {
        if (color[i] == 0)
            dfs(i, n);
    }

    return 0;
}
