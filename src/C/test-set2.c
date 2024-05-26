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


/*
 */
void apply_tests_to_strie( FILE *f, set2_node *st, int *add, int *skp ) {

   // save simsearch params
   int d1 = *add;
   int d2 = *skp;

   // init main vars
   int el = -1;
   char *lin = (char *)malloc(MAX_STRING_SIZE);
   char *tok = (char *)malloc(INIT_STRING_SIZE);

   // set of integers to store sets read from file
   set *s1 = set_alloc();
   set *sp = set_alloc();

   // read lines from input 
   while (fgets(lin, MAX_STRING_SIZE, f) != NULL) {

      // reset s1 to act as an empty set
      set_reset(s1);
   
      // read next token from lin
      tok = (char *)strtok(strtrm(lin)," \n\f\r");
      do {

	 el = atoi(tok);
         set_insert(s1, el);

      } while ((tok = (char *)strtok(NULL," \n\f\r")) != NULL);

      // print the query
      printf("? ");
      set_print(stdout, s1);
      printf("\n");
      
      // reset set sp and simsearch params
      set_open(s1);
      set_reset(sp);
      *add = d1;
      *skp = d2;
      
      // find in st the sets that are similar to s1
      set2_simsearch(st, s1, sp, add, skp);
   }

   // free the set s1
   set_free(s1);
   set_free(sp);
   
   // free allocated structures
   free(lin);
   free(tok);
   
} /*apply_tests_to_strie*/

/*
 */
int main( int argc, char *argv[] )
{  

   //printf("-------Reading a dataset from a file.\n");
   FILE *infile = fopen(argv[1], "r");
   set2_node *st = set2_load(infile);

   //printf("-------Printing a dataset from set-trie st.\n");
   //set2_store(stdout, st);
   fclose(infile);

   // simserach params
   int add = 2;
   int skp = 2;

   //printf("-------Foreach set from testset search simsets in st: add=%d, skp=%d.\n", add, skp);
   apply_tests_to_strie(stdin, st, &skp, &add);
   
} /*main*/



int old_main( int argc, char *argv[] )
{  

   printf("-------Reading a dataset from a file.\n");
   FILE *infile = fopen(argv[1], "r");
   set2_node *st = set2_load(infile);

   //printf("-------Printing a dataset from set-trie st.\n");
   //set2_store(stdout, st);
   fclose(infile);

   printf("-------Creating set s1.\n");
   set *s1 = set_alloc(10);

   //int a1[] = {3,4,5,6,8,9,10,14,15,18};
   //int a1[] = {0,1,4,5,6};
   //int a1[] = {1,4,8};
   //int a1[] = {1,3,5};
   //int a1[] = {0,1,6,287,551,579,600,743,2204,6872,10224,14095,15417,50611,59152};
   //int a1[] = {0,1,6,287,551,579,600,743};
   //int a1[] = {0,1,15};
   //int a1[] = {0,1,2,3,4,5,18,20,32,49,87,109,195,227,330,906,1767,2011,3048,3521,5974,19771,22470,29289,35522,57714,89070,105592};
   //int a1[] = {0, 1, 2, 3, 4, 5, 11,13,156,185,254,374,2709,4393,26323};
   int a1[] = {0,1,2,3,907,18341};
   
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

   printf("-------Find in st sets similar to s1: add=%d, skp=%d.\n", add, skp);
   set2_simsearch(st, s1, sp, &skp, &add);
   
} /*main*/
