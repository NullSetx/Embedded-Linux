#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

int a = 1;//BSS
int b = 123; //RO

int main(int argc, char *argv[])
{
	printf("a : %d\n", a);	
	return 0;
}
