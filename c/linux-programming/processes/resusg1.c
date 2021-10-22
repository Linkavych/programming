/*
 * This program uses the system() function to call an external command
 * and retrieve timing data with times()
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

void doit(char *, clock_t);

int main(void) {

	clock_t start, end;
	struct tms t_start, t_end;

	start = times(&t_start);
	system("grep the /usr/share/doc/*/* > /dev/null 2> /dev/null");
	end = times(&t_end);

	doit("elapsed", end - start);

	fputs("parent times", stdout);
	doit("\tuser CPU", t_end.tms_utime);
	doit("\tsys CPU", t_end.tms_stime);

	fputs("child times", stdout);
	doit("\tuser CPU", t_end.tms_cutime);
	doit("\tsys CPU", t_end.tms_cstime);

	exit(EXIT_SUCCESS);
}

void doit(char *str, clock_t time) {

	// get clock ticks/second
	long tps = sysconf(_SC_CLK_TCK);

	printf("%s: %6.2f secs \n", str, (float)time/tps);
}
