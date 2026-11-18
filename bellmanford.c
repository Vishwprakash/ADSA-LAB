#include <stdio.h>

#define N 20
#define INF 9999

struct Edge
{
    int u, v, w;
};

int main()
{
    int n, e, i, j, src;
    int dist[N];
    struct Edge edge[N * N];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v weight):\n");

    for (i = 0; i < e; i++)
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);

    printf("Enter source vertex: ");
    scanf("%d", &src);

    for (i = 0; i < n; i++)
        dist[i] = INF;

    dist[src] = 0;

    for (i = 1; i < n; i++)
    {
        for (j = 0; j < e; j++)
        {
            int u = edge[j].u;
            int v = edge[j].v;
            int w = edge[j].w;

            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (j = 0; j < e; j++)
    {
        int u = edge[j].u;
        int v = edge[j].v;
        int w = edge[j].w;

        if (dist[u] != INF && dist[u] + w < dist[v])
        {
            printf("Negative weight cycle exists.\n");
            return 0;
        }
    }

    printf("\nShortest distances:\n");

    for (i = 0; i < n; i++)
        printf("%d -> %d = %d\n", src, i, dist[i]);

    return 0;
}
