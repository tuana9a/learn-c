#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
float int_num[100];//chỉ trong lúc tính toán ko phải const
int int_pos=0;
char char_num[100][10];//cái này là chỗ cố định để lấy toán hạng
int char_pos=0;
float ket_qua;
void get_num(char *s)//lấy số hàm này đã ở trong hàm calc
{
	float temp=0.0;
	while(isdigit(*s))
	{
		temp=10.0*temp + (*s) - '0';
		++s;
	};
	int_num[int_pos++]=temp; 
}

int calc(char *s[],int n)//tính kết quả của 1 trường hợp hoàn chỉnh s return ERROR:0 hoặc SUCESS:1 
{
	int i;
	int exp_count=n-1,operand_count=n;
	for(i=0;i<=2*n-2;++i)
		if(isdigit(*s[i])!=0 && operand_count>=0)
		{
			get_num(s[i]);
			--operand_count;
		}
		else if(i>=2 && exp_count>=0)
				switch(*s[i])
				{
					case '+':if(int_pos >=2){int_num[int_pos-2]=int_num[int_pos-2]+int_num[int_pos-1];int_pos-=1;}else{/*printf("ERROR\n");*/int_pos=0;return 0;};break;//nếu không có in_pos =0 nó sẽ không reset lại toàn bộ và nó lại tính tiếp từ in_pos cũ
					case '-':if(int_pos >=2){int_num[int_pos-2]=int_num[int_pos-2]-int_num[int_pos-1];int_pos-=1;}else{/*printf("ERROR\n");*/int_pos=0;return 0;};break;
					case '*':if(int_pos >=2){int_num[int_pos-2]=int_num[int_pos-2]*int_num[int_pos-1];int_pos-=1;}else{/*printf("ERROR\n");*/int_pos=0;return 0;};break;
					case '/':if(int_pos >=2){int_num[int_pos-2]=int_num[int_pos-2]/int_num[int_pos-1];int_pos-=1;}else{/*printf("ERROR\n");*/int_pos=0;return 0;};break;
					/*case '%':if(int_pos-2>=0){int_num[int_pos-2]=int_num[int_pos-2]%int_num[int_pos-1];int_pos-=1;}else{printf("ERROR\n");return 0;};break;*/
					default:/*printf("ERROR\n");*/break;//return 0;
				}
		else {/*printf("ERROR\n");*/ return 0;};
	if(int_num[int_pos-1]==ket_qua) 
	{
		print_test(s,n);
		printf("=%6.2f\n",int_num[int_pos-1]);	
	}
	int_pos=0;//tiếp nhận trường hợp mới
	return 1;
}

// OLD print_test
/*
void print_test(char *s[],int n)//in ra test đang thử
{
	printf("|");
	for(int i=0;i<=2*n-2;++i)
		printf("%s",s[i]);
	printf("|");
}
*/

// NEW print_test
void print_test(char *s[],int n)
{

}

int random_it(char *s[],char *all[][10],int n,int temp_pos)//đánh random các vị trí của toán hạng và toán tử
{
	if(temp_pos<2*n-1)
	{
		strcpy(s[temp_pos],"opd");random_it(s,all,n,temp_pos+1);
		strcpy(s[temp_pos],"exp");random_it(s,all,n,temp_pos+1);
	}
	else
	{
		copy_temp_to_all(s,all,n);

		return 0;
	}
}

void copy_temp_to_all(char *temp[],char *all[][10],int n)//lưu các trường hợp random vào mảng all
{
	static int i=0;
	int j;
	if(i<1000)
	{
		for(j=0;j<2*n-1;++j) strcpy(all[i][j],temp[j]);
		//print_test(all[i],n);
		++i;
	};
	//printf("ok stored\n");
}

int luy_thua(int x, int n)
{
	int temp=1;
	while((n--)>0) temp=temp*x;
	return temp;
}

int fill_exp(char *s[],int n,int temp_pos,int exp_count)//n số toán hạng, temp_pos vị trí trong xâu con trỏ// lol thay các exp bằng toán tử và tính các trường hợp của toán tử only
{
	//printf("ok%d",temp_pos);
	if(temp_pos<n*2-1 && --exp_count>=0)
	{
		if
		(	strcmp(s[temp_pos],"exp")==0 ||
			strcmp(s[temp_pos],"+")==0   ||
			strcmp(s[temp_pos],"-")==0   ||
			strcmp(s[temp_pos],"*")==0   ||
			strcmp(s[temp_pos],"/")==0)/*   ||
			strcmp(s[temp_pos],"%")==0     ) */
		{
			strcpy(s[temp_pos],"+");fill_exp(s,n,temp_pos+1,exp_count);
			strcpy(s[temp_pos],"-");fill_exp(s,n,temp_pos+1,exp_count);
			strcpy(s[temp_pos],"*");fill_exp(s,n,temp_pos+1,exp_count);
			strcpy(s[temp_pos],"/");fill_exp(s,n,temp_pos+1,exp_count);
			/*strcpy(s[temp_pos],"%");fill_exp(s,n,temp_pos+1,exp_count);*/
		}
		else
		{
			//if(strcmp(s[temp_pos],"opd")==0 || isdigit(*s[temp_pos])) strcpy(s[temp_pos],char_num[char_pos++]);
			fill_exp(s,n,temp_pos+1,exp_count+1);	
		}
	}
	else if(exp_count<0)
	{
		//printf("ERROR\n");
		return 0;
	}
	else
	{
		//printf("print_test ok0\n");
		calc(s,n);
	}
}

int fill_opd(char *s[],int n)//điền vào các toán hạng cố định
{
	char_pos=0;
	int operand_count=n;
	int i=0;
	while(i<2*n-1)
		if(strcmp(s[i],"opd")==0 && --operand_count>=0)
		{
			strcpy(s[i++],char_num[char_pos++]);
			//operand_count--;
		}
		else if(operand_count<0)
		{
			char_pos=0;
			return 0;	
		}
		else ++i;
	char_pos=0;
	return 1;
}

void take_const_num(int n)// lấy các số cố định
{
	for(int i=0;i<n;++i)
	{
		gets(char_num[i]);
	}
}

int main(void)
{
	int n;
	printf("nhap vao so luong operand:");
	scanf("%d",&n);
	getchar();
	take_const_num(n);
	printf("nhap vao ket qua:");
	scanf("%f",&ket_qua);
	//printf("ok take_num\n");
	char *all[1000][10];
	char *temp[10];
	for(int i=0;i<2*n-1;++i) temp[i]=(char*)malloc(10);
	for(int i=0;i<luy_thua(2,2*n-1);++i) for(int j=0;j<10;++j) all[i][j]=(char*)malloc(10);	
	random_it(temp,all,n,0);
	//printf("ok random_it\n");
	for(int i=0;i<luy_thua(2,2*n-1);++i)
	{
		if(fill_opd(all[i],n))
		{
			fill_exp(all[i],n,0,n-1);
		}
		//else printf("ERROR\n");
	}
	//print_all(all,n);
	printf("END.\n");
	for(int i=0;i<luy_thua(2,2*n-1);++i) for(int j=0;j<2*n-1;++j) free(all[i][j]);
	for(int i=0;i<2*n-1;++i) free(temp[i]);
	//printf("%d\n",luy_thua(2,3));
}