/*
 * queue.c
 *
 *  Created on: Mar 13, 2018
 *      Author: Hamed
 */
/**
 a C queue implementation using linked list
 */
#include "queue.h"

/*initialize the queue*/
void initQueue(Queue *q) {
	q->head = NULL;
	q->tail = NULL;
}
/*insert an element to the end of the queue*/
void enqueue(Queue *q, GraphNode* _value) {
	//allocate a new QeueuElement for _value
	QueueElement *newElement;
	newElement = (QueueElement*) malloc(sizeof(QueueElement));
	newElement->value = _value;
	newElement->next = NULL;
	if (q->head == NULL) {
		//first element
		q->head = newElement;
		q->tail = newElement;
	} else {
		//put it to the tail
		q->tail->next = newElement;
		q->tail = newElement;
	}
}
/*delete the first element from the queue*/
GraphNode* dequeue(Queue *q) {
	QueueElement *element;
	if (q->head == NULL) {
		//empty queue
		return NULL;
	} else {
		element = q->head;
		q->head = q->head->next;
		return element->value;
	}
}
/*get the front value of the queue, but don't delete it*/
/*GraphNode* front(struct Queue *q) {
	return q->head->value;
}*/
/*check if the queue is empty*/
/*int ifEmpty(struct Queue *q) {
	return (q->head == NULL ? 1 : 0);
}*/

