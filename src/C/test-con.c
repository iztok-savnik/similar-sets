/*--------------------------------------------------------------------------
 *  Testing, testing, ... 
 *
 *  Copyright (c) 2015-2020, FAMNIT, University of Primorska
 *--------------------------------------------------------------------------
 */

#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>
#include <string.h>
#include "config.h"
#include "connector.h"

/*-------------------------- MAIN program ----------------------------------
 */

int main( int argc, char *argv[] )
{  
   printf("-------Creating a sequence of a given length.\n");
   connector *sp = con_alloc(2000);

   // used variables
   void *ip = (void *)malloc(sizeof(int));
   int i = 0;
   int k = -1;
   link *kp;

   printf("-------Initialization of a sequence.\n");
   for (int i = 0; i<50; i++) {
     void *ip = (void *)malloc(sizeof(int));
     *((int *)ip) = (i+1)*10;
     if (!con_write(sp, i*10, ip)) {
        printf("Problem...\n");
     }
   }

   printf("-------Testing con_lookup.\n");
   if ((kp = con_lookup(sp, 42)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 42);
      kp = con_peek(sp);
      printf("Current: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   }
   if ((kp = con_lookup(sp, 450)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 450);
   }
   if ((kp = con_lookup(sp, 155)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 155);
      kp = con_peek(sp);
      printf("Current: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   }
   if ((kp = con_lookup(sp, 495)) != NULL) {
      printf("Lookup: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
   } else {
      printf("Lookup: no such key=%d\n", 495);
      if (con_eos(sp)) {
         printf("Current: eos for key=%d\n", 495);
      } else { 
         kp = con_peek(sp);
         printf("Current: key=%d, val=%d\n", kp->key, *(int *)(kp->val));
      }
   }


   printf("-------Print sequence from the beginning to the end.\n");
   con_open(sp);
   i = 0;
   while ((kp = con_read(sp)) != NULL) {
     printf("cnt=%d, key=%d, val=%d\n", i++, kp->key, *(int *)(kp->val));
   }
 

   printf("-------Disposing the sequence.\n");
   con_free(sp);
				   
} /*main*/

