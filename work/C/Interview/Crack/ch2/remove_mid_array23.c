#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;
typedef struct 
{
	ElementType val;
	struct Node *next;
}Node;
Node *init(ElementType a[],int n)
{
	Node *head,*tmp,*current;
	int i;
	for(i=0;i<n;++i)
	{
		tmp=(Node*)malloc(sizeof(Node));
		if(tmp==NULL)
			return;
		tmp->val=a[i];
		tmp->next=NULL;
		if(i==0)
			head=current=tmp;
		else
		{
			current->next=tmp;
			current=tmp;
		}
	}
	return head;
}
void print_ll(Node *head)
{
	while(head!=NULL)
	{
		printf("%d ",head->val);
		head=head->next;
	}
}
void remove_ll(Node *node)
{
	Node *tmp;
	if(node==NULL||node->next==NULL)
		return;
	tmp=node->next;
	node->val=tmp->val;
	node->next=tmp->next;
	free(tmp);
}
void test()
{
	ElementType arr[]={1,2,3,4,5,6,7};
	Node *list=init(arr,7);
	remove_ll(list);
	print_ll(list);
}
int main()
{
	test();
	return 0;
}