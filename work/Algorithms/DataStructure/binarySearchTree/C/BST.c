#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
typedef int ElementType;
typedef int BOOL;
struct Node {
	struct Node* left;
	struct Node* right;
	ElementType value;
};
typedef struct Node Node;
typedef Node * Tree;

BOOL insert(Tree* root,int val){
	Node* current;
	Node* new;
	while((current=*root)!=NULL){
		if(val>current->value)
			root=&(current->right);
		else
			root=&(current->left);
	}
	new=(Node*)malloc(sizeof(Node));
	if(new==NULL)
		return FALSE;
	new->value=val;
	new->left=NULL;
	new->right=NULL;
	*root=new;
	return TRUE;
}
Tree insert_T(Tree tree,ElementType x)
{
	if(tree==NULL)
	{
		tree=(Tree)malloc(sizeof(Node));
		if(tree==NULL)
			printf("Error\n");
		else
		{
			tree->left=NULL;
			tree->right=NULL;
			tree->value=x;
		}
	}
	else
	if(tree->value>x)
		tree->left=insert_T(tree->left,x);
	else
	if(tree->value<x)
		tree->right=insert_T(tree->right,x);
	return tree;
}

Node *findMin(Tree tree)
{
	if(tree==NULL||tree->left==NULL)
		return tree;
	else
		return findMin(tree->left);
}
Node *findMax(Tree tree0
{
	if(tree==NULL||tree->right==NULL)
		return tree;
	else
		return findMax(tree->right);
}
Tree delete(Tree tree,ElementType x)
{
	Node *tmp;
	if(tree==NULL)
		printf("Error\n");
	else
	if(x>tree->value)
		tree->right=delete(tree->right,x);
	else
	if(x<tree->value)
		tree->left=delete(tree->left,x);
	else
	{
		if(tree->left&&tree->right)
		{
			tmp=findMin(tree->right);
			tree->value=tmp->value;
			tree->right=delete(tree->right,tmp->value);
		}
		else
		{
			tmp=tree;
			if(tree->left==NULL)
				tree=tree->right;
			else
			if(tree->right==NULL)
				tree=tree->left;
			free(tmp);
		}
	}
	return tree;
}
Node *find(Tree tree,ElementType x)
{
	if(tree==NULL)
		return NULL;
	if(tree->value==x)
		return tree;
	else
	if(tree->value>x)
		return find(tree->left,x);
	else
		return find(tree->right,x);
}
void pre_traverse(Tree tree)
{
	if(tree==NULL)
		return ;
	printf("%d,",tree->value);
	pre_traverse(tree->left);
	pre_traverse(tree->right);
}
void post_traverse(Tree tree)
{
	if(tree==NULL)
		return ;
	printf("%d,",tree->value);
	post_traverse(tree->right);
	post_traverse(tree->left);
}
void in_traverse(Node* root){
	if(root==NULL)
		return;
	in_traverse(root->left);
	printf("%d,",root->value);
	in_traverse(root->right);
}
void test()
{
	Tree tree=NULL;
	insert(&tree,5);
	insert(&tree,2);
	insert(&tree,7);
	insert(&tree,4);
	insert(&tree,9);
	insert(&tree,1);
	insert(&tree,12);
	pre_traverse(tree);
	printf("\n");
	tree=delete(tree,4);
	pre_traverse(tree);
	printf("min:%d\n",findMin(tree)->value);
}
int main(){
	test();
}