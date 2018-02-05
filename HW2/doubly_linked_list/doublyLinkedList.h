/***************************************************************************** 
* Copyright (C) 2018 by Sridhar Pavithrapu 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about double linked lists.
* Sridhar Pavithrapu and the University of Colorado are not liable for 
* any misuse of this material.  
*****************************************************************************/ 


/** 
* @file doublyLinkedList.h
* 
* @brief  Includes function declarations for inserting nodes at different position, 
*		removing nodes at different position, destroying all nodes, 
*		finding peak value and size for the double linked lists. 
*
* @author Sridhar Pavithrapu 
*
* @date January 26 2018 
**/


#ifndef __DOUBLYLINKEDLIST_H__
#define __DOUBLYLINKEDLIST_H__

/* Headers section */
#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 
#include <stddef.h>
#include <string.h>

/* Macros section */
#define GET_LIST_CONTAINER(addr, type, member) ({ \
	const __typeof__( ((type *)0)->member ) *__mptr = (addr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})


/***Global Structures ***/

/*
​* ​ ​ @brief   ​ : Structure for the nodes of doubly linked list
​*  ​ @contents : prev -> pointer to previous node
*               next -> pointer to next node   
​*/

typedef struct node{
	
	struct node *prev;
	struct node *next;
}NODE;

/***Global Structures ***/

/*
​* ​ ​ @brief   ​ : Structure for the information of nodes of doubly linked list
​*  ​ @contents : data -> data value stored in the node
*               list -> node pointing to structure NODE   
​*/

typedef struct info{
	
	uint32_t data;
	struct node list;
}INFO;


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
​* ​ ​ @param​ ​ info ​      Data to be added to the Linked List
​* ​ ​ @return​ ​Node pointing to head
​*/
NODE* insert_at_beginning(NODE* head_ptr, uint32_t info);

/**
​* ​ ​ @brief​ : Adds a node at the end of the linked list
​*
​* ​ ​ Returns a node pointing to head
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​* ​ ​ @param​ ​ info ​      Data to be added to the Linked List
​*
​* ​ ​ @return​ ​Node pointing to head
​*/
NODE* insert_at_end(NODE* head_ptr,uint32_t info);

/**
​* ​ ​ @brief​ : Adds a node at the required index of the linked list
​*
​* ​ ​ Returns a node pointing to head
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​* ​ ​ @param​ ​ info ​      Data to be added to the Linked List
​* ​ ​ @param​ ​ index ​     index where data is to be added
​*
​* ​ ​ @return​ ​Node pointing to head
​*/
NODE* insert_at_position(NODE* head_ptr,uint32_t info,uint32_t index);

/**
​ * ​ ​ @brief​ : Remove a node at beginning of Linked List
​ *
​ * ​ ​ Returns a node pointing to head
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​ *
​ * ​ ​ @return​ ​ Node pointing to head
​ */
NODE* delete_at_beginning(NODE* head_ptr);

/**
​ * ​ ​ @brief​ : Remove a node at end of Linked List
​ *
​ * ​ ​ Returns a node pointing to head
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​ *
​ * ​ ​ @return​ ​ Node pointing to head
​ */
NODE* delete_at_end(NODE* head_ptr);

/**
​* ​ ​ @brief​ : Remove a node at the required index of the linked list
​*
​* ​ ​ Returns a node pointing to head
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​* ​ ​ @param​ ​ index ​     index where node is to be removed
​*
​* ​ ​ @return​ ​Node pointing to head
​*/
NODE* delete_at_position(NODE* head_ptr, uint32_t index);

/**
​ * ​ ​ @brief​ : Returns current size of the LinkedList
​ *
​ * ​ ​ Returns size of Linked List
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t size(NODE* head_ptr);

/**
​* ​ ​ @brief​ : Printing data of nodes of the linked list
​*
​* ​ ​ Returns a success with integer 0
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​*
​* ​ ​ @return​ uint32_t
​*/
uint32_t print_list(NODE* head_ptr);

/**
​* ​ ​ @brief​ : Get data of the given index node
​*
​* ​ ​ Returns a data of the node pointed
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A pointer to the head of the Linked List
*   @param  index      index of the node
​*
​* ​ ​ @return​ ​uint32_t
​*/
uint32_t get_data(NODE* head_ptr,uint32_t index);


#endif 