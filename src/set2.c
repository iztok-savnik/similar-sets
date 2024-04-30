/*
 *  File: set2.c
 *  Author: Iztok Savnik
 * 
 *  Description: A data structure for storing and querying large sets
 *  of sets.
 *
 *  Copyright (c) 2024, FAMNIT, University of Primorska
 */

#include <ctype.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include "config.h"
#include "set.h"
//#include "common.h"
#include "connector.h"
#include "set2.h"
 
/*
  Create a new set-trie.
 */
set2_node *set2_alloc()
{
   set2_node *st = (set2_node *)malloc(sizeof(set2_node));
   st->isset = false;
   st->istail = false;
   st->sub.link = NULL;
   st->cnt = 0;
   return st;
   
} /*set2_alloc*/

/*
  Dispose a set-trie referenced by st.
 */
void set2_free( set2_node *st )
{
} /*set2_free*/

/*
  Inserts elements from two sets from their cursor on to the set-trie
  st by merging them in common prefix
 */
void set2_insert_merge( set2_node *st, set *u1, set *u2 )
{
   int el;
   link *lp = NULL;
   set *sp = NULL;
   set2_node *s2p = st;
   
   while (!set_eos(u1) && !set_eos(u2)) {

      int el1 = set_read(u1);
      int el2 = set_read(u2);

      // there is no connector in s2p; for both cases
      s2p->sub.link = con_alloc(INIT_CONNECT_SIZE);

      if (el1 != el2) {
 	 // create and set set2-node for u1
	 set2_node *sn1 = set2_alloc();
	 if (set_eos(u1)) {
	    sn1->isset = true;
	 } else {
	    sn1->istail = true;
	    sn1->sub.tail = u1;
	 }
	 con_insert(s2p->sub.link, el1, sn1);

 	 // create and set set2-node for u2
	 set2_node *sn2 = set2_alloc();
	 if (set_eos(u2)) {
	    sn2->isset = true;
	 } else {
	    sn2->istail = true;
	    sn2->sub.tail = u2;
	 }
	 con_insert(s2p->sub.link, el2, sn2);
	 
         // nothing more to do
	 return;
	 
      } else /* (el1 == el2) */ {
	
 	 // create new set node for e1=e2.
	 set2_node *sn1 = set2_alloc();

	 // link s2p to sn1 through el1.
	 con_insert(s2p->sub.link, el1, sn1);
	 s2p = sn1;
      }
   }

   // the only case when s2p->sub.link stays NULL
   // u1 = u2; 
   if (set_eos(u1) && set_eos(u2)) {
      s2p->isset = true;
      return;
   }
   // end of u1
   if (set_eos(u1)) {
      s2p->isset = true;
      s2p->istail = true;
      s2p->sub.tail = u2;

   // end of u2
   } else {
      s2p->isset = true;
      s2p->istail = true;
      s2p->sub.tail = u1;
      
   }
} /*set2_insert_merge*/

/*
  Insert a parameter set se into a set-trie st.
 */
void set2_insert( set2_node *st, set *se )
{
   int el;
   link *lp = NULL;
   set *sp = NULL;
   set2_node *s2p = st;
   
   while (!set_eos(se)) {

      if (s2p->istail) {
         // we are in tail set
         sp = s2p->sub.tail;       
	 s2p->sub.link = NULL;

	 // no more tail & merge sp and se in sub-trie
	 s2p->istail = false;
         set2_insert_merge(s2p, sp, se);
	 return;
       }

      // newly created set2-node?
      if (s2p->sub.link == NULL) {

 	 // create tail set
 	 s2p->istail = true;
	 s2p->sub.tail = se;
         return;
      }

      // read next element 
      el = set_read(se);
      if ((lp = con_lookup(s2p->sub.link, el)) == NULL) {

	 // child for el does not exist; create new one
	 set2_node *new_s2p = set2_alloc();
	 con_insert(s2p->sub.link, el, new_s2p);
	 s2p = new_s2p;
	 
      } else {

	 // child for el exists; just move there
	 s2p = lp->val;
      }
   }

   // mark the end of set
   s2p->isset = true;
   return;
} /*set2_insert*/

/*
  Search in set-trie st the sets that are similar to the set se. The
  current path from root to active node is stored in the set sp. 
 */
void set2_simsearch( set2_node *st, set *se, set *sp, int skp, int add )
{
   int nel = 0;           // next element
   int cnl = 0;           // count delete operations
   link *li = NULL;

   // are we at the end of a set?
   if (st->isset) {

      // sp is similar to se if length of se's tail is less than or
      // equal to number of skipped elements in se.
      if (set_tl_length(se) <= skp) {

         set_print(stdout, sp);
	 fprintf(stdout, " ");
         set_tl_print(stdout, se);
	 fprintf(stdout, "\n");
      }
   }

   // are we in a tail?
   if (st->istail) {
     
      if (set_tl_similar(st->sub.tail, se, skp, add)) {

         // left for testing. should be the same as st->sub.tail
         set_print(stdout, sp);
         fprintf(stdout, " ");
         set_tl_print(stdout, st->sub.tail);
         fprintf(stdout, "\n");        
      }
      return;
   }

   // open access to links
   con_open(st->sub.link);

   while (!con_eos(st->sub.link)) {

      // peek the next elm in se
      nel = set_peek(se);

      // one more can be added?
      if (add > 0) {
      
         // go through all elements
         for (li = con_read(st->sub.link);
	      (li != NULL) && ((li->key < nel) || (nel == -1));
	      li = con_read(st->sub.link)) {

            set_push(sp, li->key);
            set2_simsearch(li->val, se, sp, skp, add-1);
            set_pop(sp);
         }
      }
    
      // more links?
      if (li != NULL) {

         if (li->key == nel) {

            // descend in both, se and st 
	    set_read(se);
            set_push(sp, nel);
	    set2_simsearch(li->val, se ,sp, skp, add);
	    set_pop(sp);
	    set_unread(se, 1);

         }

	 if (skp > 0) {

 	    // descend only in se, ie., skip one in se, or delete one
	    // in se.  note: we delete nel from the solution.
	    // advancement to next elements possible ONLY while skp>0.
	    nel = set_read(se);
 	    cnl++;
	    skp--;
	 } else {

	    // return back cursor in se
            if (cnl > 0) {
               set_unread(se, cnl);
	    }
	    return;
	 }
      }
   }
   return;
   
} /*set2_simsearch*/

/*
  Write a set-trie to file in left-deep first order to the file f.
 */
void set2_wtf( FILE *f, set2_node *st, set *se )
{
   // common pointer to link instances in set-trie
   link *li;

   // end of set in set2 node
   if (st->isset) {
      set_print(f, se);
      fprintf(f, "\n");
      // no return: set may be followed by other supersets
   } 

   // end of set with tail
   if (st->istail) {
      set_print(f, se);
      fprintf(f, " ");
      set_tl_print(f, st->sub.tail);
      fprintf(f, "\n");
      return;
   } 

   // nothing more to do if the leaf reached
   if (st->sub.link == NULL) {
      return;
   }
   
   // open read access to connector
   con_open(st->sub.link);

   // go through all elements
   for (li = con_read(st->sub.link); li != NULL; li = con_read(st->sub.link)) {

      set_push(se, li->key);
      set2_wtf(f, li->val, se);
      set_pop(se);
   }

}/*set2_wtf*/

/*
  Store sets from set-trie st in left-deep first order to the file f.
 */
void set2_store( FILE *f, set2_node *st )
{
   // set used to trace the descent path
   set *se = set_alloc();

   // write a set-trie to file
   set2_wtf(f, st, se);

   // free the allocated set
   set_free(se);
} /*set2_store*/

/*
  Load set-trie strie from file f.
 */
set2_node* set2_load( FILE *f )
{
   // init main vars
   int el = -1;
   char *lin = (char *)malloc(MAX_STRING_SIZE);
   char *tok = (char *)malloc(INIT_STRING_SIZE);

   // prepare the root of set-trie 
   set2_node *s2p = set2_alloc();

   // read lines from input 
   while (fgets(lin, MAX_STRING_SIZE, f) != NULL) {

      // set of integers
      set *s1 = set_alloc();
   
      // read next token from lin
      tok = (char *)strtok(strtrm(lin)," \n\f\r");
      do {

	 el = atoi(tok);
         set_insert(s1, el);

      } while ((tok = (char *)strtok(NULL," \n\f\r")) != NULL);
         
      // reset access to se and insert s1 into set-trie
      set_open(s1);
      set2_insert(s2p, s1);
   }

   // free allocated structures
   free(lin);
   free(tok);

   // return ptr to set-trie root
   return s2p;
   
}/*set2_load*/

