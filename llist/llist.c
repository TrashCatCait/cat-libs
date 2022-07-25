#include <stdio.h>
#include <stdlib.h>

/*
 * C basic linked list implementation to act as linked 
 * list for all generic data types and structs
 */

//Single linked list 
typedef struct list_node {
    void *data; //generic data here
    struct list_node *next; //next entry; 
} list_t;

//Double linked list
typedef struct dlist_node {
    void *data; //generic data 
    struct dlist_node *next;
    struct dlist_node *prev;
} dlist_t;
