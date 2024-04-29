/*--------------------------------------------------------------------------
 *
 * config.c--
 *    
 * Copyright (c) 2015, FAMNIT, University of Primorska
 *--------------------------------------------------------------------------
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "config.h"

/* Local variables */

/*-------------------------------------------------------------------------- 
 * Delete leading and trailing ' ' and '\'' from input string.
 *--------------------------------------------------------------------------
 */
char *strtrm(char *S)
{
  int len;

  if (S == NULL) 
    return NULL;
  while ((*S == ' ') || (*S == '\t')) S++;
  len = strlen(S)-1;
  while ((*(S+len) == ' ') || (*(S+len) == '\t') || (*(S+len) == '\f') || 
         (*(S+len) == '\n') || (*(S+len) == '\r') || (*(S+len) == '\0'))
    *(S+len--) = '\0';
  *(S+len+1) = '\n';
  return S;
}/*strtrm*/


/*--------------------------------------------------------------------------
 *   Interpret command line options. 
 *--------------------------------------------------------------------------
 */
int interpret( char opt[] )
{
  char *cptr;

  if (opt[0] == '-') {
    switch (opt[1]) {
    case 'm':
      if (opt[2] == '1')
         ST_do_subseteq = 1;
      if (opt[2] == '2')
         ST_do_supseteq = 1;
      if (opt[2] == '3')
         ST_do_get_subseteq = 1;
      if (opt[2] == '4')
         ST_do_get_supseteq = 1;
      return true;
    case 'p':
      ST_print_input = 1;
      return true;
    case 'h':
      ST_help = 1;
      return true;
    default: 
      /* unknown option */
      printf("Unknown option: %s\n",opt);
    }
  } 
}/*interpret*/


/*--------------------------------------------------------------------------- 
 *   Initialize the program parameters. 
 *---------------------------------------------------------------------------
 */
void init_params(int parc, char *param[])
{
  int i;

  // display help if no params
  if ((parc==1) || ((parc==2) && (param[1][0]=='-'))) { 
     ST_help = 1;
     return;
  }

  /* first open test file and store fp */
  testf = fopen(param[parc-1],"r");
  if (testf == NULL) {
     printf("Can't open file: %s\n", param[1]);
     exit(0);
  }
 
  /* reset parameters */
  ST_display = 1; 	
  ST_help = 0; 	
  ST_print_input = 0; 	
  ST_do_subseteq = 0; 	
  ST_do_supseteq = 0; 	
  ST_do_get_subseteq = 0; 	
  ST_do_get_supseteq = 0; 	

  /* initialize other variables */
  testf_rewind = false;

  // interpret command line options 
  i = 1;                
  while (i < (parc-1)) {
    if (!interpret(param[i])) 
       printf( "Can't interpret option: %s\n", param[i++]);
    i++;
  }
}/*init_params*/

