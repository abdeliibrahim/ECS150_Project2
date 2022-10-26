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


queue_t* thread_q;

int tid;  
struct uthread_tcb {
	
	uthread_ctx_t *ctx;
	int state;
	void* stack; 
	pid_t tid; //thread id
	struct uthread_tcb* nextThread; // this has to point to the next thread in the queue, intailly it will be null 
	
};

static struct uthread_tcb* current;

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2/4 */
	queue_dequeue(thread_q, current);
	return current;
}

void uthread_yield(void)
{
	/* TODO Phase 2 */
	struct uthread_tcb* next; 
	struct uthread_tcb* cur = uthread_current();	
	queue_dequeue(thread_q, next);
	cur->state = DONE;
	next->state = RUNNING;
	current = next;
	uthread_ctx_switch(cur->ctx, next->ctx);
}

void uthread_exit(void)
{
	/* TODO Phase 2 */
	struct uthread_tcb* next; 
	struct uthread_tcb* cur = uthread_current();	
	queue_dequeue(thread_q, next);
	cur->state = DONE;
	next->state = RUNNING;
	queue_enqueue(thread_q, cur);
	current = next;
	uthread_ctx_switch(cur->ctx, next->ctx);
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
	queue_enqueue(thread_q, newThread);
	return succ;
	
	
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	if(thread_q == NULL){
	thread_q = queue_create();
	uthread_create(func, arg);
	struct uthread_tcb* intailThread;
	intailThread = uthread_current();
	intailThread->state = RUNNING;
	queue_enqueue(thread_q,intailThread);
	
	}
	else{
		uthread_create(func, arg);
	}

	while(1){
		if(queue_length(thread_q) == NULL);
			break;
		thread_yeild();
	}

}

void uthread_block(void)
{
	/* TODO Phase 4 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 4 */
}

