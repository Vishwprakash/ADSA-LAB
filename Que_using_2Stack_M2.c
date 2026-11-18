#include <stdio.h>

#define MAX 100

int s1[MAX], s2[MAX];
int top1 = -1, top2 = -1;

void push(int s[], int *top, int x)
{
    s[++(*top)] = x;
}

int pop(int s[], int *top)
{
    return s[(*top)--];
}

void enqueue(int x)
{
    push(s1, &top1, x);
}

void dequeue()
{
    if (top1 == -1)
    {
        printf("Queue is Empty\n");
        return;
    }

    while (top1 != -1)
        push(s2, &top2, pop(s1, &top1));

    printf("Deleted = %d\n", pop(s2, &top2));

    while (top2 != -1)
        push(s1, &top1, pop(s2, &top2));
}

void display()
{
    int i;

    for (i = 0; i <= top1; i++)
        printf("%d ", s1[i]);

    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);

    display();

    dequeue();

    display();

    return 0;
}
