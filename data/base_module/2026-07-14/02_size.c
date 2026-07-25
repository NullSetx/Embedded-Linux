#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

struct op_t{
	char ch;
	double d;//8
};
int main(void)
{
	printf("sizeof(struct op_t) : %d\n", sizeof(struct op_t));
	return 0;
}
