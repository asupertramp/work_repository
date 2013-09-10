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

//n�����ų�һȦ����1��ʼ��������m���˳��У�������1��������ֱ��ʣ���һ���ˣ������š�
int joseph( int n, int m ) {
    int  idx = 0;
    int x;
    for(x = 2; x <= n; ++x )
        idx = (idx + m) % x;
    return  ( idx + 1 );
}

//n�����ų�һȦ����1��ʼ��������m���˳��У�������1��������ֱ��ʣr���ˣ������r���˵ı�š�

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
