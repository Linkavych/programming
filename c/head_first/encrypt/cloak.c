/*
 * Simple program for encrypting a message with XOR and decrypting it
 *
 * Takes in an integer for XOR, and returns the value of the message
 */
#include <stdio.h>
#include <stdlib.h>
#include "encrypt.h"

int main(int argc, char *argv[])
{
	int xor_val = atoi(argv[1]);
	char msg[80];

	if (argc < 2) {
		printf("Usage: %s <xor_value>\n", argv[0]);
	}

	while (fgets(msg, 80, stdin)){
		encrypt(msg, xor_val);
		printf("The message: %s\n", msg);
	}
}

