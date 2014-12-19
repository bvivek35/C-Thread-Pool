#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#include "task.h"
#include "threadpool.h"

int my_count1;
int my_count2;
pthread_mutex_t lock1;
pthread_mutex_t lock2;

void *f1(void *a)
{
	printf(" In function f1()\n");
	pthread_mutex_lock(&lock1);
	++my_count1;
	pthread_mutex_unlock(&lock1);
	return 0;
}
void *f2(void *a)
{
	printf("In function f2()\n");
	pthread_mutex_lock(&lock2);
	++my_count2;
	pthread_mutex_unlock(&lock2);
	return 0;
}

int main()
{
	my_count1 = 0;
	my_count2 = 0;
	pthread_mutex_init(&lock1, NULL);
	pthread_mutex_init(&lock2, NULL);
	threadpool_t *pool = threadpool_create(2);
	
		
	threadpool_add_task(pool, mk_task(f1, NULL));
	threadpool_add_task(pool, mk_task(f2, NULL));
	threadpool_add_task(pool, mk_task(f1, NULL));
	threadpool_destroy(pool, immediate_shutdown);	
	threadpool_add_task(pool, mk_task(f2, NULL));
	
	printf("my_count1 from f1() %d\n", my_count1);
	printf("my_count2 from f2() %d\n", my_count2);
}