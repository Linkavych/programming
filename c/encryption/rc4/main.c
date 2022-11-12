/*
 * Using the openssl encryption library to encrypt a file
 *
 * rc4 implementation
 *
 * autho: @linkavych
 * date: 2022-10-1
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <openssl/rc4.h>

void usage(void);

int main(int argc, char *argv[]) 
{
    int input;
    RC4_KEY *key;
    char *bufin, *bufout;

    if (argc != 3) {
        usage();
    }

    input = open(argv[1], "rb+");
    if (input < 0){
        printf("No file found\n");
        exit(1);
    }

    struct stat buf;
    if (fstat(input, &buf) == -1) {
        printf("Failed at fstat");
        exit(1);
    }
    off_t size = buf.st_size;

    bufin = (char *)malloc(sizeof(char) *size);
    bufout = (char *)malloc(sizeof(char) *size);

    fread(bufin, 1, size,input);

    unsigned char *inkey;

    inkey = malloc(sizeof(char) * (strlen(argv[2]) + 1));

    int len = strlen(argv[2]);

    strncpy(inkey, argv[2], len);

    int key_len = strlen(inkey);

    RC4_set_key(key, key_len, inkey);

    RC4(key, size, bufin, bufout);

    free(bufin);
    free(bufout);

    return 0;
}

void usage(void) {
    printf("[!] Error!\n");
}




