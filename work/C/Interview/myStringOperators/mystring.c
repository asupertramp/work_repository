int m_strcmp(const char *str1,const char *str2){	assert(str1&&str2);	while(*str1&&*str2)	{		if(*str1!=*str2)			return *str1-*str2;		str1++;		str2++;	}	if(*str1==*str2)		return 0;	else		if(*str=='\0')			return -1;		else			return 1;}char *m_strstr(const char *haystack, const char * needle){	if(!haystack&&needle)		return 0;	while(*haystack!='\0')	{		char *tmp=needle;		while(*tmp=	}}size_t m_strlen (const char *s);char *m_strcpy(char *dest, const char *src);char *m_strcat(char *dest, const char *src);int m_toupper(int c);char * m_strchr (const char *s, int c);