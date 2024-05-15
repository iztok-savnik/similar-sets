/*--------------------------------------------------------------------------
 *
 *  set.h--
 *    
 *  Copyright (c) 1995-1998, Jozef Stefan Institute
 *                2015, FAMNIT, University of Primorska
 *--------------------------------------------------------------------------
 */

#ifndef SET_H
#define SET_H


/* Constants */

#define SET_LEN  sizeof(set_type)      	/* Maximal length of a set */
#define SET_MASK 0xffffffff      	/* Mask for computing set op. */

#define WrdBits (sizeof(int) * 8)              /* Number of bits in a word */
#define MaxSetEl 300 	                        /* max number of set elements. */
#define MaxSetWrd ((MaxSetEl / WrdBits) + 1)    /* max number of set elements. */


/* SET type definition */

typedef struct set_type { 
  unsigned int bits[MaxSetWrd];
} set_type;  		


/*----------------------- Exported functions -------------------------------
 */

extern set_type* set_emp( set_type *S );
extern set_type* set_cpy( set_type *S, set_type *S1 );
extern set_type* set_union( set_type *S, set_type *S1, set_type *S2 );
extern set_type* set_intsc( set_type *S, set_type *S1, set_type *S2 );
extern set_type* set_diff( set_type *S, set_type *S1, set_type *S2 );
extern set_type* set_add( set_type *S, int el );
extern set_type* set_del( set_type *S, int el );
extern boolean   set_elm( int el, set_type *S );
extern boolean   set_subs( set_type *S1, set_type *S2 );
extern boolean   set_equ( set_type *S1, set_type *S2 );
extern int       set_card( set_type *S );
extern boolean   set_next_el( set_type *S, int cEl, int *nEl );
extern void      set_print( set_type *S );

#endif  /* SET_H */


