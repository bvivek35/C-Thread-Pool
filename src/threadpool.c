#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

#include "threadpool.h"
#include "task.h"
#include "queue.h"

static void __threadpool_free(threadpool_t *);
static void *__thread_fn(void *pool);


threadpool_t *threadpool_create(int n)
{
	threadpool_t *pool = malloc(sizeof *pool);
	
	pool->__threads = malloc(n * sizeof *(pool->__threads));
	pool->__task_queue = mk_queue();
	
	pthread_mutex_init(&(pool->__pool_lock), NULL);
	pthread_cond_init(&(pool->__pool_notify_task), NULL);
	
	pool->__n_threads = n;
	pool->__n_task_pending = 0;
	pool->__n_started_threads = 0;
	pool->__shutdown = working;
	
	int i;
	for (i = 0; i < n; ++i)
	{
		pthread_create(&(pool->__threads[i]), NULL, 
						__thread_fn,(void *)pool);
	} 

	return pool;	
}


void threadpool_add_task(threadpool_t *pool, task_t *task)
{
	pthread_mutex_lock(&(pool->__pool_lock));
	
	if (pool->__shutdown == working)
	{
		printf("adding to q\n");
		pool->__n_task_pending += 1;
		enqueue(pool->__task_queue, task);
		pthread_cond_signal(&(pool->__pool_notify_task));
	}
	printf("len : %d\n", get_len(pool->__task_queue));
	pthread_mutex_unlock(&(pool->__pool_lock));
}


void threadpool_destroy(threadpool_t *pool, shutdown_t status)
{
	pthread_mutex_lock(&(pool->__pool_lock));
	if (pool->__shutdown == working)
	{	
		printf("destroy\n");
		int i;
		pool->__shutdown = status;
		if (status == immediate_shutdown)
		{
			printf("Emptying q\n");
			empty_queue(pool->__task_queue);
		}

		pthread_cond_broadcast(&(pool->__pool_notify_task));
		pthread_mutex_unlock(&(pool->__pool_lock));

		for (i = 0; i < pool->__n_threads; ++i)
		{
			printf("joining %d\n", i);
			pthread_join(pool->__threads[i], NULL);
		}
	}
	
	__threadpool_free(pool);
}

static void __threadpool_free(threadpool_t *pool)
{
	free(pool->__threads);
	destroy_queue(pool->__task_queue);
	
	pthread_mutex_destroy(&(pool->__pool_lock));
	pthread_cond_destroy(&(pool->__pool_notify_task));
	
	free(pool);
}


static void *__thread_fn(void *tpool)
{
	threadpool_t *pool = (threadpool_t *)tpool;
	
	task_t *task;

	while(1)
	{
		pthread_mutex_lock(&(pool->__pool_lock));

		while (is_queue_empty(pool->__task_queue) && 
				pool->__shutdown == working)
		{
			printf("looping\n");
			pthread_cond_wait(&(pool->__pool_notify_task), 
							&(pool->__pool_lock));
		}
		
		printf("waking\n");	
		if (is_queue_empty(pool->__task_queue))
		{
			printf("breaking : %d\n", get_len(pool->__task_queue));
			break;			 
		}
		
		task = dequeue(pool->__task_queue);
		pool->__n_started_threads += 1;
 		pool->__n_task_pending -= 1;
		
		pthread_mutex_unlock(&(pool->__pool_lock));	
		
		printf("running\n");
		run_task(task);
		
		pthread_mutex_lock(&(pool->__pool_lock));
		pool->__n_started_threads -= 1;
		pthread_mutex_unlock(&(pool->__pool_lock));	
	}
	
	pthread_mutex_unlock(&(pool->__pool_lock));
	pthread_exit(NULL);

	return NULL;
}



