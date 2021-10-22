/*
 * Correct way to open a pipe and fork
 * a child process
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>

#define BUFSZ PIPE_BUF

void err_quit(char *msg);

int main(int argc, char *argv[]){

	int fd[2];
	int fdin;
	char buf[BUFSZ];
	int pid, len;

	// Create a pipe
	if ((pipe(fd)) < 0)
		err_quit("pipe");

	// fork and close fds
	if ((pid = fork()) < 0)
		err_quit("fork");

	if (pid == 0) {
		// Child is read, close write
		close(fd[1]);
		while ((len = read(fd[0], buf, BUFSZ)) > 0)
			write(STDOUT_FILENO, buf, len);
		close(fd[0]);
	} else {
		// parent is write, close read
		close(fd[0]);
		if ((fdin = open(argv[1], O_RDONLY)) < 0) {
			perror("open");
			write(fd[1], "123\n", 4);
		} else {
			while ((len = read(fdin, buf, BUFSZ)) > 0)
				write(fd[1], buf, len);
			close(fdin);
		}
		//close write
		close(fd[1]);
	}
	// REAP the exit
	waitpid(pid, NULL, 0);

	exit(EXIT_SUCCESS);
}

void err_quit(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
