#include <stdio.h>

void merge(int a[], int b[], int lb, int mid, int ub);

void merge_sort(int a[], int b[], int lb, int ub)
{
    if (ub > lb)
    {
        int mid = (lb + ub) / 2;
        merge_sort(a, b, lb, mid);
        merge_sort(a, b, mid + 1, ub);
        merge(a, b, lb, mid, ub);
    }
}

void merge(int a[], int b[], int lb, int mid, int ub)
{
    int i = lb;
    int j = mid + 1;
    int k = lb;

    while (i <= mid && j <= ub)
    {
        if (a[i] <= a[j])
        {
            b[k++] = a[i++];
        }
        else
        {
            b[k++] = a[j++];
        }
    }

    while (i <= mid)
    {
        b[k++] = a[i++];
    }

    while (j <= ub)
    {
        b[k++] = a[j++];
    }

    for (i = lb; i <= ub; i++)
    {
        a[i] = b[i];
    }
}

int main()
{
    int a[] = {39, 27, 48, 11, 0,1,78};
    int len = sizeof(a) / sizeof(a[0]);
    int b[len];
    merge_sort(a, b, 0, len - 1);

    printf("Sorted array: ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
