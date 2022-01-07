
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CÁC HÀM BỔ TRỢ
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//hàm tính lũy thừa
int luy_thua(int x, int n)
{
	int temp=1;
	while((n--)>0) temp=temp*x;
	return temp;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//BƯỚC 1:NHẬP VÀO CÁC THÔNG SỐ CỦA BÀI TOÁN
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//kết quả của phép tính muốn làm đúng để float vì phép chia tạo ra số thực
float ket_qua;

//mảng 2 chiều dưới đây là chỗ để lưu các số của bài toán dùng ở đây và ở một chỗ ở dưới nữa
char char_num[10][10];
//hàm nhập vào các số cố định của bải toán

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void take_const_num(int n)
{
	for(int i=0;i<n;++i)
	{
		printf("Type in the operand %d: ",i+1);
		do
		{
			gets(char_num[i]);
			if(strlen(char_num[i]) == 0)
			{
				printf("\nSorry you're so stupid\n Retype the operand %d: ",i+1);
			}
		}
		while(strlen(char_num[i]) == 0);

	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//BƯỚC 2:RANDOM VỊ TRÍ TOÁN TỬ VÀ TOÁN HẠNG
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//hàm điền vào các toán hạng cố định và không làm tăng thêm các trường hợp
int char_pos=0;//cái này để lấy số trong mảng 2 chiều đã lưu các số của bài toán ở trên
int fill_operand(int n,char *s[])
{
	char_pos=0;
	int operand_count=n;
	int i=0;
	while(i<2*n-1)
		if(strcmp(s[i],"opd")==0 && --operand_count>=0)
		{
			strcpy(s[i++],char_num[char_pos++]);
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
//hàm điền vào các toán tử có làm tăng thêm rất nhiều trường hợp và tính luôn kết quả bằng hàm calc_RPN và kiểm tra nó luôn
int fill_expression(int n,char *s[],int temp_pos,int exp_count)
{
	//printf("ok%d",temp_pos);
	if(temp_pos<n*2-1 && exp_count>=0)//lần trước mình trừ luôn ở lúc so sánh là sai kiểu k cần biết thỏa mãn hay k đều trừ dẫn đến bị thiếu trường hợp
	{
		if
		(	strcmp(s[temp_pos],"exp")==0 ||
			strcmp(s[temp_pos],"+")==0   ||
			strcmp(s[temp_pos],"-")==0   ||
			strcmp(s[temp_pos],"*")==0   ||
			strcmp(s[temp_pos],"/")==0/*   ||
			strcmp(s[temp_pos],"%")==0     ) */
		)
		{
			strcpy(s[temp_pos],"+");fill_expression(n,s,temp_pos+1,exp_count-1);
			strcpy(s[temp_pos],"-");fill_expression(n,s,temp_pos+1,exp_count-1);
			strcpy(s[temp_pos],"*");fill_expression(n,s,temp_pos+1,exp_count-1);
			strcpy(s[temp_pos],"/");fill_expression(n,s,temp_pos+1,exp_count-1);
			/*strcpy(s[temp_pos],"%");fill_expression(n,s,temp_pos+1,exp_count);*/
		}
		else
		{
			fill_expression(n,s,temp_pos+1,exp_count);//cái này là lúc tìm thấy opd thì sẽ next(tức bỏ qua) và phải cộng bù cái exp_count	
		}
	}
	else if(exp_count<0)
	{
		//printf("ERROR\n");
		//phải có bước này trước calc_RPN vì có trường hợp dùng hết toán tử tức trường hợp lỗi sẽ cần return để ngắt
		return 0;
	}
	else
	{
		//printf("print_test ok0\n");
		calc_RPN(n,s);
	}
}
//copy ramdon dạng opd và exp sang một biến mới để tránh trường hợp dùng luôn bản nguyên thủy
void copy_temp_to_copied(int n,char *temp[],char *copied_s[])
{
	for(int j=0;j<2*n-1;++j) strcpy(copied_s[j],temp[j]);
	//printf("ok stored\n");
}
//hàm random vị trí của các toán tử và toán hạng(dạng 1010101), rồi fill_operand và fill_expression và  tính luôn 
int random_it(int n,char *s[],char *all[][2*n-1],int temp_pos)
{
	if(temp_pos<2*n-1)
	{
		strcpy(s[temp_pos],"opd");random_it(n,s,all,temp_pos+1);
		strcpy(s[temp_pos],"exp");random_it(n,s,all,temp_pos+1);
		return 1;
	}
	else
	{
		char *copied_s[2*n-1];
		for(int i=0;i<2*n-1;++i) copied_s[i]=(char*)malloc(10*sizeof(char));

		copy_temp_to_copied(n,s,copied_s);
		if(fill_operand(n,copied_s)) fill_expression(n,copied_s,0,n-1);

		for(int i=0;i<2*n-1;++i) free(copied_s[i]);
		return 0;
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//BƯỚC 3:TÍNH NÓ THỬ NÓ VÀ IN RA NÓ
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//OLD version of print_test đọc đéo hiểu
void print_test_old(int n,char *s[])//in ra trường hợp đang test tại baất kỳ thời điểm nào bạn muốn
{
	printf("|");
	for(int i=0;i<=2*n-2;++i)
		printf(" %s ",s[i]);
	printf("|");
}

// NEW version of print_test đọc dễ hiểu 
//hàm này sẽ lưu các phần tử đệ quy theo kiểu nửa số nửa chữ kiểu n3 + 3 hoặc chỉ có số
void store_to_print_test_new(int n,char *copied_s[],int current_pos_copied_s,char *storage_recursive_print_test[],int storage_recursive_pos){
	storage_recursive_print_test[storage_recursive_pos][0]='\0';
	strcat(storage_recursive_print_test[storage_recursive_pos],"(");
	strcat(storage_recursive_print_test[storage_recursive_pos],copied_s[current_pos_copied_s-2]);
	strcat(storage_recursive_print_test[storage_recursive_pos],copied_s[current_pos_copied_s]);
	strcat(storage_recursive_print_test[storage_recursive_pos],copied_s[current_pos_copied_s-1]);
	strcat(storage_recursive_print_test[storage_recursive_pos],")");
}

//hàm in đệ quy này sẽ in theo số hiệu từ to về nhỏ nên chắc chắn là chuẩn hàm in này cũng sẽ cần sửa lại

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void print_test_new(int n,char *storage_recursive_print_test[], int storage_recursive_pos)
{
	int copied_storage_recursive_pos=storage_recursive_pos;
	for(int i=0;i<strlen(storage_recursive_print_test[storage_recursive_pos]);++i){
		if(storage_recursive_print_test[copied_storage_recursive_pos][i]=='n')//khi gặp dấu hiệu
		{
			print_test_new(n,storage_recursive_print_test,storage_recursive_print_test[storage_recursive_pos][++i]-'0');// sẽ đọc ký tự tiếp theo và thêm i để bỏ qua ký tự này
		}
		else printf("%c",storage_recursive_print_test[copied_storage_recursive_pos][i]);
	}
	//printf("%s\n",storage_recursive_print_test);
}


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
char num_to_char(int num)
{
 	switch(num)
 	{
 		case 0:return'0';
 		case 1:return'1';
 		case 2:return'2';
 		case 3:return'3';
 		case 4:return'4';
 		case 5:return'5';
 		case 6:return'6';
 		case 7:return'7';
 		case 8:return'8';
 		case 9:return'9';
 	}
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
int char_to_num(char c)
{
	switch(c)
	{
		case'0':return 0;
		case'1':return 1;
		case'2':return 2;
		case'3':return 3;
		case'4':return 4;
		case'5':return 5;
		case'6':return 6;
		case'7':return 7;
		case'8':return 8;
		case'9':return 9;
	}
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
void free_memory(int n,char *s[])
{
	for(int i=0;i<n;++i) free(s[i]);
}
//hàm tính RPN và nếu đúng kết quả sẽ in ra màn hình mảng đang test

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
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
	char *storage_recursive_print_test[n-1];//mảng này lưu các phần tử của đệ quy
	int storage_recursive_pos=0;
	for(int i=0;i<n-1;++i)
	{
		storage_recursive_print_test[i]=(char*)malloc(21*sizeof(char*));
	}
	//-----------------------------------------------------------------------
	for(int i=0;i<=2*n-2;++i)
		if(isdigit(*s[i])!=0 && operand_count>=0)
		{
			//đúng là số
			get_num(s[i]);
			--operand_count;
			strcpy(copied_s[current_pos_copied_s++],s[i]);
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
			store_to_print_test_new(n,copied_s,current_pos_copied_s,storage_recursive_print_test,storage_recursive_pos);
			current_pos_copied_s-=2;
			//strcpy(copied_s[current_pos_copied_s++],"n");
			copied_s[current_pos_copied_s][0]='n';// n stands for notation để nhận biết đệ quy
			copied_s[current_pos_copied_s][1]=num_to_char(storage_recursive_pos);//cái này để lưu vị trí của phần rtuwr đệ quy khi đọc xâu đến đây
			copied_s[current_pos_copied_s][2]='\0';
			storage_recursive_pos++;
			current_pos_copied_s++;
		}
		else {/*printf("ERROR\n");*/ return 0;};
	if(int_num[int_pos-1]==ket_qua) 
	{
		//print_test_old(n,s);
		print_test_new(n,storage_recursive_print_test,storage_recursive_pos-1);	
		printf("=%6.1f\n",int_num[int_pos-1]);	
	}
	/*for(int i=0;i<n-1;++i)
	{
		printf("i:%d:%s\n",i,storage_recursive_print_test[i]);
	}*/
	//print_test_old(n,s);printf("=%6.1f\n",int_num[int_pos-1]);
	int_pos=0;//reset vị trí trong mảng int_num về 0 để tiếp nhận trường hợp mới
	free_memory(n-1,storage_recursive_print_test);
	free_memory(2*n-1,copied_s);
	return 1;
}
















//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void do_it_all(){
	int n;
	printf("\nHow many operands do you want?\nNOTE: Please Input UNDER 6 ( e.g. 2,3,4,5) due to low RAM (4GB)\nYour Answer:");
	do
	{
		scanf("%d",&n);
		if(n<2 || n>5 || isdigit(n))
		{
			getchar();
			printf("Sorry you're so stupid\nRetype it: ");
		}
	}
	while(n<2 || n>5 || isdigit(n));
	getchar();
	take_const_num(n);
	printf("Type in the result you wants: ");
	scanf("%f",&ket_qua);
	getchar();
	//printf("ok take_num\n");
	char *all[luy_thua(2,2*n-1)][2*n-1];
	char *temp[2*n-1];
	for(int i=0;i<2*n-1;++i) temp[i]=(char*)malloc(10*sizeof(char));
	for(int i=0;i<luy_thua(2,2*n-1);++i) for(int j=0;j<2*n-1;++j) all[i][j]=(char*)malloc(10*sizeof(char));	
	random_it(n,temp,all,0);
	//printf("ok random_it\n");
	for(int i=0;i<luy_thua(2,2*n-1);++i)
	{
		if(fill_operand(n,all[i]))
		{
			fill_expression(n,all[i],0,n-1);//fill expression và tình luôn kết quả cho ra màn hình
		}
		//else printf("ERROR\n");
	}
	//print_all(all,n);
	printf("END.\n");
	for(int i=0;i<luy_thua(2,2*n-1);++i) for(int j=0;j<2*n-1;++j) free(all[i][j]);
	for(int i=0;i<2*n-1;++i) free(temp[i]);
}


int main(void)
{
	while(1)
	do_it_all();
} 
