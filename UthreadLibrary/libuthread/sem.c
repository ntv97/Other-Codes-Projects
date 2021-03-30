#include <stddef.h>
#include <stdlib.h>

#include "private.h"
#include "queue.h"
#include "sem.h"

/* Semaphore obj. that has a count and 
 * queue of blocked threads */
struct semaphore {
	/* TODO Phase 3 */
	size_t count;
	queue_t blocked_threads;
};

/* Create new allocated semaphore obj. */ 
sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
	sem_t new_Sem = (sem_t)malloc(sizeof(struct semaphore));

	if(!new_Sem)
		return NULL;

	new_Sem->blocked_threads = queue_create();
	new_Sem->count = count;

	return new_Sem;
}

/* Destroy sem obj. */
int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */
	if(!sem)
		return -1;

	queue_destroy(sem->blocked_threads);
	free(sem);
	
	return 0;
}

/* Takes lock, decrement by one */
int sem_down(sem_t sem)
{
	/* TODO Phase 3 */
	preempt_disable();

	if(!sem)
		return -1;

	/* If sem->count is 0 block the thread */
	if (sem->count == 0) {
		struct uthread_tcb *blocked_thr;

		blocked_thr = uthread_current();
		/* Enqueue into sem's blocked queue */
		queue_enqueue(sem->blocked_threads, blocked_thr);

		/* uthread's block will make it yield */
		uthread_block();
	} else {
		sem->count -= 1;
	}

	preempt_enable();

	return 0;
}

/* Release lock, increment by one */
int sem_up(sem_t sem)
{
        /* TODO Phase 3 */
	preempt_disable();

        if(!sem) {
                return -1;
        }

	/* If there are blocked threads, unblock the oldest blocked */
	if (queue_length(sem->blocked_threads) > 0 ) {
                struct uthread_tcb* new_thr;

                queue_dequeue(sem->blocked_threads, (void**)&new_thr);

		uthread_unblock(new_thr);
        } else {
		sem->count += 1;
	}

	preempt_enable();

        return 0;
}

