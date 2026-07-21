#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//结构体不可以嵌套，但可以联合
struct CC{
	int c;
};
struct BB{
	int b;
	struct CC c;
};

struct AA{
	int a;
	struct BB b;//联合
};

int main(void)
{
	struct AA a = {123, 789, 1122};

	printf("sizeof(struct AA) = %d\n", sizeof(struct AA));
	printf("a.a = %d\n", a.a);
	printf("a.b.b = %d\n", a.b.b);
	printf("a.b.c.c = %d\n", a.b.c.c);

	/*struct BB b = {456};*/

    /*
	 *printf("AA : a.a = %d\n", a.a);
     */
	/*printf("BB : b.b = %d\n", b.b);*/
	/*printf("AA : a.b = %d\n", a.b.b);*/

	return 0;
}
