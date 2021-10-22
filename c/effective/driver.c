/*
 * Program to help explore how to structure a C program in a useful
 * manner. Accepts a whitespace delimited list of integer values
 * as input and outputs whether each value is a prime number.
 */
#include "isprime.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>




static void print_help(void){
	printf("%s", "primetest num1 [num2, num3...numN]\n\n");
	printf("%s", "Tests positive integers for primality. Supports testing ");
	printf("%s [2-%llu].\n", "numbers in the range", ULLONG_MAX);
}

// Convert command line arguments to unsigned long long values ref by val.
// Return true if the arg conversion succeeds, false otherwise
static bool convert_arg(const char *arg, unsigned long long *val){
	char *end;

	//strtoll returns an in-band error indicator; clear errno before call
	errno = 0;
	*val = strtoull(arg, &end, 10);

	// Check for failures where the call returns sentinel val and sets errno
	if ((*val == ULLONG_MAX) && errno) return false;
	if (*val == 0 && errno) return false;
	if (end == arg) return false;

	//If here, we converted the arg, but we only want to allow values
	//greater than one, so reject less than or equal to one
	if (*val <= 1) return false;
	return true;
}


// Process all command-line arguments
static unsigned long long *convert_command_line_args(int argc, const char *argv[], size_t *num_args){
	
	*num_args = 0;

	if (argc <= 1) {
		// No command line args provided; print help
		print_help();
		return NULL;
	}

	// Allocate an array large enough for all user args. Test for failure.
	unsigned long long *args = (unsigned long long *) malloc(sizeof(unsigned long long) * (argc - 1));
	bool failed_conversion = (args == NULL);

	for (int i = 1; i < argc && !failed_conversion; ++i){
		// Attempt to convert the arg to integer. If fail, set 
		// failed_conversion to true.
		unsigned long long one_arg;
		failed_conversion |= !convert_arg(argv[i], &one_arg);
		args[i-1] = one_arg;
	}

	if (failed_conversion){
		// Free array, print help, bail
		free(args);
		print_help();
		return NULL;
	}

	*num_args = argc - 1;
	return args;
}

int main(int argc, const char *argv[]) {
	size_t num_args;
	unsigned long long *vals = convert_command_line_args(argc, argv, &num_args);

	if (!vals) return EXIT_FAILURE;

	for (size_t i = 0; i < num_args; ++i) {
		printf("%llu is %s.\n", vals[i], is_prime(vals[i], 100) ? "Probably prime" :"Not Prime");
	}

	free(vals);
	return EXIT_SUCCESS;
}


