#include <stdio.h>

#define N 20

int SIZE = 4;

int isSafe(char chessBoard[N][N], int r, int c)
{
    int i, j;

    /* Check column */
    for (i = 0; i < SIZE; i++)
    {
        if (chessBoard[i][c] == 'Q')
            return 0;
    }

    /* Check row */
    for (i = 0; i < SIZE; i++)
    {
        if (chessBoard[r][i] == 'Q')
            return 0;
    }

    /* Check left diagonal */
    for (i = r, j = c; i >= 0 && j >= 0; i--, j--)
    {
        if (chessBoard[i][j] == 'Q')
            return 0;
    }

    /* Check right diagonal */
    for (i = r, j = c; i >= 0 && j < SIZE; i--, j++)
    {
        if (chessBoard[i][j] == 'Q')
            return 0;
    }

    return 1;
}

void printBoard(char chessBoard[N][N])
{
    int r, c;

    printf("\n");

    for (r = 0; r < SIZE; r++)
    {
        for (c = 0; c < SIZE; c++)
        {
            printf("%c ", chessBoard[r][c]);
        }
        printf("\n");
    }
}

void solution(char chessBoard[N][N], int r)
{
    int c;

    /* Base condition */
    if (r == SIZE)
    {
        printBoard(chessBoard);
        return;
    }

    for (c = 0; c < SIZE; c++)
    {
        if (isSafe(chessBoard, r, c))
        {
            chessBoard[r][c] = 'Q';

            solution(chessBoard, r + 1);

            chessBoard[r][c] = '-';
        }
    }
}

int main()
{
    char chessBoard[N][N];
    int r, c;

    for (r = 0; r < SIZE; r++)
    {
        for (c = 0; c < SIZE; c++)
        {
            chessBoard[r][c] = '-';
        }
    }

    printBoard(chessBoard);

    solution(chessBoard, 0);

    return 0;
}
