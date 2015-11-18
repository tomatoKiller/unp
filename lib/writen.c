#include "../unp.h"

ssize_t writen(int fd, const void *vptr, size_t n)
{
	size_t 	nleft;
	ssize_t nwriten;
	const char *ptr;

	ptr = vptr;

	while( nleft > 0)
	{
		if( (nwriten = write(fd, ptr, nleft)) <= 0)
		{
			if (errno == EINTR)
				nwriten = 0;
			else
				return -1;
		}

		nleft -= nwriten;
		ptr += nwriten;
	}

	return n;
}
