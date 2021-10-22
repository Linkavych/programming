/*
 * A naive stat(1) program
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/sysmacros.h>

int main(int argc, char *argv[]) {

	struct stat buf;
	mode_t mode;
	char type[80];

	if (argc != 2){
		puts("Usage: ./mstat FILENAME");
		exit(EXIT_FAILURE);
	}

	if ((lstat(argv[1], &buf)) < 0) {
		perror("lstat");
		exit(EXIT_FAILURE);
	}

	mode = buf.st_mode;
	printf("FILE: %s\n", argv[1]);
	printf("INODE: %ld\n", buf.st_ino);
	printf("DEVICE: %d, %d\n", major(buf.st_dev), minor(buf.st_dev));

	printf("MODE: %#o\n", buf.st_mode & ~(S_IFMT));
	printf("LINKS: %ld\n", buf.st_nlink);
	printf("UID: %d\n", buf.st_uid);
	printf("GID: %d\n", buf.st_gid);


	if (S_ISLNK(mode))
		strcpy(type, "Symbolic link");
	else if (S_ISREG(mode))
		strcpy(type, "Regular file");
	else if (S_ISDIR(mode))
		strcpy(type, "Directory");
	else if (S_ISCHR(mode))
		strcpy(type, "Character device");
	else if (S_ISBLK(mode))
		strcpy(type, "Block Device");
	else if (S_ISFIFO(mode))
		strcpy(type, "FIFO");
	else if (S_ISSOCK(mode))
		strcpy(type, "Socket");
	else
		strcpy(type, "Uknown");

	printf("TYPE: %s\n", type);
	printf("SIZE: %ld\n", buf.st_size);
	printf("BLK SIZE: %ld\n", buf.st_blksize);
	printf("Blocks: %ld\n", buf.st_blocks);
	printf("ACCESSED: %s", ctime(&buf.st_atime));
	printf("MODIFIED: %s", ctime(&buf.st_mtime));
	printf("CHANGED : %s", ctime(&buf.st_ctime));

	exit(EXIT_SUCCESS);
}
	
