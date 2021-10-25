#include<stdio.h>
#include<string.h>
void main(void)
{
	int i=0,j=0,step=100000;
	while(step>0)		//chuyen thanh "step<0" neu muon tim max positive
	{
		i=i-step;	// chuyen thanh "i=i+step" neu muon tim max positive
		if(i<0) 
		{
			j=i;	// chuyen dieu kien thanh "i>0" neu muon tim max positive
		}
		else
		{
			i=j;
			step--;
		}
	};
	printf("ket qua max la: %d\n",j);
}