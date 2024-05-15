/*
 *  File: main.c
 *  Author: Iztok Savnik
 *
 *  Description: Data structure for storing and searching large sets
 *  of sets. 
 *
 *  Copyright (c) 2015-2024, FAMNIT, University of Primorska
 */

// 23/09/2015 - interface added 
// 07/05/2015 - unnecessary code cleaned, strie_subseteq() tested
// 06/05/2015 - strie_supseteq() tested
// 22/04/2015 - read, construct and print set2
// 01/10/2020 - sets of arbitrary length 

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
#include "queue.h"
#include "set2.h"
#include "main.h"

/*-------------------------- MAIN program ----------------------------------
 */

main( int argc, char *argv[] )
{  
  // interpret parameters
  init_params(argc, argv);
 
  /* display help and exit if help is turned on */
  if (ST_help) {
     do_help();
     exit(0);
  }

  /* read and print input */
  do_read_set2();
  if (ST_print_input) do_print_set2();

  /* do tests */
  if (ST_do_subseteq) do_test_subseteq();
  if (ST_do_supseteq) do_test_supseteq();
  if (ST_do_get_subseteq) do_test_get_subseteq();
  if (ST_do_get_supseteq) do_test_get_supseteq();

} /* main() */

/*--------------------------------------------------------------------------
 *  Display short instructions.
 *--------------------------------------------------------------------------
 */
void do_help()
{
  printf("\n");
  printf("Usage:\t set2 [-m{1,2,3,4}][-h][-p] test-file < input-file > output-file \n\n");
  printf("test-file\t file including set of sets to be tested\n");
  printf("input-file\t input file including set of sets is standard unix input of \n");
  printf("\t\t program set2 (stdin)\n");
  printf("output-file\t output results are written to the standard Unix output \n");
  printf("\t\t channel (stdout)\n");
  printf("-m1\t tests use method set2_subseteq() \n");
  printf("-m2\t tests use method set2_supseteq() \n");
  printf("-m3\t tests use method set2_get_subseteq() \n");
  printf("-m4\t tests use method set2_get_supseteq() \n");
  printf("-h\t display this message \n");
  printf("-p\t print input set of sets to output-file \n");
}/*do_help*/


/*---------------------------------------------------------------------------
 * Read set of sets from file.
 *--------------------------------------------------------------------------
 */
void do_read_set2()
{
  set2_read(stdin, &gst);
} /* do_read_set2() */

/*---------------------------------------------------------------------------
 * Print set of sets from file.
 *--------------------------------------------------------------------------
 */
void do_print_set2()
{
  printf("--Input set of sets\n");
  set2_write(stdout, gst, "set=", true);
} /* do_print_set2() */

/*---------------------------------------------------------------------------
 * Test supseteq operation. 
 *--------------------------------------------------------------------------
 */
void do_test_supseteq()
{
  int el,first;
  char *lin = (char *)malloc(200);
  char *tok = (char *)malloc(200);
  set_type S;
  
  if (testf_rewind++) rewind(testf);
  printf("--Test supseteq\n");

  // read lines from input 
  fgets(lin, 200, testf);
  while (!feof(testf)) {
     // omit leading and trailing white chrs 
     lin = strtrm(lin);
  
     // create set   
     set_emp(&S);
     tok = (char *)strtrm((char *)strtok(lin,",\n"));
     do {
        el = atoi(tok);
        set_add(&S, el);
     } while ((tok = strtrm((char *)strtok(NULL,",\n\f"))) != NULL);
         
     // print set
     printf("set=");
     set_print(&S);

     // set time related stuff
     long tsec, tnsc;
     struct timespec tstart={0,0}, tend={0,0};
     clock_gettime(CLOCK_MONOTONIC, &tstart);

     // check supseteq
     supseteq_cnt = 0;
     boolean result = set2_supseteq(gst, &S, 0);
     clock_gettime(CLOCK_MONOTONIC, &tend);

     if ((tend.tv_nsec - tstart.tv_nsec) < 0) {
        tsec = tend.tv_sec - tstart.tv_sec - 1;
        tnsc = 1000000000 + tend.tv_nsec - tstart.tv_nsec;
     } else {
        tsec = tend.tv_sec - tstart.tv_sec;
        tnsc = tend.tv_nsec - tstart.tv_nsec;
     }

     // print result
     if (result) 
       printf(";val=true;cnt=%d;nsc=%ld\n", supseteq_cnt, tnsc);
     else
       printf(";val=false;cnt=%d;nsc=%ld\n", supseteq_cnt, tnsc);

     // get next line
     fgets(lin, 200, testf);
  }

} /* do_test_supseteq() */

/*---------------------------------------------------------------------------
 * Test subseteq operation. 
 *--------------------------------------------------------------------------
 */
void do_test_subseteq()
{
  int el;
  char *lin = (char *)malloc(200);
  char *tok = (char *)malloc(200);
  set_type S;

  if (testf_rewind++) rewind(testf);
  printf("--Test subseteq\n");

  /* read lines from input */
  fgets(lin, 200, testf);
  while (!feof(testf)) {
     // omit leading and trailing white chrs 
     lin = strtrm(lin);
  
     // create set     
     set_emp(&S);
     tok = (char *)strtrm((char *)strtok(lin,",\n"));
     do {
        el = atoi(tok);
        set_add(&S, el);
     } while ((tok = strtrm((char *)strtok(NULL,",\n\f"))) != NULL);
         
     // print set
     printf("set=");
     set_print(&S);

     // set time related stuff
     long tsec, tnsc;
     struct timespec tstart={0,0}, tend={0,0};
     clock_gettime(CLOCK_MONOTONIC, &tstart);

     // check subseteq
     subseteq_cnt = 0;
     boolean result = set2_subseteq(gst, &S, 0); 
     clock_gettime(CLOCK_MONOTONIC, &tend);

     if ((tend.tv_nsec - tstart.tv_nsec) < 0) {
        tsec = tend.tv_sec - tstart.tv_sec - 1;
        tnsc = 1000000000 + tend.tv_nsec - tstart.tv_nsec;
     } else {
        tsec = tend.tv_sec - tstart.tv_sec;
        tnsc = tend.tv_nsec - tstart.tv_nsec;
     }

     // print result
     if (result) 
       printf(";val=true;cnt=%d;nsc=%ld\n", subseteq_cnt, tnsc);
     else
       printf(";val=false;cnt=%d;nsc=%ld\n", subseteq_cnt, tnsc);

     // get next line
     fgets(lin, 200, testf);
  }

} /* do_test_subseteq() */

/*---------------------------------------------------------------------------
 * Test get_subseteq operation. 
 *--------------------------------------------------------------------------
 */
void do_test_get_subseteq()
{
  int el;
  char *lin = (char *)malloc(200);
  char *tok = (char *)malloc(200);
  set_type S, R;

  if (testf_rewind++) rewind(testf);
  printf("--Test get_subseteq\n");

  // read lines from input 
  fgets(lin, 200, testf);
  while (!feof(testf)) {
     // omit leading and trailing white chrs 
     lin = strtrm(lin);
  
     // convert line to set
     set_emp(&S);
     tok = (char *)strtrm((char *)strtok(lin,",\n"));
     do {
        el = atoi(tok);
        set_add(&S, el);
     } while ((tok = strtrm((char *)strtok(NULL,",\n\f"))) != NULL);
      
     // print set
     printf("set=");
     set_print(&S);

     // check get subseteq
     queue_free(wqu);
     queue_new(&wqu);
     subseteq_cnt = 0;

     // set time related stuff
     long tsec, tnsc;
     struct timespec tstart={0,0}, tend={0,0};
     clock_gettime(CLOCK_MONOTONIC, &tstart);

     // get all subseteq
     set_emp(&R);
     set2_get_subseteq(gst, &S, 0, &R, true); 
     clock_gettime(CLOCK_MONOTONIC, &tend);

     if ((tend.tv_nsec - tstart.tv_nsec) < 0) {
        tsec = tend.tv_sec - tstart.tv_sec - 1;
        tnsc = 1000000000 + tend.tv_nsec - tstart.tv_nsec;
     } else {
        tsec = tend.tv_sec - tstart.tv_sec;
        tnsc = tend.tv_nsec - tstart.tv_nsec;
     }

     // printing
     printf(";cnt=%d;sets=%d;nsc=%ld\n", subseteq_cnt, queue_count(wqu), tnsc);
     //queue_print(wqu);
     //printf("\n");

     // get next line
     fgets(lin, 200, testf);
  }

} /* do_test_get_subseteq() */

/*---------------------------------------------------------------------------
 * Test get_supseteq operation. 
 *--------------------------------------------------------------------------
 */
void do_test_get_supseteq()
{
  int el;
  char *lin = (char *)malloc(200);
  char *tok = (char *)malloc(200);
  set_type S, R;

  if (testf_rewind++) rewind(testf);
  printf("--Test get_supseteq\n");

  // read lines from input 
  fgets(lin, 200, testf);
  while (!feof(testf)) {
     // omit leading and trailing white chrs 
     lin = strtrm(lin);
  
     // convert line to set
     set_emp(&S);
     tok = (char *)strtrm((char *)strtok(lin,",\n"));
     do {
        el = atoi(tok);
        set_add(&S, el);
     } while ((tok = strtrm((char *)strtok(NULL,",\n\f"))) != NULL);
 
     // print set
     printf("set=");
     set_print(&S);

     // check get supseteq
     queue_free(wqu);
     queue_new(&wqu);
     set_emp(&R);
     supseteq_cnt = 0;

     // set time related stuff
     long tsec, tnsc;
     struct timespec tstart={0,0}, tend={0,0};
     clock_gettime(CLOCK_MONOTONIC, &tstart);

     // get all supseteq
     set_emp(&R);
     set2_get_supseteq(gst, &S, 0, &R, false); 
     clock_gettime(CLOCK_MONOTONIC, &tend);

     if ((tend.tv_nsec - tstart.tv_nsec) < 0) {
        tsec = tend.tv_sec - tstart.tv_sec - 1;
        tnsc = 1000000000 + tend.tv_nsec - tstart.tv_nsec;
     } else {
        tsec = tend.tv_sec - tstart.tv_sec;
        tnsc = tend.tv_nsec - tstart.tv_nsec;
     }

     // printing
     printf(";cnt=%d;sets=%d;nsc=%ld\n", supseteq_cnt, queue_count(wqu), tnsc);
     //queue_print(wqu);
     //printf("\n");

     // get next line
     fgets(lin, 200, testf);
  }

} /* do_test_get_supseteq() */
