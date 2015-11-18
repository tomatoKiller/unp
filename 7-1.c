#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int tcpsendbuf, udpsendbuf;
	int len;

	len = sizeof(tcpsendbuf);	
	if( getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &tcpsendbuf, &len) < 0)
	{
		printf("getsockopt error\n");
		exit(1);
	}

	if(len != sizeof(int) )
	{
		printf("size error\n");
		exit(1);
	}

	printf("the size of tcp send buffer is %d\n", tcpsendbuf);


	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	len = sizeof(udpsendbuf);	
	if( getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &udpsendbuf, &len) < 0)
	{
		printf("getsockopt error\n");
		exit(1);
	}

	if(len != sizeof(int) )
	{
		printf("size error\n");
		exit(1);
	}

	printf("the size of udp send buffer is %d\n", udpsendbuf);

	return 0;
}
