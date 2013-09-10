#include<stdio.h>
#include<stdlib.h>
typedef struct NODE{
	struct NODE *next;
	int data;
} Node;
//建立无序链表
Node * build(int *arr,int num)
{
	int i;
	Node *pre;
	Node *cur;
	Node *list;
	list=malloc(num*sizeof(Node));
	if(list==NULL)
	{
		printf("Out of memort\n");
		exit(1);
	}
	for(i=0;i<num;i++)
	{
		list[i].data=*(arr+i);
		list[i].next=NULL;
		cur=&list[i];
		if(i!=0)
			pre->next=cur;
		pre=cur;			
	}
	return list;
}
//建立有序链表
Node * buildSorted(int *arr,int num)
{
	int i;
	Node *pre;
	Node *cur;
	Node *list;
	list=malloc(num*sizeof(Node));
	if(list==NULL)
	{
		printf("Out of memort\n");
		exit(1);
	}
	for(i=0;i<num;i++)
	{
		list[i].data=*(arr+i);
		list[i].next=NULL;
		cur=&list[i];
		if(i!=0)
			pre->next=cur;
		pre=cur;			
	}
	return list;
}
//遍历链表
int ergodic(Node *first)
{
	Node *temp=first;
	
	while(temp!=NULL){
		printf("%d    ",temp->data);
		temp=temp->next;		
	}
	return 1;
}
//插入有序链表
int insert(Node *first,int data)
{
	
}
//插入链表
int insert(Node *first,int data,int position)
{
	Node *newNode;
	Node *cur;
	int i;
	newNode=malloc(sizeof(Node));
	if(newNode==NULL)
	{
		printf("Out of memory\n");
		exit(1);
	}	
	newNode->data=data;
	newNode->next=NULL;
	
	cur=first;
	for(i=0;i<position-1;i++)
	{
		if(cur->next==NULL)
		{
			cur->next=newNode;
			return 1;
		}
		cur=cur->next;
	}
	newNode->next=cur->next;
	cur->next=newNode;
	return 1;
}

int delete(Node *first,int data)
{
		Node *pre=NULL;
		Node *cur=first;
		while(cur!=NULL)
		{
			if(cur->data==data)
				break;
			pre=cur;
			cur=cur->next;
		}
		if(cur==NULL)
			printf("can't find %d in the linkedlist\n",data);
		else
			pre->next=cur->next;
		return 1;
}

int find(Node *first,int data)
{
	int position=1;
	Node *temp=first;
	do{
		if(temp->data==data)
			return position;
		temp=temp->next;
		position++;
	}while(temp!=NULL);
	return 0;
}

int getLen(Node *first)
{
	int len=0;
	Node * temp=first;
	while(temp!=NULL)
	{
		temp=temp->next;
		len++;
	}
	return len;
}

int main()
{
	int arr[]={1,2,3,4,5};
	Node *first;
	first=build(arr,5);
	ergodic(first);		//遍历
	int val=3;
	printf("position:%d\n",find(first,val));
	val=6;
	printf("position:%d\n",find(first,val));
	insert(first,8,2);
	ergodic(first);	
	
	printf("the length of the linkedlist:%d\n",getLen(first));
	
	delete(first,3);
	printf("the length of the linkedlist:%d\n",getLen(first));
	delete(first,3);
	printf("the length of the linkedlist:%d\n",getLen(first));
	ergodic(first);	
	
	free(first);
	first=NULL;
	ergodic(first);	
	
	return 1;
}