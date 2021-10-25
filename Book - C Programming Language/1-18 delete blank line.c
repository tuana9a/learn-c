#include<stdio.h>
int main()
{
int c,i;
while((c=getchar()) != EOF) 
	if(c=='\t' || c==' ' ) {}
		else 
		{
			if(c=='\n' && i=='\n') {} 
				else putchar(i);
			i=c;
		}
}