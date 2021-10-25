
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//CÁC HÀM BỔ TRỢ
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//hàm tính lũy thừa
int luy_thua(int x, int n)
{
	int temp = 1;
	while ((n--) > 0)
		temp = temp * x;
	return temp;
}
void free_memory(int n, char *s[])
{
	for (int i = 0; i < n; ++i)
		free(s[i]);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//NHẬP VÀO CÁC THÔNG SỐ CỦA BÀI TOÁN
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//kết quả của phép tính muốn làm đúng để float vì phép chia tạo ra số thực
float ket_qua;

//mảng 2 chiều dưới đây là chỗ để lưu các số của bài toán dùng ở đây và ở một chỗ ở dưới nữa
char char_num[10][10];
//hàm nhập vào các số cố định của bải toán

//hàm kiêm tra xem input có chứa chữ hay không, 1 là có chứa chữ, 0 là không có
int check_const_num_input(int i)
{
	for (int j = 0; j < strlen(char_num[i]); ++j)
	{
		if (isdigit(char_num[i][j]) == 0)
			return 1;
	};
	return 0;
}
void take_const_num(int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("Type in the operand %d (positive interger): ", i + 1);
		do
		{
			gets(char_num[i]);
			if (strlen(char_num[i]) == 0 || strlen(char_num[i]) > 10 || check_const_num_input(i))
			{
				printf("\nSorry you're so stupid\n Retype the operand %d (positive interger): ", i + 1);
			}
		} while (strlen(char_num[i]) == 0 || strlen(char_num[i]) > 10 || check_const_num_input(i));
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//TÍNH THỬ VÀ IN RA
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//OLD version of print_test đọc đéo hiểu
void print_test_old(int n, char *temp[]) //in ra trường hợp đang test tại baất kỳ thời điểm nào bạn muốn
{
	printf("|");
	for (int i = 0; i <= 2 * n - 2; ++i)
		printf(" %s ", temp[i]);
	printf("|");
}

// NEW version of print_test đọc dễ hiểu
//hàm này sẽ lưu các phần tử đệ quy theo kiểu nửa số nửa chữ kiểu n3 + 3 hoặc chỉ có số
void store_to_print_test_new(int n, char *copied_s[], int current_pos_copied_s, char *storage_recursive_print_test[], int storage_recursive_pos)
{
	storage_recursive_print_test[storage_recursive_pos][0] = '\0';
	strcat(storage_recursive_print_test[storage_recursive_pos], "(");
	strcat(storage_recursive_print_test[storage_recursive_pos], copied_s[current_pos_copied_s - 2]);
	strcat(storage_recursive_print_test[storage_recursive_pos], copied_s[current_pos_copied_s]);
	strcat(storage_recursive_print_test[storage_recursive_pos], copied_s[current_pos_copied_s - 1]);
	strcat(storage_recursive_print_test[storage_recursive_pos], ")");
}

//hàm in đệ quy này sẽ in theo số hiệu từ to về nhỏ nên chắc chắn là chuẩn hàm in này cũng sẽ cần sửa lại
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void print_test_new(int n, char *storage_recursive_print_test[], int storage_recursive_pos)
{
	int copied_storage_recursive_pos = storage_recursive_pos;
	for (int i = 0; i < strlen(storage_recursive_print_test[storage_recursive_pos]); ++i)
	{
		if (storage_recursive_print_test[copied_storage_recursive_pos][i] == 'n') //khi gặp dấu hiệu
		{
			print_test_new(n, storage_recursive_print_test, storage_recursive_print_test[storage_recursive_pos][++i] - '0'); // sẽ đọc ký tự tiếp theo và thêm i để bỏ qua ký tự này
		}
		else
			printf("%c", storage_recursive_print_test[copied_storage_recursive_pos][i]);
	}
	//printf("%s\n",storage_recursive_print_test);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
char num_to_char(int num)
{
	switch (num)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	}
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
int string_to_num(char *s)
{
	int result = 0;
	for (int i = 0; i < strlen(s); ++i)
	{
		result = result * 10 + s[i] - '0';
	};
	return result;
}

float int_num[10];	  //mảng để lưu số trong lúc tính toán trong hàm calc_RPN
int int_pos = 0;	  //số này là vị trí (index) trong mảng int_num ở trên
void get_num(char *s) //hàm này sẽ chuyển xâu thành số và lưu lại trong mảng int_num và dùng Reverse Polish Notation để tính toán
{
	float temp = 0.0;
	while (isdigit(*s))
	{
		temp = 10.0 * temp + (*s) - '0';
		++s;
	};
	int_num[int_pos++] = temp;
}

//hàm tính RPN và nếu đúng kết quả sẽ in ra màn hình mảng đang test
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
int calc_RPN(int n, char *s[]) //tính kết quả của 1 trường hợp hoàn chỉnh s return ERROR:0 hoặc SUCESS:1
{
	//-----------------------------------------------------------------------
	char *copied_s[2 * n - 1]; //mảng này để làm cái temp sẽ có giá trị gần kiểu như s nhưng sẽ kểu RPN cho recursive print_test
	int current_pos_copied_s = 0;
	for (int i = 0; i < 2 * n - 1; ++i)
	{
		copied_s[i] = (char *)malloc(10 * sizeof(char));
	}
	//-----------------------------------------------------------------------
	char *storage_recursive_print_test[n - 1]; //mảng này lưu các phần tử của đệ quy
	int storage_recursive_pos = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		storage_recursive_print_test[i] = (char *)malloc(21 * sizeof(char *));
	}
	//-----------------------------------------------------------------------
	for (int i = 0; i <= 2 * n - 2; ++i)
		if (isdigit(*s[i]) != 0)
		{
			//đúng là số
			get_num(s[i]);
			strcpy(copied_s[current_pos_copied_s++], s[i]);
		}
		else
		{
			//không phải là số

			switch (*s[i])
			{
			case '+':
				int_num[int_pos - 2] = int_num[int_pos - 2] + int_num[int_pos - 1];
				int_pos -= 1;
				break;
			case '-':
				int_num[int_pos - 2] = int_num[int_pos - 2] - int_num[int_pos - 1];
				int_pos -= 1;
				break;
			case '*':
				int_num[int_pos - 2] = int_num[int_pos - 2] * int_num[int_pos - 1];
				int_pos -= 1;
				break;
			case '/':
				int_num[int_pos - 2] = int_num[int_pos - 2] / int_num[int_pos - 1];
				int_pos -= 1;
				break;
			}
			strcpy(copied_s[current_pos_copied_s], s[i]);
			store_to_print_test_new(n, copied_s, current_pos_copied_s, storage_recursive_print_test, storage_recursive_pos);
			current_pos_copied_s -= 2;
			//strcpy(copied_s[current_pos_copied_s++],"n");
			copied_s[current_pos_copied_s][0] = 'n';								// n stands for notation để nhận biết đệ quy
			copied_s[current_pos_copied_s][1] = num_to_char(storage_recursive_pos); //cái này để lưu vị trí của phần rtuwr đệ quy khi đọc xâu đến đây
			copied_s[current_pos_copied_s][2] = '\0';
			storage_recursive_pos++;
			current_pos_copied_s++;
		}
	if (int_num[int_pos - 1] == ket_qua)
	{
		//print_test_old(n,s);
		print_test_new(n, storage_recursive_print_test, storage_recursive_pos - 1);
		printf("=%6.1f\n", int_num[int_pos - 1]);
	}
	/*for(int i=0;i<n-1;++i)
	{
		printf("i:%d:%s\n",i,storage_recursive_print_test[i]);
	}*/
	//print_test_old(n,s);printf("=%6.1f\n",int_num[int_pos-1]);
	int_pos = 0; //reset vị trí trong mảng int_num về 0 để tiếp nhận trường hợp mới
	free_memory(n - 1, storage_recursive_print_test);
	free_memory(2 * n - 1, copied_s);
	return 1;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//RANDOM VỊ TRÍ TOÁN TỬ VÀ TOÁN HẠNG
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//hàm điền vào các toán hạng cố định và không làm tăng thêm các trường hợp
int char_pos = 0; //cái này để lấy số trong mảng 2 chiều đã lưu các số của bài toán ở trên
void fill_operand(int n, char *temp[])
{
	char_pos = 0;
	int i = 0;
	while (i < 2 * n - 1)
		if (strcmp(temp[i], "opd") == 0)
		{
			strcpy(temp[i++], char_num[char_pos++]);
		}
		else
			++i;
	char_pos = 0;
}

//hàm random toán tử và tính luôn kết quả bằng hàm calc_RPN
void fill_expression(int n, char *temp[], int temp_pos)
{
	//printf("ok%d",temp_pos);
	if (temp_pos < n * 2 - 1)
	{
		if (strcmp(temp[temp_pos], "exp") == 0 ||
			strcmp(temp[temp_pos], "+") == 0 ||
			strcmp(temp[temp_pos], "-") == 0 ||
			strcmp(temp[temp_pos], "*") == 0 ||
			strcmp(temp[temp_pos], "/") == 0)
		{
			strcpy(temp[temp_pos], "+");
			fill_expression(n, temp, temp_pos + 1);
			strcpy(temp[temp_pos], "-");
			fill_expression(n, temp, temp_pos + 1);
			strcpy(temp[temp_pos], "*");
			fill_expression(n, temp, temp_pos + 1);
			strcpy(temp[temp_pos], "/");
			fill_expression(n, temp, temp_pos + 1);
		}
		else
		{
			fill_expression(n, temp, temp_pos + 1);
		}
	}
	else
	{
		//printf("print_test ok0\n");
		//print_test_old(n,temp);
		//printf("\n");
		calc_RPN(n, temp);
	}
}

//copy random *temp[] dạng opd và exp sang một biến mới để tránh trường hợp không dùng lại được temp
void copy_temp_to_copied(int n, char *temp[], char *copied_temp[])
{
	for (int j = 0; j < 2 * n - 1; ++j)
		strcpy(copied_temp[j], temp[j]);
	//printf("ok stored\n");
}

//hàm random vị trí của các toán tử và toán hạng(dạng 1010101), rồi fill_operand và fill_expression và  tính luôn
int random_it(int n, char *temp[], int temp_pos, int exp_count, int opd_count)
{
	if (
		exp_count > n - 1 ||
		opd_count > n ||
		exp_count == opd_count && temp_pos > 1)
	{
		return 0;
	}
	if (temp_pos == 2 * n - 1)
	{
		char *copied_temp[2 * n - 1];
		for (int i = 0; i < 2 * n - 1; ++i)
			copied_temp[i] = (char *)malloc(10 * sizeof(char));
		copy_temp_to_copied(n, temp, copied_temp);

		fill_operand(n, copied_temp);
		fill_expression(n, copied_temp, 0);

		//printf("\n");
		//print_test_old(n,copied_temp);
		//printf("\n");
		free_memory(n, copied_temp);
		return 0;
	}

	strcpy(temp[temp_pos], "opd");
	random_it(n, temp, temp_pos + 1, exp_count, opd_count + 1);
	strcpy(temp[temp_pos], "exp");
	random_it(n, temp, temp_pos + 1, exp_count + 1, opd_count);
	return 1;
}

int check_string_input(char *s)
{
	for (int j = 0; j < strlen(s); ++j)
	{
		if (isdigit(s[j]) == 0)
			return 1;
	};
	return 0;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void do_it_all()
{
	int n = 0;
	char s[10];
	printf("\nHow many operands do you want?\nNOTE: Please Input positive interger UNDER 10 (e.g. 2,3,..,9)\nYour Answer:");
	do
	{
		gets(s);
		//getchar();
		if (check_string_input(s))
		{
			printf("Sorry you're so stupid\nRetype number of operands(positive interger): ");
			continue;
		}
		n = string_to_num(s);
		if (n < 2 || n > 9)
		{
			// getchar();
			printf("Sorry you're so stupid\nRetype number of operands(positive interger): ");
		}
	} while (n < 2 || n > 9);
	//getchar();
	take_const_num(n);
	printf("Type in the result you wants(positive interger): ");
	do
	{
		gets(s);
		//getchar();
		if (check_string_input(s))
		{
			printf("Sorry you're so stupid\nRetype result you want(positive interger): ");
			continue;
		}
		ket_qua = string_to_num(s);
		break;
	} while (1);

	char *temp[2 * n - 1];
	for (int i = 0; i < 2 * n - 1; ++i)
		temp[i] = (char *)malloc(10 * sizeof(char));
	random_it(n, temp, 0, 0, 0);
}

int main(void)
{
	while (1)
		do_it_all();
}
