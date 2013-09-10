class MyString
{
	public:
		typedef unsigned int size_type;
		MyString();
		MyString(MyString &other);
		MyString(const char *str);
		MyString(int n,char c);
		~MyString();
		
		bool empty(){return strSize==0?true:false;}
		size_type size(){return strSize}
		bool operator==(const MyString &other);
		MyString& operator=(const MyString &other);
		MyString& operator+(const MyString &other);
		char operator[](size_type index);
	private:
		char *c;
		size_type strSize;
		
};
MyString::MyString()
{
	strSize=0;
	c=NULL;
}
MyString::MyString(MyString &other)
{
	size_type otherSize=other.size();
	if(otherSize==0)
	{
		MyString();
		return;
	}
	c=(char*)malloc(otherSize+1);
	if(c==NULL)
		exit(1);
	char *temp=c;
	for(size_type i=0;i<otherSize;++i)
		*temp++=other[i];
	*temp='\0';
	strSize=otherSize;
}


MyString::MyString(const char*str)
{
	if(str==NULL)
	{
		MyString();
		return;
	}
	size_type length=(size_type) strlen(str);
	c=(char*) malloc(length+1);
	if(c==NULL)
		exit(1);
	char *tmp=c;
	while((*tmp++=*str++)!='\0')
		;
	strSize=length;
}
MyString::~MyString()
{
	free(c);
	c=NULL;
	strSize=0;
}
char MyString::operator[](size_type index)
{
	if(index>=this->strSize)
		return '\0';
	return c[index];
}