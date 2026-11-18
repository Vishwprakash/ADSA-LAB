#include <stdio.h>

#define N 20
#define INF 9999

int cost[N][N];
int visited[N];
int n;
int minCost = INF;

void tsp(int city, int count, int total)
{
    int i;

    if (count == n)
    {
        if (cost[city][0] != 0)
        {
            total = total + cost[city][0];

            if (total < minCost)
                minCost = total;
        }

        return;
    }

    for (i = 0; i < n; i++)
    {
        if (!visited[i] && cost[city][i] != 0)
        {
            visited[i] = 1;

            tsp(i, count + 1, total + cost[city][i]);

            visited[i] = 0;
        }
    }
}

int main()
{
    int i, j;

    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    visited[0] = 1;

    tsp(0, 1, 0);

    printf("Minimum tour cost = %d\n", minCost);

    return 0;
}
