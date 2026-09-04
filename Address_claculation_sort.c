#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct node *bucket[10];

void insert(int value, int address)
{
    struct node *newnode;
    struct node *temp;

    newnode = (struct node *)malloc(sizeof(struct node));

    newnode->data = value;
    newnode->next = NULL;

    if (bucket[address] == NULL ||
        value < bucket[address]->data)
    {
        newnode->next = bucket[address];
        bucket[address] = newnode;
    }
    else
    {
        temp = bucket[address];

        while (temp->next != NULL &&
               temp->next->data < value)
        {
            temp = temp->next;
        }

        newnode->next = temp->next;
        temp->next = newnode;
    }
}

void address_sort(int a[], int n)
{
    int i, address, k;
    struct node *temp, *p;

    for (i = 0; i < 10; i++)
        bucket[i] = NULL;

    for (i = 0; i < n; i++)
    {
        address = a[i] / 10;

        if (address >= 10)
            address = 9;

        insert(a[i], address);
    }

    k = 0;

    for (i = 0; i < 10; i++)
    {
        temp = bucket[i];

        while (temp != NULL)
        {
            a[k] = temp->data;
            k++;

            p = temp;
            temp = temp->next;
            free(p);
        }
    }
}

int main()
{
    int a[] = {23, 7, 45, 12, 89, 34, 56, 18, 3, 72};
    int n = sizeof(a) / sizeof(a[0]);

    address_sort(a, n);

    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}
