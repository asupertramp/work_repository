#include<iostream>#include<vector>#include<string>using namespace std;vector<string> permutation(string s){	vector<string> vs;	if(s.size()==1)	{		vs.push_back(s);		return vs;	}	vs=permutation(s.substr(1));	vector<string> result;	for(vector<string>::iterator iter=vs.begin();iter!=vs.end();++iter)	{		string tmp=*iter;		for(size_t i=0;i<=tmp.size();++i)		{			string app=tmp.substr(0,i)+s[0]+tmp.substr(i);			result.push_back(app);		}	}	return result;}void print_vector(vector<string> p){	for(vector<string>::iterator iter=p.begin();iter!=p.end();++iter)	{		cout<<*iter<<endl;	}	cout<<p.size()<<endl;}int main(){		while(1)	{		string s;		cin>>s;		vector<string> p=permutation(s);		print_vector(p);	}	return 0;}