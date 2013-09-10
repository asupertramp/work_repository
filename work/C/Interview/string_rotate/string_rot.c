//字符串循环左移问题。abcde fghijk->fghijk abcde
//第一步：abcde->edcba,fghijk->kjihgf 整个字符串变为：edcba kjihgf
//第二步：翻转整个字符串.复杂度O(n);
//编程珠玑上有介绍。
//其他方法：
#include<stdio.h>
#include<string.h>
char * reverse(char *beg,char *end)
{
	if(beg==NULL)
		return NULL;
	char temp;
	char *ptmp=beg;
	while(*beg!='\0'&&*end!='\0'&&beg<end)
	{
		temp=*beg;
		*beg=*end;
		*end=temp;
		++beg;
		--end;
	}
	return ptmp;
}

char *str_rot(char *beg,int pos)
{
	if(beg==NULL)
		return NULL;
	int len=strlen(beg);
	reverse(beg,beg+pos);
	reverse(beg+pos+1,beg+len-1);
	reverse(beg,beg+len-1);
	return beg;
}

int gcd(int m,int n)
{
	int tmp;
	if(m<n)
	{
		tmp=m;
		m=n;
		n=tmp;		
	}
	while(m%n!=0)
	{
		tmp=m/n;
		if(tmp<n)
		{
			m=n;
			n=tmp;
		}
		else
			m=tmp;
	}
	return n;
}
void str_rot2(char *begin, char *mid, char *end)  
{     
    int n = end - begin;     
    int k = mid - begin;     
    int d = gcd(n, k);     
    int i, j;     
    for (i = 0; i < d; i ++)     
    {     
        int tmp = begin[i];     
        int last = i;              
        //i+k为i右移k的位置，%n是当i+k>n时从左重新开始。  
        for (j = (i + k) % n; j != i; j = (j + k) % n)    
        {     
            begin[last] = begin[j];         
            last = j;     
        }         
        begin[last] = tmp;     
    }     
} 

int main()
{
	char tmp[]="abcdefghijk";
	str_rot(tmp,4);
	puts(tmp);
	str_rot2(tmp,tmp+2,tmp+strlen(tmp));
	puts(tmp);

	
}