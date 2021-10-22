/*
 * An implementation of cat with memory maps
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

void err_quit(char *msg);

int main(int argc, char *argv[]){

	int fd;
	char *src;
	struct stat statbuf;

	//open the source file
	if (argc != 2){
		puts("USAGE: ./mmcat <failename>");
		exit(EXIT_FAILURE);
	}

	if (( fd = open(argv[1], O_RDONLY)) < 0) {
		err_quit("open");
	}

	//get file length for mapping
	fstat(fd, &statbuf);

	// map the file
	if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) < 0){
		err_quit("mmap");
	}

	// write it all out
	write(STDOUT_FILENO, src, statbuf.st_size);

	//clean up the mess
	close(fd);
	munmap(src, statbuf.st_size);

	exit(0);
}

void err_quit(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
