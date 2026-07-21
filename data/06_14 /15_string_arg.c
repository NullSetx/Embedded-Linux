#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void init(char s[], int size)
{
	int i;

	for (i = 0; i < size - 1; i++)
	{
		s[i] = rand() % 26 + 'a';
	}
	s[size - 1] = '\0';
}

void display(char s[])
{
	int i = 0;

	while (s[i] != '\0')
	{
		putchar(s[i]);
		i++;
	}
	putchar(10);
}
int main(void)
{
	char s[64];

	init(s, sizeof(s) / sizeof(s[0]));

	printf("s : %s\n", s);
	printf("strlen(s) : %d\n", strlen(s));

	display(s);
	return 0;
}
