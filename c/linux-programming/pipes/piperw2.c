/*
 * A rewrite of piperw, but now using popen
 * and pclose to cimplify pipe handling
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>

#define BUFSZ PIPE_BUF

void err_quit(char *msg);

int main(int argc, char *argv[]){

	FILE *fp;
	char *cmdstring = "cat pipeopn.c";
	char buf[BUFSZ];

	//create the pipe
	if ((fp = popen(cmdstring, "r")) == NULL)
		err_quit("popen");

	//read cmdstring output
	while ((fgets(buf, BUFSZ, fp)) != NULL)
		printf("%s", buf);

	//close and reap
	pclose(fp);
	exit(EXIT_SUCCESS);
}

void err_quit(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}
