#include<stdio.h>
#include<string.h>
//#include<stdlib.h>
#include<ctype.h>
void reverse_recursion(char s[],int i,int j)
{
	int temp;
	if(i>=j)
		return;
	temp=s[i];
	s[i]=s[j];
	s[j]=temp;
	reverse_recursion(s,i+1,j-1);
}
void main(void)
{
	char s[10];
	gets(s);
	reverse_recursion(s,0,strlen(s)-1);//strlen-1 vi do la phan tu ngat xau '\0'
	printf("%s\n",s);
}
