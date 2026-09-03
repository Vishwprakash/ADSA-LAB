#include <stdio.h>

void heapify(int a[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[largest]) // left
        largest = l;

    if (r < n && a[r] > a[largest])  // right
        largest = r;

    if (largest != i)
    {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    int i, temp;
// building maxheap
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

//  deleting root
    for (i = n - 1; i > 0; i--)
    {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        heapify(a, i, 0);
    }
}

int main()
{
    int a[] = {23, 29, 15, 19, 31, 7, 9, 5, 2};
    int n = sizeof(a) / sizeof(a[0]);

    heapSort(a, n);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}
