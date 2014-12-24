/*
* Interface to use the FIFO ADT
* This is a queue of task_t ADT
*
* SEE include/task.h for the task_t ADT
* SEE src/queue.c for the implementation
*
* Look below for the supported functions 
*/


#ifndef QUEUE_H

#define QUEUE_H


#include <task.h>


/*
* a node in the queue
* encapsulate the node contents which is the task_t*
* have a link which makes it a self-referential data structure
* 
* @var __task : ptr to the task_t ADT (SEE include/task.h)
* @var __link : a self reference
*/

struct __queue_node
{
        task_t *__task;
        struct __queue_node *__link;
};
typedef struct __queue_node __queue_node_t;


/*
* queue_t is the opaque type that encapsulates the queue ADT
*
* all entries to the queue occur at the tail end
* all deletions occur at the head end
* also, keep a note on the number of entries in the queue
*
* @var __head : ptr to the head of the queue where items exit
* @var __tail : ptr to the tail of the queue where items are enqueued
* @var __n : keep count of the number of entries in the queue
*/

struct __queue
{
        __queue_node_t *__head;
        __queue_node_t *__tail;
	int __n;
};
typedef struct __queue queue_t;


/*
* SUPPORTED FUNCTIONS BELOW
*/


/*
* make a new queue
* Initializes the queue_t ADT
* Acts as a constructor
*
* @return queue_t* : ptr to new queue just created
*/

queue_t *mk_queue();


/*
* add a new task to the queue
*
* @param queue : the queue to which the new task needs to be added to
* @param task : the task that needs to be added
*/

void enqueue(queue_t *queue, task_t *task);


/*
* remove or consume an item i.e. task
* 
* @param queue : queue from which an item needs to be removed
* 
* @return task_t* : ptr to the task which was just removed 
*/

task_t *dequeue(queue_t *queue);


/*
* get the number of items currently in the queue
*
* @param queue : queue whose current length need to be determined
*
* @return int : the length of the queue	
*/

int get_len(const queue_t *queue);


/*
* check if the queue is empty. A boolean function
* 
* @param queue : queue to be considered
*
* @return int : 0 if queue is empty
*		1 if not empty
*/

int is_queue_empty(const queue_t *queue);


/*
* destroy the queue and free all its contents
* acts a a destructor for queue_t ADT
*
* @param queue : queue which needs to be removed
*/

void destroy_queue(queue_t *queue);

/*
* empties the queue by dumping all current contents
* 
* @param queue : queue which needs to be emptied
*/

void empty_queue(queue_t *queue);

#endif
