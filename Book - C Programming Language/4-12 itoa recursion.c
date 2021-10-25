#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//#include<ctype.h>
void itoa_recursion(int n,char s[])
{
	static int i=0;
	if(n==0)
	{
		return;
	}
	itoa_recursion(n/10,s);
	s[i++]=n%10 +'0';
	s[i]='\0';
}
void main(void)
{
	char s[10];
	int n=41235;
	itoa_recursion(n,s);
	printf("s: %s\n",s);
}