#include "unp.h"
int main()
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	int recvbuflen, msslen;

	int len ;
	
	len= sizeof recvbuflen;

	Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuflen, &len);

	len = sizeof msslen;

	Getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &msslen, &len) ;

	printf("recvbuf == %d, MSS == %d\n", recvbuflen, msslen);


	struct sockaddr_in servaddr;

	bzero(&servaddr, sizeof(servaddr) );

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8887);
	Inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
	
	len= sizeof recvbuflen;

	Getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuflen, &len);

	len = sizeof msslen;

	Getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, &msslen, &len) ;

	printf("after connect: recvbuf == %d, MSS == %d\n", recvbuflen, msslen);

	exit(0);
}
