#include<stdio.h>
int main()
{
	int dodai,a,b,i;
	char s[1000];
	dodai=all_lines(s);
	if((a=start(s,dodai))==0 || (b=end(s,dodai,a))==0) {printf("%s",s);}
	else
	{
		for(i=0;i<a;++i) printf("%c",s[i]);
		for(i=b;i<=dodai;++i) printf("%c",s[i]);
	};
	printf("\nEND.\n");
}
//ghi tat ca van ban vao mang s --> return do dai van ban
int all_lines(char s[])
{
	int c,i;
	i=0;
	while((c=getchar()) != EOF)
	{
		s[i]=c;++i;
	}
	return i-1;
}
//doc den ky tu bat dau --> return chi so bat dau
int start(char s[], int dodai)
{
	int i,c,a;
	c=a=0;
	for(i=0;i<=dodai && c==0;++i)
		if(s[i]=='/' && s[i+1]=='*'){c=1;a=i;}
	return a;
}
//doc tu ky tu bat dau den ky tu ket thuc --> return chi so ket thuc
int end(char s[],int dodai, int start)
{
	int i,c,a;
	c=a=0;
	for(i=start;i<=dodai && c==0;++i)
		if(s[i]=='*' && s[i+1]=='/'){c=1;a=i+2;}
	return a;
}