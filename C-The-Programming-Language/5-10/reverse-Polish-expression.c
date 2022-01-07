#include<stdio.h>
#include<ctype.h>
#include<string.h>
//#include<stdlib.h>
int num[100];
int pos=0;
void get_num(char *s)// get num into num[] one per call
{
	int temp=0;
	while(isdigit(*s))
	{
		temp=10*temp + (*s) - '0';
		++s;
	};
	num[pos++]=temp; 
}
int calc(char *s, int *result)// get expression and evaluate it return ERROR:0 and SUCESS:1 
{
	switch(*s)
	{
		case '+':num[pos-2]=num[pos-1]+num[pos-2];pos-=2;break;
		case '-':num[pos-2]=num[pos-2]-num[pos-1];pos-=2;break;
		case '*':num[pos-2]=num[pos-1]*num[pos-2];pos-=2;break;
		case '/':num[pos-2]=num[pos-2]/num[pos-1];pos-=2;break;
		default:printf("ERROR!\n");return 0;
	};
	*result=num[pos++];
	return 1;
}
int main(int argc, char *argv[])
{
	int i,result=0;
	for(i=1;i<argc;++i)
		if(isdigit(*argv[i])) get_num(argv[i]);
		else if(calc(argv[i],&result));
		else return 0;
	printf("result:%d",result);
	return 0;
}