#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//实现切割
int cut_word(char *s, char **t, char ch)
{
	int count = 0;

	t[count++] = s;
	while (*s != '\0')
	{
		if (*s == ch)
		{
			*s = '\0';
			t[count++] = s + 1;
		}
		s++;
	}
	return count;
}

int main(void)
{
	int i, j;
	char buf[] = "12:12,9:51,19:03,4:46,23:27,12:01,11:53,9:00,20:02";
	//指针数组；数组，数组每一个成员都是指针
	char *t[10] = {};
	int count;
	char *tmp = NULL;
	int len = 0;
	char s[1024] = {};

	printf("%s\n", buf);
	count = cut_word(buf, t, ',');

	for (i = 0; i < count; i++)
	{
		printf("%s ", t[i]);
	}
	putchar(10);

	for (i = 0; i < count; i++)
	{
		for (j = i + 1; j < count; j++)
		{
			if (atoi(t[i]) > atoi(t[j]))//小时
			{
				tmp = t[i];
				t[i] = t[j];
				t[j] = tmp;
			}
			else if (atoi(t[i]) == atoi(t[j]) && atoi(strchr(t[i], ':') + 1) > atoi(strchr(t[j], ':') + 1))//分钟
			{
				tmp = t[i];
				t[i] = t[j];
				t[j] = tmp;
			
			}
		}
	}
	for (i = 0; i < count; i++)
	{
		printf("%s ", t[i]);
	}
	putchar(10);

	for (i = 0; i < count; i++)
	{
		memmove(s + len, t[i], strlen(t[i]));
		len += strlen(t[i]);
		memmove(s + len, ",", 1);
		len += 1;
	}
	s[len - 1] = '\0';
	strcpy(buf, s);
	printf("%s\n", s);
	printf("%s\n", buf);

	return 0;
}
