#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
	char ch;

	printf("input char : ");
	scanf("%c", &ch);

	printf("ch : %c\n", ch);
	//判断是否是字母 大写和小写
	//'a' => 97
	//'A' => 65
	if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
	{
		if (ch >= 'a')
		{
			//一定是小写
			printf("ch : %c\n", ch - 32);
		}
		else
		{
			printf("ch : %c\n", ch + 32);
		}
	}
	else
	{
		printf("ch : %c\n", ch);
	}
	return 0;
}
