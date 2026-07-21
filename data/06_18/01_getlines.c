#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

int my_atoi(char s[])
{
	int i = 0;
	int sum = 0;

	while (s[i] != '\0')
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			return sum;
		}
		sum *= 10;
		sum += s[i] - 48;

		i++;
	}

	return sum;
}


int main(void)
{
	char buf[1024];

	printf("input string : ");
	fgets(buf, sizeof(buf), stdin);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';

	printf("buf : %s\n", buf);
	printf("atoi : %d\n", atoi(buf));
	printf("atoi(hello) : %d\n", atoi("hello"));
	printf("atoi(hello123) : %d\n", atoi("hello123"));
	printf("atoi(123hello) : %d\n", atoi("123hello"));
	printf("================\n");
	printf("my_atoi : %d\n", my_atoi(buf));
	printf("my_atoi(hello) : %d\n", my_atoi("hello"));
	printf("my_atoi(hello123) : %d\n", my_atoi("hello123"));
	printf("my_atoi(123hello) : %d\n", my_atoi("123hello"));
	return 0;
}
