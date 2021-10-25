#include<stdio.h>
#include<string.h>
void tachtenho(char hoten[], char ho[], char ten[])
{
	char *idx = strchr(hoten,' ');// kiem tra co dau cach khong
	char temp[100];
	if(idx == NULL ) strcpy(ten,hoten);//neu khong co dau cach thi ten se la ho ten luon
	else
	{
		int i,c;
		for(i=strlen(idx);i>=1&&c!=' ';--i)
		{
			if(idx[i]==' ') c=' ';
		};//tim gia tri i la vi tri truoc dau cach cuoi trong idx
		for(c=0;c<=strlen(idx)-i-1;++c) ten[c]=idx[c+i+2];
		for(c=0;c<=strlen(hoten)-(strlen(idx)-i);++c) ho[c]=hoten[c];
		ho[c]='\0';
	};
}
void main(void)
{
	char hoten[100],ten[50],ho[50];
	gets(hoten);
	tachtenho(hoten,ho,ten);
	printf("ket qua ho la:%s\n",ho);
	printf("ket qua ten la:%s\n",ten);
}
