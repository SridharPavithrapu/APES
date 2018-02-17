#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_info{
	
    char alphabet;
	int count;
	
}NODE_INFO;

typedef struct node {
	
    NODE_INFO details;
    struct node* next;
	
}NODE;

NODE* destroy(NODE* head_ptr);

NODE* insert_at_beginning(NODE* head_ptr, char data);

NODE* traverse(NODE* head_ptr,char data);


#endif 
