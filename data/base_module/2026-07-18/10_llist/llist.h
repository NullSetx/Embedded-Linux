#ifndef __KEN_LLIST_H__
#define __KEN_LLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <share.h>


typedef enum sort_t{
	ASCENDING,
	DESCENDING
}SORT;

//链表和顺序表区别
//	顺序表的地址空间是连续的
//	链表的地址空间不连续
//
//	顺序表的执行效率要低于链表
//
//线性表 ： 顺序表 链表  栈 队列
//
//

//定义函数指针类型
//注意两点：1 函数返回类型匹配
//          2 函数参数要一一对应 (三一致原则)
typedef void (llist_op_t)(const void *);
//                        内部数据       外部数据
typedef int (llist_cmp_t)(const void *, const void *);
typedef void (llist_mod_t)(void *, const void *);
//                         内部数据      内部数据
typedef int (llist_sort_t)(const void *, const void *);


//双向链表节点信息
struct node_t{
	void *data;//数据域  保存用户数据
	//指针域
	struct node_t *next;//指向下一个节点地址
	struct node_t *prev;//指向上一个节点地址
};

//有头  无序 循环 双向链表
typedef struct llist_t{
	struct node_t head;//所有的数据
	int size;//数据类型
	int num;//数据个数
}LLIST;


//声明函数
//初始化
extern LLIST *llist_creat(int size);

//==============insert===============
//尾插（头的前面）
extern int llist_insert_end(LLIST *handle, void *data);
//头插(头的后面)
extern int llist_insert_front(LLIST *handle, void *data);
extern int llist_insert_index(LLIST *handle, void *data, int index);

//==================del============
extern void llist_del_front(LLIST *handle, void *key, llist_cmp_t *cmp);
extern void llist_del_end(LLIST *handle, void *key, llist_cmp_t *cmp);
extern void llist_del_index(LLIST *handle, int index);
extern void llist_del_all(LLIST *handle, void *key, llist_cmp_t *cmp);
//==============find=============
extern void *llist_find_front(LLIST *handle, void *key, llist_cmp_t *cmp);
extern void *llist_find_end(LLIST *handle, void *key, llist_cmp_t *cmp);
extern void *llist_find_index(LLIST *handle, int index);
extern LLIST *llist_find_all(LLIST *handle, void *key, llist_cmp_t *cmp);
//================mod===============
extern void llist_mod_front(LLIST *handle, void *key1, llist_cmp_t *cmp, void *key2, llist_mod_t *mod);
extern void llist_mod_end(LLIST *handle, void *key1, llist_cmp_t *cmp, void *key2, llist_mod_t *mod);
extern void llist_mod_index(LLIST *handle, int index, void *key2, llist_mod_t *mod);
extern void llist_mod_all(LLIST *handle, void *key1, llist_cmp_t *cmp, void *key2, llist_mod_t *mod);
//=================
extern int llist_num(LLIST *handle);
//========sort==========
extern void llist_sort(LLIST *handle, llist_sort_t *sort, SORT flag);

//========store load===========
extern void  llist_store(LLIST *handle, const char *path);

extern LLIST *llist_load(const char *path);

//============print=======
extern void llist_travel_next(LLIST *handle, llist_op_t *op);
extern void llist_travel_prev(LLIST *handle, llist_op_t *op);

//===============destroy===========
extern void llist_destroy(LLIST **handle);

#endif //LLIST_H



