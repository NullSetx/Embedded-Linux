#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <time.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>

typedef void (PRI)(void *);

//定义定时器
struct timer_t{
	int time;//定时器时间
	int count_time;//累加定时器累加器
	PRI *print;
	void *data;
	int flag;//0 表示循环  1 表示不循环

	struct timer_t *next;
	struct timer_t *prev;
};

//定义全局head  双向 循环 链表
struct timer_t head = {.next = &head, .prev = &head};

void ls(void *data)
{
	printf("%d\n", (int *)data);
}

void destroy(void)
{
	struct timer_t *tail = NULL;
	struct timer_t *save = NULL;
	printf("destroy!\n");
	for (tail = head.next; tail != &head; tail = save)
	{
		save = tail->next;
		free(tail);
		tail = NULL;
	}
}
void add_timer(int time, PRI *func, void *data, int flag)
{
	struct timer_t *new = NULL;

	//定时器属性添加到定时器节点信息中
	new = (struct timer_t *)malloc(sizeof(struct timer_t));
	ERRP(new == NULL, malloc, goto ERR1);

	new->time = time;
	new->count_time = 0;
	new->print = func;
	new->data = data;
	new->flag = flag;

	//节点链接到定时器头节点中
	//尾插
	new->next = &head;
	new->prev = head.prev;
	head.prev->next = new;
	head.prev = new;
	
	//头插
	return ;
ERR1:
	return ;
}



void travel(int sig)
{
	struct timer_t *tail = NULL;
	struct timer_t *save = NULL;

	for (tail = head.next; tail != &head; tail = save)
	{
		save = tail->next;
		tail->count_time++;
		if (tail->count_time == tail->time)
		{
			tail->print(tail->data);
			tail->count_time = 0;
			if (tail->flag)
			{
				tail->next->prev = tail->prev;
				tail->prev->next = tail->next;
				free(tail);
				tail = NULL;
			}
		}
	}
}
void init_timer(int t)
{
	
	//2捕捉定时器信号
	ERRP(signal(SIGALRM, travel) == SIG_ERR, signal, goto ERR1);


	//1 设置定时器
	struct itimerval it ;

	it.it_value.tv_sec = 2;
	it.it_value.tv_usec = 1000;
	it.it_interval.tv_sec = t;
	it.it_interval.tv_usec = 0;
	
	ERRP(setitimer(ITIMER_REAL, &it, NULL) == -1, setitimer, goto ERR1);


	return ;
ERR1:
	return ;

}



int main(int argc, char *argv[])
{
	//1 初始化定时器
	init_timer(1);

	//2 添加定时器
	add_timer(1, ls, (void *)11111, 0);
	add_timer(3, ls, (void *)33333, 1);
	add_timer(5, ls, (void *)55555, 0);
	add_timer(6, ls, (void *)66666, 0);
	add_timer(8, ls, (void *)88888, 1);
	add_timer(15, ls, (void *)1515, 1);

	atexit(destroy);

	getchar();//睡眠方式执行
	return 0;
}









