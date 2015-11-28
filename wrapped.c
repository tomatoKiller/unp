#include "unp.h"
#include <pthread.h>

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

int Accept(int listenfd, SA * sa, socklen_t *addrlen)
{
	int n;
again:
	if( (n = accept(listenfd, sa, addrlen)) < 0)
	{
		if( errno == EINTR )
			goto again;
		else
		{
			printf("accept error\n");
			exit(1);
		}
	}
	return n;
}

void Listen(int listenfd, int backlog)
{
	if(listen(listenfd, backlog) < 0)
		err_sys("listen error");
}

void Close(int fd)
{
	if( close(fd) < 0)
		err_quit("close error");
}

void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
	if(setsockopt(fd, level, optname, optval, optlen) < 0)
		err_sys("setsockopt error");
}

void Shutdown(int fd, int how)
{
	if( shutdown(fd, how) < 0)
		err_sys("shutdown error");
}

Sigfunc	* Signal(int signo, Sigfunc * func)
{
	struct 	sigaction 	act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if( signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else
	{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
#endif
	}

	if (sigaction(signo, &act, &oact) < 0)
		return SIG_ERR;

	return oact.sa_handler;

}

void Writen(int fd, const void *ptr, size_t nbytes)
{
	if( writen(fd, ptr, nbytes) != nbytes )
		err_sys("writen error");
}

void Getpeername(int fd, SA * cliaddr, socklen_t *addrlen)
{
	if( getpeername(fd, cliaddr, addrlen) < 0)
		err_sys("getpeername error");
}

void *Malloc(ssize_t nbytes)
{
	void *ptr;
	if( (ptr = malloc(nbytes)) == NULL)
		err_quit("malloc error");
	return ptr;
}

int Fcntl(int fd, int flag, int arg)
{
	int 	ret;
	if( (ret = fcntl(fd, flag, arg)) < 0)
		err_sys("fcntl error");
	return ret;
}
int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		struct timeval * timeout)
{
	int n = select(nfds, readfds, writefds, exceptfds, timeout);
	if( n < 0)
		err_quit("select error");

	return n;

}

void Pthread_once(pthread_once_t *onceptr, void (*init)(void))
{
	int 	n;
	n = pthread_once(onceptr, init);
	if(n > 0)
		err_sys("pthread_once error");
}

void Pthread_key_create(pthread_key_t *keyptr, void(*destructor)(void *value))
{
	int 	n;
	n = pthread_key_create(keyptr, destructor);

	if(n > 0)
		err_sys("pthread_key_create error");
}

void *Calloc(size_t n, size_t size)
{
	void 	*ret;
	ret = calloc(n, size);
	if(ret == NULL)
		err_quit("calloc error");
	return ret;
}


void Pthread_mutex_lock(pthread_mutex_t *mptr)
{
	int 	n;
	n = pthread_mutex_lock(mptr);

	if(n > 0)
		err_sys("pthread_mutex_lock error");
}

void Pthread_mutex_unlock(pthread_mutex_t *mptr)
{
	int 	n;
	n = pthread_mutex_unlock(mptr);

	if(n > 0)
		err_sys("pthread_mutex_unlock error");
}

void Pthread_cond_wait(pthread_cond_t *cptr, pthread_mutex_t *mptr)
{
	int 	n;
	n = pthread_cond_wait(cptr, mptr);

	if(n > 0)
		err_sys("pthread_cond_wait error");
}

void Pthread_cond_signal(pthread_cond_t *cptr)
{
	int 	n;
	n = pthread_cond_signal(cptr);

	if(n > 0)
		err_sys("pthread_cond_signal error");
}

void Pthread_join(pthread_t tid, void **retval)
{
	int 	n;
	n = pthread_join(tid, retval);

	if(n > 0)
		err_sys("pthread_join error");
}

