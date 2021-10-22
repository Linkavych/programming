/*
 * Building a simple NTP client from a project on Github
 * Just learning and following along
 *
 * 2021-07-25
 */

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define NTP_TIMESTAMP_DELTA 2208988800ull

#define LI(packet)	(uint8_t) ((packet.li_vn_mode & 0xC0) >> 6) 
#define VN(packet)	(uint8_t) ((packet.li_vn_mode & 0x38) >> 3)
#define MODE(packet)	(uint8_t) ((packet.li_vn_mode & 0x07) >> 0)

void error(char *msg) {

	perror(msg);

	exit(0);
}

int main(int argc, char *argv[]) {

	int sockfd, n; //Socket file descriptor and the n return result from writing/reading the socket
	int portno = 123; // NTP UDP port

	char *host_name = "us.pool.ntp.org";	// NTP server

	// NTP packet struct - 48 bytes
	
	typedef struct {

		uint8_t li_vn_mode;		// Eight bits. lin, vn, mode.
						// li - Two bits; Leap indicator
						// vn - Three bits; Version number of protocol
						// mode - Three bits; Client will pick mode 3 for client.

		uint8_t stratum;		// Eight bits - Stratum level of the local clock
		uint8_t poll;			// Eight bits - Maximum level between successive messages.
		uint8_t precision;		// Eight bits - Precision level of the local clock.

		uint32_t rootDelay;		// 32 bits - Total round trip delay time
		uint32_t rootDispersion;	// 32 bits - Max error allowed from primary clock source.
		uint32_t refID;			// 32 bits - Reference clock identifier

		uint32_t refTM_s;		// 32 bits - Reference timestamp seconds
		uint32_t refYM_f;		// 32 bits - Reference timestamp fractional seconds

		uint32_t origTM_s;		// 32 bits - Originate timestamp seconds
		uint32_t origTM_f;		// 32 bits - Originate timestamp fractional seconds

		uint32_t rxTM_s;		// 32 bits - Received timestamp seconds
		uint32_t rxTM_f;		// 32 bits - Received timestamp fractional seconds

		uint32_t txTM_s;		// 32 bits - Transmit timestamp seconds (MOST IMPORTANT FIELD FOR CLIENT)
		uint32_t txTM_f;		//32 bits - Transmit timestamp fractional seconds

	} ntp_packet;				// Total: 384 bits, 48 bytes

	// Create the packet and set it to 0
	ntp_packet packet = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	memset(&packet, 0, sizeof(ntp_packet));

	// Set the first byte's bits to 00,011,011 for li = 0, vn = 3, mode = 3; rest set to 0
	*((char *) &packet + 0) = 0x1b;

	// Create a UDP socket, convert the host_name to an IP, set the port
	// connect, send, and read the return packet
	
	struct sockaddr_in serv_addr; // Server address data structure
	struct hostent *server;		// Server data structure

	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  // The UDP socket

	if (sockfd < 0)
		error("[!] Error opening socket");

	server = gethostbyname(host_name);		// Converts a URL to an IP address

	if (server == NULL)
		error("[!] Error: No such host name");

	// Zero out the server address structure
	
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

        // Copy the server's IP to the server address struct
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);

	serv_addr.sin_port = htons(portno);	// Converts portno integer to network big-endian and saves in struct for server

	// Call server using IP and port
	
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("[!] Error connecting");

	// Send the NTP packet; check if fails
	
	n = write(sockfd, (char *) &packet, sizeof(ntp_packet));

	if (n < 0)
		error("[!] Error: Not able to write to socket");

	// Wait and receive the packet back from the NTP server
	
	n = read(sockfd, (char *) &packet, sizeof(ntp_packet));

	if (n < 0)
		error("[!] Error: Not able to read from the socket");

	// These two fields contain the time-stamp seconds as the packet left the NTP server.
	// The numer of seconds correspond to the seconds passed since 1900
	// ntohl() converts the bit/byte order from network to host endianess
	
	packet.txTM_s = ntohl(packet.txTM_s); // Seconds
	packet.txTM_f = ntohl(packet.txTM_f); // Fractions of seconds

	// Extract 32bits that represent the time-stamp seconds (since NTP epoch) from when packet left server
	// Subtract 70 years of seconds from seconds since 1900
	// Leaves seconds since the UNIX epoch 1970
	
	time_t txTM = (time_t) (packet.txTM_s - NTP_TIMESTAMP_DELTA);

	// Print the time from the server, accounting for local time and conversion from UTC
	
	printf("Time: %s", ctime((const time_t*) &txTM));

	return 0;
}



