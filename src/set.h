/*
 * File: set.h
 * 
 * Copyright (c) 2023, FAMNIT, University of Primorska
 * Author: Iztok Savnik
*/				        	  
 
#ifndef SET_H
#define SET_H

/* Global constants, types, ... */ 

/*
  A set is a structure composed of the length of a set stored in a
  sorted array of integer numbers.
*/
typedef struct set {
  int length;
  int last;
  int cursor ;
  int *arr;
} set;

/* Exported functions */

extern set    *set_alloc();
extern boolean set_free( set *sp );
extern boolean set_reset( set *sp );
extern void    set_sort( set* sp );

extern int     set_get( set *sp, int ix );
extern boolean set_put( set *sp, int ix, int el );

extern int     set_size( set *sp );
extern boolean set_member( set* sp, int el );
extern boolean set_open( set *sp );
extern boolean set_open_at( set *sp, int el );

extern int     set_peek( set *sp );
extern int     set_read( set *sp );
extern void    set_unread( set *sp, int n );
extern boolean set_write( set *sp, int el );
extern boolean set_insert( set *sp, int el );
extern boolean set_eos( set *sp );

extern boolean set_push( set *sp, int el );
extern int     set_pop( set *sp );
extern void    set_print( FILE *f, set *sp );

extern int     set_tl_length( set *sp );
extern void    set_tl_print( FILE *f, set *sp );
extern boolean set_tl_similar( set *sp, set *se, int skp, int add );

#endif /* SET_H */
