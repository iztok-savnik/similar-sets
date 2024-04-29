/*--------------------------------------------------------------------------
 *
 * strie.h--
 *    
 * Copyright (c) 2015, FAMNIT, University of Primorska
 *--------------------------------------------------------------------------
 */

#ifndef STRIE_H
#define STRIE_H

/* Set-trie data struture stores the set of sets */
typedef struct set2_type {
  int cnt;          /* number of sets in strie with a given prefix */	
  boolean iss;      /* path represents set */
  struct set2_type *child[MaxSetEl-1]; /* array of sub-tries */
} set2_type;

/* Counters ... */

int vertex_cnt;     /* vertex counter */
int supseteq_cnt;   /* num of vertexes visited by strie_supeq) */
int subseteq_cnt;   /* num of vertexes visited by strie_subeq) */

/* Global variables */

set2_type *gst;  /* working strie */
set2_type *gst0; /* working strie0 */


/*---------------------- Exported functions -------------------------------
 */

extern void set2_new( set2_type **strie );
extern void set2_dispose( set2_type **strie );

extern void set2_insert( set2_type *strie, set_type *S );
extern boolean set2_member( set2_type *strie, set_type *S, int ci );
extern boolean set2_subseteq( set2_type *strie, set_type *S, int ci );
extern boolean set2_supseteq( set2_type *strie, set_type *S, int ci );
extern void set2_get_subseteq( set2_type *strie, set_type *S, int ci, set_type *R, boolean fs );
extern void set2_get_supseteq( set2_type *strie, set_type *S, int ci, set_type *R, boolean covered );

extern void set2_read( FILE *f, set2_type **strie );
extern void set2_write( FILE *f, set2_type *strie, char* prefix, boolean first );

#endif /*STRIE_H*/
