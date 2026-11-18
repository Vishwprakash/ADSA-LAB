#include <stdio.h>

#define MAX 100

int q1[MAX], q2[MAX];
int front1 = 0, rear1 = -1;
int front2 = 0, rear2 = -1;

void enqueue(int q[], int *rear, int x)
{
    q[++(*rear)] = x;
}

int dequeue(int q[], int *front, int rear)
{
    if (*front > rear)
        return -1;

    return q[(*front)++];
}

void push(int x)
{
    enqueue(q1, &rear1, x);
}

void pop()
{
    int temp;
    int oldFront, oldRear;

    if (front1 > rear1)
    {
        printf("Stack is Empty\n");
        return;
    }

    while (front1 < rear1)
    {
        temp = dequeue(q1, &front1, rear1);
        enqueue(q2, &rear2, temp);
    }

    printf("Deleted = %d\n", dequeue(q1, &front1, rear1));

    oldFront = front1;
    oldRear = rear1;

    front1 = front2;
    rear1 = rear2;

    front2 = oldFront;
    rear2 = oldRear;
}

void display()
{
    int i;

    for (i = front1; i <= rear1; i++)
        printf("%d ", q1[i]);

    printf("\n");
}

int main()
{
    push(10);
    push(20);
    push(30);

    display();

    pop();

    display();

    return 0;
}
