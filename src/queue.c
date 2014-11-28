/*
* Implememtation of a FIFO data structure
* Each item of the queue contains a task(well a ptr to it)
*/	

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "task.h"

/*
* Free a node of the queue.
* Note this does not free the task assoc with that node.
* You will need to call destroy_task(SEE include/task.h) explicitly 
*/
static void destroy_queue_node(__queue_node_t *);


/*
* A function that returns a new queue.
* SEE include/queue.h 
*/

queue_t *mk_queue()
{
#if 0
	printf("mk_queue()\n");
	
	return NULL;
#endif		
	
	queue_t *tmp = malloc(sizeof *tmp);
	
	tmp->__head = NULL;
	tmp->__tail = NULL;
	tmp->__n = 0;
	
	return tmp;
}

/*
* Add a task to the queue
* Insert from tail end
* Delete from head end
* SEE include/queue.h
*/

void enqueue(queue_t *queue, task_t *task)
{
#if 0
	printf("enqueue\n");
#endif
	__queue_node_t *tmp = malloc(sizeof tmp);
	tmp->__task = task;
	tmp->__link = NULL;
	
	if (queue->__n == 0)
	{
		/*setup head for 1st insertion*/
		queue->__head = tmp;	
	}
	else
	{	
		/*add to the tail end*/
		queue->__tail->__link = tmp;
	}
	
	queue->__tail = tmp;
	
	queue->__n += 1;
}

/*
* Remove a task from the queue
* SEE include/queue.h	
*/

task_t *dequeue(queue_t *queue)
{
#if 0
	printf("dequeue()\n");
	
	return NULL;
#endif
	
	__queue_node_t *tmp = queue->__head;	
	
	task_t *ret_task = tmp->__task;
	
	queue->__head = queue->__head->__link;
	
	/*reset if empty queue*/	
	if (!queue->__head)
	{
		queue->__head = NULL;
		queue->__tail = NULL;
	
	}
	
	destroy_queue_node(tmp);
	
	queue->__n -= 1;
	
	return ret_task;
}

/*
* Get the current no. of items in the queue
* SEE include/queue.h	
*/

int get_len(const queue_t *queue)
{
	return queue->__n;
}

/*
* Chcek if the queue is empty.
* Boolean function.
* 1 -> empty
* 0 -> non empty
* SEE include/queue.h 	
*/

int is_queue_empty(const queue_t *queue)
{
	return queue->__n == 0;
}

/*
* Destroy the queue.
* Frees all nodes ALONG WITH ASSOC TASK
* SEE include/queue.h
*/

void destroy_queue(queue_t *queue)
{
#if 0	
	printf("destroy_queue()\n");
#endif
	
	__queue_node_t *head = queue->__head;
	__queue_node_t *tmp;
	
	while (head)
	{
		tmp = head;
		
		head = head->__link;
		
		destroy_task(tmp->__task);
		destroy_queue_node(tmp);
	}
	free(queue);
}

/*
* Just free the node WITHOUT THE ASSOC TASK
*/
static void destroy_queue_node(__queue_node_t *tmp)
{
	free(tmp);
}
