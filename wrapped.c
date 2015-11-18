#include "unp.h"

void Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{
	if( getsockopt(sockfd, level, optname, optval, optlen) < 0)
	{
		printf("getsockopt error\n");
		exit(1);
	}
}

void Inet_pton(int af, const char *src, void *dst)
{
	if(inet_pton(af, src, dst) < 0)
	{
		printf("inet_pton error\n");
		exit(1);
	}
}

void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen)
{
	if( connect(sockfd, serv_addr, addrlen) < 0)
	{
		perror("connect:");
		exit(1);
	}
}
void Bind(int sockfd, SA *serv_addr, socklen_t addrlen)
{
	if( bind(sockfd, serv_addr, addrlen) < 0)
	{
		perror("bind: ");
		exit(1);
	}
}
int Socket(int domain, int type, int protocol)
{
	int retsock;
	if( (retsock = socket(domain, type, protocol) ) < 0)
	{
		perror("socket: ");
		exit(1);
	}
	return retsock;
}
int Recvfrom(int sockfd, void *buff, size_t nbytes, int flags, SA *from, socklen_t *addrlen)
{
	int ret;
	if( (ret = recvfrom(sockfd, buff, nbytes, flags, from, addrlen)) < 0) 
	{
		perror("recvfrom: ");
		exit(1);
	}
	return ret;
}

int Sendto(int sockfd, const void *buff, size_t nbytes, int flags, const SA *from, socklen_t addrlen)
{
	int ret;
	if( (ret = sendto(sockfd, buff, nbytes, flags, from, addrlen)) < 0)
	{
		perror("sendto: ");
		exit(1);
	}
	return ret;
}


int Fputs(const char *str, FILE *fp)
{
	int ret;
	if ( (ret = fputs(str, fp)) == EOF)
	{
		printf("fputs error\n");
		exit(1);
	}
	return ret;
}

char * Fgets(char *buf, int len, FILE *fp)
{
	char* ret = fgets(buf, len, fp);
	if( ret == NULL && ferror(fp) )
	{
		printf("fgets error\n");
		exit(1);
	}

	return ret;
}

char *Sock_ntop(const SA * sa, socklen_t addrlen)
{
	char *ptr;
	if( (ptr = sock_ntop(sa, addrlen)) == NULL)
	{
		printf("sock_ntop:  address format wrong\n");
		exit(1);
	}
	return ptr;
}
void Getsockname(int sockfd, SA * sa, socklen_t *addrlen)
{
	if( getsockname(sockfd, sa, addrlen) < 0)
	{
		perror("getsockname: ");
		exit(1);
	}
}
