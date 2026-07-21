#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//ctrl + ] : 跳转
//ctrl + o : 返回
/*size_t*/

//求字符串有效长度
// size_t strlen(const char *s);
int str_len(char s[])
{
	int count = 0;

	while (s[count] != '\0')
		count++;

	return count;	
}
int main(void)
{
	int i;
	//"" 初始化会自动补\0
	/*char s[] = "hello\0";*/

	//不会自动添加\0
	/*char s[] = {'h', 'e', 'l', 'l', 'o', '\0'};*/

	/*printf("sizeof(s) : %d\n", sizeof(s));*/
	
	char name[64] = "my";

	printf("sizeof(name) : %d\n", sizeof(name));

	printf("len : %d\n", str_len(name));
	printf("len : %d\n", strlen(name));

	for (i = 0; i < strlen(name); i++)
	{
		putchar(name[i]);

	}
	putchar(10);
	i = 0;
	while (name[i] != '\0')
	{
		printf("%c", name[i]);
		i++;
	}
	putchar(10);
    /*
	 *for (i = 0; i < 64; i++)
	 *{
	 *    printf("%c", name[i]);
	 *}
	 *putchar(10);
     */
	return 0;
}
