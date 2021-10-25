#include<stdio.h>
#include<ctype.h>
double atof(char *s);
void main(void)
{
	char s[100];
	while(1)
	{
		printf("Input It:\n");
		gets(s);
		printf("Result is: %lf\n",atof(s));	
	}
}
double atof(char *s)
{
	double value=0,ten_handle=1;
	int e_handle=0,i,sign;
	for(i=0;isspace(s[i]);++i);//xoa khoang trong
	sign=(s[i]=='-')?-1:1;//xet dau
	if(s[i]=='+' || s[i]=='-') ++i;
	for(;s[i]!='.' && s[i]!='e' && s[i]!='\0';++i)
		value=value*10.0 +s[i]-'0';
	if(s[i]=='.')
	{
		for(++i;s[i]!='e' && s[i]!='\0';++i)
		{
			value=value*10.0+s[i]-'0';
			ten_handle*=10.0;
		}
	};
	if(s[i++]=='e')
	{
		if(s[i]=='-')
		{
			for(++i;s[i]!='\0';++i)
				e_handle=e_handle*10+s[i]-'0';
			for(int j=1;j<=e_handle;++j)
				ten_handle*=10.0;
		}
		else
		{
			for(;s[i]!='\0';++i)
				e_handle=e_handle*10+s[i]-'0';
			for(int j=1;j<=e_handle;++j)
				ten_handle/=10.0;
		};
	};
	return sign*value/ten_handle;
}