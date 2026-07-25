#include "llist.h"

#define MAX 10

//学生结构体为例
struct cls_t{
	char name[64];
	int id;
	int age;
	char sex;
	float lin;
	float c;
	float sum;
};

//==============cmp==================
int cmp_name(const void *d1, const void *d2)
{
	return strcmp(((struct cls_t *)d1)->name, (char *)d2);
}
int cmp_id(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->id - *(int *)d2);
}
int cmp_age(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->age - *(int *)d2);
}
int cmp_sex(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->sex - *(char *)d2);
}

//==============mod==================
void mod_name(void *d1, const void *d2)
{
	strcpy(((struct cls_t *)d1)->name, (char *)d2);
}
void mod_id(void *d1, const void *d2)
{
	(((struct cls_t *)d1)->id = *(int *)d2);
}
void mod_age(void *d1, const void *d2)
{
	 (((struct cls_t *)d1)->age = *(int *)d2);
}
void mod_sex(void *d1, const void *d2)
{
	 (((struct cls_t *)d1)->sex = *(char *)d2);
}


//==============sort================
int sort_name(const void *d1, const void *d2)
{
	return strcmp(((struct cls_t *)d1)->name, ((struct cls_t *)d2)->name);
}
int sort_id(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->id - ((struct cls_t *)d2)->id);
}
int sort_age(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->age - ((struct cls_t *)d2)->age);
}
int sort_sex(const void *d1, const void *d2)
{
	return (((struct cls_t *)d1)->sex - ((struct cls_t *)d2)->sex);
}


int sort_sum(const void *d1, const void *d2)
{
	float f;

	f = ((struct cls_t *)d1)->sum - ((struct cls_t *)d2)->sum;
	/*printf("f : %f\n", f);*/
	//0.000534
	if (f > -0.005 && f < 0.005)
		return 0;
	else if (f > 0.00001)
		return 1;
	else
		return -1;
		
}

void ls(const void *data)
{
	struct cls_t *cls = (struct cls_t *)data;
	printf("name : %s id : %d age : %d sex : %c lin : %.2f c : %.2f sun : %.2f\n", cls->name, cls->id, cls->age, cls->sex, cls->lin, cls->c, cls->sum);

}



int main(int argc, char *argv[])
{
	int i;
	struct cls_t cls, *p_cls = NULL;		//临时接受用户输入
	LLIST *handle = NULL;
	int ret;
	struct cls_t stu = {"tom", 10086, 20, 'M', 88.99, 99.88, 88.99 + 99.88};

	int index;
	char name[64];
	char name1[64];
	int id;
	int age;
	char sex = 'M';
	char sex1 = 'F';

	if (argc == 2)
	{
		printf("load ...\n");
		handle = llist_load("./cls.db");
		ERRP(NULL == handle, llist_load, goto ERR1);

		llist_travel_next(handle , ls);
		
		return 0;
	}


	//初始化handle 
	handle = llist_creat(sizeof(struct cls_t));
	ERRP(NULL == handle, llist_creat, goto ERR1);


	//循环接受用户输入
	for (i = 0; i < MAX; i++)
	{
		
		snprintf(cls.name, sizeof(cls.name), "cls_%c%c", rand() % 26 + 'A', rand() % 26 + 'a');
		cls.id = 1122000 + rand() % 1000;
		cls.age = rand() % 3 + 17;
		cls.sex = "MF"[rand() % 2];
		cls.lin = 30.0 * (rand() / (RAND_MAX + 1.0)) + 70;
		cls.c = 20.0 * (rand() / (RAND_MAX + 1.0)) + 80;
		cls.sum = cls.lin + cls.c;

		//添加数据到链表结尾
		/*ret = llist_insert_end(handle, &cls);*/
		ret = llist_insert_front(handle, &cls);
		ERRP(ret == -1, llist_insert_end, goto ERR2);
		/*ls (&cls);*/
	}

	llist_travel_next(handle, ls);
	printf("num : %d\n", llist_num(handle));
	printf("================\n");
/*
 *    sex = 'M';
 *    sex1 = 'F';
 *
 *    llist_mod_all(handle, &sex, cmp_sex, &sex1, mod_sex);
 */
	llist_sort(handle, sort_sum, DESCENDING);
	llist_travel_next(handle, ls);
	llist_store(handle, "cls.db");
	printf("sizeof(cls_t) : %d\n", sizeof(struct cls_t));
    /*
	 *sex = 'M';
	 *llist_travel_next(llist_find_all(handle, &sex, cmp_sex), ls);
     */

/*
 *    age = 21;
 *
 *    p_cls = llist_find_front(handle, &age, cmp_age);
 *    if (NULL == p_cls)
 *    {
 *        printf("no match info!\n");
 *    }
 *    else
 *    {
 *        ls(p_cls);
 *    }
 */
	/*llist_del_all(handle, &sex, cmp_sex);*/
/*
 *    printf("input del index : ");
 *    scanf("%d", &index);
 *
 *    llist_del_index(handle, index);
 */
	/*llist_travel_next(handle, ls);*/
	printf("num : %d\n", llist_num(handle));


    /*
	 *GETLINES("input mod name1 : ", name);
	 *GETLINES("input mod name2 : ", name1);
     */
    /*
	 *printf("input mod age : ");
	 *scanf("%d", &age);
     */

	/*llist_mod_front(handle, name, cmp_name, &age, mod_age);*/
    /*
	 *llist_mod_front(handle, name, cmp_name, name1, mod_name);
	 *llist_travel_next(handle, ls);
     */

	
/*
 *    printf("input find index : ");
 *    scanf("%d", &index);
 *
 *    p_cls = llist_find_index(handle, index);
 *    if (NULL == p_cls)
 *    {
 *        printf("no find!\n");
 *    }
 *    else
 *    {
 *        ls(p_cls);
 *    }
 */

/*
 *    GETLINES("input del name : ", name);
 *
 *    llist_del_front(handle, name, cmp_name);
 *    llist_travel_next(handle, ls);
 *    printf("================\n");
 *    printf("input del id : ");
 *    scanf("%d", &id);
 *    llist_del_front(handle, &id, cmp_id);
 *    llist_travel_next(handle, ls);
 *    printf("================\n");
 *    printf("input del age : ");
 *    scanf("%d", &age);
 *    llist_del_front(handle, &age, cmp_age);
 *    llist_travel_next(handle, ls);
 *    printf("================\n");
 *
 */


/*
 *    printf("input insert index : ");
 *    scanf("%d", &index);
 *
 *    llist_insert_index(handle, &stu, index);
 *    llist_travel_next(handle, ls);
 */


	llist_destroy(&handle);

	return 0;
ERR2:
	llist_destroy(&handle);
ERR1:
	return -1;
}
