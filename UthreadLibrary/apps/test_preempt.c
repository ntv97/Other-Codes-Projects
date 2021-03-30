#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "uthread.h"
#include "private.h"

/* Thread that will run when thread 1 is interrupted */
void thread2(void *arg)
{
	for (int x = 0; x < 20; x++) {
		printf("I am not starving\n");
		printf("Yay!!!\n");
	}
	exit(0);
}

/* Infinite thread that will get interrupted */
void thread1(void *arg)
{
	uthread_create(thread2, NULL);

	while(1) {
        	printf("I'm thread 1, I'm hogging CPU\n");
	}
}

/* Start the thread */
int main(void)
{
	uthread_start(thread1, NULL);
	return 0;
}

