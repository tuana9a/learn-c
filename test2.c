#include<stdio.h>
#include<ctype.h>
#include<string.h>
main()
{
	FILE *text=fopen("/home/tuana9a/Dropbox/c/text.txt","r");
	int n=fgetc(text)-'0';
	printf("n1:%d\n",n);
	int temp=fgetc(text);
	printf("n2:%c\n",n);
	//int origin[n][n];
	//for(int i=0;i<n;++i)

	printf("\n");
}
/*void restore(int n,int *(temp[n][n]))	
{
	for(int i=0;i<n;++i)
	for(int j=0;j<n;++j)
		*temp[i][j]=*origin[i][j];
}
*/