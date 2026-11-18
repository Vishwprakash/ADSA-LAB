#include <stdio.h>

#define N 20

int graph[N][N];
int color[N];
int n, m;

int safe(int v, int c)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (graph[v][i] && color[i] == c)
            return 0;
    }

    return 1;
}

int coloring(int v)
{
    int c;

    if (v == n)
        return 1;

    for (c = 1; c <= m; c++)
    {
        if (safe(v, c))
        {
            color[v] = c;

            if (coloring(v + 1))
                return 1;

            color[v] = 0;
        }
    }

    return 0;
}

int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter number of colors: ");
    scanf("%d", &m);

    if (coloring(0))
    {
        printf("Color assignment:\n");

        for (i = 0; i < n; i++)
            printf("Vertex %d -> Color %d\n", i, color[i]);
    }
    else
    {
        printf("Coloring is not possible.\n");
    }

    return 0;
}
