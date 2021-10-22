/*
 * Just testing interfacing with the sqlite3 API
 */
#include <sqlite3.h>
#include <stdio.h>

int main(void) {

	printf("%s\n", sqlite3_libversion());

	return 0;
}
