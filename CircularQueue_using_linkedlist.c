#include <stdio.h>
#include <stdlib.h>

struct node
{
    int d;
    struct node *next;
};
struct node *rare = NULL;

void enqueue(int x)
{
    struct node *newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->d = x;
    if (rare = NULL)
    {
        rare = newnode;
        rare->next = rare;
    }
    else
    {
        newnode->next = rare->next;
        rare->next = newnode;
        rare = newnode;
    }
}

void dequeue()
{
    struct node *temp;
    if(rare== NULL)
    {
        printf("Queue is empty");
        return;
    }
    temp = rare->next;
    printf("Deleted : %d ",temp->d);
    
}
