/*
 * queue.h
 *
 *  Created on: Mar 13, 2018
 *      Author: Hamed
 */

#ifndef QUEUE_H_
#define QUEUE_H_

//Queue Header

#include <stdio.h>
#include <stdlib.h>
typedef struct Point {
   float x;
   float y;
} Point;
typedef struct GraphNode {
   int x;
   int y;
   struct GraphNode* previous;
   struct GraphNode* left;
   struct GraphNode* right;
   struct GraphNode* middle;
} GraphNode;
typedef struct QueueElement {
   GraphNode* value;
   struct QueueElement *next;
} QueueElement;
typedef struct Queue {
   struct QueueElement* head;
   struct QueueElement* tail;
} Queue;
void initQueue(struct Queue *q);
void enqueue(struct Queue *q, struct GraphNode* _value);
GraphNode* dequeue(struct Queue *q);
struct GraphNode* front(struct Queue *q);
int ifEmpty(struct Queue *q);

//End Queue

#endif /* QUEUE_H_ */
