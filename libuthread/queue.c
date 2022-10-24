#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


struct node {
	int val;
	struct node* next;
};
struct queue {
		struct node* head;
		struct node* tail;
		int count;

};


queue_t queue_create(void)
{
	queue_t queue = malloc(sizeof(struct queue));
	queue->head = NULL;
	queue->tail = NULL;
	queue->count = 0;
	return queue;
}

int queue_destroy(queue_t queue)
{
	if (queue->head == NULL || queue->count != 0)
		return (-1);
	else{
		free(&queue);  // maybe get rid of &
	}
	return(0);
	
}

int queue_enqueue(queue_t queue, void *data)
{
	if(data == NULL || queue == NULL || queue->count == sizeof(struct queue)) 
		return -1;
	
	if (queue->head == NULL) {
		queue->head = data;
		queue->head->next = NULL;
	}
	else if (queue->head != NULL) {
		queue->tail->next = data;
		data = queue->tail;
		queue->tail->next = NULL;
		
	}
	queue->count++;
	return 0;
}

int queue_dequeue(queue_t queue, void **data) // ptr= null 
{
	if (queue == NULL || queue->head == NULL)
		return -1;
	*data = queue->head; 
	queue->head = queue->head->next;
	
	queue->count--;
	
		
	return 0;
}
/*

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
	if(queue->count == 0)
		return -1;

	return queue->count;
	

}*/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>



#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3, *ptr;
	queue_t q;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}

int main(void)
{
	test_create();
	test_queue_simple();


	return 0;
}

