#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    time_t t;
    struct tm *tmp;
    char buf1[16];
    char buf2[64];

    time(&t);
    tmp = localtime(&t);

    if (strftime(buf2, 64, "%a %b %d %r %Z %Y", tmp) == 0)
        printf("buffer length 64 is too small\n");
    else
        printf("%s\n", buf2);

    exit(0);
}
