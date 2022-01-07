#include<stdio.h>
#include<string.h>
#include"letters.c"

void print(char* s) {
	for (int j = 1;j <= 5;++j) {
		for (int i = 0;i < strlen(s);++i) {
			switch (s[i]) {
			case 'a':printA(j);break;
			case 'b':printB(j);break;
			case 'c':printC(j);break;
			case 'd':printD(j);break;
			case 'e':printE(j);break;
			case 'f':printF(j);break;
			case 'g':printG(j);break;
			case 'h':printH(j);break;
			case 'i':printI(j);break;
			case 'j':printJ(j);break;
			case 'k':printK(j);break;
			case 'l':printL(j);break;
			case 'm':printM(j);break;
			case 'n':printN(j);break;
			case 'o':printO(j);break;
			case 'p':printP(j);break;
			case 'q':printQ(j);break;
			case 'r':printR(j);break;
			case 's':printS(j);break;
			case 't':printT(j);break;
			case 'u':printU(j);break;
			case 'v':printV(j);break;
			case 'w':printW(j);break;
			case 'x':printX(j);break;
			case 'y':printY(j);break;
			case 'z':printZ(j);break;
			case ' ':printSpace(j);break;
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
