/*
 * Creating a memory mapped file
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

void err_quit(char *msg);

int main(int argc, char *argv[]){

	int fd;
	void *map;
	struct stat statbuf;

	//open the file to map
	if (argc != 2) {
		puts("USAGE: ./mkmap <file>");
		exit(EXIT_FAILURE);
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		err_quit("open");
	}

	//get file length for map
	fstat(fd, &statbuf);

	//map the input file
	if (( map = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED){
		err_quit("mmap");
	}
	printf("map created at %p\n", &map);

	// close and unmap the file
	close(fd);

	munmap(map, statbuf.st_size);
	exit(EXIT_SUCCESS);
}

void err_quit(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
