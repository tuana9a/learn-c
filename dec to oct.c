#include<stdio.h>
//#include<math.h>
int pow(int x, int n)
{
    if(n>=1) return x*pow(x,n-1);
    return 1;
}
int main()
{
    long int n;
    printf("nhap vao:");
    scanf("%d",&n);
    long int i=0;
    //printf("%d",pow(8));
    while(pow(8,i)<=n) ++i;
    //printf("%d\n",i);
    char result[100];
    long int temp=0;
    long int j,x=1;
    for(j=0;j<i;++j)
    {
        long int e;
        for(e=0;e*pow(8,i-x)<=n;++e);
        result[j]=e-1+'0';
        n-=(e-1)*pow(8,i-x);
        ++x;
    };
    result[j]='\0';
    printf("%s",result);
}
