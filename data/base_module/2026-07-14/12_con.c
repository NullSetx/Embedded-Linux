#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>

#define FLAG 1
#define AA	0
#define BB 	0
#define CC  3

int main(void)
{
/*
 *    #if 1
 *    printf("hello!\n");
 *    #endif
 *
 *    #if FLAG
 *    printf("world!\n");
 *    #endif
 *
 *    #if FLAG
 *        printf("AA!\n");
 *    #else
 *        printf("BB!\n");
 *    #endif
 */

	#if AA
		printf("AA!\n");
	#elif BB
		printf("BB!\n");
	#elif CC
		printf("CC!\n");
	#else
		printf("other!\n");
	#endif	
	return 0;
}
