#include <stdio.h>
#include <string.h>

#define N 100

void badChar(char pat[], int bad[])
{
    int i;

    for (i = 0; i < 256; i++)
        bad[i] = -1;

    for (i = 0; pat[i] != '\0'; i++)
        bad[(unsigned char)pat[i]] = i;
}

void boyerMoore(char text[], char pat[])
{
    int bad[256];
    int n = strlen(text);
    int m = strlen(pat);
    int s = 0;

    badChar(pat, bad);

    while (s <= n - m)
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == text[s + j])
            j--;

        if (j < 0)
        {
            printf("Pattern found at position: %d\n", s);

            if (s + m < n)
                s += m - bad[(unsigned char)text[s + m]];
            else
                s += 1;
        }
        else
        {
            int shift = j - bad[(unsigned char)text[s + j]];

            if (shift < 1)
                shift = 1;

            s += shift;
        }
    }
}

int main()
{
    char text[N], pat[N];

    printf("Enter text: ");
    scanf(" %[^\n]", text);

    printf("Enter pattern: ");
    scanf(" %[^\n]", pat);

    boyerMoore(text, pat);

    return 0;
}
