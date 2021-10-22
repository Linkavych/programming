/*
 * Using getpwnam() and getlogin() to get the user's login name and their information
 * from /etc/passwd
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(void) {

	char *login;
	struct passwd *pentry;

	// get the login name of the user
	if ((login = getlogin()) == NULL) {
		perror("getlogin");
		exit(EXIT_FAILURE);
	}
	printf("getlogin() returned: %s\n", login);

	//get the passwd entry for  the login user
	if ((pentry = getpwnam(login)) == NULL) {
		perror("getpwnam");
		exit(EXIT_FAILURE);
	}
	printf("gecos: %s %s %s %s\n", pentry->pw_gecos, pentry->pw_name, pentry->pw_shell, pentry->pw_dir);

	exit(EXIT_SUCCESS);
}


