#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

#include  <stdio.h>

/*
struct for the semphores 
*/
struct semaphore {
	/* TODO Phase 3 */
	queue_t blocked;
	int count;

	
};

sem_t sem_create(size_t count)
{
	// allocate memeory for the semaphore
	struct semaphore* sem = malloc(sizeof(struct semaphore)); 
	// intializes the count 
	sem->count = count;
	// creates a blocked queue for the semephore
	sem->blocked = queue_create();


	return sem; 

}

/*
dealocates the memeory crated for the semaphore 
*/
int sem_destroy(sem_t sem)
{

	if(sem == NULL || sem->blocked != NULL)
		return -1;
	else
		free(sem);
	return 0;
}

int sem_down(sem_t sem)
{

	if(sem == NULL)
		return -1;

	// enqueue the current into the queue if count =< 0
	if(sem->count == 0 || sem->count < 0){
		// gets the current thread 
		struct uthread_tcb* thread = uthread_current();
		// adds it into the blcok queue
		queue_enqueue(sem->blocked, thread);
		uthread_block();
	}
	else{
	// if count is not zero then we decrement the count 
	sem->count--;
	}
	
	
	return 0;

}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */
	if(sem == NULL) {
		return -1;
	}	
	// if there is thread waiting in the sem queue
	if (queue_length(sem->blocked) != 0) {
		// create a void pointer
		void * ptr = malloc(sizeof(ptr));
		// unblocks the thread in sem queue and call the unblock function
		queue_dequeue(sem->blocked, (void**)&ptr);
		uthread_unblock(ptr);
	}
	else{
	// other wise we increment the count
	sem->count++;
	}
	
	return 0;
}
