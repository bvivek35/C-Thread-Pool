/*
* File contains implementation of the task_t ADT
* Stores a fn and a var to be passed to it
* This info can later be used to invoke a call to that fn as was intended
*
* Implements the include/task.h interface
*/

#include <stdio.h>
#include <stdlib.h>

#include "task.h"


/*
* Creates a task from the given function ptr and arg.
*/

task_t *mk_task(void *(*func)(void *), void *arg)
{
#if 0
	printf("mktask()\n");
	
	return NULL;
#endif
	
	task_t *tmp = malloc(sizeof *tmp);
	tmp->__func = func;
	tmp->__arg = arg;
	
	return tmp;
	
}

/*
* Getter method for the function held in the task
*
* Cryptic declaration of get_func. Let's try to decode it
* RULES :
* 1) Read from right and then left. Keep alternating.
* 2) If a parenthesis is present, it gets higher precedence than rule-1
*	
* get_func is a fn taking const task_t* as arg 
*        (and rest of the decl is return type)
* 		returning ptr to a fn taking 
*			void* as arg 
*			returning void*
*/

void *(*get_func(const task_t *task))(void *)
{
#if 0
	printf("get_func()\n");
	
	return NULL;
#endif
	
	return task->__func;
}


/*
* Getter function for the arg held in task
*/

void *get_arg(const task_t *task)
{
#if 0
	printf("get_arg()\n");
	
	return NULL;
#endif
	
	return task->__arg;
}


/*
* frees memory used by the task structure
*/

void destroy_task(task_t *task)
{

#if 0	
	printf("destroy_task()\n");
#endif	
	free(task);
}


/*
* Executes the function in the task with its assoc arg
*/

void *run_task(const task_t *task)
{
	return get_func(task)(get_arg(task));
}
