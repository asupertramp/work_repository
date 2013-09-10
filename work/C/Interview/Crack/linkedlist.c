#include<stdio.h>
#include<malloc.h>
typedef int NODE_TYPE;
typedef struct NODE{
	NODE_TYPE val;
	struct NODE *next;
}Node;

void sll_insert(Node **link,NODE_TYPE v)
{
	Node *newNode=(Node*)malloc(sizeof(Node));
	if(newNode==NULL)
		exit(1);
	newNode->val=v;
	newNode->next=*link;
	*link=newNode;
}
void sll_delete(Node*pre,Node *todel)
{
	if(todel==NULL)
		return;
	
	pre->next=todel->next;
	free(todel);
}
void sll_destroy(Node*root)
{
	Node*current,*next;
	current=root;
	while(current!=NULL)
	{
		next=current->next;
		free(current);
		cruuent=next;
	}
}

Node* sll_find(Node *head,NODE_TYPE v)
{
	Node *pre=NULL;
	while(head!=NULL)
	{
		if(head->val==v)
			return head;
		head=head->next;
	}
	return head;
}

void sll_traverse(Node *head, void(visit)(NODE_TYPE ))
{
	while(head!=NULL)
	{
		visit(head->val);
		head=head->next;
	}
}
void printv(NODE_TYPE v)
{
	printf("%d ",v);
}
int main()
{
	int i;
	Node *root=NULL;
	for(i=0;i<5;++i)
	{
		sll_insert(&root,i);
	}
	sll_traverse(root,printv);
	sll_destroy(root);
}