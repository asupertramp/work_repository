#include<stdio.h>
#include<stdlib.h>
#define QUEUE_SIZE 1024
#define TRUE 1;
#define FALSE 0;
typedef int BOOL;
typedef int ElementType;
ElementType queue[QUEUE_SIZE];
int front;
int rear;
void makeEmpty()
{
	front=0;
	rear=0;
}
BOOL isEmpty()
{
	return front==rear;
}
BOOL isFull()
{
	return front-rear==1;
}
BOOL enqueue(ElementType x)
{
	if(isFull())
		return FALSE;
	if(rear==QUEUE_SIZE)
		rear=0;
	queue[rear++]=x;
	return TRUE;
}
ElementType dequeue()
{
	if(isEmpty())
	{
		printf("empty\n");
		exit(1);
	}
	if(front==QUEUE_SIZE)
		front=0;
	return queue[front++];
}

void test()
{
	int i;
	for(i=0;i<20;++i)
		enqueue(i);
	for(i=0;i<10;++i)
		printf("%d ",dequeue());
}
int main()
{
	test();
}