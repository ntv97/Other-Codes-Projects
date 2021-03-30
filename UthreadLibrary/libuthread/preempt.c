#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100


struct sigaction sigact;
struct itimerval timer_int;
sigset_t timer_sig;

/* Handler for SIGVTALRM */
static void timer_inter(__attribute__((unused)) int signum) {
	uthread_yield();
}

/* Disable interrupt */
void preempt_disable(void)
{
	/* TODO Phase 4 */
	sigprocmask(SIG_BLOCK, &timer_sig, NULL);
}

/* Enable alarm */
void preempt_enable(void)
{
	/* TODO Phase 4 */
	sigprocmask(SIG_UNBLOCK, &timer_sig, NULL);
}

/* Start the timer, set the handler, set timer */
void preempt_start(void)
{
	/* TODO Phase 4 */
	memset(&sigact, 0, sizeof(sigact));
	sigemptyset(&timer_sig);

	sigaddset(&timer_sig, SIGVTALRM);
	sigact.sa_handler = &timer_inter;
	sigaction(SIGVTALRM, &sigact, NULL);

	/* specifies when a timer should expire */
	timer_int.it_interval.tv_usec = 1000000/HZ;
	timer_int.it_interval.tv_sec = 0;

	/* period between successive timer interrupts */
	timer_int.it_value.tv_usec = timer_int.it_interval.tv_usec;
	timer_int.it_value.tv_sec = 0;

	setitimer(ITIMER_VIRTUAL, &timer_int, NULL);

}

/* Stop timer inter. */
void preempt_stop(void)
{
	/* TODO Phase 4 */
	timer_int.it_interval.tv_usec = 0;
	timer_int.it_value.tv_usec = 0;

	setitimer(ITIMER_VIRTUAL, &timer_int, NULL);
}
