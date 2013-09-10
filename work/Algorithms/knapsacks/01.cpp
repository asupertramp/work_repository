#include <iostream>
 using namespace std;
 
 //��Ʒ���ݽṹ
 typedef struct commodity
 {
     int value;  //��ֵ
     int weight; //����
 }commodity;
 
 const int N = 3;  //��Ʒ����
 const int W = 50; //����������
 
 //��ʼ��Ʒ��Ϣ
 commodity goods[N+1]={{0,0},{60,10},{100,20},{120,30}};
 int select[N+1][W+1];
 
 int max_value();
 
 int main()
 {
     int maxvalue = max_value();
     cout<<"The max value is: ";
     cout<<maxvalue<<endl;
     int remainspace = W;
     //�����ѡ�����Ʒ�б�
     for(int i=N; i>=1; i--)
     {
         if (remainspace >= goods[i].weight)
         {
              if ((select[i][remainspace]-select[i-1][remainspace-goods[i].weight]==goods[i].value))
              {
                  cout << "item " << i << " is selected!" << endl;
                  remainspace = remainspace - goods[i].weight;//�����i����Ʒ��ѡ����ô����ʣ����������ȥ��i����Ʒ������ ;
              }
         }
     }
     return 0;
 }
 int max_value()
 {
     //��ʼû����Ʒʱ�򣬱����ļ�ֵΪ0
     for(int w=1;w<=W;++w)
         select[0][w] = 0;
     for(int i=1;i<=N;++i)
     {
         select[i][0] = 0;  //��������Ϊ0ʱ������ֵΪ0
            for(int w=1;w<=W;++w)
            {
                if(goods[i].weight <= w)  //��ǰ��Ʒi������С�ڵ���w������ѡ��
                {
                    if( (goods[i].value + select[i-1][w-goods[i].weight]) > select[i-1][w])
                     select[i][w] = goods[i].value + select[i-1][w-goods[i].weight];
                    else
                     select[i][w] = select[i-1][w];
                }
                else //��ǰ��Ʒi����������w����ѡ��
                  select[i][w] = select[i-1][w];
            }
     }
     return select[N][W];  //����������ֵ
 }