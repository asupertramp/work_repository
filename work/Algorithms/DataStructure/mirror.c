//将一个多叉树做镜像操作
typedef struct TreeNode    
{    
    int data;    
    struct TreeNode *firstchild;    
    struct TreeNode *nextsibling;    
}TreeNode,*Tree;    
void MirrorTree(Tree root)    
{    
    if(!root)    
        return ;    
    if(root->firstchild)    
    {    
        Tree p=root->firstchild;    
        Tree cur=p->nextsibling;    
        p->nextsibling=NULL;    
        while(cur)    
        {    
            Tree curnext=cur->nextsibling;    
            cur->nextsibling=p;    
            if(p->firstchild)    
                MirrorTree(p);    
            p=cur;    
            cur=curnext;    
        }    
        root->firstchild=p;    
    }    
}    
int main(void)    
{    
    TreeNode *root=(TreeNode *)malloc(sizeof(TreeNode));    
    Init();    
    MirrorTree(root);    
    OutPut();    
}  