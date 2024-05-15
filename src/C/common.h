/*--------------------------------------------------------------------------
 *
 * File: common.h
 *    
 * Copyright (c) 2023, FAMNIT, University of Primorska
 *--------------------------------------------------------------------------
 */

#ifndef COMMON_H
#define COMMON_H

/* Declaration of circular typedef references. */
typedef struct set2_node set2_node;
typedef struct connector connector;
typedef struct link link;

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

/* A type kv_pair is a structure composed of two fields. */
typedef struct link {
  int key;           /* a key is an element of a set */
  set2_node *val;    /* value is, in this case, a ptr to a s2_node */
} link;

/* A connector is a structure composed of a sequence of key-value
   pairs sorted by keys. The length of a sequence and the index of the
   currently accessed key-value pair are included. */
typedef struct connector {
  int length;        // length of the array seq
  int last;          // inx of last occupied element
  int cursor;        // indx of the last pair 
  link *seq;         // sorted array of links 
} connector;

#endif /*COMMON_H*/
