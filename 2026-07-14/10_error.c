#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>


//容错宏
#define ERRP(con, info, ret) do{					\
							if (con)				\
							{						\
								printf(#info" error Line:%d File:%s\n",__LINE__,__FILE__);		\
								ret;				\
							}						\
						}while(0)

int main(void)
{
	int ***p = NULL;

	p = (int ***)malloc(sizeof(int **));
	p = NULL;
	ERRP(NULL == p, malloc p, goto ERR1);

    /*
	 *if (NULL == p)
	 *{
	 *    printf("malloc p false!\n");
	 *    return -1;
	 *}
     */

	*p = (int **)malloc(sizeof(int *));
	ERRP(NULL == *p, malloc *p, goto ERR2);
    /*
	 *if (NULL == *p)
	 *{
	 *    free(p);
	 *    printf("malloc *p false!\n");
	 *    return -1;
	 *}
     */

	**p = (int *)malloc(sizeof(int));
	ERRP(NULL == **p, malloc **p, goto ERR3);

/*
 *    if (NULL == **p)
 *    {
 *        free(*p);
 *        free(p);
 *        printf("malloc **p false!\n");
 *        return -1;
 *
 *    };
 */

	***p = 1213;
	ERRP(123 != ***p, data , goto ERR4);


    /*
	 *if (***p != 123)
	 *{
	 *    free(**p);
	 *    free(*p);
	 *    free(p);
	 *    printf("malloc value false!\n");
	 *    return -1;
	 *
	 *}
     */

	free(**p);
	free(*p);
	free(p);
	return 0;
ERR4:
	free(**p);
ERR3:
	free(*p);
ERR2:
	free(p);
ERR1:
	return -1;
}
