#include<stdio.h>
int main()
{
	char line[100], result[100];
	int c;
	while((c=store_line(line))>=0)
	{
		reverse(line,result,c);
		printf("%s",result);
	}
}
int store_line(char l[])
{
	int i,c;
	i=0;
	while((c=getchar()) != EOF && c!='\n')
	{
		l[i]=c;
		++i;
	}
	if(c=='\n') l[i]=c;
	return i;
}
void reverse(char in[],char out[], int c)
{
	int i;
	for(i=0;i<=c;++i)
		out[i]=in[c-i];
}