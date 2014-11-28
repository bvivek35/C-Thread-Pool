/*
* Interface to the task_t ADT
* task_t can store a function and an arg that it can accept
* this information can be used to call the function
*
* SEE src/task.c for the implementation
*
* Look below for supported functions
*/


#ifndef TASK_H

#define TASK_H


/*
* ADT to store the function and it's arg.
*
* @var func : a ptr to the function that needs to be stored
* @var arg : argument that needs to be passed to the function at it's call
* If you ned to pass multiple arguments, then pass a structure.
*/

struct __task
{
	void *(*__func)(void *);
	void *__arg;
};
typedef struct __task task_t;


/*
* SUPPORTED FUNCTIONS BELOW
*/


/*
* creates a new task_t given the function and its arg.
* acts as a constructor
*
* @param void *(*)(void *) : ptr to the function
* @param void * : the arg
*/

task_t *mk_task(void *(*)(void *), void *);


/*
* getter function for the function stored in task_t
*
* @param const task_t* : the task whose fn needs to be extracted
*
* @return void *(*)(void *) : the fn ptr itself
*
* Cryptic declaration of get_func. Let's try to decode it
* RULES :
* 1) Read from right and then left. Keep alternating.
* 2) If a parenthesis is present, it gets higher precedence than rule-1
*       
* get_func is a fn taking const task_t* as arg 
*        (and rest of the decl is return type)
*               returning ptr to a fn taking 
*                       void* as arg 
*                       returning void*
*/

void *(*get_func(const task_t *))(void *);


/*
* getter function for the arg stored in the task_t ADT
*
* @param task_t* : the task_t whose arg needs to be extracted
* 
* @return void* : the arg itself
*/

void *get_arg(const task_t *);


/*
* free the task_t
* acts as a destructor
*
* @param task_t* : the task_t that needs to be freed
*/

void destroy_task(task_t *);


/*
* execute the function contained in the task_t along with assoc arg
*
* @param task_t* : the task_t which contains fn and arg
*
* @return void* : the return value that the function returns is passed back
*/

void *run_task(const task_t *);


#endif
