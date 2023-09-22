
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"

struct Node {
	void *data;
	struct Node *next;
};
struct queue {
	struct Node *head;
	struct Node *tail;
	size_t length;
};



queue_t queue_create(void)
{
	/* TODO Phase 1 */

	queue_t queue;

	if (NULL !=(queue = (queue_t)malloc(sizeof(struct queue)))) {
		queue->length = 0;
		queue->head = queue->tail = NULL;
		return queue;
	}

	return NULL;
}

int queue_destroy(queue_t queue)
{
	if (queue == NULL || queue->length > 0)
		return -1;
	else
		free(queue);
	return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */

	struct Node *new_node;
	new_node = malloc(sizeof(struct Node));
	if (new_node == NULL){
		return -1;
	}
	new_node->data = data;
	new_node->next = NULL;
	// first node
	if(queue->head == NULL && queue->tail == NULL) {
		queue->head = queue->tail = new_node;
		++queue->length;
		return 0;
	}
	else{
		queue->tail->next = new_node;
		queue->tail = new_node;
		++queue->length;
		return 1;
	}

	return -1;
}

int queue_dequeue(queue_t queue, void **data)
{
	if (data == NULL || queue == NULL || queue->length == 0)
		return -1;
	struct Node *new_node = queue->head;
	*data = new_node->data;
	queue->head = queue->head->next;
	free(new_node);
	// Nothing left to point to, set both pointers to null
	if(queue->head == NULL) {
		queue->tail = NULL;
		queue->length = 0;
		return 0;
	}
	--queue->length;
	return 0;

}

int queue_delete(queue_t queue, void *data)
{
	int i = 0;
	struct Node *curr_node,*prev_node;
	curr_node = prev_node = queue->head;
	if(queue->head == NULL)
		return -1;
	while (i<queue_length(queue)) {
		if (curr_node->data == data) {
			prev_node->next = curr_node->next;
			curr_node = curr_node->next;
			--queue->length;
			return 0;
		}
		else {
			prev_node = curr_node;
			curr_node = curr_node->next;
		}
		++i;
	}
	return -1;
}

int queue_iterate(queue_t queue, queue_func_t func)
{
	int i = 0;
	struct Node *curr_node = queue->head;
	if(queue->head == NULL)
		return -1;
	while (i<queue_length(queue)){
		func(queue,curr_node->data);
		curr_node = curr_node->next;
		++i;
	}
	return 0;
}

int queue_length(queue_t queue)
{
	return queue->length;
}

