#include "../unp.h"

int main(int argc, char **argv)
{
	int 	listenfd, connfd, udpfd, nready, maxfd1;
	char 	mesg[MAXLINE];
	pid_t  	childpid;
	fd_set	rset;
	ssize_t	n;
	socklen_t	len;
	const	int	on = 1;
	struct sockaddr_in 	servaddr, cliaddr;


	void sig_chld(int);

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	udpfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(udpfd, (SA *)&servaddr, sizeof(servaddr));

	Signal(SIGCHLD, sig_chld);

	FD_ZERO(&rset);

	maxfd1 = max(listenfd, udpfd) + 1;

	for(;;)
	{
		FD_SET(listenfd, &rset);
		FD_SET(udpfd, &rset);

		if( (nready = select(maxfd1, &rset, NULL, NULL, NULL)) < 0)
		{
			if( errno == EINTR)
				continue;
			else
			{
				printf("select error.");
				exit(1);
			}
		}

		if( FD_ISSET(listenfd, &rset) )
		{
			len = sizeof(cliaddr);
			connfd = Accept(listenfd, (SA *)&cliaddr, &len);

			if( (childpid = fork()) == 0)
			{
				/* child process */
				Close(listenfd);
				str_echo(connfd);
				exit(0);
			}
			Close(connfd);
		}

		if( FD_ISSET(udpfd, &rset))
		{
			len = sizeof(cliaddr);
			n = Recvfrom(udpfd, mesg, MAXLINE, 0, (SA *)&cliaddr, &len);

			Sendto(udpfd, mesg, n, 0, (SA *)&cliaddr, len);
		}
	}

	exit(0);
}
