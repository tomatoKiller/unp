#include "../unp.h"
#include <pthread.h>

typedef struct {
	int 	rl_cnt;
	char 	*rl_bufptr;
	char 	rl_buf[MAXLINE];
} Rline;
