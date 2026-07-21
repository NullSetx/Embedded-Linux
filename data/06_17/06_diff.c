#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	
	char s1[128] = "hello";
	char s2[128] = "world";

	//hello => hel lo
	//hello => he llo
	//world => wo rld 
	/*memcpy(s1 + 3, s2 + 2, strlen(s2 + 2) + 1);*/
	/*memcpy(s1 + 3, s1 + 2, strlen(s1 + 2) + 1);*/
	/*memmove(s1 + 3, s1 + 2, strlen(s1 + 2) + 1);*/
	/*memmove(s1 + 3, s2 + 2, strlen(s2 + 2) + 1);*/
	
	printf("s1 : %s\n", s1);//helrld


	return 0;
}
