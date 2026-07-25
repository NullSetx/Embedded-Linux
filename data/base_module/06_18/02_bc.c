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


void rever(char s[])
{
	int i, len = strlen(s);
	char tmp;
	//hello = > 5
	for (i = 0; i < len / 2; i++)
	{
		tmp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = tmp;
	}
}

int main(void)
{
	char s1[1024] = {};
	char s2[1024] = {};
	char s3[1024] = {};
	int min, max;
	int i;

	printf("input string : ");
	fgets(s1, sizeof(s1), stdin);
	if (s1[strlen(s1) - 1] == '\n')
		s1[strlen(s1) - 1] = '\0';

	printf("input string : ");
	fgets(s2, sizeof(s2), stdin);
	if (s2[strlen(s2) - 1] == '\n')
		s2[strlen(s2) - 1] = '\0';

	min = strlen(s1) > strlen(s2) ? strlen(s2) : strlen(s1);
	max = strlen(s1) > strlen(s2) ? strlen(s1) : strlen(s2);

	printf("s1 : %*s\n", max + 1, s1);
	printf("s2 : %*s\n", max + 1, s2);

	rever(s1);
	rever(s2);
    /*
	 *printf("s1 : %s\n", s1);
	 *printf("s2 : %s\n", s2);
     */

	for (i = 0; i < min; i++)
	{
		s3[i + 1] = (s3[i] + (s1[i] - 48) + (s2[i] - 48)) / 10;
		s3[i] = (s3[i] + (s1[i] - 48) + (s2[i] - 48)) % 10 + 48;
	}

	for (; i < max; i++)
	{
		s3[i + 1] = (strlen(s1) > strlen(s2) ? ((s1[i] - 48) + s3[i]) / 10 : ((s2[i] - 48) + s3[i]) / 10 );
		s3[i] = (strlen(s1) > strlen(s2) ? ((s1[i] - 48) + s3[i]) % 10 + 48 : ((s2[i] - 48) + s3[i]) % 10 + 48);
	}
	if (s3[i] == 1)
		s3[i] = '1';

	rever(s3);
	printf("s3 : %*s\n", max + 1, s3);
	return 0;
}
