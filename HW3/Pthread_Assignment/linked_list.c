/*************************************************************************************
*
* FileName        :    linked_list.c
* Description     :    This file contains necessary function for linked list
					   
* File Author Name:    Sridhar Pavithrapu 
* Tools used      :    gcc, gedit
* References      :    None
*
***************************************************************************************/

/* Headers Section */
#include "linked_list.h"

/* Function definitions */

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
NODE* insert_at_beginning(NODE* head_ptr, char data){

	printf("\nIn insert_at_beginning function \n");
	
	/* Creating a new node */
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	if(new_node == NULL){
		
			printf("Error in malloc\n");
			return NULL;
	}
	
	/* Check for empty linked list */
	if(head_ptr == NULL){
		
		if(data>='A' && data<='Z'){
			new_node->details.alphabet = data + LINKED_LIST_NUM_THIRTY_TWO;
		}
		else{
			new_node->details.alphabet = data;
		}
		new_node->details.count = LINKED_LIST_NUM_ONE;
		new_node->next = NULL;
		head_ptr = new_node;
		return head_ptr;
	}
	else{
		/* Creating linked list at the beginning */
		if(data>='A' && data<='Z'){
			new_node->details.alphabet = data + LINKED_LIST_NUM_THIRTY_TWO;
		}
		else{
			new_node->details.alphabet = data;
		}
		new_node->details.count = LINKED_LIST_NUM_ONE;
		new_node->next = head_ptr;
		head_ptr = new_node;
		return head_ptr;
	}

}


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
NODE* destroy(NODE* head_ptr){
	
	printf("In destroy function \n");
	NODE *current = head_ptr;
	NODE *next_element;
	if(head_ptr == NULL){
		
		printf("Not deleting any item, since head pointer is NULL");
		return NULL;
	}
	else{
		/* Destroying all the nodes in the linked list */
		while (current->next != NULL) {
			
		   next_element = current->next;
		   free(current);
		   current = next_element;
		}
		head_ptr = NULL;
		return head_ptr;
	}
	
}

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
NODE* traverse(NODE* head_ptr,char data){
	
	printf("\nIn traverse function \n");
	
	int flag = LINKED_LIST_NUM_ZERO;
	
	/* Converting alphabets from upper case to lower case */
	if(data>='A' && data<='Z'){
		data = data + LINKED_LIST_NUM_THIRTY_TWO;
	}

	/* If head is NULL, create the first node */
	if(head_ptr == NULL){
		head_ptr = insert_at_beginning(head_ptr, data);
	}
	else{
		/* Insert node at the beginning */
		NODE *current = head_ptr;
		while (current != NULL) {	
			printf("current->details.alphabet:%c, data:%c\n",current->details.alphabet,data);
			if(current->details.alphabet == data){
				
				current->details.count++;	
				flag = LINKED_LIST_NUM_ONE;
				break;
			}
		   current = current->next;
		}
		
		if(flag == LINKED_LIST_NUM_ZERO){
			
			head_ptr = insert_at_beginning(head_ptr, data);
		}
	}
	return head_ptr;
}

