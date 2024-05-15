/*--------------------------------------------------------------------------
 *
 *  config.h--
 *    
 *  Copyright (c) 2015, FAMNIT, University of Primorska
 *--------------------------------------------------------------------------
 */				        	  
 
#ifndef CONFIG_H
#define CONFIG_H

/* Global constants, types, ... */ 

#define true 		1
#define false		0
#define STRLEN          200
#define max(a,b)  ((a) > (b) ? (a) : (b))
#undef	DEBUG_FDEP
typedef int  boolean;           

/* Files */

FILE *testf;  
boolean testf_rewind;

/* Config parameters */

int ST_display; 	
int ST_help; 	
int ST_print_input; 	
int ST_do_subseteq; 	
int ST_do_supseteq; 	
int ST_do_get_subseteq; 	
int ST_do_get_supseteq; 	

/*---------------------------- Exported functions ------------------------------
 */

extern char *strtrm( char *S );
//extern void init_params(int parc, char *param[]);

#endif /* CONFIG_H */
