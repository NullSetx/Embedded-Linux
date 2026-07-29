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

void dididi(int sig)
{
    /*
	 *static int count = 0;
	 *if (count == 5)
	 *    return ;
     */
	printf("sig : %d didi ...\n", sig);
	/*count++;*/
	alarm(1);
}

int main(int argc, char *argv[])
{
	int count = 5;
	signal(SIGALRM, dididi);

	//定闹钟
	alarm(3);
    /*
	 *while (1)
	 *{
	 *    alarm(3);
	 *    sleep(3);
	 *}	
     */

	/*getchar();*/
	while (count--)
	{
		pause();//等到任意一个信息
		/*count++;*/
	}
	return 0;
}
