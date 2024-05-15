/*--------------------------------------------------------------------------
 *
 *  set.c--
 *    
 *  Copyright (c) 1995-1998, Jozef Stefan Institute
 *                2015, FAMNIT, University of Primorska
 *--------------------------------------------------------------------------
 */

#include <stdio.h>
#include "config.h"      
#include "set.h"      

/*--------------------------------------------------------------------------
 * Make set S empty.
 *--------------------------------------------------------------------------
 */
set_type* set_emp( set_type *S )
{
/*  S = (set_type *)malloc(sizeof(set_type));  */
  int wd;
  for (wd = 0; wd < MaxSetWrd; wd++) 
      (*S).bits[wd] = 0;
  return S;
}/*set_null*/

/*--------------------------------------------------------------------------
 * S = S1;
 *--------------------------------------------------------------------------
 */
set_type* set_cpy( set_type *S, set_type *S1 )
{
  int wd;
  for (wd = 0; wd < MaxSetWrd; wd++) 
      (*S).bits[wd] = (*S1).bits[wd];
  return S;
}/*set_null*/

/*--------------------------------------------------------------------------
 * S = S1 + S2;
 *--------------------------------------------------------------------------
 */
set_type* set_union( set_type *S, set_type *S1, set_type *S2 )
{
  int wd;
  for (wd = 0; wd < MaxSetWrd; wd++) 
      (*S).bits[wd] = (*S1).bits[wd] | (*S2).bits[wd];
  return S;
}

/* -------------------------------------------------------------------------
 * S = S1 * S2;
 * -------------------------------------------------------------------------
 */
set_type* set_intsc( set_type *S, set_type *S1, set_type *S2 )
{
  int wd;
  for (wd = 0; wd < MaxSetWrd; wd++) 
      (*S).bits[wd] = (*S1).bits[wd] & (*S2).bits[wd];
  return S;
}

/*--------------------------------------------------------------------------
 * S = S1 - S2;
 *--------------------------------------------------------------------------
 */
set_type* set_diff( set_type *S, set_type *S1, set_type *S2 )
{
  int wd;
  for (wd = 0; wd < MaxSetWrd; wd++) 
    (*S).bits[wd] = (*S1).bits[wd] & (( (*S1).bits[wd] & (*S2).bits[wd] ) ^ SET_MASK );
  return S;
}

/*--------------------------------------------------------------------------
 * S = S + {el};
 *--------------------------------------------------------------------------
 */
set_type* set_add( set_type *S, int el )
{
  int wd = el / WrdBits;
  int el1 = el % WrdBits;
  (*S).bits[wd] = (*S).bits[wd] | (1 << el1);
  return S;
}

/*--------------------------------------------------------------------------
 * S = S - {el};
 *--------------------------------------------------------------------------
 */
set_type* set_del( set_type *S, int el )
{
  int wd = el / WrdBits;
  int el1 = el % WrdBits;
  (*S).bits[wd] = (*S).bits[wd] & ((1 << el1) ^ SET_MASK);
  return S;
}

/*--------------------------------------------------------------------------
 * Membership test. 
 *--------------------------------------------------------------------------
 */
boolean set_elm( int el, set_type *S )
{
  int wd = el / WrdBits;
  int el1 = el % WrdBits;
  return ( ((*S).bits[wd] & (1 << el1)) > 0 );
}

/*--------------------------------------------------------------------------
 * Subsumption test. 
 *--------------------------------------------------------------------------
 */
boolean set_subs( set_type *S1, set_type *S2 )
{
  boolean bl = true;
  int wd;

  for (wd = 0; wd < MaxSetWrd; wd++) 
    bl = bl && ( ((*S1).bits[wd] & (*S2).bits[wd]) == (*S1).bits[wd] );

  return bl;
}

/*--------------------------------------------------------------------------
 * Equality test.
 *--------------------------------------------------------------------------
 */
boolean set_equ( set_type *S1, set_type *S2 )
{
  boolean bl = true;
  int wd;

  for (wd = 0; wd < MaxSetWrd; wd++) 
    bl = bl && ( (*S1).bits[wd] == (*S2).bits[wd] );

  return bl;
}

/*--------------------------------------------------------------------------
 * Calculate the cardinality of the set S. 
 *--------------------------------------------------------------------------
 */
int set_card( set_type *S )
{
  int cnt, i;

  cnt = 0;
  for (i = 0; i < MaxSetEl; i++) {
    if (set_elm(i, S))
       cnt++;
  }
  return cnt;
}/*set_card*/

/*--------------------------------------------------------------------------
 * Find the first element (from the set S) that is greater than cEl and
 * return it as nEl. Function returns FALSE if there is no such element.
 *--------------------------------------------------------------------------
 */
boolean set_next_el( set_type *S, 
   int cel, 		/* current elm */
   int *nel )    	/* next elm */
{
  *nel = cel;
  while (!set_elm(*nel, S) && *nel < MaxSetEl)
    (*nel)++;
  return (*nel < MaxSetEl);      /* set_elm(*nEl, S); */
}/*set_next_el*/

/*--------------------------------------------------------------------------
 * Prints set S.
 *--------------------------------------------------------------------------
 */
void set_print( set_type *S ) 
{
  int ce = 0;
  int ne = 0;
  int first = true;

  while (set_next_el(S, ce, &ne)) {
     if (first) first = false; else printf(","); 
     printf("%i", ne);
     ce = ne+1;
  }

}/*set_print*/


 

