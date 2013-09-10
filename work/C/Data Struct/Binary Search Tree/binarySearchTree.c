#include<stdio.h>
#include<stdlib.h>

struct TreeNode;
typedef struct TreeNode *Tree;
typedef struct TreeNode *Position;
typedef int elementType;
enum retrieveType{
	PRE,INO,POST
};
Tree makeEmpty(Tree t);
Position find(Tree t,elementType key);
Position insert(Tree t,elementType key);
Position min(Tree t);
Position max(Tree t);
Tree delete(Tree t,elementType key);
Tree retrieve(Tree t,enum retrieveType rType);
struct TreeNode{
	elementType key;
	Tree left;
	Tree right;	
};

Tree makeEmpty(Tree t)
{
	if(t!=NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		free(t);
	}
	return NULL;
}

Position find(Tree t,elementType key)
{
	if(t==NULL)
		return NULL;
	if(t->key==key)
		return t;
	else if(t->key>key)
		return find(t->left,key);
	else
		return find(t->right,key);
}

Position min(Tree t)
{
	if(t==NULL)
		return NULL;
	if(t->left==NULL)
		return t;
	else 
		return min(t->left);
}

Position max(Tree t)
{
	if(t==NULL)
		return NULL;
	if(t->right==NULL)
		return t;
	else
		return max(t->right);
}

Tree insert(Tree t,elementType key)
{
	if(t==NULL)
	{
		t= (Position)malloc(sizeof(struct TreeNode));
		if(t==NULL)
			return NULL;
		t->key=key;
		t->left=t->right=NULL;
		return t;
	}
	if(t->key>key)
		t->left=insert(t->left,key);
	else
		t->right=insert(t->right,key);
	return t;
}

Tree delete(Tree t,elementType key)
{
	Position tmp;
	if(t==NULL)
		return NULL;
	if(t->key>key)
		t->left=delete(t->left,key);
	else if(t->key<key)
		t->right=delete(t->right,key);
	else
	{
		if(t->left&&t->right)
		{
			tmp=min(t->right);
			t->key=tmp->key;
			t->right=delete(t->right,t->key);
		}
		else
		{
			tmp=t;
			if(t->left==NULL)
				t=t->right;
			else if(t->right==NULL)
				t=t->left;
			free(tmp);
		}
	}
	return t;
}

Tree retrieve(Tree t, enum retrieveType rType)
{
	if(t==NULL)
		return NULL;
	switch(rType)
	{
		case PRE:
			printf("%d,",t->key);
			retrieve(t->left,rType);
			retrieve(t->right,rType);
			break;
		case INO:
			retrieve(t->left,rType);
			printf("%d,",t->key);
			retrieve(t->right,rType);
			break;
		case POST:
			retrieve(t->left,rType);
			retrieve(t->right,rType);
			printf("%d,",t->key);
			break;
	}
	return t;
}

int main()
{
	int arr[]={5,2,6,3,8,9,1,10,4,12};
	int i;
	Position p=NULL;
	for(i=0;i<10;i++)
	{
		p=insert(p,arr[i]);
	}
	retrieve(p,PRE);
	printf("\n");
	retrieve(p,INO);
	printf("\n");
	retrieve(p,POST);
	printf("\n");
	
	insert(p,7);
	retrieve(p,INO);
	printf("\n");
	
	delete(p,3);
	retrieve(p,INO);
	printf("\n");
	
	//makeEmpty(p);
	return 1;
}