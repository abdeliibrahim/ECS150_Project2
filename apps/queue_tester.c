#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue.h>

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


void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");
	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue simple */
void  enqueue_simple(queue_t queue, void *data)
{
    int res = queue_enqueue(queue, data);


}

int main(void)
{
	queue_t q;
    q = queue_create();
    for (int i =0; i< 10; i++){
        enqueue_simple(q, &i);
        printf("element %d in q: %s");
    }
	return 0;
}