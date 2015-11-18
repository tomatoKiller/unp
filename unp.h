#ifndef UNP_H
#define UNP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netinet/tcp.h>   // just for TCP_MAXSEG

#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#define SA struct sockaddr 

#define MAXLINE 	4096
#define SERV_PORT	8787


#define bzero(addr, len) memset((addr), 0, (len) )


void Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
void Inet_pton(int af, const char *src, void *dst);
void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
void Bind(int sockfd, SA *serv_addr, socklen_t addrlen);
int Socket(int domain, int type, int protocol); 
int Recvfrom(int sockfd, void *buff, size_t nbytes, int flags, SA *from, socklen_t *addrlen);
int Sendto(int sockfd, const void *buff, size_t nbytes, int flags, const SA *from, socklen_t addrlen);

char * Fgets(char *buf, int len, FILE *fp);
int Fputs(const char *str, FILE *fp);

char *Sock_ntop(const SA * sa, socklen_t addrlen);


#endif
