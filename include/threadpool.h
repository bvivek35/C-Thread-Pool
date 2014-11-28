/*
* Interface to the threadpool_t ADT
* 
*/
#ifndef THREADPOOL_H

#define THREADPOOL_H


#include <pthread.h>

#include "task.h"
#include "queue.h"


struct __threadpool
{
	pthread_t *__threads;
	queue_t *__task_queue;
	
	pthread_mutex_t __pool_lock;
	pthread_cond_t __pool_notify_task;
	
	int __n_threads;
	int __task_pending;
	int __shutdown;	
};
typedef struct __threadpool threadpool_t;



threadpool_t *threadpool_create(int);

void threadpool_add_task(task_t *);

void destroy_threadpool(threadpool_t *);

#endif
