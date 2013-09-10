#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
	int val;
	struct Node*next;
}Node;

Node *make_list(int *arr,int n)
{
	Node *head,*node,*tmp;
	int i;
	head=(Node*)malloc(sizeof(Node));
	if(head==NULL)
		return NULL;
	head->val=arr[0];
	head->next=NULL;
	node=head;
	for(i=1;i<n;++i)
	{
		tmp=(Node*)malloc(sizeof(Node));
		if(tmp==NULL)
			return NULL;
		tmp->val=arr[i];
		tmp->next=NULL;
		node->next=tmp;
		node=tmp;
	}
	return head;
}
void make_hoop(Node *head,int pos)
{
	Node *hoop_pos,*cur;
	int tmp=pos;
	while(head&&--pos)
		head=head->next;
	if(head==NULL)
	{
		printf("链表长度小于%d\n",tmp);
		return ;
	}
	if(pos==0)
	{
		hoop_pos=head;
		while(head->next)
			head=head->next;
		head->next=hoop_pos;
	}
	return ;
}

Node *find_hoop(Node *head)
{
	Node *fast=head;
	Node *slow=head;
	do
	{
		slow=slow->next;
		fast=fast->next;
		if(fast==NULL)
			return NULL;
		fast=fast->next;
	}while(fast!=slow&&fast);
	if(fast==NULL)
	{
		printf("没有环\n");
		return NULL;
	}
	fast=head;
	while(fast!=slow)
	{
		fast=fast->next;
		slow=slow->next;
	}
	return fast;	
}

int length(Node *head)
{
	int len=0;
	while(head)
	{
		head=head->next;
		len++;
	}
	return len;
}

//大整数加法,高位在前（低位在前比较简单）
Node *big_int_add(Node *head1,Node *head2)
{
	//int len1,len2;
	Node *result,*cur,*cp,*new;
	Node *tmp=NULL;
	int bsum;
	//len1=length(head1);
	//len2=length(head2);
	result=(Node *)malloc(sizeof(Node));
	if(result==NULL)
		return NULL;
	bsum=head1->val+head2->val;
	if(bsum/10)
	{
		result->val=bsum/10;
		cur=(Node*)malloc(sizeof(Node));
		cur->val=bsum%10;
		result->next=cur;
		cp=cur;
	}
	if(bsum==9)
	{
		result->val=bsum;
		tmp=(Node*)malloc(sizeof(Node));
		tmp->val=0;
		tmp->next=result;
		cur=result;
		cp=tmp;
	}
	if(bsum<9)
	{
		result->val=bsum;
		cur=result;
		cp=result;
	}
	head1=head1->next;
	head2=head2->next;
	while(head1&&head2)
	{
		bsum=head1->val+head2->val;
		new=(Node*)malloc(sizeof(Node));
		new->val=bsum%10;
		new->next=NULL;
		cur->next=new;
		cur=new;
		if(bsum/10)
		{
			cp->val++;
			while(cp->next!=cur)
			{
				cp=cp->next;
				cp->val=0;
			}
			cp=cur;
		}
		if(bsum<9)
			cp=cur;
		head1=head1->next;
		head2=head2->next;
	}
	if(tmp&&tmp->val!=0)
		return tmp;
	else
		return result;
}

void print_list(Node *head)
{
	while(head)
	{
		printf("%d,",head->val);
		head=head->next;
	}
	printf("\n");
}

Node* reverse_list(Node*head)
{
	Node *cur,*pre,*nex;
	if(head==NULL)
		return NULL;
	pre=head;
	cur=head->next;
	while(cur)
	{
		nex=cur->next;
		cur->next=pre;
		pre=cur;
		cur=nex;
	}
	head->next=NULL;
	return pre;
}

int main()
{
	int arr[]={1,2,3,4,5,6,7,8,9,1};
	int arr2[]={8,3,3,4,5,6,7,8,9,1};
	Node *tail,*head2,*result;
	Node *head1=make_list(arr,sizeof(arr)/sizeof(int));
	head2=make_list(arr2,sizeof(arr2)/sizeof(int));
	print_list(head1);
	print_list(head2);
	result=big_int_add(head1,head2);
	print_list(result);
	//tail=find_hoop(head);
	//make_hoop(head,5);
	//tail=find_hoop(head);
	//printf("\n%d\n",tail->val);
	//print_list(head);
	//tail=reverse_list(head);
	//print_list(tail);
	return 0;
}