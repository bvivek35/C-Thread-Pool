/*
* Interface to the threadpool_t ADT
* 
*/
#ifndef THREADPOOL_H

#define THREADPOOL_H


#include <pthread.h>

#include "task.h"
#include "queue.h"

enum __shutdown
{
	working,
	graceful_shutdown,
	immediate_shutdown,
};
typedef enum __shutdown shutdown_t;


struct __threadpool
{
	pthread_t *__threads;
	queue_t *__task_queue;
	
	pthread_mutex_t __pool_lock;
	pthread_cond_t __pool_notify_task;
	
	int __n_threads;
	int __n_task_pending;
	int __n_started_threads;
	shutdown_t __shutdown;	
};
typedef struct __threadpool threadpool_t;

threadpool_t *threadpool_create(int);

void threadpool_add_task(threadpool_t *, task_t *);

void threadpool_destroy(threadpool_t *, shutdown_t);

#endif
