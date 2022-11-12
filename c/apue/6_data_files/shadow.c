#include "apue.h"
#include <shadow.h>

int main(void)
{
    struct spwd *pass;

    if((pass = getspnam("linkavych")) != 0){
        perror("getspnam");
        exit(1);
    }

    printf("%s\n", pass->sp_pwdp);

    exit(0);
}
