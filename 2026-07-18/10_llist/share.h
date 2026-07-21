#ifndef __KEN_SHARE_H__
#define __KEN_SHARE_H__

#include <stdio.h>
#include <string.h>

#define GETLINES(info, buf)				\
	do{									\
		printf(info);						\
		fgets(buf, sizeof(buf), stdin);		\
		if (buf[strlen(buf) - 1] == '\n')	\
			buf[strlen(buf) - 1] = '\0';	\
	}while (0)


//容错宏   条件    错误信息  返回值
#define ERRP(con, info, ret) do{					\
							if (con)				\
							{						\
								printf(#info" error line : %d funcname : %s filename : %s\n", __LINE__, __func__, __FILE__);		\
								ret;				\
							}						\
						}while(0)


#define PRI_C(val) printf(#val" : %c\n", val)
#define PRI_D(val) printf(#val" : %d\n", val)
#define PRI_O(val) printf(#val" : %#o\n", val)
#define PRI_H(val) printf(#val" : %#x\n", val)
#define PRI_S(val) printf(#val" : %s\n", val)
#define PRI_P(val) printf(#val" : %p\n", val)

#endif

