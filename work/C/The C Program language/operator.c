#include <stdlib.h>
#include <math.h>
testBS()
{
	int a[] = {2,343,342,1,123,43,4343,433,687,654,3};
	int *a_p = &a;
	//计算数组长度
	int size = sizeof(a)/sizeof(int);
	//基数排序
	bucketSort3( a_p , size );
	//打印排序后结果
	int i ;
	for(i = 0 ; i < size ; i++ ) {
		printf("%d\n ",a[i]);
	}
	int t;
	scanf("%d",&t);
}
//基数排序
void bucketSort3(int *p , int n)
{
	//获取数组中的最大数
	int maxNum = findMaxNum( p , n );
	//获取最大数的位数，次数也是再分配的次数。
	int loopTimes = getLoopTimes(maxNum);
	int i ;
	//对每一位进行桶分配
	for( i = 1 ; i <= loopTimes ; i++) {
		sort2(p , n , i );
	}
}
//获取数字的位数
int  getLoopTimes(int num)
{
	int count = 1 ;
	int temp = num/10;
	while( temp != 0 ) {
		count++;
		temp = temp / 10;
	}
	return count;
}
//查询数组中的最大数
int findMaxNum( int *p , int n)
{
	int i ;
	int max = 0;
	for( i = 0 ; i < n ; i++) {
		if(*(p+i) > max) {
			max = *(p+i);
		}
	}
	return max;
}
//将数字分配到各自的桶中，然后按照桶的顺序输出排序结果
void sort2(int *p , int n , int loop)
{
	//建立一组桶  此处的20是预设的  根据实际数情况修改
	int buckets[10][20] = {} ;
	//求桶的index的除数
	//如798   个位桶index = ( 798 / 1 )  % 10 = 8
	//             十位桶index = ( 798 / 10 ) % 10 = 9
	//             百位桶index = ( 798 / 100 )  % 10 = 7
	//  tempNum 为上式中的1、10、100
	int tempNum = (int) pow(10 , loop-1);
	int i , j ;
	for( i = 0 ; i < n ; i++ ) {
		int  row_index = (*(p+i) / tempNum) % 10;
		for(j = 0 ; j < 20 ; j++) {
			if(buckets[row_index][j] ==NULL) {
			buckets[row_index ][j]  =  *(p+i) ;
			break;
			}
		}
	}
	//将桶中的数，倒回到原有数组中
	int k = 0 ;
	for(i = 0 ; i < 10 ; i++) {
		for(j = 0 ; j < 20 ; j++) {
			if(buckets[i][j] != NULL) {
			*(p + k ) = buckets[i][j] ;
			buckets[i][j]=NULL;
			k++;
			}
		}
	}
}