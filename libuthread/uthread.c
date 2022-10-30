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

struct uthread_tcb* current;

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2/4 */
	return current;
}

void uthread_yield(void)
{

	if (queue_length(thread_q) == 0)
		return;
	struct uthread_tcb* cur = uthread_current();
	cur->state = WAITING;
	queue_enqueue(thread_q, cur);
	if(queue_length(thread_q) != 0){
	//printf("in the if statement of yield\n");
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
	//printf("Inside create  \n");
	struct uthread_tcb* newThread = malloc(sizeof(struct uthread_tcb));
	newThread->stack = uthread_ctx_alloc_stack();
	newThread->state = READY;
	newThread->tid = tid;
	newThread->ctx = malloc(sizeof(uthread_ctx_t));
	newThread->nextThread = NULL;
	tid++; 
	int succ = uthread_ctx_init(newThread->ctx, newThread->stack, func, arg);
	if (succ == -1) {
		perror("Error.");
		return -1;
	}
	//preempt_disable();
	queue_enqueue(thread_q, newThread);
	//printf("exiting the create \n");
	//preempt_enable();
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
	idealThread->ctx = malloc(sizeof(uthread_ctx_t));
	//uthread_ctx_init(idealThread->ctx, idealThread->stack, NULL, NULL);
	current = idealThread;
	uthread_create(func, arg);
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

