#include <stdio.h>
#include <sys/utsname.h>

int main(void)
{
    struct utsname name;

    uname(&name);

    printf("%s - %s - %s - %s - %s\n", name.nodename, name.sysname, name.machine, name.release, name.version);

    return 0;

}
