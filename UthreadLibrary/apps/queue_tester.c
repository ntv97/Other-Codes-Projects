#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

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

queue_t q;
int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int *ptr;

/* Enqueue all elements of data in q */
void enqueue_all(void) {
	for (unsigned i = 0; i < sizeof(data) / sizeof(data[0]); i++)
		queue_enqueue(q, &data[i]);
}

/* Dequeue all the elements in q */
void dequeue_all(void) {
        int *ptr, len = queue_length(q);

        for (int i = 0; i < len; i++)
                queue_dequeue(q, (void**)&ptr);
}

/* Print one data */
void print(void *data) {
	int *ptr = (int *)data;
	printf("data = %d\n", *ptr);
}

/* Increment and delete data 5 */
static void inc_item(void *data) {
	int *a = (int*)data;

	*a += 1;
}

/* Print */
/* Enqueue data, inc each by 1 */
/* Should end up w/ 2,3,4,7,8,9,10,11  in q */
void test_iter(void) {
	queue_iterate(q, inc_item);
	printf("After inc each item:\n");
	queue_iterate(q, print);
	TEST_ASSERT(data[0] == 2);
}

/* Destroy (if queue still contains items, dequeue all first) */
void test_destroy(void) {
	if(queue_length(q) !=0)
		dequeue_all();

	TEST_ASSERT(queue_destroy(q) == 0);
}

/* Delete first(2), middle(6), and last(11) elements */
/* Should end up w/ 3,4,5,7,8,9,10  in q */
static void iter_delete(void *data) {
	int *element = (int*)data;

	printf("data = %d\n", *element);
	if(*element == 2 || *element == 6 || *element == 11)
		TEST_ASSERT(queue_delete(q, data) != -1);
}

/* Testing delete by calling iter_delete */
void test_delete(void) {
	queue_iterate(q, iter_delete);

	printf("After deleting 2,6,11 from queue: \n");
	queue_iterate(q, print);
	TEST_ASSERT(queue_length(q) == 7);

}

/* Create */
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}

/* Enqueue, dequeue all, enqueue again to test if reusable */
void test_reuse() {
	enqueue_all();
	TEST_ASSERT(queue_length(q) == 10);
	dequeue_all();
	TEST_ASSERT(queue_length(q) == 0);
	enqueue_all();
	TEST_ASSERT(queue_length(q) == 10);
}

int main(void)
{
	test_create();
	test_queue_simple();
	test_reuse();
	test_iter();
	test_delete();
	test_destroy();

	return 0;
}
