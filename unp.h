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
#include <signal.h>
#include <errno.h>

#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include <netdb.h>
#include <sys/un.h>

#define SA struct sockaddr 

/* constant variable define */

#define MAXLINE 	4096
#define SERV_PORT	8787
#define LISTENQ		10
#define BUFFSIZE	1024
#define UNIXSTR_PATH	/tmp/unix.str

/* function macro define */

#define bzero(addr, len) memset((addr), 0, (len) )

#define max(a, b) ((a) < (b) ? (b) : (a) )
#define min(a, b) ((a) < (b) ? (a) : (b) )

/* function declaration */
void err_ret(const char* fmt, ...);
void err_sys(const char* fmt, ...);
void err_dump(const char* fmt, ...);
void err_msg(const char* fmt, ...);
void err_quit(const char* fmt, ...);


ssize_t writen(int fd, const void *ptr, size_t nbytes);
void Writen(int fd, const void *ptr, size_t nbytes);

typedef	void Sigfunc(int);

void str_echo(int sockfd);

Sigfunc * Signal(int signo, Sigfunc * func);
void Shutdown(int fd, int how);
void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);
void Close(int fd);
void Listen(int listenfd, int backlog);
int Accept(int listenfd, SA * sa, socklen_t *addrlen);

void Getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
void Inet_pton(int af, const char *src, void *dst);
void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
void Bind(int sockfd, SA *serv_addr, socklen_t addrlen);
int Socket(int domain, int type, int protocol); 
int Recvfrom(int sockfd, void *buff, size_t nbytes, int flags, SA *from, socklen_t *addrlen);
int Sendto(int sockfd, const void *buff, size_t nbytes, int flags, const SA *from, socklen_t addrlen);

char * Fgets(char *buf, int len, FILE *fp);
int Fputs(const char *str, FILE *fp);


char * sock_ntop(const SA * sa, socklen_t addrlen);
char *Sock_ntop(const SA * sa, socklen_t addrlen);

void Getsockname(int sockfd, SA * sa, socklen_t *addrlen);
void Getpeername(int fd, SA * cliaddr, socklen_t *addrlen);

int tcp_connect(const char *host, const char *serv);
void *Malloc(ssize_t nbytes);
void daemon_inetd(const char*, int);

ssize_t read_fd(int fd, void *ptr, size_t nbytes, int *recvfd);

ssize_t write_fd(int fd, void *ptr, size_t nbytes, int sendfd);

char *gf_time(void);
int Fcntl(int fd, int flag, int arg);

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		struct timeval * timeout);
#define Tcp_connect(host,serv) tcp_connect(host, serv)
void *Calloc(size_t n, size_t size);

void Pthread_key_create(pthread_key_t *keyptr, void(*destructor)(void *value));
void Pthread_once(pthread_once_t *onceptr, void (*init)(void));

void Pthread_mutex_lock(pthread_mutex_t *mptr);
void Pthread_mutex_unlock(pthread_mutex_t *mptr);
void Pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr);
void Pthread_cond_signal(pthread_cond_t *cptr);

void Pthread_join(pthread_t tid, void **retval);
#endif
