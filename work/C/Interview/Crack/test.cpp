#include<iostream>
#include<deque>
#include<vector>
#include<stack>
using namespace std;
typedef struct Node {
	int val;
	struct Node * left;
	struct Node *right;
};
void pre_tra(Node *tree)
{
	if(tree==NULL)
		return;
	stack<Node*> s;
	s.push(tree);
	while(!s.empty())
	{
		Node *n=s.top();
		cout<<n->val<<endl;
		s.pop();
		if(n->right!=NULL)
			s.push(n->right);
		if(n->left!=NULL)
			s.push(n->left);
	}
}
void in_tra(Node *tree)
{
}
void inOrder(Node* root)
{
    stack<Node*> S;
    while ( root != NULL || !S.empty() )
    {
        while( root != NULL )   // 左子树入栈
        {
            S.push(root);
            root = root->left;
        }
        if ( !S.empty() )
        {
            root = S.top();
            cout<<root->val<<endl;   
			S.pop();
            root = root->right;  // 通过下一次循环实现右子树遍历
        }
    }
}
void postOrder(Node *root)
{
	stack<Node*> s;
	
}
Node* insert(Node *tree,int v)
{
	if(tree==NULL)
	{
		Node* n=new Node();
		if(n==NULL)
			return NULL;
		n->val=v;
		n->left=n->right=NULL;
		return n;
	}
	if(tree->val>v)
		tree->left=insert(tree->left,v);
	else
		tree->right=insert(tree->right,v);
	return tree;
}
Node *build_tree(int a[],int n)
{
	Node *tree=new Node();
	if(tree==NULL)
		return NULL;
	tree->val=a[0];
	for(int i=1;i<n;++i)
		tree=insert(tree,a[i]);
	return tree;
}
int main()
{
	int a[]={6,2,8,4,2,9,1,0,5};
	Node *tree=build_tree(a,9);
	pre_tra(tree);
	cout<<endl;
	inOrder(tree);
	return 0;
}