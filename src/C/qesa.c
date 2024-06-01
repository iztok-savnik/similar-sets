/*
  File: questa.c

  Copyright (c) 2024, FAMNIT, University of Primorska
  Author: Iztok Savnik
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "config.h"
#include "set.h"
#include "qesa.h"

/*
  Creating a new qesa collection.
*/
qesa *qesa_alloc()
{
   qesa *qp = (qesa *)malloc(sizeof(qesa));
   if (qp == NULL) {
      printf("error: (qesa_alloc) malloc failed.\n");
      return NULL;
   }

   qp->length = INIT_QESA_SIZE;
   qp->last = -1;
   qp->cursor = -1;
   qp->arr = (void *)malloc(INIT_QESA_SIZE * sizeof(qesa));
   if (qp->arr == NULL) {
      printf("error: (qesa_alloc) malloc array failed.\n");
      return NULL;
   }

   return qp;
} /*qesa_alloc*/

/*
  Dispose the qesa collection.
 */
boolean qesa_free(qesa *qp)
{
   free(qp->arr);
   free(qp);
   return true;
} /*qesa_free*/

/*
  Returns the actual size of the set. 
 */
int qesa_size(qesa *qp )
{
   return ((qp->last) + 1);

} /*qesa_size*/

/*
  Returns the complete length of the qesa array. 
 */
int qesa_length(qesa *qp )
{
   return qp->length;

} /*qesa_length*/

/*
  Reset qesa to the state such that the space remains as it is and
  the set is prepared for loading the elements.
 */
boolean qesa_reset(qesa *qp)
{
  // reset the last and cursor
   qp->last = -1;
   qp->cursor = -1;
   return true;
   
} /*qesa_reset*/

/*
  Initialize the cursor to start reading from the beginning of the
  qesa qp. Qesa is to be read from the beginning to the end by using
  operation set_read(). The end of the sequence can be recorded when
  qesa_read() returns -1, or qesa_eos() returns true.
 */
boolean qesa_open(qesa *qp)
{
   qp->cursor = -1;
   return true;
} /*qesa_open*/

/*
  Return the next element from qesa referenced by qp and advance the
  cursor. The value NULL is returned if the cursor is at the last
  element.
 */
void *qesa_read(qesa *qp)
{
   if (qp->cursor >= qp->last)
      return NULL;
   else 
     return (void *)(qp->arr[++(qp->cursor)]);
} /*qesa_read*/

/*
  Check if qesa cursor is at the last element in an array representing
  a qesa.
 */
boolean qesa_eos(qesa *qp)
{
   if (qp->cursor >= qp->last)
      return true;
   else
      return false;
   
} /*qesa_eos*/

/*
  Add a new element at the end of the array representing a qesa.
 */
boolean qesa_write(qesa *qp, void *ptr)
{
   // check for space
   if (qp->last >= (qp->length - 1)) {
      qp->length *= 2;
      qp->arr = (void *)realloc(qp->arr, qp->length * sizeof(void *));
      if (qp->arr == NULL) {
         printf("error: (qesa_write) realloc failed.\n");
         return false;
      }
   }

   // insert ptr at the end of int sequence
   qp->arr[++(qp->last)] = ptr;
   return true;
  
} /*qesa_write*/

/*
  Prints a set st to file f with the spaces in between the elements.
*/
void qesa_print(FILE *f, qesa *qp)
{
   // print all elements from the beginning to the end of set
   for (int i = 0; i <= qp->last; i++) {
      set_print (f, (set *)(qp->arr[i]));
      fprintf(f, "\n");
   }
   
} /*qesa_print*/


