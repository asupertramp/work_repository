#include<stdio.h>
#include"bst.c"
int main()
{
	TreeNode *root=NULL;
	int i;
	for(i=0;i<10;++i)
		BST_Insert(&root,i);
	BST_Pre_Traverse(root);
	BST_Delete(&root,9);
	BST_Pre_Traverse(root);
}