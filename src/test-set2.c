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
#include "set.h"
#include "set2.h"
#include "connector.h"

/*-------------------------- MAIN program ----------------------------------
 */

int main( int argc, char *argv[] )
{  

   printf("-------Reading a dataset from a file.\n");
   FILE *infile = fopen(argv[1], "r");
   set2_node *st = set2_load(infile);

   printf("-------Printing a dataset from set-trie st.\n");
   set2_store(stdout, st);
   fclose(infile);

   printf("-------Creating set s1.\n");
   set *s1 = set_alloc(10);

   //int a1[] = {3,4,5,6,8,9,10,14,15,18};
   int a1[] = {0,1,4,5,6};
   
   printf("-------Inserting elms in s1.\n");
   int n = sizeof(a1)/sizeof(a1[0]);
   for (int i=0; i < n; i++) {
       set_write(s1, a1[i]);
   }

   printf("-------Printing s1.\n");
   set_print(stdout, s1); printf("\n");

   printf("-------Creating set sp.\n");
   set *sp = set_alloc(10);

   int add = 2;
   int skp = 2;

   printf("-------Find in st sets similar to s1.\n");
   set2_simsearch(st, s1, sp, &skp, &add);
   
   //   printf("-------Writting a dataset from a set-trie.\n");
   set2_store(stdout, st);
   fclose(infile);

} /*main*/

