typedef struct TreeNode* STACK_TYPE;
STACK_TYPE  pop(void);
STACK_TYPE top();
void push(STACK_TYPE v);
int is_full();
int is_empty();
void creat_stack();
void destroy_stack();
