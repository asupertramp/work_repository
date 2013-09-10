#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//字符串前缀和后缀相同的最大长度
int maxPreSufix(char* str,int length){
	int i,j,max=0;
	for(i=length-1;i>0;i--){
		for(j=0;j<i;j++){
			if(*(str+j)!=*(str+length-i+j))
				break;
		}
		if(j==i){
			max=i;
			break;
		}
	}
	return max;
}
//生成字符串的所有前缀字符串的最大前后缀相同长度
void genPartMatchTable(char *str,int **table,int length){
	*table=(int*)malloc(length*sizeof(int));
	if(*table==NULL){
		printf("failed\n");
		return;
	}
	int i;
	
	for(i=0;i<length;i++)
		*(*table+i)=maxPreSufix(str,i+1);
}

int KMP(char*str,char*pat){
	int i,j;
	int sl=strlen(str);
	int pl=strlen(pat);
	if(sl<pl){
		printf("no match\n");
		return 0;
	}
	int **table=(int**)malloc(sizeof(int));
	genPartMatchTable(pat,table,strlen(pat));

	for(i=0,j=0;i<sl&&j<pl;){
		if(*(str+i)!=*(pat+j)){
			if(j==0){
				i++;
				continue;
			}
			j=*(*table+j-1);
		}
		else{
			i++;
			j++;
		}
	}
	free(table);
	if(j==pl)
		return i-j;
	return -1;
}

int main(){
	char * str="aabcddaabcd";
	char * str1="abcddabcd";
	char * str2="abcddaab";
	char * str3="abcddaabcde";
	char *pat="aab";
	int i;
		
	//KMP(str,pat);
	printf("%d\n",KMP(str,pat));
	printf("%d\n",KMP(str1,pat));
	printf("%d\n",KMP(str2,pat));
	printf("%d\n",KMP(str3,pat));
}