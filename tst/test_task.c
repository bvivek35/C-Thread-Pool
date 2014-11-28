#include <stdio.h>
#include <stdlib.h>

#include "task.h"

void *f(void *arg)
{
	printf("running f(%d)\n", (int)arg);
	return 10;
}

int main()
{
	task_t *t = mk_task(f, 4);
	
	printf("got back : %d\n", run_task(t));
}
