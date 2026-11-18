#include <stdio.h>

#define N 20

struct Job
{
    char id;
    int deadline;
    int profit;
};

int main()
{
    struct Job job[N];
    char result[N];
    int n, i, j, maxDeadline = 0;
    int slot[N];

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    printf("Enter job id, deadline and profit:\n");

    for (i = 0; i < n; i++)
    {
        scanf(" %c%d%d", &job[i].id,
              &job[i].deadline,
              &job[i].profit);

        if (job[i].deadline > maxDeadline)
            maxDeadline = job[i].deadline;
    }

    /* Sort jobs according to profit */
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (job[i].profit < job[j].profit)
            {
                struct Job temp = job[i];
                job[i] = job[j];
                job[j] = temp;
            }
        }
    }

    for (i = 0; i < N; i++)
        slot[i] = 0;

    for (i = 0; i < n; i++)
    {
        for (j = job[i].deadline; j >= 1; j--)
        {
            if (slot[j] == 0)
            {
                slot[j] = 1;
                result[j] = job[i].id;
                break;
            }
        }
    }

    printf("Job sequence: ");

    for (i = 1; i <= maxDeadline; i++)
    {
        if (slot[i])
            printf("%c ", result[i]);
    }

    return 0;
}
