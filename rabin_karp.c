#include <stdio.h>
#include <string.h>

#define N 100

void rabinKarp(char text[], char pat[])
{
    int n = strlen(text);
    int m = strlen(pat);
    int d = 256, q = 101;
    int p = 0, t = 0, h = 1;
    int i, j;

    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < m; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (i = 0; i <= n - m; i++)
    {
        if (p == t)
        {
            for (j = 0; j < m; j++)
                if (text[i + j] != pat[j])
                    break;

            if (j == m)
                printf("Pattern found at position: %d\n", i);
        }

        if (i < n - m)
        {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            if (t < 0)
                t = t + q;
        }
    }
}

int main()
{
    char text[N], pat[N];

    printf("Enter text: ");
    scanf("%s", text);

    printf("Enter pattern: ");
    scanf("%s", pat);

    rabinKarp(text, pat);

    return 0;
}
