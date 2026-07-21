#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


char *my_strcpy(char *dest, const char *src)
{
	int i = 0;
	char *tmp = dest;

	while ((*dest++ = *src++) != '\0')
		;
    /*
	 *while ((dest[i] = src[i++]) != '\0')
	 *    ;
     */
	return tmp;	
	return dest;
}
int main(void)
{
	char dest[128] = {};
	char *p = NULL;

	p = my_strcpy(dest, "hello");

	printf("dest : %s\n", dest);
	printf("p : %s\n", p);
	
	return 0;
}
