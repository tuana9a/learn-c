#include<stdio.h>
#include<ctype.h>
//#include<string.h>
#include<stdlib.h>
void strcat(char *s, char *t)
{
	int len_s= strlen(s),len_t=strlen(t);
	for (int i=len_s;i<=len_s+len_t;i++)
	{
		s[i]=t[i-len_s];
	}
}
int main(void)
{
	
	char y[100]="hello ";
	char s[]="world";
	strcat(y,s);
	printf("%s\n",y);
	return 0;
}
