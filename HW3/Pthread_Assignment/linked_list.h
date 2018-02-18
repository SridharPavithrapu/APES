/***************************************************************************** 
* Copyright (C) 2018 by Sridhar Pavithrapu 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about double linked lists.
* Sridhar Pavithrapu and the University of Colorado are not liable for 
* any misuse of this material.  
*****************************************************************************/ 


/** 
* @file linked_list.h
* 
* @brief  Includes function declarations for inserting nodes at beginning, 
*		destroying all nodes, and traversing through the nodes. 
*
* @author Sridhar Pavithrapu 
*
* @date Feb 17 2018 
**/

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

/* Headers section */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Macros section */
#define LINKED_LIST_NUM_ZERO (0)
#define LINKED_LIST_NUM_ONE (1)
#define LINKED_LIST_NUM_THIRTY_TWO (32)

/***Global Structures ***/

/*
​* ​ ​ @brief   ​ : Structure for the nodes information in linked list
​*  ​ @contents : alphabet -> character
*               count -> count of similar characters   
​*/
typedef struct node_info{
	
    char alphabet;
	int count;
	
}NODE_INFO;

/*
​* ​ ​ @brief   ​ : Structure for the information of nodes of linked list
​*  ​ @contents : details -> information stored in the node
*               next -> node pointing to next node   
​*/
typedef struct node {
	
    NODE_INFO details;
    struct node* next;
	
}NODE;


/*** Function Declarations ***/

/**
​* ​ ​ @brief​ : Destroys all nodes from the linked list
​*
​* ​ ​ Returns a node pointing to head
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​*
​* ​ ​ @return​ ​Node pointing to head
​*/
NODE* destroy(NODE* head_ptr);

/**
​* ​ ​ @brief​ : Adds a node at the beginning of the linked list
​*
​* ​ ​ Returns a node pointing to head
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​* ​ ​ @param​ ​ data ​      Data to be added to the Linked List
​* ​ ​ @return​ ​Node pointing to head
​*/
NODE* insert_at_beginning(NODE* head_ptr, char data);

/**
​* ​ ​ @brief​ : Traverse the linked list for creating nodes as per the received data
​*
​* ​ ​ Returns a node pointing to head
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​* ​ ​ @param​ ​ data ​      Data to be added to the Linked List
​*
​* ​ ​ @return​ ​Node pointing to head
​*/
NODE* traverse(NODE* head_ptr,char data);


#endif 
