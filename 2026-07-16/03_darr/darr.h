#ifndef __KEN_DARR_H__
#define __KEN_DARR_H__



#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>


//定义一个函数指针的类型
typedef void (darr_op_t)(const void *);
//                        内部数据     外部数据
typedef int (darr_cmp_t)(const void *, const void *);
typedef void (darr_mod_t)(void *, const void *);
//                         内部数据      内部数据
typedef int (darr_sort_t)(const void *, const void *);

typedef int  INT;
typedef int IINT;
//抽象数据类型
typedef struct darr_t{
	void *data;//表示数据
	int size;//数据类型
	int num;//数据个数
}DARR;



//初始化handle
DARR *darr_creat(int size);

//==============insert=====================
//            数据长度     原来数据    新添加数据  数据大小
//添加数据到结尾
void darr_insert_end(DARR *handle, const void *data);
//添加数据到开头
void darr_insert_front(DARR *handle, const void *data);
//指定位置插入
void darr_insert_index(DARR *handle, const void *data, int index);

//==============del===========================
//从前往后删除，找到第一个则删除
void darr_del_front(DARR *handle, const void *key, darr_cmp_t *cmp);

//从后往前删除
void darr_del_end(DARR *handle, const void *key, darr_cmp_t *cmp);
//
//指定位置删除
void darr_del_index(DARR *handle, int index);
//
//删除所有
void darr_del_all(DARR *handle, const void *key, darr_cmp_t *cmp);
//================fid===================

void *darr_find_front(DARR *handle, const void *key, darr_cmp_t *cmp);
void *darr_find_end(DARR *handle, const void *key, darr_cmp_t *cmp);
void *darr_find_index(DARR *handle, int index);
DARR *darr_find_all(DARR *handle, const void *key, darr_cmp_t *cmp);
//
// ================mod==========================
// 第一个参数：表示数据
// 第二个参数：表示被修改数据
// 第三个参数：表示查找的方法
// 第四个参数：表示修改数据
// 第五个参数：表示修改的方法
void darr_mod_front(DARR *handle, const void *old_key, darr_cmp_t *cmp, void *new_key, darr_mod_t *mod);
void darr_mod_end(DARR *handle, const void *old_key, darr_cmp_t *cmp, void *new_key, darr_mod_t *mod);
void darr_mod_index(DARR *handle, int index, void *new_key, darr_mod_t *mod);
void darr_mod_all(DARR *handle, const void *old_key, darr_cmp_t *cmp, void *new_key, darr_mod_t *mod);

//===========求数据个数=============
int darr_num(DARR *handle);
//==============sort===============
void darr_sort_ascending(DARR *handle, darr_sort_t *sort);
void darr_sort_descending(DARR *handle, darr_sort_t *sort);

//===========store and load===============

void darr_store(DARR *handle, const char *path);
DARR *darr_load(const char *path);


//
//


//
//
//遍历函数
void darr_travel(DARR *handle, darr_op_t *op);

//销毁
void darr_destroy(DARR **handle);

#endif // DARR_H
