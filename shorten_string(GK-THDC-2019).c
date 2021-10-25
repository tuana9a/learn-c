#include<stdio.h>
#include<string.h>
void cat(char *s)
{
	for(int i=strlen(s)-2;i>=0;++i)
		if(s[i]==' ' || s[i]=='\t')
			s[i]='\0';
		else break;
	printf("lentgh s:%d\n",strlen(s));//cat lan mot
	while(s[0]==' ' || s[0]=='\t')
		for(int i=0;i<strlen(s);++i)
			s[i]=s[i+1];
	printf("lentgh s:%d\n",strlen(s));//cat lan cuoi
}
int main(void)
{
	char s[]=" 	34 	";
	cat(s);
	printf("%s\n",s);
	printf("%d\n",strlen(s));//check xem dung ket qua can tinh khong
	return 0;
}
