//������������ n �� m��������1��2��3.......n �� ����ȡ������,
//ʹ��͵��� m ,Ҫ���������еĿ�������г�����

#include<list>  
#include<iostream>  
using namespace std;  
  
list<int>list1;  
void find_factor(int sum, int n)   
{  
    // �ݹ����  
    if(n <= 0 || sum <= 0)  
        return;  
      
    // ����ҵ��Ľ��  
    if(sum == n)  
    {  
        // ��תlist  
        list1.reverse();  
        for(list<int>::iterator iter = list1.begin(); iter != list1.end(); iter++)  
            cout << *iter << " + ";  
        cout << n << endl;  
        list1.reverse();      
    }  
      
    list1.push_front(n);      //���͵�01��������  
    find_factor(sum-n, n-1);   //��n��n-1��������sum-n  
    list1.pop_front();  
    find_factor(sum, n-1);     //����n��n-1��������sum   
}  
  
int main()  
{  
    int sum, n;  
    cout << "��������Ҫ���ڶ��ٵ���ֵsum:" << endl;  
    cin >> sum;  
    cout << "��������Ҫ��1.....n������ȡֵ��n��" << endl;  
    cin >> n;  
    cout << "���п��ܵ����У����£�" << endl;  
    find_factor(sum,n);  
    return 0;  
} 