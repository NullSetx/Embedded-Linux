#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//定义学生结构体
struct cls_t{
	int age;//4
	float sum;//4
	/*char *name ;//4个字节*/
	char name[];//柔性数组
	//......
};
//1 柔性数组只能在结构体中定义，且必须是最后一个成员。
//2 柔性数组不占结构体内存空间
//3 内存连续分配，访问效率更高，释放简单
//4 申请空间的时候：总内存 = 结构体空间大小 + 柔性数组需要的空间大小
//
int main(void)
{
	//定义学生结构体变量 定义并初始化
	struct cls_t *p = NULL;

	printf("sizeof(struct cls_t) : %d\n", sizeof(struct cls_t));
    p = (struct cls_t *)malloc(sizeof(struct cls_t) + 10);
   /*p->name = (char *)malloc(10);*/
	strcpy(p->name, "tom");
    printf("name : %s\n", p->name);

	free(p);
	//外部接受数据保存在p结构体中
	//
/*
 *    p = (struct cls_t *)malloc(sizeof(struct cls_t));
 *    if (p == NULL)
 *    {
 *        return -1;
 *    }
 *
 *    p->name = (char *)malloc(10);
 *    if (p->name == NULL)
 *    {
 *        free(p);
 *        return -1;
 *    }
 *    strcpy(p->name, "tom");
 *
 *    printf("name : %s\n", p->name);
 *    
 *    free(p->name);
 *    free(p);
 *
 */
	return 0;
}
