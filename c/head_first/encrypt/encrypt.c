/*
 * Simple XOR encryption algorithm
 *
 */
#include "encrypt.h"

void encrypt(char *message, int xor_val)
{
	while (*message) {
		*message = *message ^ xor_val;
		message++;
	}
}

