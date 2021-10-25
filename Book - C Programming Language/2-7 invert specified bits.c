#include<stdio.h>
int main(void)
{
    char result[10],temp[10];
    int x,y;
    while(1)
    {
        int c,i;
        printf("x= ");
        scanf("%d",&x);
        y=invert(x,2,2);

        c=binary_convert(x,temp);
        reverse_result(temp,c,result);
        printf("x dang nhi phan la:");
        for(i=0;i<=c;++i)
            printf("%c",result[i]);
        printf("\n");

        c=binary_convert(y,temp);
        reverse_result(temp,c,result);
        printf("y dang nhi phan la:");
        for(i=0;i<=c;++i)
            printf("%c",result[i]);
        printf("\n");
    };
}
int binary_convert(int x,char out[])//chuyen sang nhi phan nhung bi nguoc
{
    int i=0;
    while(x>0)
    {
        if(x%2==1) out[i++]='1';
        else if(x%2==0) out[i++]='0';
        x/=2;
    };
    return i-1;
}
void reverse_result(char in[],int in_length,char out[])//chuyen nguoc lai
{
    int i;
    for(i=0;i<=in_length;++i) out[i]=in[in_length-i];
}

int invert(int x, int p, int n)
{
    return (x^(~(~0<<n)<<(p+1-n)));
}
