#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>


#include "threadpool.h"


pthread_t t[4];
pthread_mutex_t lock;

int x;

void *f(void *arg) 
{
	pthread_mutex_lock(&lock);
	
	printf("%d\n", x);
	++x;
	
	pthread_mutex_unlock(&lock);	
	
	return 0;
}

int main()
{
	int i;
	
	x = 0;
	
	pthread_mutex_init(&lock, 0);
	
	for (i = 0; i < 4; ++i)	
	{
		pthread_create(&t[i], 0, (void *(*)(void *))f, 0);
	}
	
	for (i = 0; i < 4; ++i)
		pthread_join(t[i], 0);

	return 0;
}
