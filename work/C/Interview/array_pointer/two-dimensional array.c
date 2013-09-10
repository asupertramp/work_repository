//c语言中左结合操作符的优先级高于有结合操作符的优先级
void func(char (*p)[5]){}	//p为一个指针，指向一个char型数组，该数组有5个元素

void func2(char p[][5]){}

void func3(char **p){}

void func4(char *p){}

void func5(char *p[]){}

int main(){
	char *str[]={"1234sdfasd","21asdfasdfafs23"};	//str是一个数组，它的元素为char*类型
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
