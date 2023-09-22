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
/* Callback function that increments items */
static void iterator_inc(queue_t q, void *data)
{
    int *a = (int*)data;

    if (*a == 42)
        queue_delete(q, data);
    else
        *a += 1;
}

void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    size_t i;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Increment every item of the queue, delete item '42' */
    queue_iterate(q, iterator_inc);
    TEST_ASSERT(data[0] == 2);
    TEST_ASSERT(queue_length(q) == 9);
}

/* test dequeue when queue size is zero */
void test_dequeue_zero()
{
    int *ptr;
    fprintf(stderr, "*** TEST dequeue_zero ***\n");
    queue_t q;
    q = queue_create();
    TEST_ASSERT(queue_dequeue(q, (void**)&ptr) == -1);

}

/* test equeue length */
void test_queue_length()
{
    int data[] = {1, 2, 3, 4, 5};
	queue_t q;
	fprintf(stderr, "*** TEST queue_length ***\n");
	q = queue_create();
    size_t i;
    for (i = 0; i < 5; i++)
    {
		queue_enqueue(q, &data[i]);
	}
    TEST_ASSERT(queue_length(q) == 5);
}

/* test queue length when size=NULL*/
void test_queue_NULL()
{
    queue_t q = NULL;
	q = queue_create();
	fprintf(stderr, "*** TEST queue_NULL ***\n");
	TEST_ASSERT(queue_length(q) == 0);
}

int main(void)
{
	test_create();
	test_queue_simple();
	test_iterator();
    test_dequeue_zero();
    test_queue_length();
    test_queue_NULL();
	return 0;
}