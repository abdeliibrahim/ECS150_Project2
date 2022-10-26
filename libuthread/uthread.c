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

//#define START 0
#define READY 0
#define RUNNING 1
#define WAITING 2
#define Block 3
#define DONE 4


queue_t glob;

int tid;  
struct uthread_tcb {
	
	uthread_ctx_t *ctx;
	int state;
	void* stack; 
	pid_t tid; //thread id
	struct uthread_tcb* nextThread; // this has to point to the next thread in the queue, intailly it will be null 
	
};

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2/4 */
	
}

void uthread_yield(void)
{
	/* TODO Phase 2 */
	// Context switching in yelled 
}

void uthread_exit(void)
{
	/* TODO Phase 2 */
	// also context switching 
}

int uthread_create(uthread_func_t func, void *arg)
{	
	// This function looks good according to the TA
	// push it into the queue after it was created
	// Info the current thread
	struct uthread_tcb* newThread = malloc(sizeof(struct uthread_tcb));
	newThread->stack = uthread_ctx_alloc_stack();
	newThread->state = READY;
	newThread->tid = tid;
	newThread->nextThread = NULL;
	tid++; 
	int succ = uthread_ctx_init(newThread->ctx, newThread->stack, func, arg);
	queue_enqueue(glob, newThread);
	return succ;
	
	
}

int uthread_start(uthread_func_t func, void *arg)
{
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

