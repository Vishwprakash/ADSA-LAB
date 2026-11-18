#include <stdio.h>

#define N 20

int main()
{
    int coin[N], n, amount;
    int i, count = 0;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    printf("Enter coin values:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &coin[i]);

    printf("Enter amount: ");
    scanf("%d", &amount);

    /* Sort coins in descending order */
    for (i = 0; i < n - 1; i++)
    {
        int j;
        for (j = i + 1; j < n; j++)
        {
            if (coin[i] < coin[j])
            {
                int t = coin[i];
                coin[i] = coin[j];
                coin[j] = t;
            }
        }
    }

    printf("Coins used: ");

    for (i = 0; i < n; i++)
    {
        while (amount >= coin[i])
        {
            amount = amount - coin[i];
            printf("%d ", coin[i]);
            count++;
        }
    }

    printf("\nNumber of coins = %d\n", count);

    if (amount != 0)
        printf("Exact amount cannot be formed.\n");

    return 0;
}
