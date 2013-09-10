#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
using namespace std;
void func(int i)
{
	cout<<i<<endl;
}
int Gen()
{
	return 12;
}
bool Comp(int i)
{
	if(i>5)
		return true;
	else
		return false;
}
int main()
{
	vector<int> iv;
	vector<int> iv2(10);
	vector<int>::iterator iter;
	for(int i=0;i<10;++i)
		iv.push_back(10-i);
	stable_sort(iv.begin(),iv.end());
	partition(iv.begin(),iv.end(),Comp);
	partial_sort(iv.begin(),iv.begin()+5,iv.end());
	remove(iv.begin(),iv.end(),3);
	reverse(iv.begin(),iv.end());
	random_shuffle(iv.begin(),iv.end());
	cout<<accumulate(iv.begin(),iv.end(),11)<<endl;
	cout<<*min_element(iv.begin(),iv.end())<<endl;//·µ»Øµü´úÆ÷
	unique(iv.begin(),iv.end());
	nth_element(iv.begin(),iv.begin(),iv.end());
	for_each(iv.begin(),iv.end(),func);
	//for_each(iv.begin(),iv.end(),func);
	//fill_n(iv.begin(),5,11);
	//for_each(iv.begin(),iv.end(),func);
	//generate_n(iv.begin(),3,Gen);
	//for_each(iv.begin(),iv.end(),func);
	//copy(iv.begin(),iv.end(),iv2.begin());
	//for_each(iv.begin(),iv.end(),func);
	return 0;
}