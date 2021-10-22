/*
 * A timestamp demon to demonstrate how to create daemonized
 * applications for working with the system
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syslog.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main(void) {

	pid_t pid, sid;
	int fd, len;
	time_t timebuf;

        // open the syslog; done automatically by this call
	syslog("lpedated", LOG_PID, LOG_DAEMON);

	pid = fork();
	if (pid < 0){
		syslog(LOG_ERR, "%s\n", "fork");
		exit(EXIT_FAILURE);
	}

	if (pid > 0){
		// in the parent; need to bail
		exit(EXIT_SUCCESS);
	}

	// in the child
	// start a new session
	if ((sid = setsid()) < 0) {
		syslog(LOG_ERR, "%s\n","setsid");
		exit(EXIT_FAILURE);
	}

	// make / the current directory
	if ((chdir("/")) < 0) {
		syslog(LOG_ERR, "%s\n", "chdir");
		exit(EXIT_FAILURE);
	}

	// reset the file mode
	umask(0);

	//close stdin/out/err from parent
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// get to work
	len = strlen(ctime(&timebuf));

	while(1){
		char *buf = malloc(sizeof(char) * (len + 1)); // allocate enough memory to write a time stamp

		if (buf == NULL){ // error check malloc
			perror("malloc error");
			exit(EXIT_FAILURE);
		}
		if ((fd = open("/var/log/lpedated.log", O_CREAT|O_WRONLY|O_APPEND, 0600)) < 0) {
			syslog(LOG_ERR, "%s\n", "open");
			exit(EXIT_FAILURE);
		}

		time(&timebuf);
		strncpy(buf, ctime(&timebuf), len + 1); // actually write our timestamp to a file
		write(fd, buf, len + 1);
		close(fd);
		sleep(60);
	}
	//close syslog
	closelog();

	exit(EXIT_SUCCESS);
}

