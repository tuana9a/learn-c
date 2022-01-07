#include<stdio.h>
#include<string.h>
// void nhpadanhsach(char **ds, int n)
void tachtenho(char hoten[100], char ho[50], char ten[50])
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
void nhapdanhsach(char ds[200][100], int n)
{
	
	for(int i=0;i<n;++i)
	{
		printf("Ho ten: ");
		gets(ds[i]);
	}
}
// so sanh 2 hoten theo ho va ten 
// tra ve -1 neu hoten 1 dung truoc hoten2
// tra ve 0 neu giong nhau
// tra ve +1 neu hoten1 dung sau hoten2
int sosanh(char ht1[100],char ht2[100])
{
	char ho1[50], ten1[50], ho2[50], ten2[50];
	tachtenho(ht1,ho1,ten1);//printf("%s%s\n",ho1,ten1);
	tachtenho(ht2,ho2,ten2);//printf("%s%s\n",ho2,ten2);
	if(strcmp(ten1,ten2)==0)
		return strcmp(ho1,ho2);
	else 
		return strcmp(ten1,ten2);
}
// sap xep theo ten va ho
void sapxep(char ds[200][100], int n)
{
	for(int i=0;i<n;++i)
		for(int j=0; j<n-1;++j)
		{
			if(sosanh(ds[j],ds[j+1])>0)
			{
				char temp[100];
				strcpy(temp,ds[j]);
				strcpy(ds[j],ds[j+1]);
				strcpy(ds[j+1],temp);
			}
		}
}
void inDS(char ds[200][100], int n)
{
	for(int j=0;j<=n;++j)
		printf("%s\n",ds[j]);
}
void main(void)
{
	char ds[200][100];
	int n;
	printf("Nhap vao so luong nguoi ma ban muon sap xep:\n");
	scanf("%d",&n);
	getchar();
	nhapdanhsach(ds,n);
	sapxep(ds,n);
	inDS(ds,n);
}