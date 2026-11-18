#include <stdio.h>

#define N 20

int g[N][N];
int visited[N];
int path[N];

int n, directed;
int minLen = N + 1;
int maxLen = 0;

void checkCycle(int len) {
    if (len < 3)
        return;

    if (len < minLen)
        minLen = len;

    if (len > maxLen)
        maxLen = len;
}

void dfsCycle(int start, int u, int len) {
    int v;

    for (v = 0; v < n; v++) {

        if (!g[u][v])
            continue;

        if (v == start) {
            if (len >= 3) {

                if (directed) {
                    checkCycle(len);
                }
                else if (path[1] < path[len - 1]) {
                    checkCycle(len);
                }
            }
        }
        else if (!visited[v] && v >= start) {

            visited[v] = 1;
            path[len] = v;

            dfsCycle(start, v, len + 1);

            visited[v] = 0;
        }
    }
}

int main() {
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter 1 for Directed, 0 for Undirected: ");
    scanf("%d", &directed);

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            visited[j] = 0;

        visited[i] = 1;
        path[0] = i;

        dfsCycle(i, i, 1);
    }

    if (maxLen == 0) {
        printf("\nNo cycle found.\n");
    }
    else {
        printf("\nSmallest cycle length = %d\n", minLen);
        printf("Largest cycle length = %d\n", maxLen);
    }

    return 0;
}
