#include <stdio.h>
#define n 100

int que[n];
int f = -1, r = -1;

void enqueuq(int i)
{
    if ((r + 1) % n == f)
    {
        printf("Queue is full");
        return;
    }
    if (f == -1)
        f = 0;

    r = (r + 1) % n;
    que[r] = i;
}

void dequque()
{
    if (f == -1)
    {
        printf("Queue is Empty");
        return;
    }
    printf("Dequeue : %d ", que[f]);
    if (f == r)
    {
        f = -1;
        r = -1;
    }
    else
    {
        f = (f + 1) % n;
    }
    printf("\n");
}

void display()
{
    if (f == -1)
    {
        printf("Queue is Empty");
        return;
    }
    int i = f;
    while (1)
    {
        printf("Enqueue : %d\n", que[i]);
        if (i == r)
        {
            break;
        }
        i = (i + 1) % n;
    }
    printf("\n");
}

int main()
{
    enqueuq(10);
    enqueuq(20);
    enqueuq(30);
    enqueuq(40);

    display();

    dequque();
    dequque();

    enqueuq(50);
    enqueuq(60);
    display();
}
