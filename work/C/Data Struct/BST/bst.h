typedef int TREE_TYPE;
typedef struct TREE_NODE{
	TREE_TYPE val;
	struct TREE_NODE *left;
	struct TREE_NODE *right;
}TreeNode;
int BST_Insert(TreeNode **link,TREE_TYPE v);
int BST_Delete(TreeNode **link,TREE_TYPE v);
void BST_Traverse(TreeNode *root);