#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int selected[MAX];
int n, m;

int isClique(int count)
{
    int i, j;

    for (i = 0; i < count; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (!graph[selected[i]][selected[j]])
                return 0;
        }
    }

    return 1;
}

int findClique(int start, int count)
{
    int i;

    if (count == m)
        return isClique(count);

    for (i = start; i < n; i++)
    {
        selected[count] = i;

        if (findClique(i + 1, count + 1))
            return 1;
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

    printf("Enter clique size: ");
    scanf("%d", &m);

    if (m > n)
    {
        printf("Clique does not exist.\n");
        return 0;
    }

    if (findClique(0, 0))
        printf("Clique of size %d exists.\n", m);
    else
        printf("Clique of size %d does not exist.\n", m);

    return 0;
}
