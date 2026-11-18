#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int path[MAX];
int n;

int safe(int v, int pos)
{
    int i;

    if (!graph[path[pos - 1]][v])
        return 0;

    for (i = 0; i < pos; i++)
    {
        if (path[i] == v)
            return 0;
    }

    return 1;
}

int hamiltonian(int pos)
{
    int v;

    if (pos == n)
    {
        if (graph[path[pos - 1]][path[0]])
            return 1;

        return 0;
    }

    for (v = 1; v < n; v++)
    {
        if (safe(v, pos))
        {
            path[pos] = v;

            if (hamiltonian(pos + 1))
                return 1;

            path[pos] = -1;
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

    for (i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0;

    if (hamiltonian(1))
    {
        printf("Hamiltonian cycle: ");

        for (i = 0; i < n; i++)
            printf("%d ", path[i]);

        printf("%d\n", path[0]);
    }
    else
    {
        printf("Hamiltonian cycle does not exist.\n");
    }

    return 0;
}
