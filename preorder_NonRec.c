#include <stdio.h>
#include <stdlib.h>

#define N 100

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *newNode(int x)
{
    struct Node *temp;

    temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = x;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

void preorder(struct Node *root)
{
    struct Node *stack[N];
    int top = -1;
    struct Node *temp;

    if (root == NULL)
        return;

    stack[++top] = root;

    while (top != -1)
    {
        temp = stack[top--];

        printf("%d ", temp->data);

        if (temp->right != NULL)
            stack[++top] = temp->right;

        if (temp->left != NULL)
            stack[++top] = temp->left;
    }
}

int main()
{
    struct Node *root;

    root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    printf("Preorder: ");
    preorder(root);

    return 0;
}
