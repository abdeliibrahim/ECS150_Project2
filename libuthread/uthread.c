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


queue_t thread_q;

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
	return current;
}

void uthread_yield(void)
{
	/* TODO Phase 2 */
	// put the current at the end of the queue
	// get the next thread in the queue
	struct uthread_tcb* cur = uthread_current();
	if(cur->tid != 0){
		cur->state = WAITING;
		queue_enqueue(thread_q, cur);
	}	
	if(queue_length(thread_q) != 0){
	struct uthread_tcb* next = malloc(sizeof(struct uthread_tcb)) ; 
	queue_dequeue(thread_q, (void**)&next);
	next->state = RUNNING;
	current = next;
	uthread_ctx_switch(cur->ctx, next->ctx);
	}

}

void uthread_exit(void)
{
	/* TODO Phase 2 */
	struct uthread_tcb* next = malloc(sizeof(struct uthread_tcb));
	struct uthread_tcb* cur = uthread_current();	
	queue_dequeue(thread_q, (void**)&next);
	cur->state = DONE;
	next->state = RUNNING;
	current = next;
	uthread_ctx_switch(cur->ctx, next->ctx);
}

int uthread_create(uthread_func_t func, void *arg)
{	

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

int uthread_run (bool preempt, uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
	if(thread_q == NULL ){
	thread_q = queue_create();
	struct uthread_tcb* idealThread = malloc(sizeof(struct uthread_tcb));
	idealThread->stack = uthread_ctx_alloc_stack();
	idealThread->state = RUNNING;
	idealThread->tid = tid;
	tid++;
	current = idealThread;
	//uthread_create(func, arg);
	
	}
	else{
		uthread_create(func, arg);
	}

	while(1){
		if(queue_length(thread_q) == 0)
			break;
		uthread_yield();
	}
	return 0;
}

void uthread_block(void)
{
	/* TODO Phase 4 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 4 */
}

