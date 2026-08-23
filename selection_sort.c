#include <stdio.h>

void selection_sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
            if (min != i)
            {
                int temp = arr[min];
                arr[min] = arr[i];
                arr[i] = temp;
            }
    }
}
int main()
{
    int arr[] = {11, 2, 5, 23, 45, 0};
    int size = sizeof(arr) / sizeof(arr[0]);

    // function calling
    selection_sort(arr, size);

    printf("sorted array is : ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
