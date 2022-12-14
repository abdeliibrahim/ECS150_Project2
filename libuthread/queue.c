#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#include <assert.h>
#include <stdio.h>

struct node
{
	int val;
	struct node *next;
};
struct queue
{
	struct node *head;
	struct node *tail;
	struct node *cur;
	struct node *prev;
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
	else
	{
		free(&queue); // maybe get rid of &
	}
	return (0);
}

int queue_enqueue(queue_t queue, void *data)
{
	if (data == NULL || queue == NULL || queue->count == sizeof(struct queue))
		return -1;

	if (queue->head == NULL)
	{
		queue->head = data;
		queue->head->next = NULL;
	}
	else if (queue->head != NULL)
	{
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

int queue_delete(queue_t queue, void *data)
{
	if (queue == NULL || data == NULL)
		return -1;

	if (queue->head == data)
	{
		queue->head = queue->head->next;
	}
	
	if (queue->head != data){
		queue->cur = queue->head;
		queue->prev;
		while (queue->cur != data)
		{
			queue->prev = queue->head;
			queue->cur = queue->cur->next;
		
		}
		queue->prev->next = queue->cur->next;

	}
	queue->count--;
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	if (queue == NULL || func == NULL)
		return -1;
	return 0;
}

int queue_length(queue_t queue)
{
	if (queue->count == 0)
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
	int data = 0, *ptr;
	int data2 = 1;
	int data3 = 2;
	int data4 = 3;
	int data5= 4;
	queue_t q;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, 1);
	queue_enqueue(q, 2);
	queue_enqueue(q, 3);
	queue_enqueue(q, 4);
	queue_enqueue(q, 5);
	printf("%d\n", queue_length(q));
	queue_delete(q, data);
	printf("%d\n", queue_length(q));
	

}

int main(void)
{
	test_create();
	test_queue_simple();


	return 0;
}