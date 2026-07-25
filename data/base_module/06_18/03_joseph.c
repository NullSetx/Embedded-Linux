#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>



int main(void)
{
	int i, m, n;
	char buf[1024];
	char name[10][64];
	int count = 0, out = 0;

	printf("input m and n : ");
	scanf("%d%d", &m, &n);

	printf("m : %d n : %d\n", m , n);

	getchar();
	for (i = 0; i < m; i++)
	{
		printf("input string : ");
		fgets(name[i], sizeof(name[i]), stdin);
		if (name[i][strlen(name[i]) - 1] == '\n')
			name[i][strlen(name[i]) - 1] = '\0';

        /*
		 *fgets(buf, sizeof(buf), stdin);
		 *if (buf[strlen(buf) - 1] == '\n')
		 *    buf[strlen(buf) - 1] = '\0';
         */

		/*strcpy(name[i], buf);	*/
	}

	for (i = 0; i < m; i++)
	{
		printf("%s ", name[i]);
	}
	putchar(10);

	out = m;
	while (1)
	{
		if (out == 0)
		{
			break;
		}
		for (i = 0; i < m; i++)
		{
			if (name[i][0] != '\0')
				count++;

			if (count == n)
			{
				printf("%s ", name[i]);
				//memset(name[i], 0, sizeof(name[i]));
				name[i][0] = '\0';
				out--;
				count = 0;
			}
		}
	}
	putchar(10);
	return 0;
}
