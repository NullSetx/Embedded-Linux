#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <share.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int ret;
	struct stat s;
	
	ret = stat(argv[1], &s);
	ERRP(ret == -1, stat, goto ERR1);

	PRI_D(s.st_dev);     /* ID of device containing file */
	PRI_D(s.st_ino);     /* inode number */
	PRI_O(s.st_mode);    /* protection */
	PRI_D(s.st_nlink);   /* number of hard links */
	PRI_D(s.st_uid);     /* user ID of owner */
	PRI_D(s.st_gid);     /* group ID of owner */
	PRI_D(s.st_rdev);    /* device ID (if special file) */
	PRI_D(s.st_size);    /* total size, in bytes */
	PRI_D(s.st_blksize); /* blocksize for file system I/O */
	PRI_D(s.st_blocks);  /* number of 512B blocks allocated */
	PRI_D(s.st_atime);   /* time of last access */
	PRI_D(s.st_mtime);   /* time of last modification */
	PRI_D(s.st_ctime);   /* time of last status change */

	return 0;
ERR1:
	return -1;
}
