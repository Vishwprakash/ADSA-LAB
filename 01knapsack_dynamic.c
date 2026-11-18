#include <stdio.h>

#define N 20

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int main()
{
    int n, W;
    int weight[N], value[N];
    int dp[N + 1][N + 1];
    int i, w;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter weights:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &weight[i]);

    printf("Enter values:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &value[i]);

    printf("Enter capacity: ");
    scanf("%d", &W);

    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                dp[i][w] = 0;

            else if (weight[i - 1] <= w)
                dp[i][w] = max(value[i - 1] +
                               dp[i - 1][w - weight[i - 1]],
                               dp[i - 1][w]);

            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    printf("Maximum profit = %d\n", dp[n][W]);

    return 0;
}
