#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	char *s1 = "hel\0lo";
	/*char s2[] = "hello\0";*/
	char s2[] = {'h', 'e', 'l', 'l', 'o'};

	//sizeof() 求空间大小
	//strlen() 求字符串有效长度
	
	printf("sizeof(s1) = %d strlen(s1) = %d\n", sizeof(s1), strlen(s1));
	//4 5 | 4 5 | 8 5 | 6 5
	printf("sizeof(s2) = %d strlen(s2) = %d\n", sizeof(s2), strlen(s2));
	//20 5 | 4 5 | 6 5 | 6 5
/*
 *    s1 = s2;
 *
 *    printf("s1 : %s\n", s1);
 *    printf("s2 : %s\n", s2);
 *
 *    for (i = 0; i < 5; i++)
 *    {
 *        putchar(s2[i]);
 *    }
 *    putchar(10);
 */
	return 0;
}
