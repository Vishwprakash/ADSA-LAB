#include <stdio.h>

int getmax(int a[], int n)
{
    int max = a[0];

    for (int i = 1; i < n; i++)
    {
        if (max < a[i])
        {
            max = a[i];
        }
    }

    return max;
}

void counter_sort(int a[], int n, int pos)
{
    int count[10] = {0};
    int b[n];

    // Count digits
    for (int i = 0; i < n; i++)
    {
        count[(a[i] / pos) % 10]++;
    }

    // Find positions
    for (int i = 1; i < 10; i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    // Place elements in b[]
    for (int i = n - 1; i >= 0; i--)
    {
        b[--count[(a[i] / pos) % 10]] = a[i];
    }

    // Copy back to a[]
    for (int i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
}

void radix_sort(int a[], int n)
{
    int maximum = getmax(a, n);

    for (int pos = 1; maximum / pos > 0; pos = pos * 10)
    {
        counter_sort(a, n, pos);
    }
}

int main()
{
    int a[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(a) / sizeof(a[0]);

    radix_sort(a, n);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    return 0;
}
// T(n) = 0(d(n+k))
// S(n) = 0(n+k)
