#include <iostream>  
using namespace std;  
  
void DFS_bracket(char* str,int n, int left_used, int right_used)  
{  
    if(left_used == right_used && left_used + right_used == 2*n)  
    {  
        for(int i = 0; i < left_used*2; ++i)  
            cout<<str[i];  
        cout<<endl;  
        return;  
    }  
    if(left_used < right_used || left_used + right_used >= 2*n)  
    {  
        return ;  
    }  
    int index = left_used + right_used;  
    str[index] = '(';  
    DFS_bracket(str, n, left_used + 1, right_used);  
   
    str[index] = ')';
    DFS_bracket(str, n, left_used, right_used + 1);  
}  
int main()  
{  
    int parenthesisnum;  
    cin>>parenthesisnum;  
  
    char* str = new char[parenthesisnum*2+1];  
    DFS_bracket(str,parenthesisnum,0,0);  
    return 0;  
}  