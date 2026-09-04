#include <stdio.h>

void merge(int a[], int l, int m, int h)
{
    int b[h - l + 1];
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= h)
    {
        if (a[i] <= a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
        k++;
    }

    while (i <= m)
    {
        b[k] = a[i];
        i++;
        k++;
    }

    while (j <= h)
    {
        b[k] = a[j];
        j++;
        k++;
    }

    for (i = 0; i < k; i++)
    {
        a[l + i] = b[i];
    }
}

void merge_sort(int a[], int n)
{
    int size, i, m, h;

    for (size = 1; size < n; size = size * 2)
    {
        for (i = 0; i < n - size; i = i + 2 * size)
        {
            m = i + size - 1;
            h = i + 2 * size - 1;

            if (h >= n)
                h = n - 1;

            merge(a, i, m, h);
        }
    }
}

int main()
{
    int a[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(a) / sizeof(a[0]);

    merge_sort(a, n);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}
