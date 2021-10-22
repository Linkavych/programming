/*
 * This program uses the system() function to call an external command
 * and retrieve timing data with getrusage() 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

void doit(char *, long);
void err_quit(char *);

int main(void) {

	struct rusage usage;
	system("grep the /usr/share/doc/*/* > /dev/null 2> /dev/null");

	// get the resource structure
	if ((getrusage(RUSAGE_SELF, &usage)) == -1) {
		err_quit("getrusage");
	}


	fputs("parent times\n", stdout);
	doit("\tuser CPU", usage.ru_utime.tv_sec);
	doit("\tsys CPU", usage.ru_stime.tv_sec);

	fputs("parent memory stats\n", stdout);
	doit("\tminor faults", usage.ru_minflt);
	doit("\tmajor faults", usage.ru_majflt);
	doit("\tpage swaps", usage.ru_nswap);

	// get resource structure of child
	if ((getrusage(RUSAGE_CHILDREN, &usage)) == -1) {
		err_quit("getrusage");
	}

	fputs("child times\n", stdout);
	doit("\tuser CPU", usage.ru_utime.tv_sec);
	doit("\tsys CPU", usage.ru_stime.tv_sec);

	fputs("child memory stats\n", stdout);
	doit("\tminor faults", usage.ru_minflt);
	doit("\tmajor faults", usage.ru_majflt);
	doit("\tpage swaps", usage.ru_nswap);

	exit(EXIT_SUCCESS);
}

void doit(char *str, long resval) {

	// get clock ticks/second
	printf("%s: %ld\n", str, resval);
}

void err_quit(char *str) {

	perror(str);
	exit(EXIT_FAILURE);
}
