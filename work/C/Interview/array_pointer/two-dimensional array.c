//c���������ϲ����������ȼ������н�ϲ����������ȼ�
void func(char (*p)[5]){}	//pΪһ��ָ�룬ָ��һ��char�����飬��������5��Ԫ��

void func2(char p[][5]){}

void func3(char **p){}

void func4(char *p){}

void func5(char *p[]){}

int main(){
	char *str[]={"1234sdfasd","21asdfasdfafs23"};	//str��һ�����飬����Ԫ��Ϊchar*����
	char arr[3][5];
	
	func(arr);//ok
	func2(arr);//ok
	//func3(arr);//error
	//func4(arr);//error
	//func5(arr);//error
	
	func3(str);//ok
	func5(str);//ok
	
	
	//func(str);//error
		
	return 0;
}
