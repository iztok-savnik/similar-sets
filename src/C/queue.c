/*
  File: queue.c
  Copyright (c) 2015, FAMNIT, University of Primorska
 */
 
#include <stdio.h>
#include <malloc.h>
#include "config.h"
#include "set.h"
#include "queue.h"

/*
  Create new empty queue. 
 */
void queue_new(queue_type **queue)
{
  *queue = (queue_type *)malloc(sizeof(queue_type));
  (*queue)->first_el = NULL;
  (*queue)->last_el = NULL;
}/*queue_new*/

/*
  Add a new element El to the queue Queue. 
 */
void queue_add(queue_type *queue, set_type *S )
{
  queue_element *prev_first_el;

  if (queue->first_el == NULL) {
    queue->first_el = (queue_element *)malloc(sizeof(queue_element));
    queue->first_el->prev = NULL;
    queue->first_el->set = *S;
    queue->last_el = queue->first_el;
    return;
  }
  prev_first_el = queue->first_el;
  queue->first_el = (queue_element *)malloc(sizeof(queue_element));
  prev_first_el->prev = queue->first_el;
  queue->first_el->prev = NULL;
  queue->first_el->set = *S;
}/*queue_add*/


/*
  Add element El to the end of Queue. 
 */
void queue_add_to_end(queue_type *queue, set_type *S )
{
  queue_element *prev_last_el;

  if (queue->last_el == NULL) {
    queue->last_el = (queue_element *)malloc(sizeof(queue_element));
    queue->last_el->prev = NULL;
    queue->last_el->set = *S;
    queue->first_el = queue->last_el;
    return;
  }
  prev_last_el = queue->last_el;
  queue->last_el = (queue_element *)malloc(sizeof(queue_element));
  queue->last_el->prev = prev_last_el;
  queue->last_el->set = *S;
}/*que_add_to_end*/


/*
  Get element El from the queue Queue. 
 */
void queue_get(queue_type *queue, set_type *S)
{
  queue_element *queue_el;

  if (queue->last_el == NULL) {
    printf("queue empty\n");
    return;
  }
  *S = queue->last_el->set;
  queue_el = queue->last_el;
  queue->last_el = queue->last_el->prev;
  free(queue_el);
}/*queue_get*/


/*
  Initialize the queue. 
 */
void queue_init(queue_type *queue)
{
  queue->first_el = NULL;
  queue->last_el = NULL;
}/*queue_init*/


/*
  Dispose the queue Queue. 
 */
void queue_free(queue_type *queue)
{
  queue_element *queue_el;

  if (queue == NULL) return;

  while (queue->last_el != NULL) {
    queue_el = queue->last_el;
    queue->last_el = queue->last_el->prev;
    free(queue_el);
  }
  free(queue);
}/*queue_free*/


/*
  Test if the queue is empty. 
 */
boolean queue_empty(queue_type *queue )
{
  if (queue->last_el == NULL)
    return true;
  else
    return false;
}/*queue_empty*/

/*
  Prints contents of queue.
 */
void queue_print(queue_type *queue )
{
  int first = true;
  queue_element *elm = queue->last_el;

  while (elm != NULL) {
     //if (first) first = false; else printf(":");
     set_print(&(elm->set)); printf("\n");
     elm = elm->prev;
  }

}/*queue_print*/


/*
  Counts number of elements in queue.
 */
int queue_count(queue_type *queue )
{
  int cnt = 0;
  queue_element *elm = queue->last_el;

  while (elm != NULL) {
     cnt++;
     elm = elm->prev;
  }

  return cnt;

}/*queue_count*/







