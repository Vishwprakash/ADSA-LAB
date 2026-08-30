#include <stdio.h>

int main()
{
    int a[] = {23, 29, 15, 19, 31, 7, 9, 5, 2};
    int n = sizeof(a) / sizeof(a[0]);

    int gap = n / 2;

    for (int i = gap; i >= 1; i = i / 2)
    {
        gap = i;

        for (int j = gap; j < n; j++)
        {
            for (int k = j - gap; k >= 0; k = k - gap)
            {
                if (a[k + gap] >= a[k])
                {
                    break;
                }
                else
                {
                    int temp = a[k + gap];
                    a[k + gap] = a[k];
                    a[k] = temp;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}
