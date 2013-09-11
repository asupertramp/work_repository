#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Node
{
	int val;
	struct Node* left;
	struct Node* right;
}Node;

int size(Node *tree)
{
	if(tree==NULL)
		return 0;
	return 1+size(tree->left)+size(tree->right);
}

int is_full(Node *tree)
{
	int h=height(tree);
	int count=size(tree);
	if(count==pow(2,h)-1)
		return 1;
	else
		return 0;
}
int height(Node*root)
{
	if(root==NULL)
		return 0;
	if(root->left==NULL&&root->right==NULL)
		return 1;
	if(root->left==NULL)
		return height(root->right)+1;
	else
		return height(root->left)+1;
}
Node *insert_search_tree(Node *root,int x)
{
	if(root==NULL)
	{
		root=(Node*)malloc(sizeof(Node));
		root->val=x;
		root->left=NULL;
		root->right=NULL;
		return root;
	}
	if(root->val>x)
		root->left=insert_search_tree(root->left,x);
	else
	if(root->val<x)
		root->right=insert_search_tree(root->right,x);
	return root;
}
Node *build_search_tree(int *arr,int n)
{
	Node *root=NULL;
	int i;
	for(i=0;i<n;++i)
		root=insert_search_tree(root,arr[i]);
	return root;
}

Node *insert_balanced_tree(Node *tree,int x)
{
	int lh,rh,lf,rf;
	if(tree==NULL)
	{
		tree=(Node*)malloc(sizeof(Node));
		tree->val=x;
		tree->left=NULL;
		tree->right=NULL;
		return tree;
	}
	lh=height(tree->left);
	rh=height(tree->right);
	lf=is_full(tree->left);
	rf=is_full(tree->right);
	if((lh>rh&&lf)||(lh==rh&&lf&&!rf))
		tree->right=insert_balanced_tree(tree->right,x);
	else
		tree->left=insert_balanced_tree(tree->left,x);
	return tree;
}

Node *build_balanced_tree(int *arr,int n)
{
	Node *tree=NULL;
	int i;
	for(i=0;i<n;++i)
		tree=insert_balanced_tree(tree,arr[i]);
	return tree;
}

void traverse(Node *tree)
{
	if(tree==NULL)
		return ;
	traverse(tree->left);
	printf("%d,",tree->val);
	traverse(tree->right);
		
}



int is_balance(Node*tree)
{
	if(abs(height(tree->left)-height(tree->right))>1)
		return 0;
	else
		return 1;
}
int main()
{
	int arr[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int h;
	Node *tree=build_search_tree(arr,sizeof(arr)/sizeof(int));
	traverse(tree);
	h=height(tree);
	printf("\n%d\n",h);
	h=is_balance(tree);
	printf("平衡性:%s平衡",h==1?" ":"不");
	
	tree=build_balanced_tree(arr,sizeof(arr)/sizeof(int));
	traverse(tree);
	h=height(tree);
	printf("\n%d\n",h);
	h=is_balance(tree);
	printf("平衡性:%s平衡",h==1?" ":"不");
	
	return 0;
}