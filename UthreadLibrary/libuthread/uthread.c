#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "queue.h"
#include "uthread.h"

static queue_t exited_q;
static queue_t ready_q;
static struct uthread_tcb *cur_thr;

/* Describes each thread's states */
enum state {
	ready,
	running,
	blocked,
	exited
};

/* Thread control block */
struct uthread_tcb {
        /* TODO Phase 2 */
	enum state t_state;
	uthread_ctx_t *context;
	void *stack;
};

/* Get current running thread */
struct uthread_tcb *uthread_current(void) {
        if(!cur_thr)
                return NULL;

        return
                cur_thr;
}

/* Get new allocated thread */
struct uthread_tcb *get_new_thr(void)
{
        /* TODO Phase 2 */
	struct uthread_tcb *tcb = malloc(sizeof(struct uthread_tcb));

	tcb->t_state = ready;
	tcb->context = malloc(sizeof(uthread_ctx_t));
	tcb->stack = uthread_ctx_alloc_stack();

	return tcb;
}

/* Zombie function that regularly gets cleaned by idle thread */
void zombie_thread(void) {
	if(queue_length(exited_q)==0)
		return;

	struct uthread_tcb *zomb_thr;

	queue_dequeue(exited_q, (void**)&zomb_thr);
	free(zomb_thr->context);
	uthread_ctx_destroy_stack(zomb_thr->stack);
	free(zomb_thr);

}

/* Switch from running current thread to next ready thread */
void uthread_yield(void)
{
        /* TODO Phase 2 */
	preempt_disable();

	struct uthread_tcb *prev_thr = get_new_thr();

	/* Current thread becomes prev_thr, get oldest thread from ready_q,
	 * that becomes cur_thr and context switch */
	prev_thr = cur_thr;
	if(queue_dequeue(ready_q, (void**)&cur_thr) != -1) {
		cur_thr->t_state = running;

		/* Put current current thread into ready_q */
		if(prev_thr->t_state == running) {
			prev_thr->t_state = ready;
			queue_enqueue(ready_q, prev_thr);
		/* If exited thread, deallocate its memory */
		} else if(prev_thr->t_state == exited) {
			queue_enqueue(exited_q, prev_thr);
		}

		/* Context switch from current thread to next ready thread */
		uthread_ctx_switch(prev_thr->context, cur_thr->context);
	}

	preempt_enable();
}

/* State of thread changes to exited and 
 * yield function handle it */
void uthread_exit(void)
{
        /* TODO Phase 2 */
	preempt_disable();

	cur_thr->t_state = exited;
	uthread_yield();

	preempt_enable();
}

/* Create a thread and out into ready queue, enable interr. */
int uthread_create(uthread_func_t func, void *arg)
{
        /* TODO Phase 2 */
	preempt_disable();

	struct uthread_tcb *new_thr = get_new_thr();

	if(!new_thr)
		return -1;

	/* Initialize thread */
	uthread_ctx_init(new_thr->context, new_thr->stack,func, arg);
	queue_enqueue(ready_q, new_thr);

	preempt_enable();

	return 0;
}

/* Idle thread. Initialize queues, turns on preempt,
 * yield, cleans zombie threads, and turn preempt
 * back on at the end  */
int uthread_start(uthread_func_t func, void *arg)
{
        /* TODO Phase 2 */
	preempt_start();
	preempt_enable();

	ready_q = queue_create();
	exited_q = queue_create();
	cur_thr = get_new_thr();
	cur_thr->t_state = running;

	if(uthread_create(func, arg))
		return -1;

	/* Idle loop, yielding and cleaning up 
	 * exited thread */
	while(queue_length(ready_q)) {
		uthread_yield();
		zombie_thread();
	}

	while(queue_length(exited_q)) {
		zombie_thread();
	}

	queue_destroy(ready_q);
	queue_destroy(exited_q);

	/* Turn off preempt when finished */
	preempt_disable();
	preempt_stop();

	return 0;
}

/* Yield function handles block threads */
void uthread_block(void)
{
        /* TODO Phase 2/3 */	
	cur_thr->t_state = blocked;
	uthread_yield();
}

/* Change state and add it back to ready_q */
void uthread_unblock(struct uthread_tcb *uthread)
{
        /* TODO Phase 2/3 */
	uthread->t_state = ready;
	queue_enqueue(ready_q, uthread);
}
