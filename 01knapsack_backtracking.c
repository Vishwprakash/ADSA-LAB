#include <stdio.h>

#define N 20

int n, W;
int weight[N], value[N];
int maxValue = 0;

void knapsack(int i, int wt, int val)
{
    if (i == n)
    {
        if (val > maxValue)
            maxValue = val;
        return;
    }

    if (wt + weight[i] <= W)
        knapsack(i + 1, wt + weight[i], val + value[i]);

    knapsack(i + 1, wt, val);
}

int main()
{
    int i;

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

    knapsack(0, 0, 0);

    printf("Maximum profit = %d\n", maxValue);

    return 0;
}
