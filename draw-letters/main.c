#include<stdio.h>
#include<string.h>
#include"letters.c"

void print(char* s) {
	for (int j = 1;j <= 5;++j) {
		for (int i = 0;i < strlen(s);++i) {
			switch (s[i]) {
			case 'a':print_A(j);break;
			case 'b':print_B(j);break;
			case 'c':print_C(j);break;
			case 'd':print_D(j);break;
			case 'e':print_E(j);break;
			case 'f':print_F(j);break;
			case 'g':print_G(j);break;
			case 'h':print_H(j);break;
			case 'i':print_I(j);break;
			case 'j':print_J(j);break;
			case 'k':print_K(j);break;
			case 'l':print_L(j);break;
			case 'm':print_M(j);break;
			case 'n':print_N(j);break;
			case 'o':print_O(j);break;
			case 'p':print_P(j);break;
			case 'q':print_Q(j);break;
			case 'r':print_R(j);break;
			case 's':print_S(j);break;
			case 't':print_T(j);break;
			case 'u':print_U(j);break;
			case 'v':print_V(j);break;
			case 'w':print_W(j);break;
			case 'x':print_X(j);break;
			case 'y':print_Y(j);break;
			case 'z':print_Z(j);break;
			case ' ':print_space(j);break;
			}
			if (i == strlen(s) - 1) {
				printf("\n");
			}
		}
	}

}

int main(void) {
	char s[100];
	while (1) {
		printf("Type in the String you want to print, Press Ctrl + C to exit:\n");
		fgets(s, 100, stdin);
		print(s);
		printf("\n");
	}
	return 0;
}
