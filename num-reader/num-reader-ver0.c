#include<stdio.h>
/*void convert_speak_to_speakout(char speak[],char speakout[])//coppy array cho chu
{
	int i;
	i=0;
	while(i<=4)
	{
		speakout[i]=speak[i];
		++i;
	};
}*/
void convert_number(int number,char speakout[])//tu so chuyen sang chu
{
	int i;
	/*char zero[]="khong";
	char one[]="mot";
	char two[]="hai";
	char three[]="ba";
	char four[]="bon";
	char five[]="nam";
	char six[]="sau";
	char seven[]="bay";
	char eight[]="tam";
	char nine[]="chin";*/
	for(i=0;i<=9;++i)//tim gia tri cua chu so
		if(i==number)
			if(i==0) speakout="mot";
			else if(i==1) speakout="hai";
			else if(i==2) convert_speak_to_speakout(two,speakout);
			else if(i==3) convert_speak_to_speakout(three,speakout);
			else if(i==4) convert_speak_to_speakout(four,speakout);
			else if(i==5) convert_speak_to_speakout(five,speakout);
			else if(i==6) convert_speak_to_speakout(six,speakout);
			else if(i==7) convert_speak_to_speakout(seven,speakout);
			else if(i==8) convert_speak_to_speakout(eight,speakout);
			else if(i==9) convert_speak_to_speakout(nine,speakout);
	;
}
int power(int x,int n)//x mu n
{
	int i,result;
	i=1;
	result=1;
	while(i<=n)
	{
		result=result*x;
		++i;
	};
	return result;
}
int getnumber(long int number,long int s[])
{
	long int c,b,i;
	c=number;
	b=0;
	while((c%10) != 0 || c/10 != 0)
	{
		c=c/10;
		++b;
	};
	for(i=0;i<b;++i)
	{
		s[i]=(number/power(10,b-i-1))%10;
	};
	return b;
}
void main(void)
{
	long i,number,s[100],length,donvi=0;
	char speakout[5];
	printf("nhap vao so ban muon doc: ");
	scanf("%ld",&number);
	length=getnumber(number,s);
	for(i=0;i<length;++i)
	{
		convert_number(s[i],speakout);
		printf("%s ",speakout);
		if((donvi=length-1-i)==0) printf("");
		else if((donvi=length-1-i)==1) printf("muoi");
		else if((donvi=length-1-i)==2) printf("tram");
		else if((donvi=length-1-i)==3) printf("nghin");
		else if((donvi=length-1-i)==4) printf("muoi");
		else if((donvi=length-1-i)==5) printf("tram");
		else if((donvi=length-1-i)==6) printf("trieu");
		else if((donvi=length-1-i)==7) printf("muoi");
		else if((donvi=length-1-i)==8) printf("tram");
		else if((donvi=length-1-i)==9) printf("ty");
		else if((donvi=length-1-i)==10) printf("muoi");
		else if((donvi=length-1-i)==11) printf("tram");
		else if((donvi=length-1-i)==12) printf("nghin");
		else if((donvi=length-1-i)==13) printf("muoi nghin");
		else if((donvi=length-1-i)==14) printf("tram nghin");
		printf("\n");
	}
}