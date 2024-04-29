/*--------------------------------------------------------------------------
 *
 *  set2.c--
 *    
 *  Copyright (c) 2015, FAMNIT, University of Primorska
 *--------------------------------------------------------------------------
 */

#include <ctype.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include "config.h"
#include "set.h"
#include "queue.h"
#include "set2.h"
 
/*-------------------------------------------------------------------------- 
 * Create new set-trie st and initialize root node.
 *--------------------------------------------------------------------------
 */
void set2_new(set2_type **st)
{
  int ci;

  *st = (set2_type *)malloc(sizeof(set2_type)+1);
  (*st)->iss = false;
  (*st)->cnt = 0;
  vertex_cnt++;

  for (ci = 0; ci < MaxSetEl; ci++) {
    (*st)->child[ci] = NULL;
  }
}/*set2_new*/

/*-------------------------------------------------------------------------- 
 * Insert parameter set S in set-trie strie.
 *--------------------------------------------------------------------------
 */
void set2_insert( set2_type *strie, set_type *S )
{
  set2_type *new_strie;
  set2_type *ctrie;      /* current vertex */
  int ci;

  /* start from root vertex */
  ctrie = strie;
  ctrie->cnt++;

  /* insert into sub-trie */ 
  for (ci = 0; ci < MaxSetEl; ci++) {
     if (set_elm(ci, S)) {
        if (ctrie->child[ci] == NULL) {
           /* Create a new vertex */
	   set2_new( &(ctrie->child[ci]) );
        }

        /* update vertex */
        ctrie = ctrie->child[ci];
        ctrie->cnt++;
     }
  }

  /* mark last vertex */
  ctrie->iss = true;  
}/*set2_insert*/

/*--------------------------------------------------------------------------
 * Given the set S function searches for superset of S in set-trie strie. 
 * Function returns true if such superset exists and false otherwise. 
 *--------------------------------------------------------------------------
 */
boolean set2_supseteq( set2_type *strie, set_type *S, int ce ) {

  boolean is_in;
  int ne, ci;

  supseteq_cnt++;
  if (strie == NULL)
     return false;
           
  /* is set S already covered? */
  if (!set_next_el(S, ce, &ne)) 
     return true;

  /* set starting point */
  ci = ce;
  is_in = false;
  
  /* search for next element of strie path */
  while (!is_in && ci <= ne) {
     if (strie->child[ci] != NULL)
        is_in = set2_supseteq(strie->child[ci], S, ci+1 );
     ci++;
  }

  return is_in;
}/*set2_supseteq*/

/*--------------------------------------------------------------------------
 * Given set S function retrieves from set-trie strie all supersets of S.
 * Resulting supersets are stored in queue wqu. 
 *--------------------------------------------------------------------------
 */
void set2_get_supseteq( set2_type *strie, set_type *S, int ce, 
                        set_type *R, boolean covered ) {

  int ne, ci;

  if (strie == NULL) return;
  supseteq_cnt++;

  // determine next el; MaxSetEl-1 if no 
  if (!set_next_el(S, ce, &ne)) {
     covered = true;
     ne--;  /* ne = MaxSetEl-1 */
  }

  // superset found? 
  if (strie->iss && covered) queue_add(wqu, R);

  // return if leaf without children
  if (ce == MaxSetEl) return;

  /* set starting point */
  ci = ce;
  
  /* search for next element of strie path */
  while (ci <= ne) {
     if (strie->child[ci] != NULL) {
        set_add(R, ci);
        set2_get_supseteq(strie->child[ci], S, ci+1, R, covered );
        set_del(R, ci);
     }
     ci++;
  }

}/*set2_get_supseteq*/

/*--------------------------------------------------------------------------
 * Given the set S function searches for subset of S in set-trie strie. 
 * Function returns true if such subset exists and false otherwise. 
 *--------------------------------------------------------------------------
 */
boolean set2_subseteq( set2_type *strie, set_type *S, int ce ) {
  boolean is_in;
  int ne; 
  
  subseteq_cnt++;
  if ( strie == NULL )
    return false;
 
  /* this is last element of subset in strie? */
  if (strie->iss) 
     return true; 
 
  /* determine next element in set S */ 
  if (!set_next_el(S, ce, &ne)) 
     return false; 
 
  /* search for the next element in strie */
  is_in = false; 
  if (strie->child[ne] != NULL) 
     /* matching? then descend in both sets */
     is_in = set2_subseteq(strie->child[ne], S, ne+1);   
 
  /* skip element ne if not found */
  if (!is_in)                              
    return set2_subseteq(strie, S, ne+1);     
  else 
    return true;      
}/*set2_subseteq*/

/*--------------------------------------------------------------------------
 * Given the set S function retrieves from set-trie strie all subsets of S. 
 * Resulted subsets are stored in queue gqu.  
 *--------------------------------------------------------------------------
 */
void set2_get_subseteq( set2_type *strie, set_type *S, int ce, 
                        set_type *R, boolean fs ) {
  int ne; 

  subseteq_cnt++;
  if ( strie == NULL )
     return;
 
  /* this is last element of subset in strie? */
  if (strie->iss && fs) {
     queue_add(wqu, R);
     //return; 
  }

  /* determine next element in set S */ 
  if (!set_next_el(S, ce, &ne)) 
     return; 
 
  /* search for the next element in strie */
  if (strie->child[ne] != NULL) {
     /* matching? then descend in both sets */
     set_add(R, ne);
     set2_get_subseteq(strie->child[ne], S, ne+1, R, true);   
     set_del(R, ne);
  }

  /* skip element ne and find remaining subsets*/
  set2_get_subseteq(strie, S, ne+1, R, false);     
    
}/*set2_get_subseteq*/

/*
 *-------------------------- read, write strie ----------------------------
 */

/*--------------------------------------------------------------------------
 * Writes sets from set-trie strie in depth-first order to the file f. 
 *--------------------------------------------------------------------------
 */
void set2_write( FILE *f, set2_type *strie, char *prefix, boolean first )
{
  int el;
  char *sel = (char *)malloc(200);
  char *prefix1 = (char *)malloc(200);

  if (strie->iss) {
     fprintf(f, "%s\n", prefix);
  } 
  
  for (el = 0; el < MaxSetEl; el++) {
      if (strie->child[el] != NULL) {
  
         if (first) sprintf(sel, "%d", el);
         else       sprintf(sel, ",%d", el);
         strcpy(prefix1, prefix);
         strcat(prefix1, sel);

         set2_write(f, strie->child[el], prefix1, false);
      }
  }
}/*set2_write*/

/*--------------------------------------------------------------------------
 * Read set-trie strie from file f. 
 *--------------------------------------------------------------------------
 */
void set2_read( FILE *f, set2_type **strie )
{
  int el;
  char *lin = (char *)malloc(200);
  char *tok = (char *)malloc(200);
  set_type S;

  /* prep set-trie */
  set2_new(strie);

  /* read lines from input */
  fgets(lin, 200, f);
  while (!feof(f)) {
     // omit leading and trailing white chrs 
     //lin = strtrm(lin);
     //printf("Line %s",lin);
  
     // create set 
     set_emp(&S);
     tok = (char *)strtrm((char *)strtok(lin,",\n\f\r"));
     do {
        el = atoi(tok);
        set_add(&S, el);
     } while ((tok = strtrm((char *)strtok(NULL,",\n\f\r"))) != NULL);
         
     // print set
     //printf("inp-set=");
     //set_print(&S);
     //printf("\n");

     set2_insert(*strie, &S);
     fgets(lin, 200, f);
  }
}/*set2_read*/




