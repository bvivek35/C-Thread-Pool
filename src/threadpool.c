/*
* Implementation of the thread-pool
* A no. of worker threads process the tasks in a task-queue
*
* Implementation of the include/threadpool.h interface
*/

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

#include "threadpool.h"
#include "task.h"
#include "queue.h"


/*
* frees all components of the thread-pool
* 
* @param threadpool_t* : pool to be freed
*/

static void threadpool_free(threadpool_t *);


/*
* a function that the worker thread must execute upon creation.
* POSIX threads must begin execution as they are created.
* this function, blocks the thread.
* when a task in the queue is available, one is woken up.
* finishes execution, then goes back to a blocked state again.
*  
* @param void* : a ptr to the threadpool casted to void* for compatibility
* 
* return void* : present for only compatibility reasons. returns NULL
*/

static void *thread_fn(void *pool);


/*
* creates a new pool and returns a ptr to the just created thread-pool
*/

threadpool_t *threadpool_create(int n)
{
	threadpool_t *pool = malloc(sizeof *pool);
	
	pool->__threads = malloc(n * sizeof(*(pool->__threads)));
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
						thread_fn,(void *)pool);
	} 

	return pool;	
}


/*
* adds a new task to the fifo task-queue of the pool
* ensures that addition takes place iff pool is NOT shutting down
*/

void threadpool_add_task(threadpool_t *pool, task_t *task)
{
	pthread_mutex_lock(&(pool->__pool_lock));
	
	if (pool->__shutdown == working)
	{
#ifdef DEBUG
		printf("adding to q\n");
#endif
		pool->__n_task_pending += 1;
		enqueue(pool->__task_queue, task);
		pthread_cond_signal(&(pool->__pool_notify_task));
	}
#ifdef DEBUG
	printf("len : %d\n", get_len(pool->__task_queue));
#endif
	pthread_mutex_unlock(&(pool->__pool_lock));
}


/*
* initalizes shutting down of the thread-pool
* broadcasts all threads to wake up
* joins all threads also and frees the pool
* after destroy has been called, all calls to add task are unacknowledged
*/

void threadpool_destroy(threadpool_t *pool, shutdown_t status)
{
	pthread_mutex_lock(&(pool->__pool_lock));
	if (pool->__shutdown == working)
	{	
#ifdef DEBUG
		printf("destroy\n");
#endif
		int i;
		pool->__shutdown = status;
		if (status == immediate_shutdown)
		{
#ifdef DEBUG
			printf("Emptying q\n");
#endif
			empty_queue(pool->__task_queue);
		}

		pthread_cond_broadcast(&(pool->__pool_notify_task));
		pthread_mutex_unlock(&(pool->__pool_lock));

		for (i = 0; i < pool->__n_threads; ++i)
		{
#ifdef DEBUG
			printf("joining %d\n", i);
#endif
			pthread_join(pool->__threads[i], NULL);
		}
	}
	
	threadpool_free(pool);
}


/*
* frees the components of the pool
*/

static void threadpool_free(threadpool_t *pool)
{
	free(pool->__threads);
	destroy_queue(pool->__task_queue);
	
	pthread_mutex_destroy(&(pool->__pool_lock));
	pthread_cond_destroy(&(pool->__pool_notify_task));
	
	free(pool);
}


/*
* function that is executed by each worker thread
* thread waits to be woken up by a conditional-variable-signal
* check if there is any work left
* 	if no work in the queue, then it is shutdown time
*	else, pick up a task and process it
*/

static void *thread_fn(void *tpool)
{
	threadpool_t *pool = (threadpool_t *)tpool;
	
	task_t *task;

	while(1)
	{
		pthread_mutex_lock(&(pool->__pool_lock));

		while (is_queue_empty(pool->__task_queue) && 
				pool->__shutdown == working)
		{
#ifdef DEBUG
			printf("looping\n");
#endif
			pthread_cond_wait(&(pool->__pool_notify_task), 
							&(pool->__pool_lock));
		}
#ifdef DEBUG		
		printf("waking\n");	
#endif
		if (is_queue_empty(pool->__task_queue))
		{
#ifdef DEBUG
			printf("breaking : %d\n", get_len(pool->__task_queue));
#endif
			break;			 
		}
		
		task = dequeue(pool->__task_queue);
		pool->__n_started_threads += 1;
 		pool->__n_task_pending -= 1;
#ifdef DEBUG
		printf("\n Thread no %d is executing\n ",pool->__n_started_threads);
#endif
		pthread_mutex_unlock(&(pool->__pool_lock));	
#ifdef DEBUG
		printf("running\n");
#endif
		run_task(task);
		
		pthread_mutex_lock(&(pool->__pool_lock));
		pool->__n_started_threads -= 1;
		pthread_mutex_unlock(&(pool->__pool_lock));	
	}
	
	pthread_mutex_unlock(&(pool->__pool_lock));
	pthread_exit(NULL);

	return NULL;
}



