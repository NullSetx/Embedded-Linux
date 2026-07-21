#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	//二维数组  => 数组指针
	char name[10][10] = {"tom", "jim", "mary"};
	char (*p)[10] = NULL;
	char *q[10] = {"tom", "jim", "mary"};//指针数组
	p = name;

	/*q = name;*/

	strcpy(p[0], "zhangsan");

	/*strcpy(q[0], "lisi");*/
	q[0] = "lisi";

	for (i = 0; i < 3; i++)
	{
		/*printf("%s \n", name[i]);*/
		printf("%s \n", q[i]);
	}


	return 0;
		
}
