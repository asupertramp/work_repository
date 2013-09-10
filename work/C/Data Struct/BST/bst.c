#include"bst.h"
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
int BST_Insert(TreeNode **link,TREE_TYPE v)
{
	TreeNode *current;
	TreeNode *new=(TreeNode*)malloc(sizeof(TreeNode));
	if(new==NULL)
		exit(1);
	new->val=v;
	new->left=NULL;
	new->right=NULL;
	while((current=*link)!=NULL)
	{
		if(current->val>v)
			link=&current->left;
		else
			link=&current->right;
	}
	*link=new;
}
TreeNode * BST_Find(TreeNode *root,TREE_TYPE v)
{
	if(root==NULL)
		return NULL;
	if(root->val==v)
		return root;
	else if(root->val>v)
		return BST_Find(root->left,v);
	else
		return BST_Find(root->right,v);
}

int BST_Delete(TreeNode **link,TREE_TYPE v)
{
	TreeNode *n=BST_Find(*link,v);
	if(n==NULL)
		return 0;
	if(n->left==NULL&&n->right==NULL)
	{
		free(n);
		n=NULL;
	}
}

void BST_Pre_Traverse(TreeNode *root)
{
	if(root==NULL)
		return;
	printf("%d,",root->val);
	BST_Pre_Traverse(root->left);
	BST_Pre_Traverse(root->right);
}