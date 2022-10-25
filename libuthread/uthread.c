#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"

#define START 0
#define READY 1
#define RUNNING 2
#define WAITING 3
#define DONE 4


queue_t glob; 
struct uthread_tcb {
	
	uthread_ctx_t *ctx;
	int state;
	void *stack;

	
	pid_t tid; //thread id
	

};

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2/4 */
}

void uthread_yield(void)
{
	/* TODO Phase 2 */
}

void uthread_exit(void)
{
	/* TODO Phase 2 */
}

int uthread_create(uthread_func_t func, void *arg)
{
	
/* TODO Phase 2 */
}

int uthread_start(uthread_func_t func, void *arg)
{
	func(arg);
	/* TODO Phase 2 */
}

void uthread_block(void)
{
	/* TODO Phase 4 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 4 */
}

