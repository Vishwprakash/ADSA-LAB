#include <stdio.h>

#define N 100

struct Point
{
    int x, y;
};

struct Point p[N];
int n;

int cross(struct Point a, struct Point b, struct Point c)
{
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}

void sortPoints()
{
    int i, j;
    struct Point temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].x > p[j].x ||
               (p[i].x == p[j].x && p[i].y > p[j].y))
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void convexHull()
{
    struct Point hull[2 * N];
    int k = 0;
    int i;

    sortPoints();

    for (i = 0; i < n; i++)
    {
        while (k >= 2 &&
               cross(hull[k - 2], hull[k - 1], p[i]) <= 0)
            k--;

        hull[k++] = p[i];
    }

    for (i = n - 2; i >= 0; i--)
    {
        while (k >= 2 &&
               cross(hull[k - 2], hull[k - 1], p[i]) <= 0)
            k--;

        hull[k++] = p[i];
    }

    k--;

    printf("Points on Convex Hull:\n");

    for (i = 0; i < k; i++)
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
}

int main()
{
    int i;

    printf("Enter number of points: ");
    scanf("%d", &n);

    printf("Enter points:\n");

    for (i = 0; i < n; i++)
        scanf("%d %d", &p[i].x, &p[i].y);

    convexHull();

    return 0;
}
