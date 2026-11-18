#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *rear = NULL;

void enqueue(int x)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = x;

    if (rear == NULL)
    {
        rear = newNode;
        rear->next = rear;
    }
    else
    {
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue()
{
    struct Node *temp;

    if (rear == NULL)
    {
        printf("Queue is Empty\n");
        return;
    }

    temp = rear->next;

    printf("Deleted = %d\n", temp->data);

    if (temp == rear)
        rear = NULL;
    else
        rear->next = temp->next;

    free(temp);
}

void display()
{
    struct Node *temp;

    if (rear == NULL)
    {
        printf("Queue is Empty\n");
        return;
    }

    temp = rear->next;

    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != rear->next);

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

    enqueue(40);

    display();

    return 0;
}
