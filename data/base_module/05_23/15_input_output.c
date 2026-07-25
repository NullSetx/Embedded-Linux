#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	int a, b;
	char ch;

	printf("please input number : ");
	scanf("%d", &a);

	printf("a : %d\n", a);

	getchar();
	printf("please input number : ");
	scanf("%c", &ch);
	/*scanf("%c", &ch);*/
	/*scanf("%d", &b);*/

	printf("ch : %c\n", ch);
	return 0;
}
