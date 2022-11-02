#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"


bool pr; 
/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

void preempt_disable(void)
{
	/* TODO Phase 4
	
	allow the timer to run
	1. create a segset_t temp
	2. check if preempt == 1
	3. call seg_emptyset, seg_addsig(temp), seg_propmask(block/unblock, temp,NULL )
	*/
	
	sigset_t temp;
	if(pr){				// checking if preempt is enabled
	sigemptyset(&temp); // Start with an empty set of signals.
  	sigaddset(&temp, SIGALRM); // Add the SIGALRM signal to the set.
	sigprocmask(SIG_BLOCK, &sigset, NULL);	// examines the signals
	}
}

void preempt_enable(void)
{
	/* TODO Phase 4 
	allow the timer to run
	1. create a segset_t temp
	2. check if preempt == 1
	3. call seg_emptyset, seg_addsig(temp), segvt_alrm, seg_propmask(block/unblock, temp,NULL )	
	*/
 	
	sigset_t temp; 
	if(pr){ // checking if preempt is enabled
	sigemptyset(&temp); // Start with an empty set of signals.
  	sigaddset(&temp, SIGALRM); // Add the SIGALRM signal to the set.
	sigprocmask(SIG_UNBLOCK, &sigset, NULL); // examines the signals
	}
}


void handler(int temp){
	uthread_yield();
}
/*
The following code is inspired by this resource provided by the TA:
https://www.cs.bham.ac.uk/~exr/lectures/opsys/13_14/examples/signals/timer_signals.c
*/
void preempt_start(bool preempt)
{
	pr = preempt;
	if(preempt){
	struct sigaction action;		// Allocate struct on stack.
	action.sa_handler = handler;	// Set the function pointer our handler.
	//action.sa_flags = 0;          // Use no special flags.
	sigfillset(&action.sa_mask);	// Again, full set of signals blocked while this
                                   	// handler runs
	struct itimerval timer;			// creating the struck for the timer
	/*
	setting up the timer
	*/
	timer.it_value.tv_usec = 1000000/HZ;
	timer.it_value.tv_sec = 1;
	timer.it_interval = timer.it_value; 
	}

}

void preempt_stop(void)
{
	/* TODO Phase 4 */
}

