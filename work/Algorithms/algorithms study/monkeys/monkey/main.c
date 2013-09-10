#include <stdio.h>

int joseph(int n, int m);
int joseph2(int n, int m,int r);
int main(void)
{
    int n=6,m=4;
    int position=joseph(n,m);
    printf("%d ",position);

    joseph2(n,m,2);

    return 0;

}

//n个人排成一圈，从1开始数，数到m的人出列，继续从1往下数，直到剩最后一个人，输出编号。
int joseph( int n, int m ) {
    int  idx = 0;
    int x;
    for(x = 2; x <= n; ++x )
        idx = (idx + m) % x;
    return  ( idx + 1 );
}

//n个人排成一圈，从1开始数，数到m的人出列，继续从1往下数，直到剩r个人，输出这r个人的编号。

int joseph2( int n, int m,int r )
{
    int  idx = 0;
    int x;
    for(x = 2; x <= n; ++x )
    {
        idx = (idx + m) % x;
        if(x>n-r)
            printf("%d ",idx+1);
    }

    return  ( idx + 1 );
}
