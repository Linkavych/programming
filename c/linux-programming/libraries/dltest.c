/*
 * Dynamically load liberr.so and call err_ret
 * ?
 */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void) {

	void *handle;
	void (*errfcn)(); // pointer to loaded code to use
	const char *errmsg;
	FILE *pf;

	//load the object
	handle = dlopen("liberr.so", RTLD_NOW);
	if (handle == NULL){
		printf("failed to load liberr.so: %s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	// clear the error string
	dlerror();
	errfcn = dlsym(handle, "err_ret");
	if ((errmsg = dlerror()) != NULL) {
		printf("didn't find err_ret(): %s\n", errmsg);
		exit(EXIT_FAILURE);
	}

	//use the loaded symbol
	if ((pf == fopen(" foobar", "r")) == NULL) {
		errfcn("couldn't open foobar");
	}

	//unload things
	dlclose(handle);
	exit(EXIT_SUCCESS);
}

