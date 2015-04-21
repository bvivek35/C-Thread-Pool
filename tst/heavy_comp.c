#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "task.h"
#include "threadpool.h"

int count;
pthread_mutex_t lock;

void *f(void *args)
{
	int i;
	int j;

	j = 0;

	for (i = 0; i < 1000000; ++i)
		if (i % 2)
			++j;
		else
			--j;
	
	pthread_mutex_lock(&lock);
	++count;
	pthread_mutex_unlock(&lock);
	
	return NULL;
}


int main(int argc, char **argv)
{
	count = 0;
	pthread_mutex_init(&lock, NULL);
	
	int n_threads;
	n_threads = atoi(argv[1]);
//	n_threads = 8;	
	
	threadpool_t *pool = threadpool_create(n_threads);
	
	int i;
	for (i = 0; i < 10000; ++i)
		threadpool_add_task(pool, mk_task(f, NULL));
	
	threadpool_destroy(pool, graceful_shutdown);
	
	pthread_mutex_destroy(&lock);
	
	printf("%d\n", count);
}
