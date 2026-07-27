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

int main(int argc, char *argv[])
{
	time_t t, ti;
	struct tm *tm = NULL;

	t = time(&ti);
	printf("t : %d\n", t);
	printf("ti : %d\n", ti);

	printf("time : %s\n", ctime(&t));
	/*tm = gmtime(&t);*/
	tm = localtime(&t);
	PRI_D(tm->tm_sec);         /* seconds */
	PRI_D(tm->tm_min);         /* minutes */
	PRI_D(tm->tm_hour);        /* hours */
	PRI_D(tm->tm_mday);        /* day of the month */
	PRI_D(tm->tm_mon + 1);         /* month */
	PRI_D(tm->tm_year + 1900);        /* year */
	PRI_D(tm->tm_wday);        /* day of the week */
	PRI_D(tm->tm_yday);        /* day in the year */
	PRI_D(tm->tm_isdst);       /* daylight saving time */

	printf("%d-%d-%d %d:%d:%d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour + 8, tm->tm_min, tm->tm_sec);
	return 0;
}
