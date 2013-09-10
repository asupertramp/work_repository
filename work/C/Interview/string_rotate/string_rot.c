//�ַ���ѭ���������⡣abcde fghijk->fghijk abcde
//��һ����abcde->edcba,fghijk->kjihgf �����ַ�����Ϊ��edcba kjihgf
//�ڶ�������ת�����ַ���.���Ӷ�O(n);
//����������н��ܡ�
//����������
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
        //i+kΪi����k��λ�ã�%n�ǵ�i+k>nʱ�������¿�ʼ��  
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