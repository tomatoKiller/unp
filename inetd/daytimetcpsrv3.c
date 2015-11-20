#include "../unp.h"

#include <time.h>

int main(int argc, char **argv)
{
	socklen_t	len;
	struct 		sockaddr	*cliaddr;
	char 		buff[MAXLINE];
	time_t		ticks;

	daemon_inetd(argv[0], 0);

	cliaddr = Malloc(sizeof(struct sockaddr_storage));

	len = sizeof(cliaddr);

	printf("111\n");
	Getpeername(0, cliaddr, &len);

	printf("fjjjjjjjjjjjjj\n");

	err_msg("connection from %s", Sock_ntop(cliaddr, len));

	ticks = time(NULL);

	snprintf(buff, sizeof(buff), "%.24\r\n", ctime(&ticks));

	Writen(0, buff, strlen(buff));

	Close(0);

	free(cliaddr);

	exit(0);

}
