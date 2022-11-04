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


// The different states for our threads
#define READY 0
#define RUNNING 1
#define WAITING 2
#define Block 3
#define DONE 4

// our ready queue for the threads 
queue_t thread_q;

// needed for thread ID
int tid;  
// the control block of the thread
struct uthread_tcb {
	
	uthread_ctx_t *ctx;
	int state;
	void* stack; 
	pid_t tid; 
};

// the current running thread
struct uthread_tcb* current;

struct uthread_tcb *uthread_current(void)
{
	// the function returns a pointer to the current running thread
	return current;
}

void uthread_yield(void)
{
	// disabling the interupts 
	preempt_disable();
	if (queue_length(thread_q) == 0)
		return;
	// getting the current thread
	struct uthread_tcb* cur = uthread_current();
	// check if the current thread is not block so we can put it back in the queue
	if(cur->state != Block){
	cur->state = WAITING;
	queue_enqueue(thread_q, cur);
	}	
	if(queue_length(thread_q) != 0){
	// getting the next ready thread and chaning the states
	struct uthread_tcb* next = malloc(sizeof(struct uthread_tcb)) ; 
	queue_dequeue(thread_q, (void**)&next);
	next->state = RUNNING;
	// chnaging the current thread to the thread that we jused dequeued
	current = next;
	// context switching between threads
	uthread_ctx_switch(cur->ctx, next->ctx);
	// unabling the interupts
	preempt_enable();
	}

}

void uthread_exit(void)
{
	preempt_disable();
	// allocating memmory for the next thread 
	struct uthread_tcb* next = malloc(sizeof(struct uthread_tcb));
	// tgetting the current thread
	struct uthread_tcb* cur = uthread_current();	
	// getting the next ready queue 
	queue_dequeue(thread_q, (void**)&next);
	cur->state = DONE;
	next->state = RUNNING;
	// chnaging the current thread to the thread that we jused dequeued
	current = next;
	// context switching between threads
	uthread_ctx_switch(cur->ctx, next->ctx);
	preempt_enable();
}

int uthread_create(uthread_func_t func, void *arg)
{	
	/*
	allocating the memory for the new thread that we are creating and intailizing
	the components of theis thread
	*/
	struct uthread_tcb* newThread = malloc(sizeof(struct uthread_tcb));
	newThread->stack = uthread_ctx_alloc_stack();
	newThread->state = READY;
	newThread->tid = tid;
	newThread->ctx = malloc(sizeof(uthread_ctx_t));
	tid++; 
	// creating the thread using the init funtion
	int succ = uthread_ctx_init(newThread->ctx, newThread->stack, func, arg);
	if (succ == -1) {
		perror("Error.");
		return -1;
	}
	// enqueuing the the thread into our ready queue
	queue_enqueue(thread_q, newThread);
	return succ;

	
	
}

int uthread_run (bool preempt, uthread_func_t func, void *arg)
{
	/*
	checking if it is the first time we have came to this function, if yes, then
	we create the an ideal thread, and the ready queue using the following code
	*/
	if(thread_q == NULL ){
	// starting the preempt schedualing
	preempt_start(preempt);
	thread_q = queue_create();
	/*
	following 7 lines creates the ideal thread and intializes the required
	component of the thread and set the current thread to ideal thread
	*/
	preempt_disable();
	struct uthread_tcb* idealThread = malloc(sizeof(struct uthread_tcb));
	idealThread->stack = uthread_ctx_alloc_stack();
	idealThread->state = RUNNING;
	idealThread->tid = tid;
	tid++;
	idealThread->ctx = malloc(sizeof(uthread_ctx_t));
	current = idealThread;
	preempt_enable();
	// create the first thread, aside from the ideal thread
	uthread_create(func, arg);

	}
	else{

		uthread_create(func, arg);
	}
	
	/*
	loop runs untul the thread queue is not empty and calling the yield fucntion
	every iteration 
	*/
	if(preempt)
		preempt_start(preempt);
	while(1){
		
		if(queue_length(thread_q) == 0)
			break;
		uthread_yield();
	}
	preempt_stop();
	return 0;
}

void uthread_block(void)
{

	/*
	gets the current thread and blocks it from running 
	*/
	struct uthread_tcb* cur = uthread_current();	
	cur->state = Block;
	uthread_yield();

}

void uthread_unblock(struct uthread_tcb *uthread)
{
	// unblocks the given thread and puts into the ready queue
	uthread->state = READY;
	queue_enqueue(thread_q, uthread);

}

