#include<stdio.h>
void main(void)
{
	char line[100],result[1000];
	int c=0,result_start=0;
	while((c=length(line))>0)
		if(c>=4)
		{
			store(line,c,result,result_start);
			result_start+=c;	
		};
	printf("ket qua la: \n%s",result);
}
int length(char line[])
{
	int c,i=0;
	while((c=getchar()) != EOF && c!='\n') line[i++]=c;
	if(c=='\n') line[i++]=c;
	line[i]='\0';
	return i;//day chinh la vi tri cua '\0'
}
void store(char line[],int c,char result[],int result_start)
{
	int i=0;
	while(i<c)
	{
		result[result_start+i++]=line[i];
	};
}