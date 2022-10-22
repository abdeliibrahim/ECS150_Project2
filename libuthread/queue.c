#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

struct queue {
	void* q[256];
	int counter; 
	int first;
};

queue_t queue_create(void)
{
	queue_t queue = malloc(sizeof(struct queue));
	queue->counter= 0;
	queue->first = 0;
	return (queue);	
}

int queue_destroy(queue_t queue)
{
	if (queue->q[0] != NULL || queue->counter != 0)
		return (-1);
	else{
		free(queue);
	}
	return(0);
	
}

int queue_enqueue(queue_t queue, void *data)
{
	if(data == NULL || queue == NULL)
		return -1;
	queue->q[queue->counter] = data;
	queue->counter++;
	return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	if (queue == NULL || queue->q[queue->first] == NULL)
		return -1;
	*data = queue->q[queue->first];
	queue->q[queue->first] = NULL;
	queue->first++;
	if(queue->first == queue->counter){
		queue->counter = 0;
	}
	
	
	
		
	return 0;
}

int queue_delete(queue_t queue, void *data)
{
	if(queue == NULL || data == NULL)
		return -1;
	int temp=0 ;
	for (int i =queue->first; i < queue->counter; i++){
		if(queue->q[i] == data){
			temp = i;
			break;
		}		
	}
	while(temp< queue->counter){
		queue->q[temp] = queue->q[temp+1];
	}
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func){
	if(queue == NULL || func == NULL)
		return -1;
	return 0;
	
}

int queue_length(queue_t queue)
{
	if(queue->counter == 0)
		return -1;

	return queue->counter;
	
}