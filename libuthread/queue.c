#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#include <assert.h>
#include <stdio.h>



struct node {
	void* val;
	struct node* next;
};
struct queue {
	struct node *head;
	struct node *tail;
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
	if (queue->head == NULL || queue->count == 0)
		return (-1);
	else{
		//free((void*)queue->head);
		//free((void*)queue->tail);
		//(queue->count = NULL);
		free(queue);
	}
	return(0);
	
}

int queue_enqueue(queue_t queue, void *data)
{
	if(data == NULL || queue == NULL || queue->count == sizeof(struct queue)) 
		return -1;
	
	struct node* newNode = malloc(sizeof(struct node));
	newNode->val = data;
	newNode->next= NULL;

	if (queue->head == NULL) {
		queue->head = queue->tail= newNode;
	}
	else if (queue->head != NULL) {
		queue->tail->next = newNode;
		queue->tail = newNode;
	}
	queue->count++;
	return 0;
}

int queue_dequeue(queue_t queue, void **data) // ptr= null 
{
	if (queue == NULL || data == NULL)
		return -1;
	
	struct node *decapitated = NULL;
	decapitated = queue->head;
	*data = (decapitated->val); 
	queue->head = queue->head->next;
	queue->count--;
	if (queue->head == NULL) {
		queue->tail = NULL;
	}
	free(decapitated);		
	return 0;
}


int queue_delete(queue_t queue, void *data) 
{
	if(queue->count == 0 || data == NULL)
		return -1;
	
	int found =0; 

	if(queue->head->val == data){
		struct node *decapitated = NULL;
		decapitated = queue->head;
		queue->head = queue->head->next;
		free(decapitated);	
		found = 1;
	}

	else{
		struct node* cur; 
		struct node* next; 
		cur = queue->head;
		while (cur->next != NULL)
		{
			next = cur->next;
			if(cur->next->val == data){
				struct node* remove = cur->next;
				cur->next = cur->next->next;
				free(remove);
				found = 1;
				break;
			}
			cur = next;
		}
	}
	if(found == 1)
		queue->count--;
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func){
	if(queue == NULL || func == NULL)
		return -1;
	
	struct node* cur; 
	struct node* next; 
	cur = queue->head;
		while (cur!= NULL)
		{	next = cur->next;
			func(queue, cur->val);
			cur = next;
		}

	return 0;
	
}

int queue_length(queue_t queue)
{
	if(queue== NULL)
		return -1;

	return queue->count;
	

}



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
	int data1 = 4;
	int data2= 5;
	int data3 = 6;
	queue_t q;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_enqueue(q, &data2);
	queue_enqueue(q, &data3);
	queue_enqueue(q, &data1);
	printf("%d\n", queue_length(q));
	queue_iterate(q, queue_delete);
	printf("%d\n", queue_length(q));
	//queue_dequeue(q, (void**)&ptr);
	
}

int main(void)
{
	test_create();
	test_queue_simple();


	return 0;
}
