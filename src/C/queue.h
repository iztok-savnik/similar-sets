/*
  File: queue.h
  Copyright (c) 2015, FAMNIT, University of Primorska
 */

#ifndef QUEUE_H
#define QUEUE_H

/* queue of sets */

typedef struct queue_element {
  set_type 		set;   	/* set element */
  struct queue_element *prev;   /* ptr to previous queue element. */
} queue_element;

typedef struct queue {
    queue_element  *first_el;  	/* first element of the queue */
    queue_element  *last_el;   	/* last element of the queue */
} queue;

queue  *wqu;   /* working queue */
 
/* Exported functions */

extern void 	queue_new(queue **queue);
extern void 	queue_init(queue *queue);
extern void 	queue_free(queue *queue);
extern boolean 	queue_empty(queuex *queue);
extern void 	queue_equeue(queue *queue, set_type *S);
extern void 	queue_push(queue *queue, set_type *S);
extern void 	queue_dequeue(queue *queue, set_type *S);
extern void 	queue_pop(queue *queue, set_type *S);
extern void 	queue_print(queue *queue);
extern int 	queue_count(queue *queue);

#endif /* QUEUE_H */

