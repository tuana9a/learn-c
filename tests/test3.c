
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
	char* s[3];
	char a[] = "12";
	char b[] = "ba";
	char c[] = "4";
	//strcpy(s[0],a);
	//strcpy(s[1],b);
	//strcpy(s[2],c);
	s[0] = a;
	s[1] = b;
	s[2] = c;
	printf("%d\n", isdigit(*s[0]));
	printf("%d\n", isdigit(*s[1]));
	printf("%d\n", isdigit(*s[2]));
}
