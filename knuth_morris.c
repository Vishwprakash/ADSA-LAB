#include <stdio.h>
#include <string.h>

#define N 100

void lpsArray(char pat[], int lps[])
{
    int len = 0;
    int i = 1;
    int m = strlen(pat);

    lps[0] = 0;

    while (i < m)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmp(char text[], char pat[])
{
    int n = strlen(text);
    int m = strlen(pat);
    int lps[N];
    int i = 0, j = 0;

    lpsArray(pat, lps);

    while (i < n)
    {
        if (text[i] == pat[j])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            printf("Pattern found at position: %d\n", i - j);
            j = lps[j - 1];
        }
        else if (i < n && text[i] != pat[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
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

    kmp(text, pat);

    return 0;
}
