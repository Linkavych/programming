#include "apue.h"
#include <pwd.h>
#include <stddef.h>
#include <string.h>

int main(void){

    struct passwd *pwd;

    pwd = getpwnam("linkavych");

    printf("%s - %d - %s\n", pwd->pw_name, pwd->pw_uid, pwd->pw_shell);

    return 0;
}
