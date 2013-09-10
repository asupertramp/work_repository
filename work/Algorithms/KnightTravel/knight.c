#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define N 8
//const int N = 8;

int step[N * N] = {-1};
int chess[N][N] = {0};

int Jump[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}};

int p = 0;

int canJump(int x, int y)
{
    if (x >= 0 && x < N && y >= 0 && y < N && chess[x][y] == 0)
        return 1;
    return 0;
}

void BackTrace(int t, int x, int y)
{
	int i ,j;
    if (t >= N * N)
    {
        p++;
        
        for ( i = 1; i <= N * N - 1; ++i)
        {
            printf("%d ", step[i]);
        }
        printf(" ");
        for ( i = 0; i < N; ++i)
        {
            for (j = 0; j < N; ++j)
                printf("%2d ", chess[i][j]);
            printf("\n");
        }
        printf("\n");
        exit(1);
        //return;
    }
    else
    {
        for (i = 0; i < 8; ++i)
        {
            if (canJump(x + Jump[i][0], y + Jump[i][1]))
            {
                x += Jump[i][0];
                y += Jump[i][1];
                chess[x][y] = t + 1;
                step[t] = i;
                BackTrace(t + 1, x, y);
                chess[x][y] = 0;
                x -= Jump[i][0];
                y -= Jump[i][1];
            }
        }
        
    }
}

int main()
{
    int x = 0;
    int y = 0;
    chess[x][y] = 1;
    BackTrace(1, x, y);
    printf("All Results Number = %d ", p);
}