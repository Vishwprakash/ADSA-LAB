#include <stdio.h>

#define N 50

typedef struct {
    int u, v, w;
} Edge;

int parent[N];

int find(int x) {
    while (parent[x] != x)
        x = parent[x];

    return x;
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);

    parent[b] = a;
}

void sortEdges(Edge e[], int m) {
    int i, j;
    Edge temp;

    for (i = 0; i < m - 1; i++) {
        for (j = i + 1; j < m; j++) {
            if (e[i].w > e[j].w) {
                temp = e[i];
                e[i] = e[j];
                e[j] = temp;
            }
        }
    }
}

void kruskal(Edge e[], int n, int m) {
    int i, count = 0, total = 0;

    for (i = 0; i < n; i++)
        parent[i] = i;

    sortEdges(e, m);

    printf("\nEdges in MST:\n");

    for (i = 0; i < m && count < n - 1; i++) {

        if (find(e[i].u) != find(e[i].v)) {
            printf("%d - %d : %d\n",
                   e[i].u, e[i].v, e[i].w);

            total += e[i].w;
            unite(e[i].u, e[i].v);
            count++;
        }
    }

    if (count != n - 1)
        printf("Graph is not connected\n");
    else
        printf("Minimum cost = %d\n", total);
}

int main() {
    Edge e[N];
    int n, m, i;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &m);

    printf("Enter edges (u v weight):\n");

    for (i = 0; i < m; i++)
        scanf("%d %d %d",
              &e[i].u, &e[i].v, &e[i].w);

    kruskal(e, n, m);

    return 0;
}
