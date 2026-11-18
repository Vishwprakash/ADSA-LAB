#include <stdio.h>

#define N 20

int graph[N][N];
int n;
int visited[N], disc[N], low[N];
int parent[N];
int timeCount;
int stackU[N * N], stackV[N * N], top;

// ---------- SCC using DFS ---------- 

int sccStack[N], inStack[N], sccTop;

void sccDFS(int u)
{
    int v;

    visited[u] = 1;
    disc[u] = low[u] = ++timeCount;

    sccStack[++sccTop] = u;
    inStack[u] = 1;

    for (v = 0; v < n; v++)
    {
        if (graph[u][v])
        {
            if (!visited[v])
            {
                sccDFS(v);

                if (low[v] < low[u])
                    low[u] = low[v];
            }
            else if (inStack[v] && disc[v] < low[u])
            {
                low[u] = disc[v];
            }
        }
    }

    if (low[u] == disc[u])
    {
        printf("{ ");

        do
        {
            v = sccStack[sccTop--];
            inStack[v] = 0;
            printf("%d ", v);
        } while (v != u);

        printf("}\n");
    }
}

void findSCC()
{
    int i;

    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
        inStack[i] = 0;
    }

    timeCount = 0;
    sccTop = -1;

    printf("Strongly Connected Components:\n");

    for (i = 0; i < n; i++)
    {
        if (!visited[i])
            sccDFS(i);
    }
}

// ---------- Articulation Points and Bridges ---------- 

void APBridgeDFS(int u)
{
    int v, children = 0;

    visited[u] = 1;
    disc[u] = low[u] = ++timeCount;

    for (v = 0; v < n; v++)
    {
        if (!graph[u][v])
            continue;

        if (!visited[v])
        {
            parent[v] = u;
            children++;

            APBridgeDFS(v);

            if (low[v] < low[u])
                low[u] = low[v];

            if (parent[u] == -1 && children > 1)
                printf("Articulation Point: %d\n", u);

            if (parent[u] != -1 && low[v] >= disc[u])
                printf("Articulation Point: %d\n", u);

            if (low[v] > disc[u])
                printf("Bridge: %d - %d\n", u, v);
        }
        else if (v != parent[u] && disc[v] < low[u])
        {
            low[u] = disc[v];
        }
    }
}

void findAPBridge()
{
    int i;

    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }

    timeCount = 0;

    printf("\nArticulation Points and Bridges:\n");

    for (i = 0; i < n; i++)
    {
        if (!visited[i])
            APBridgeDFS(i);
    }
}

// ---------- Biconnected Components ---------- 

void BCCDFS(int u)
{
    int v;

    visited[u] = 1;
    disc[u] = low[u] = ++timeCount;

    for (v = 0; v < n; v++)
    {
        if (!graph[u][v])
            continue;

        if (!visited[v])
        {
            parent[v] = u;

            stackU[++top] = u;
            stackV[top] = v;

            BCCDFS(v);

            if (low[v] < low[u])
                low[u] = low[v];

            if (low[v] >= disc[u])
            {
                printf("Biconnected Component: ");

                while (top >= 0)
                {
                    int a = stackU[top];
                    int b = stackV[top--];

                    printf("(%d-%d) ", a, b);

                    if (a == u && b == v)
                        break;
                }

                printf("\n");
            }
        }
        else if (v != parent[u] && disc[v] < disc[u])
        {
            if (disc[v] < low[u])
                low[u] = disc[v];

            stackU[++top] = u;
            stackV[top] = v;
        }
    }
}

void findBCC()
{
    int i;

    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
        parent[i] = -1;
    }

    top = -1;
    timeCount = 0;

    printf("\nBiconnected Components:\n");

    for (i = 0; i < n; i++)
    {
        if (!visited[i])
            BCCDFS(i);
    }
}

int main()
{
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    findSCC();
    findAPBridge();
    findBCC();

    return 0;
}
