#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
	/* TODO Phase 3 */
	queue_t blocked;
	int count;
};

sem_t sem_create(size_t count)
{
	/* TODO Phase 3 */
	struct semaphore* sem = malloc(sizeof(struct semaphore));
	sem->count = count;
	sem->blocked = queue_create();
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
	while(sem->count == 0){
		sleep(10);
	}
	return 0;
}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */
}
