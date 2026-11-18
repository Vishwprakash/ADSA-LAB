#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int color[MAX];
int n;

int bipartite()
{
    int queue[MAX];
    int front, rear;
    int i, v;

    for (i = 0; i < n; i++)
        color[i] = -1;

    for (i = 0; i < n; i++)
    {
        if (color[i] != -1)
            continue;

        front = 0;
        rear = 0;

        queue[rear++] = i;
        color[i] = 0;

        while (front < rear)
        {
            v = queue[front++];

            for (int j = 0; j < n; j++)
            {
                if (graph[v][j])
                {
                    if (color[j] == -1)
                    {
                        color[j] = 1 - color[v];
                        queue[rear++] = j;
                    }
                    else if (color[j] == color[v])
                    {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
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

    if (bipartite())
        printf("Graph is Bipartite.\n");
    else
        printf("Graph is not Bipartite.\n");

    return 0;
}
