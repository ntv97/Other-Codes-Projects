#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

typedef struct node* node_t;

/* Node struct to hold data items */
struct node {
	void *item;
	node_t next;
};

/* Queue with head pointing to first node and tail to last node */
struct queue {
	int len;
	node_t head;
	node_t tail;
};

/* Returns allocated empty queue */
queue_t queue_create(void)
{
	queue_t empty_q = (queue_t)malloc(sizeof(struct queue));

	if(!empty_q)
		return NULL;

	empty_q->len = 0;

	return empty_q;
}

/* Destroys queue if it's empty */
int queue_destroy(queue_t queue)
{
	if(queue == NULL || queue->len)
		return -1;
	
	free(queue);
	return 0;
}

/* Add data item to end of queue */
int queue_enqueue(queue_t queue, void *data)
{
	node_t current = (node_t)malloc(sizeof(struct node));

	if(!queue || !data || !current) 
		return -1;

	current->item = data;
	current->next = NULL;

	/* If queue is empty, head and tail
	 * points to first element */
	if(queue->len == 0) {
		queue->head = queue->tail = current;
	} else {
		queue->tail->next = current;
		queue->tail = current;
	}

	queue->len +=1;

	return 0;

}

/* Get oldest item and remove */
int queue_dequeue(queue_t queue, void **data)
{
	if(!queue || !data || !queue->len)
		return -1;

	node_t oldest = queue->head;

	/* Get first node and move head 
	 * to the next node */
	*data = oldest->item;
	queue->head = queue->head->next;
	queue->len -= 1;
	free(oldest);

	return 0;
}

/* Delete item specified by data */
int queue_delete(queue_t queue, void *data)
{
	if(!queue || !data || !queue->head->item)
		return -1;

	node_t cur = queue->head;

	/* If first item to delete is head,
	 * move head to next node */
	if(queue->head->item == data) {
		queue->head = queue->head->next;
		memset(&cur, 0, sizeof(cur));
		free(cur);
		queue->len -= 1;
		return 0;
	}

	node_t next = queue->head->next;

	/* Point the previous node to the current
	 * node's next */
	while(next) {
		if(next->item == data) {
			cur->next = next->next;
			queue->len -= 1;
			memset(&next, 0, sizeof(next));
			free(next);
			cur = cur->next;
			return 0;
		}

		cur = next;
		next = next->next;
	}

	return -1;
}

/* Pass every data element into function 'func' */
int queue_iterate(queue_t queue, queue_func_t func)
{
	if(!queue || !func || (queue->len == 0))
		return -1;

	node_t current = queue->head;

	/* For each node, call func(node->item) */
	while(current) {
		func(current->item);
		current = current->next;
	}

	return 0;

}

/* Return the length of queue */
int queue_length(queue_t queue)
{
	if(!queue) 
		return -1;

	return queue->len;
}
