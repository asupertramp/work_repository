#include"stack.h"
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
typedef struct STRUCT_NODE{
	STACK_TYPE val;
	struct STRUCT_NODE *next;
}StackNode;
//typedef struct StackNode * Stack;
StackNode * stack;
STACK_TYPE pop(void)
{
	StackNode *firstNode;
	STACK_TYPE va;
	assert(!is_empty());
	firstNode=stack;
	stack=stack->next;
	va=firstNode->val;
	free(firstNode);
	return va;
}
STACK_TYPE top()
{
	assert(!is_empty());
	return stack->val;
}
void push(STACK_TYPE v)
{
	StackNode *new=malloc(sizeof(StackNode));
	assert(new!=NULL);
	new->val=v;
	new->next=stack;
	stack=new;
}
int is_full()
{
	return 0;
}
int is_empty()
{
	return stack==NULL;
}
void creat_stack()
{}
void destroy_stack()
{
	while(!is_empty())
		pop();
}
