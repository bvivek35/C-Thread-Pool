#include <stdio.h>
#include <pthread.h>

#include "task.h"
#include "threadpool.h"

int count;
pthread_mutex_t lock;
pthread_t t[1];

void *f(void *args)
{
	int i;
	int j;

	j = 0;

	for (i = 0; i < 100000; ++i)
		if (i % 2)
			++j;
		else
			--j;
	
	pthread_mutex_lock(&lock);
	++count;
	pthread_mutex_unlock(&lock);
	
	return NULL;
}


int main()
{
	count = 0;
	pthread_mutex_init(&lock, NULL);
	
	int i;
	for (i = 0; i < 100000; ++i)
	{
		pthread_create(&t[0], NULL, f, NULL);
		pthread_join(&t[0], NULL);
	}	
	
	pthread_mutex_destroy(&lock);
	
	printf("%d\n", count);
}
