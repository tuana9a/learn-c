
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

//OLD print_test
void print_test_old(int n,char *s[])//in ra trường hợp đang test tại baất kỳ thời điểm nào bạn muốn
{
	printf("|");
	for(int i=0;i<=2*n-2;++i)
		printf("%s",s[i]);
	printf("|");
}

//NEW print_test 
void store_to_print_test_new(int n,char *copied_s[],int current_pos_copied_s,char *storage_recursive_print_test[],int storage_recursive_pos){
	storage_recursive_print_test[storage_recursive_pos][0]='\0';
	strcat(storage_recursive_print_test[storage_recursive_pos],"(");
	strcat(storage_recursive_print_test[storage_recursive_pos],copied_s[current_pos_copied_s-2]);
	strcat(storage_recursive_print_test[storage_recursive_pos],copied_s[current_pos_copied_s]);
	strcat(storage_recursive_print_test[storage_recursive_pos],copied_s[current_pos_copied_s-1]);
	strcat(storage_recursive_print_test[storage_recursive_pos],")");
	
}
void print_test_new(int n,char *storage_recursive_print_test[], int storage_recursive_pos)
{
	int copied_storage_recursive_pos=storage_recursive_pos;
	for(int i=0;i<strlen(storage_recursive_print_test[storage_recursive_pos]);++i){
		if(storage_recursive_print_test[copied_storage_recursive_pos][i]=='n') print_test_new(n,storage_recursive_print_test,--storage_recursive_pos);
		else printf("%c",storage_recursive_print_test[copied_storage_recursive_pos][i]);
	}
	//printf("%s\n",storage_recursive_print_test);
}


float int_num[10];//mảng để lưu số trong lúc tính toán trong hàm calc_RPN 
int int_pos=0;//số này là vị trí (index) trong mảng int_num ở trên
void get_num(char *s)//hàm này sẽ chuyển xâu thành số và lưu lại trong mảng int_num và dùng Reverse Polish Notation để tính toán
{
	float temp=0.0;
	while(isdigit(*s))
	{
		temp=10.0*temp + (*s) - '0';
		++s;
	};
	int_num[int_pos++]=temp; 
}
//hàm tính RPN và nếu đúng kết quả sẽ in ra màn hình mảng đang test
int calc_RPN(int n,char *s[])//tính kết quả của 1 trường hợp hoàn chỉnh s return ERROR:0 hoặc SUCESS:1 
{
	int exp_count=n-1,operand_count=n;//biến này là để xử lí những trường hợp mà lỗi nhiều biến hoặc phép tính hơn số lượng giới hạn
	//-----------------------------------------------------------------------
	char *copied_s[2*n-1];//mảng này để làm cái temp sẽ có giá trị gần kiểu như s nhưng sẽ kểu RPN cho recursive print_test
	int current_pos_copied_s=0;
	for(int i=0;i<2*n-1;++i)
	{
		copied_s[i]=(char*)malloc(10*sizeof(char));
	}
	//-----------------------------------------------------------------------
	char *storage_recursive_print_test[n-1];//mảng này lưu các phần tử của đệ quyj
	int storage_recursive_pos=0;
	for(int i=0;i<n-1;++i)
	{
		storage_recursive_print_test[i]=(char*)malloc(21*sizeof(char*));
	}
	//-----------------------------------------------------------------------
	for(int i=0;i<=2*n-2;++i)
	{
		if(isdigit(*s[i])!=0 && operand_count>=0)
		{
			//đúng là số
			get_num(s[i]);
			--operand_count;
			strcpy(copied_s[current_pos_copied_s++],s[i]);
			//printf("OK%d\n",i);
		}
		else if(i>=2 && exp_count>=0)
		{
			//không phải là số
			
			switch(*s[i])
			{
				case '+':if(int_pos >=2){int_num[int_pos-2]=int_num[int_pos-2]+int_num[int_pos-1];int_pos-=1;}else{/*printf("ERROR\n");*/int_pos=0;return 0;};break;//nếu không có in_pos =0 nó sẽ không reset lại toàn bộ và nó lại tính tiếp từ in_pos cũ
				case '-':if(int_pos >=2){int_num[int_pos-2]=int_num[int_pos-2]-int_num[int_pos-1];int_pos-=1;}else{/*printf("ERROR\n");*/int_pos=0;return 0;};break;
				case '*':if(int_pos >=2){int_num[int_pos-2]=int_num[int_pos-2]*int_num[int_pos-1];int_pos-=1;}else{/*printf("ERROR\n");*/int_pos=0;return 0;};break;
				case '/':if(int_pos >=2){int_num[int_pos-2]=int_num[int_pos-2]/int_num[int_pos-1];int_pos-=1;}else{/*printf("ERROR\n");*/int_pos=0;return 0;};break;
				/*case '%':if(int_pos-2>=0){int_num[int_pos-2]=int_num[int_pos-2]%int_num[int_pos-1];int_pos-=1;}else{printf("ERROR\n");return 0;};break;*/
				default:/*printf("ERROR\n");*/break;//return 0;
			}
			strcpy(copied_s[current_pos_copied_s],s[i]);
			store_to_print_test_new(n,copied_s,current_pos_copied_s,storage_recursive_print_test,storage_recursive_pos++);
			current_pos_copied_s-=2;
			strcpy(copied_s[current_pos_copied_s++],"n");
			//printf("OK\n");	
		}
		else
		{
			/*printf("ERROR\n");*/
			return 0;
		};
		//printf("OK\n");
	}
	
	/*if(int_num[int_pos-1]==ket_qua) 
	{
		print_test_old(n,s);
		printf("=%6.1f\n",int_num[int_pos-1]);	
	}*/

	//printf("pos: %d\n",storage_recursive_pos);
	for(int i=0;i<n-1;++i)
	{
		printf("i:%d:%s\n",i,storage_recursive_print_test[i]);
	}	
	print_test_new(n,storage_recursive_print_test,storage_recursive_pos-1);	
	printf("\n\n");
	//print_test_old(n,s);printf("=%6.1f\n",int_num[int_pos-1]);
	//int_pos=0;//reset vị trí trong mảng int_num về 0 để tiếp nhận trường hợp mới
	free_memory(n-1,storage_recursive_print_test);
	free_memory(2*n-1,copied_s);
	return 1;
}

int main()
{
	char *s[]={"3","4","+","4","+"};
	calc_RPN(3,s);
	char *s1[]={"3","4","+","4","+"};
	calc_RPN(3,s1);
	char *s2[]={"3","4","+","4","+"};
	calc_RPN(3,s2);
	char *s3[]={"3","4","+","4","+"};
	calc_RPN(3,s3);
	char *s4[]={"3","4","+","4","+"};
	calc_RPN(3,s4);
	char *s5[]={"3","4","+","4","+"};
	calc_RPN(3,s5);
	char *s6[]={"3","4","+","4","+"};
	calc_RPN(3,s6);
	char *s7[]={"3","4","+","4","+"};
	calc_RPN(3,s7);
	char *s8[]={"3","4","+","4","+"};
	calc_RPN(3,s8);
	char *s9[]={"3","4","+","4","+"};
	calc_RPN(3,s9);
}

void free_memory(int n,char *s[])
{
	for(int i=0;i<n;++i) free(s[i]);
}