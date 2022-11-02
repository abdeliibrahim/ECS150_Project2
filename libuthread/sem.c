#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

#include  <stdio.h>

int c = 1;
struct semaphore {
	/* TODO Phase 3 */
	queue_t blocked;
	int count;
	int counter;
	
};

sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
	struct semaphore* sem = malloc(sizeof(struct semaphore));
	sem->count = count;
	sem->blocked = queue_create();
	sem->counter = c;
	c++;
	return sem; 

}

int sem_destroy(sem_t sem)
{
	/* TODO Phase 3 */
	if(sem == NULL || sem->blocked != NULL)
		return -1;
	else
		free(sem);
	return 0;
}

int sem_down(sem_t sem)
{
	/* TODO Phase 3 */
	if(sem == NULL)
		return -1;

	// enqueue the current into the queue if count =< 0
	if(sem->count == 0 || sem->count < 0){
		struct uthread_tcb* thread = uthread_current();
		queue_enqueue(sem->blocked, thread);
		uthread_block();
	}
	else{
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
	
	if (queue_length(sem->blocked) != 0) {
		void * ptr = malloc(sizeof(ptr));
		queue_dequeue(sem->blocked, (void**)&ptr);
		uthread_unblock(ptr);
	}
	else{
	sem->count++;
	}
	
	
	return 0;
}
