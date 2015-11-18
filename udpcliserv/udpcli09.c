#include "../unp.h"

int main(int argc, char ** argv)
{
	int 	sockfd;
	socklen_t 	len;
	struct sockaddr_in  cliaddr, servaddr;

	if(argc != 2)
	{
		printf("usage: udpcli <IPaddress>");
		exit(1);
	}

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

	len = sizeof(cliaddr);

	Getsockname(sockfd, (SA *)&cliaddr, &len);

	printf("local address %s\n", Sock_ntop((SA*)&cliaddr, len));

	exit(0);

}
