/*
* Interface to the threadpool_t ADT
* This is the pool of worker threads
* worker threads take tasks from a task-queue to process
* 
* SEE include/task.h
* SEE include/queue.h
* SEE src/threadpool.c
*
* Look below for supported functions and types defined   
*/

#ifndef THREADPOOL_H

#define THREADPOOL_H


#include <pthread.h>

#include "task.h"
#include "queue.h"


/*
* Specify the possible states of the pool
* working : pool has started, threads are processing
* graceful_shutdown : disallow addition of tasks, complete the current queue of *		      tasks
* immediate_shutdown : same as graceful_shutdown but doesnot wait for the queue *		       to be emptied 	
*/

enum __shutdown
{
	working,
	graceful_shutdown,
	immediate_shutdown,
};
typedef enum __shutdown shutdown_t;


/*
* ADT to store the entire thread-pool
* @var __threads : ptr to array of worker threads that form the pool   
* @var __task_queue : a queue to hold tasks (SEE include/task.h)
* @var __pool_lock : mutex to allow exclusive access to the pool resources
* @var __pool_notify_task : conditional variable from the pthread lib. Used to 
* 			    notify the pool that there are new tasks available 
* @var __n_threads : no. of threads specified at initialization 
* @var __n_task_pending : no. of tasks available in the __task_queue
* @var __n_started_threads : no. of worker threads that are executing a task 
* 			     from the __task_queue
* @var __shutdown : status of the pool. SEE below for shutdown_t 
*/

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



/*
* SUPPORTED FUCTIONS BELOW
*/


/*
* create a new pool
* Initializes the threadpool_t ADT
* Acts as a constructor
* 
* @param int : no. of threads to be in the pool
*
* @return threadpool_t* : ptr to the pool just created
*/

threadpool_t *threadpool_create(int);


/*
* add a new task to the task-queue
* 
* @param pool : pool to which task must be added to
* @param task : the task that will be added
*/

void threadpool_add_task(threadpool_t *pool, task_t *task);


/*
* shut the pool down
* 
* @param pool : pool to shutdown
* @param status : type of shutdown to be done 
*/

void threadpool_destroy(threadpool_t *pool, shutdown_t status);

#endif
