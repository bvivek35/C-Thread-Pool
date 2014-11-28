#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

#include "threadpool.h"
#include "task.h"
#include "queue.h"


void f()
{
	printf("f()\n");
}
