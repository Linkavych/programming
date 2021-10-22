/*
 * Implementation of the liberr library
 */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liberr.h"

void err_ret(const char *fmt, ...){
	va_list ap;

	va_start(ap, fmt);
	err_prn(fmt, ap, NULL);
	va_end(ap);
	return;
}

void err_quit(const char *fmt, ...){
	va_list ap;

	va_start(ap, fmt);
	err_prn(fmt, ap, NULL);
	va_end(ap);
	exit(1);
}

void log_ret(char *logfile, const char *fmt, ...){
	va_list ap;

	va_start(ap, fmt);
	err_prn(fmt, ap, logfile);
	va_end(ap);
	return;
}

void log_quit(char *logfile, const char *fmt, ...){
	va_list ap;

	va_start(ap, fmt);
	err_prn(fmt, ap, logfile);
	va_end(ap);
	exit(1);
}

extern void err_prn(const char *fmt, va_list ap, char *logfile){

	int save_err;
	char buf[MAXLINELEN];
	FILE *plf;

	save_err = errno; //value caller might want printed
	vsprintf(buf, fmt, ap);
	sprintf(buf + strlen(buf), ": %s\n", strerror(save_err));

	fflush(stdout); //in case stdout and stderr are same

	if (logfile != NULL) {
		if ((plf = fopen(logfile, "a")) != NULL) {
			fputs(buf, plf);
			fclose(plf);
		} else {
			fputs("failed to open log file\n", stderr);
		}
	}
	fflush(NULL);
	return;
}
