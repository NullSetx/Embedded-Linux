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

int main(int argc, char *argv[])
{
	int i;
	//1 创建孤儿进程
	//
	if (fork() != 0)
	{
		printf("parent : pid = %d ppid = %d gid = %d %d sid = %d\n", 
			getpid(), getppid(), getpgid(getpid()), getpgrp(), 
			getsid(getpid()));
		exit(0);
	}
	usleep(100);
	//2 创建新的会话
	setsid();
	//child => orphan
	printf("child : pid = %d ppid = %d gid = %d %d sid = %d\n", 
		getpid(), getppid(), getpgid(getpid()), getpgrp(), getsid(getpid()));

	printf("child : pwd = %s\n", get_current_dir_name());

	//4 切换工作目录
	chdir("/");
	printf("child : pwd = %s\n", get_current_dir_name());

	//5 修改umask值
	umask(0);

	//6 退出 发送信号 -> 接受 => exit
	
	//3 关闭文件描述符
	for (i = 0; i < 1024; i++)
	{
		close(i);		
	}


	/*getchar();*/
	while (1)
		;
	return 0;
}










