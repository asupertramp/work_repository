#include <vector>  
#include <iostream>  
/** 
* Description: Calulate the longest increase subsequence 
*@param s1, source sequence 
*@param s2, output, longest increase sequence 
*/  
template<typename T> void longest_increase_subsequence(const std::vector<T>& s1, std::vector<T>& s2)  
{  
      
    int n = s1.size(); if (n<1) return;  
    int m = 0;  
    int k = 0;  
    std::vector<unsigned int> b(n+1, 1);  
    std::vector<unsigned int> p(n+1, 0);  
              
    for (int i=1;i<=n;i++)     
    {  
        for (int j=1;j<i;j++)  
        {  
            if ( s1[i-1] > s1[j-1] && b[i] < b[j] +1 )  
            {  
                b[i] = b[j] + 1;  
                p[i] = j;  
            }     
        }  
    }     
    for ( int i=1;i<=n;i++)  
    {  
        if (m<b[i])  
        {     
            m = b[i];  
            k = i;  
        }     
    }     
    s2.resize(m);  
    while (k>0)  
    {  
        s2[m-1] = s1[k-1];  
        m--;  
        k = p[k];  
    }  
}  
int main(int argc, char* argv[])  
{  
    int a[] = {5,1,6,2,3,7,4 };  
    std::vector<int> seq(a, a+sizeof(a)/sizeof(a[0]));  
    std::vector<int> r;  
    longest_increase_subsequence(seq, r);  
    for (int i=0;i<r.size();i++)  
        std::cout<<r[i]<<" ";  
    std::cout<<std::endl;  
    return 0;  
}  