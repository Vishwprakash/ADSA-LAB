#include <stdio.h>

void counter_sort(int a[], int n)
{
    int k = a[0];

    // Find maximum value
    for (int i = 1; i < n; i++)
    {
        if (a[i] > k)
            k = a[i];
    }

    int counter[k + 1];
    int b[n];

    // Initialize counter array
    for (int i = 0; i <= k; i++)
        counter[i] = 0;

    // Count the elements
    for (int i = 0; i < n; i++)
        counter[a[i]]++;

    // Find positions
    for (int i = 1; i <= k; i++)
        counter[i] = counter[i] + counter[i - 1];

    // Put elements into b[]
    for (int i = n - 1; i >= 0; i--)
        b[--counter[a[i]]] = a[i];

    for (int i = 0; i < n; i++)
        a[i] = b[i];
}

int main()
{
    int a[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(a) / sizeof(a[0]);

    counter_sort(a, n);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}
