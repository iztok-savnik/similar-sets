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

   //   printf("-------Reading a dataset from a file.\n");
   FILE *infile = fopen(argv[1], "r");
   set2_node *st = set2_load(infile);

   //   printf("-------Writting a dataset from a set-trie.\n");
   set2_store(stdout, st);
   fclose(infile);

} /*main*/

