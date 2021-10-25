#include<stdio.h>
#include<string.h>
#include<math.h>
int int_to_str(int *s,int num)
{
	int j;
	for(j=0;num>0;++j,num/=10)
	{
		s[j]=num%10;
	};
	return j;
}
void print_num(int num,int pos)
{
	static int pre_num=-1,pre_pos=-1;
	//pre_pos=pre_num=-1;
	//printf("pre_num:%d   pre_pos:%d\n",pre_num,pre_pos);
	switch(num)
	{
		case 0: if((pos-2)%3 && (pos-4)%3) printf("khong "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi ");break;
		case 1: if(pre_num==0 && (pre_pos-2)%3==0 ) printf("linh mot "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi mot "); else if((pos-2)%3!=0) printf("mot ");break;
		case 2: if(pre_num==0 && (pre_pos-2)%3==0 ) printf("linh hai "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi hai "); else printf("hai ");break;
		case 3: if(pre_num==0 && (pre_pos-2)%3==0 ) printf("linh ba "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi ba "); else printf("ba ");break;
		case 4: if(pre_num==0 && (pre_pos-2)%3==0 ) printf("linh bon "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi bon "); else printf("bon ");break;
		case 5: if(pre_num==0 && (pre_pos-2)%3==0 ) printf("linh nam "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi lam "); else printf("nam ");break;
		case 6: if(pre_num==0 && (pre_pos-2)%3==0 ) printf("linh sau "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi sau "); else printf("sau ");break;
		case 7: if(pre_num==0 && (pre_pos-2)%3==0 ) printf("linh bay "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi bay "); else printf("bay ");break;
		case 8: if(pre_num==0 && (pre_pos-2)%3==0 ) printf("linh tam "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi tam "); else printf("tam ");break;
		case 9: if(pre_num==0 && (pre_pos-2)%3==0 ) printf("linh chin "); else if(pre_num==1 && (pre_pos-2)%3==0) printf("muoi chin "); else printf("chin ");break;
	};//printf("\n");
	switch(pos)
	{
		case 2:  if(num!=0 && num!=1) printf("muoi "); break;
		case 3:  printf("tram ");break;
		case 4:  printf("nghin ");break;
		case 5:  if(num!=0 && num!=1) printf("muoi "); break;
		case 6:  printf("tram ");break;
		case 7:  printf("trieu ");break;
		case 8:  if(num!=0 && num!=1) printf("muoi "); break;
		case 9:  printf("tram ");break;
		case 10: printf("ty ");break;
		case 11: if(num!=0 && num!=1) printf("muoi "); break;
		case 12: printf("tram ");break;
		case 13: printf("nghin ty ");break;
		/*case 14: printf("ba ");break;
		case 14: printf("bon ");break;
		case 15: printf("nam ");break;
		case 16: printf("sau ");break;
		case 17: printf("bay ");break;
		case 18: printf("tam ");break;
		case 19: printf("chin ");break;*/
	};//printf("\n");
	pre_num=num;
	pre_pos=pos;
}
void out(int num)
{
	int s[20],len;
	len=int_to_str(s,num);
	for(int i=len;i>=1;--i)
	{
		print_num(s[i-1],i);
	};
	printf("\n");
}
void main()
{
	int n;
	while(1)
	{
		scanf("%d",&n);
		out(n);
	}
}