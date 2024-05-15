/*--------------------------------------------------------------------------
 *
 * File: set2.h
 *    
 * Copyright (c) 2023, FAMNIT, University of Primorska
 *--------------------------------------------------------------------------
 */

#ifndef SET2_H
#define SET2_H

/*
A set trie is a trie composed of nodes represented with a struct
s2_node. Conceptually, each s2_node includes a store of
element/pointer (key/value) pairs including elements that lead to
sub-tries (children nodes) of a given s2_node.

The links from a s2_node to its children s2_nodes is implemented with
skip lists of memory blocks. Each memory block includes a sorted array
of key/value pairs. The key can only be an element of a set that
follows (in a sorted order) the element represented b a current node.
The value represents the reference to the children s2_node-s.

The s2_node thus has 3 ...
*/

/* Declaration of circular typedef references. */
typedef struct connector connector;

/* A node of a set-trie. */
typedef struct set2_node {
   boolean isset;    /* path represents a set */
   boolean istail;   /* path is a prefix of a tail set */
   union {
      connector *link; /* reference to an instance of a kvstore */
      set *tail;       /* reference to set; tail of a set sequence */
   } sub;
   int cnt;         /* number of sets in trie with a given prefix */	
} set2_node;

/*---------------------- Exported functions ------------------------------*/

extern set2_node* set2_alloc();
extern void set2_free( set2_node *st );

extern void set2_insert( set2_node *st, set *se );
extern void set2_simsearch( set2_node *st, set *se, set *sp, int *skp, int *add );

extern set2_node* set2_load( FILE *f );
extern void set2_store( FILE *f, set2_node *st );

#endif /*SET2_H*/
