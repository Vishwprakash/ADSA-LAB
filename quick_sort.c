#include <stdio.h>

int partitioning(int arr[], int start, int end)
{
    // choose the pivot
    int pivot = arr[end];
    // index of smaller element that is indecating the right position of  pivot
    int i = (start - 1);
    for (int j = start; j < end; j++)
    {
        // if current element is smallerthen the pivot
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[end];
    arr[end] = temp;
    return (i + 1);
}
// quick function
int Quick_sort(int arr[], int start, int end)
{
    if (start < end)
    {
        // pivot returns the currect position / index of pivot
        int pivot = partitioning(arr, start, end);

        // recursion calling

        // smaller element then pivot goes left and greater goes to right
        Quick_sort(arr, start, pivot - 1);
        Quick_sort(arr, pivot + 1, end);
    }
}

int main()
{
    int arr[] = {12, 3, 45, 6, 78, 1, 34};
    int size = sizeof(arr) / sizeof(arr[0]);

    // function calling
    Quick_sort(arr, 0, size - 1);

    // print the sorted array
    printf("the sorted array is : ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
