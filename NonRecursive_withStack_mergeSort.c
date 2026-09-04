#include <stdio.h>

#define MAX 100

int stack_l[MAX];      
int stack_h[MAX];      
int stack_state[MAX];   

int top = -1;           


// Push one task into the stack
void push(int l, int h, int state)
{
    top++;

    stack_l[top] = l;
    stack_h[top] = h;
    stack_state[top] = state;
}


// Remove the top task from the stack
void pop(int *l, int *h, int *state)
{
    *l = stack_l[top];
    *h = stack_h[top];
    *state = stack_state[top];

    top--;
}

int isEmpty()
{
    if (top == -1)
        return 1;

    return 0;
}

int peek()
{
    return top;
}


void merge(int a[], int l, int m, int h)
{
    int b[MAX];

    int i = l;          
    int j = m + 1;     
    int k = 0;          


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

    // Copy sorted elements into original array
    for (i = 0; i < k; i++)
        a[l + i] = b[i];
}


void mergeSort(int a[], int n)
{
    int l, h, state, m;

    top = -1;
  
    push(0, n - 1, 0);

    while (!isEmpty())
    {
        // Take the most recent task from stack
        pop(&l, &h, &state);

        if (l >= h)
            continue;

        // Find middle of current part
        m = (l + h) / 2;


        if (state == 0)
        {
            // We first push the current task again
            push(l, h, 1);


            // Push RIGHT part
            push(m + 1, h, 0);

            // Push LEFT part last
            push(l, m, 0);
        }
        else
        {
            merge(a, l, m, h);
        }
    }
}


int main()
{
    int a[] = {38, 27, 43, 3, 9, 82, 10};

    int n = sizeof(a) / sizeof(a[0]);


    mergeSort(a, n);


    printf("Sorted array: ");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);


    return 0;
}
