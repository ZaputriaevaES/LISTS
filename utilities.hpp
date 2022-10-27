#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 

#define MAX_LIST_SIZE 30

typedef int elem_t;

struct list_elem
    {
        elem_t data;    
        int    next;    
        int    prev;    
    }; 


struct lists
    {
        int head;
        int tail;
        int free;
        int size;
        int capacity;
        char is_sort;
        struct list_elem * node;
    };


#endif //