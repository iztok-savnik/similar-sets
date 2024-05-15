/*
 *  File: connector.h
 *  Author: Iztok Savnik
 *    
 *  Copyright (c) 2023-24, FAMNIT, University of Primorska
 */				        	  
 
#ifndef CONNECTOR_H
#define CONNECTOR_H

/* Global constants, types, ... */ 

/* Declaration of circular typedef references. */
typedef struct set2_node set2_node;

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

/*---------------------------- Exported functions ------------------------------
 */

extern connector* con_alloc( int len );
extern boolean con_free( connector *sp );
extern boolean con_sort( connector *sp );
extern int     con_size(connector *sp);

extern boolean con_member( connector *sp, int key );
extern link*   con_lookup( connector *sp, int key );
extern boolean con_open( connector* sp );
extern boolean con_open_at( connector* sp, int key );
extern link*   con_peek( connector *sp );
extern link*   con_read( connector *sp );
extern boolean con_eos( connector *sp );
extern boolean con_write( connector *sp, int key, set2_node* val );
extern boolean con_insert( connector *sp, int key, set2_node* val );

#endif /* CONNECTOR_H */
