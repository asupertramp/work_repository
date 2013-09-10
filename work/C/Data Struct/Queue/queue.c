#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
#include"queue.h"
typedef struct QUEUE_NODE{
	QUEUE_TYPE val;
	struct QUEUE_NODE *next;
}QueueNode;
typedef struct LINK_QUEUE{
	QueueNode *front,*rear;
}LinkQueue;
static LinkQueue queue;

void qinsert(QUEUE_TYPE v)
{
	QueueNode *new=(QueueNode*)malloc(sizeof(QueueNode));
	assert(new!=NULL);
	new->val=v;
	new->next=NULL;
	queue.rear->next=new;
	queue.rear=new;
}
QUEUE_TYPE qdelete()
{
	QueueNode *temp;
	QUEUE_TYPE v;
	assert(!is_empty());
	temp=queue.front;
	queue.front=temp->next;
	v=temp->val;
	free(temp);
	return v;
}
void create_queue(QUEUE_TYPE v)
{
	assert(queue.front==NULL);
	queue.front=queue.rear=(QueueNode*)malloc(sizeof(QueueNode));	
	if(queue.front==NULL)
		exit(1);
	queue.front->val=v;
}
void destroy_queue()
{
	while(!is_empty())
		qdelete();
}
QUEUE_TYPE first()
{
	return queue.front->val;
}
int is_full()
{
	return 0;
}
int is_empty()
{
	return queue.front==NULL;
}