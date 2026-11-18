#include <stdio.h>
#include <stdlib.h>

#define N 16

struct Node
{
    int board[N];
    int level;
    int cost;
    int blank;
    struct Node *parent;
};

int goal[N] =
{
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 0
};

int distance(int board[])
{
    int i, j, d = 0;
    int x, y;

    for (i = 0; i < 16; i++)
    {
        if (board[i] == 0)
            continue;

        x = (board[i] - 1) / 4;
        y = (board[i] - 1) % 4;

        d += abs(i / 4 - x);
        d += abs(i % 4 - y);
    }

    return d;
}

struct Node *newNode(int board[], int blank, int level, struct Node *parent)
{
    int i;

    struct Node *node = (struct Node *)malloc(sizeof(struct Node));

    for (i = 0; i < 16; i++)
        node->board[i] = board[i];

    node->blank = blank;
    node->level = level;
    node->parent = parent;

    node->cost = level + distance(board);

    return node;
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void printBoard(int board[])
{
    int i;

    for (i = 0; i < 16; i++)
    {
        if (board[i] == 0)
            printf("   ");
        else
            printf("%2d ", board[i]);

        if (i % 4 == 3)
            printf("\n");
    }

    printf("\n");
}

int solved(int board[])
{
    int i;

    for (i = 0; i < 16; i++)
    {
        if (board[i] != goal[i])
            return 0;
    }

    return 1;
}

void printPath(struct Node *node)
{
    if (node == NULL)
        return;

    printPath(node->parent);
    printBoard(node->board);
}

int main()
{
    int start[N];
    int i, blank = 0;
    struct Node *list[10000];
    int count = 0;
    struct Node *cur, *child;
    int pos, newpos;

    printf("Enter 15-puzzle:\n");

    for (i = 0; i < 16; i++)
    {
        scanf("%d", &start[i]);

        if (start[i] == 0)
            blank = i;
    }

    cur = newNode(start, blank, 0, NULL);
    list[count++] = cur;

    while (count > 0)
    {
        int best = 0;

        for (i = 1; i < count; i++)
        {
            if (list[i]->cost < list[best]->cost)
                best = i;
        }

        cur = list[best];

        for (i = best; i < count - 1; i++)
            list[i] = list[i + 1];

        count--;

        if (solved(cur->board))
        {
            printf("\nSolution:\n");
            printPath(cur);
            return 0;
        }

        pos = cur->blank;

        if (pos / 4 > 0)
        {
            newpos = pos - 4;

            child = newNode(cur->board, newpos,
                            cur->level + 1, cur);

            swap(&child->board[pos], &child->board[newpos]);
            child->blank = newpos;
            child->cost = child->level + distance(child->board);

            list[count++] = child;
        }

        if (pos / 4 < 3)
        {
            newpos = pos + 4;

            child = newNode(cur->board, newpos,
                            cur->level + 1, cur);

            swap(&child->board[pos], &child->board[newpos]);
            child->blank = newpos;
            child->cost = child->level + distance(child->board);

            list[count++] = child;
        }

        if (pos % 4 > 0)
        {
            newpos = pos - 1;

            child = newNode(cur->board, newpos,
                            cur->level + 1, cur);

            swap(&child->board[pos], &child->board[newpos]);
            child->blank = newpos;
            child->cost = child->level + distance(child->board);

            list[count++] = child;
        }

        if (pos % 4 < 3)
        {
            newpos = pos + 1;

            child = newNode(cur->board, newpos,
                            cur->level + 1, cur);

            swap(&child->board[pos], &child->board[newpos]);
            child->blank = newpos;
            child->cost = child->level + distance(child->board);

            list[count++] = child;
        }
    }

    printf("No solution found.\n");

    return 0;
}
