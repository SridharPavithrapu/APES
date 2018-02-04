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
* @brief  Includes function declartions for inserting nodes at different position, 
*		removing nodes at different position, destroying all nodes, 
*		finding peak value and size for the double linked lists. 
* @author Sridhar Pavithrapu 
* @date January 26 2018 
**/


#ifndef __DOUBLYLINKEDLIST_H__
#define __DOUBLYLINKEDLIST_H__

/* Headers section */
#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 
#include <stddef.h>

#define GET_LIST_CONTAINER(addr, type, member) ({ \
	const typeof( ((type *)0)->member ) *__mptr = (addr); \
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
*               node -> node pointing to structure NODE   
​*/

typedef struct info{
	
	uint32_t data;
	struct node list;
}INFO;



/*** Enumerations ***/

/*
​* ​ ​ @brief​ : Enum for Error Codes
​*
​* ​ ​ Returns a code stating the status of different operations:
*   SUCCESS              : Successful opeartion
​*/

typedef enum{
	SUCCESS,
	MALLOC_ERROR,
	INVALID_POS,
	DELETE_ERROR
	
}Error_code;

/*** Function Declarations ***/

/**
​* ​ ​ @brief​ : Destroys all nodes from the linked list
​*
​* ​ ​ Returns a status code of destroy operation
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A double pointer to the head of the Linked List
​*
​* ​ ​ @return​ ​Error_code enum 
​*/
Error_code destroy(NODE* head_ptr);


/**
​* ​ ​ @brief​ : Adds a node at the beginning of the linked list
​*
​* ​ ​ Returns a status code of insert_at_beginning operation
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A double pointer to the head of the Linked List
​* ​ ​ @param​ ​ info ​      Data to be added to the Linked List
​* ​ ​ @return​ ​Error_code enum
​*/
Error_code insert_at_beginning(NODE* head_ptr, uint32_t info);

/**
​* ​ ​ @brief​ : Adds a node at the end of the linked list
​*
​* ​ ​ Returns a status code of insert_at_end operation
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A double pointer to the head of the Linked List
​* ​ ​ @param​ ​ info ​        Data to be added to the Linked List
​*
​* ​ ​ @return​ ​Error_code enum
​*/
Error_code insert_at_end(NODE* head_ptr,uint32_t info);

/**
​* ​ ​ @brief​ : Adds a node at the required index of the linked list
​*
​* ​ ​ Returns a status code of insert_at_position operation
​* ​ ​
​*
​* ​ ​ @param​ ​ head_ptr  ​ A double pointer to the head of the Linked List
​* ​ ​ @param​ ​ info ​        Data to be added to the Linked List
​* ​ ​ @param​ ​ index ​       index where data is to be added
​*
​* ​ ​ @return​ ​Error_code enum
​*/
Error_code insert_at_position(NODE* head_ptr,uint32_t info,uint32_t index);

/**
​ * ​ ​ @brief​ : Remove a node from Linked List
​ *
​ * ​ ​ Returns a status code of remove node operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ hdnode_ptr  ​ A double pointer to the head of the Linked List
​ * ​ ​ @param​ ​ index ​       index from where data is to be removed
​ *
​ * ​ ​ @return​ ​ (enum)Err_code
​ */
Error_code delete_at_beginning(NODE* head_ptr);

Error_code delete_at_end(NODE* head_ptr);

Error_code delete_at_position(NODE* head_ptr, uint32_t index);

/**
​ * ​ ​ @brief​ : Returns current size of the LinkedList
​ *
​ * ​ ​ Returns size of Linked List
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t size(NODE* head_ptr);


#endif 
