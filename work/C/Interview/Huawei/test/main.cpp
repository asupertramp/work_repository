#include <iostream>
#include <string>
using namespace std;

#define MAXN 10

struct Node
{
    int index;
    Node* next;
};

class YSF
{
    private:
        int n;//¹æÄ£
        int m;
        Node* top;
        Node* bottom;
        Node* t;
    public:
		YSF(int ln,int lm);
        void getYSF();
};
YSF::YSF(int ln,int lm)
{
	n=ln;
	m=lm;
	top=new Node();
	bottom=top;
	top->index=1;
	for(int i=1;i<n;i++)
	{
		t=new Node();
		bottom->next=t;
		t->index=i+1;
		bottom=t;
	}
	bottom->next=top;
}
void YSF::getYSF()
{
	Node* cur=top;	
	Node* pre=bottom;
	Node *tmp;
	int i;
	while(pre!=cur)
	{
		for(i=0;i<m;++i)
		{
			pre=cur;
			cur=cur->next;
		}
		pre->next=cur->next;
		tmp=cur;
		cout<<cur->index<<endl;
		cur=cur->next;
		free(tmp);		
	}
	cout<<cur->index<<endl;
	free(cur);
}
int main()
{
    YSF* ysf=new YSF(10,6);
	ysf->getYSF();
    getchar();
}