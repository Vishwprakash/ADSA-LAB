#include <stdio.h>
void insertElement(float b[], int n)
{
    int j;
    for (int i = 0; i < n; i++)
    {
        float key = b[i];
        while (j >= 0 && b[j] > key)
        {
            b[j + 1] = b[j];
            j--;
        }
        b[j + 1] = key;
    }
}
void bucket_sort(float a[], int n)
{
    int bucketCount = 10;
    float buckets[10][10];
    int bucketSize[10] = {0};
    
    // distrbute array elements into buckets
    for (int i = 0; i < n; i++)
    {
        int bi = a[i] * bucketCount;
        buckets[bi][bucketSize[bi]++] = a[i];
    }

    // sort individual buckets
    for (int i = 0; i < bucketCount; i++)
    {
        if (bucketSize[i] > 0)
        {
            insertElement(buckets[i], bucketSize[i]);
        }
    }

    // concatenate buckets back into the array
    int k = 0;
    for (int i = 0; i < bucketCount; i++)
    {
        for (int j = 0; j < bucketSize[i]; j++)
        {
            a[k++] = buckets[i][j];
        }
    }
}

int main()
{
    float a[] = {0.42, 0.32, 0.73, 0.25, 0.89, 0.11, 0.67};
    int n = sizeof(a) / sizeof(a[0]);

    bucket_sort(a, n);
    for (int i = 0; i < n; i++)
    {
        printf("%.2f ", a[i]);
    }
}
