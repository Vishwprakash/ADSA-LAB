#include <stdio.h>

#define INF 9999
#define N 20

void dijkstra(int g[N][N], int n, int src) {
    int dist[N], used[N] = {0};
    int i, j, u, min;

    for (i = 0; i < n; i++)
        dist[i] = g[src][i];

    dist[src] = 0;

    for (i = 0; i < n - 1; i++) {
        min = INF;
        u = -1;

        for (j = 0; j < n; j++) {
            if (!used[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        used[u] = 1;

        for (j = 0; j < n; j++) {
            if (!used[j] && g[u][j] != INF &&
                dist[u] + g[u][j] < dist[j]) {
                dist[j] = dist[u] + g[u][j];
            }
        }
    }

    printf("\nShortest distances from vertex %d:\n", src);

    for (i = 0; i < n; i++)
        printf("%d -> %d = %d\n", src, i, dist[i]);
}

int main() {
    int g[N][N], n, src;
    int i, j, w;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &w);

            if (i == j)
                g[i][j] = 0;
            else if (w == 0)
                g[i][j] = INF;
            else
                g[i][j] = w;
        }
    }

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(g, n, src);

    return 0;
}
