#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	
    char alphabet;
	int count;
	
}NODE_INFO;

typedef struct {
	
    NODE_INFO details;
    struct NODE* next;
	
}NODE;

NODE* destroy(NODE* head_ptr);

NODE* insert_at_beginning(NODE* head_ptr, char data);

NODE* traverse(NODE* head_ptr,char data);


#endif 