#include <stdio.h>
void insertion_sort(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}
int main()
{
    int arr[] = {11, 2, 5, 23, 45};
    int size = sizeof(arr) / sizeof(arr[0]);
    // function calling
    insertion_sort(arr, size);
    printf("sorted array is : ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
