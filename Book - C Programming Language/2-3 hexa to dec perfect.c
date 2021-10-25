#include<stdio.h>
void main(void)
{
	char in[100],out[100];
	int c;
	while(c)
	{
	    printf("Nhap vao so HEXA ma ban muon chuyen: (VD  0x123ABC) voi 0x la dau hieu nhan biet\n");
        fflush(stdin);
        if((c=get_and_convert(in,out)) == -1)
            printf("Ban nhap ngu vai cut\n");
        else
            printf("ket qua la: %d\n",c);
        printf("Ban co muon thu tiep khong? (0:Khong)\n");
        scanf("%d",&c);
	}
}
int get_and_convert(char in[],int out[])
{
	int i=0,y=0,c;
	int result=0;
	while((c=getchar()) != EOF)
	{
		in[i]=c;
		++i;
	};
	i=i-2;
	if (in[0]!='0' || (in[1]!='x' && in[1]!='X'))
    {
         return -1;
    }
	else
	{
	    for(y=i;y>=2;--y)
        {
            if(in[y]=='0') out[i]=0;
            else if(in[y]=='1') out[y]=1;
            else if(in[y]=='2') out[y]=2;
            else if(in[y]=='3') out[y]=3;
            else if(in[y]=='4') out[y]=4;
            else if(in[y]=='5') out[y]=5;
            else if(in[y]=='6') out[y]=6;
            else if(in[y]=='7') out[y]=7;
            else if(in[y]=='8') out[y]=8;
            else if(in[y]=='9') out[y]=9;
            else if(in[y]=='a' || in[y]=='A') out[y]=10;
            else if(in[y]=='b' || in[y]=='B') out[y]=11;
            else if(in[y]=='c' || in[y]=='C') out[y]=12;
            else if(in[y]=='d' || in[y]=='D') out[y]=13;
            else if(in[y]=='e' || in[y]=='E') out[y]=14;
            else if(in[y]=='f' || in[y]=='F') out[y]=15;
            else out[y]=0;
        };
	}
	out[0]=out[1]=0;
	for(y=i;y>=2;--y)
		result=result + out[y]*luythua(16,i-y);
	return result;
}
int luythua(int x,int n)
{
	if(n>=2) return luythua(x,n-1)*x;
	else if(n==1) return x;
	else if(n==0) return 1;
	return x;
}
