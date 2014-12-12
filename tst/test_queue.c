#include <stdio.h>
#include <stdlib.h>

#include "task.h"
#include "queue.h"

void *f1(void *arg)
{
	printf("f1(%d)\n", (int)arg);
	return (void *)10;
}

void *f2(void *arg)
{
	printf("f2(%d)\n", (int)arg);
	return (void *)12;
}

int main()
{
	queue_t *q1 = mk_queue();
	
	printf("%d\n", get_len(q1));
	printf("%d\n", is_queue_empty(q1));
	
	enqueue(q1, mk_task(f1,(void *) 5));
	enqueue(q1, mk_task(f2, (void *)7));

	printf("%d\n", get_len(q1));
	printf("%d\n", is_queue_empty(q1));

	enqueue(q1, mk_task(f2, (void *)2));
	enqueue(q1, mk_task(f1, (void *)9));
	
	printf("%d\n", get_len(q1));
	printf("%d\n", is_queue_empty(q1));
	
	run_task(dequeue(q1));
	run_task(dequeue(q1));
	
	printf("%d\n", get_len(q1));
	printf("%d\n", is_queue_empty(q1));
	
	run_task(dequeue(q1));
	run_task(dequeue(q1));
	
	printf("%d\n", get_len(q1));
	printf("%d\n", is_queue_empty(q1));
	
	empty_queue(q1);		
	
	enqueue(q1, mk_task(f2, (void *)2));
	enqueue(q1, mk_task(f1, (void *)9));
	
	printf("%d\n", get_len(q1));
	printf("%d\n", is_queue_empty(q1));

	destroy_queue(q1);
}
