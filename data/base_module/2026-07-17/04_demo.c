#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

struct op_t{
	int data;
	struct op_t *p;
};

struct op_t c = {30, NULL};
int main(int argc, char *argv[])
{
	//volatile
	struct op_t a = {0, NULL};
	struct op_t b = {20, NULL};

	a.p = &b;
	b.p = &c;

	printf("a => b = %d\n", a.p->data);
	printf("a => c = %d\n", a.p->p->data);

/*
 *    printf("a : %d\n", a);
 *    printf("b : %d\n", b);
 *
 *    printf("a => b : %d\n", *(&a - 1));
 *    printf("a => c : %d\n", *(&a - 2));
 */
	return 0;
}
