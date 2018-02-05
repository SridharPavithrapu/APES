/*************************************************************************************
*
* FileName        :    doublyLinkedList.c
* Description     :    This file contains necessary function for double linked list
					   system calls.
* File Author Name:    Sridhar Pavithrapu 
* Tools used      :    gcc, gedit
* References      :    None
*
***************************************************************************************/

/* Headers Section */
#include "doublyLinkedList.h"

/* Macros section */
#define LINKED_LIST_NUM_ZERO (0)
#define LINKED_LIST_NUM_ONE (1)
#define LINKED_LIST_NUM_TWO (2)
#define LINKED_LIST_NUM_THREE (3)
#define LINKED_LIST_NUM_FOUR (4)
#define LINKED_LIST_NUM_FIVE (5)
#define LINKED_LIST_NUM_SIX (6)
#define LINKED_LIST_NUM_SEVEN (7)
#define LINKED_LIST_NUM_EIGHT (8)
#define LINKED_LIST_NUM_NINE (9)
#define LINKED_LIST_NUM_TEN (10)
#define LINKED_LIST_NUM_ELEVEN (11)
#define LINKED_LIST_NUM_TWELVE (12)

/* Function definitions */

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
NODE* insert_at_beginning(NODE* head_ptr, uint32_t info){

	printf("\nIn insert_at_beginning function \n");
	
	/* Creating a new node */
	INFO *new_node = (INFO *)malloc(sizeof(INFO));
	NODE *next_element;
	if(new_node == NULL){
		
			printf("Error in malloc\n");
			return head_ptr;
	}
	
	/* Check for empty linked list */
	if(head_ptr->next == NULL){
		
		printf("Linked list is empty, so entering data in first node \n");
		new_node->data = info;
		(new_node->list).prev = NULL;
		(new_node->list).next = NULL;
		head_ptr->next = &(new_node->list);
		return head_ptr;
	}
	else{
		
		printf("Inserting node at the end\n");
		new_node->data = info;
		(new_node->list).next = head_ptr->next;
		head_ptr->next = &(new_node->list);
		next_element = (new_node->list).next;
		next_element->prev = &(new_node->list);
		return head_ptr;
	}

}

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
NODE* insert_at_end(NODE* head_ptr, uint32_t info){
	
	printf("In insert_at_end function \n");	
	
	/* Creating a new node */
	INFO *new_node = (INFO *)malloc(sizeof(INFO));
	NODE *next_element;
	if(new_node == NULL){
		
			printf("Error in malloc\n");
			return head_ptr;
	}
	
	/* Check for empty linked list */
	if(head_ptr->next == NULL){
		
		printf("Linked list is empty, so entering data in first node \n");
		new_node->data = info;
		(new_node->list).prev = NULL;
		(new_node->list).next = NULL;
		head_ptr->next = &(new_node->list);
		return head_ptr;
	}
	else{
		
		printf("Creating node at end \n");
		next_element = head_ptr->next;
		while(next_element->next){
				next_element =next_element->next;
		}
		new_node->data = info;
		next_element->next = &(new_node->list);
		(new_node->list).prev = next_element;
		return head_ptr;
	}

}

/**
​ * ​ ​ @brief​ : Returns current size of the LinkedList
​ *
​ * ​ ​ Returns size of Linked List
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t size(NODE* head_ptr){

	printf("In size function \n");

	/* Check for empty node */
	if(head_ptr->next == NULL){
		
		printf("size ==0 \n");
		return LINKED_LIST_NUM_ZERO;
	}	
	
	uint32_t count = LINKED_LIST_NUM_ONE;
	NODE *next_element;
	next_element = head_ptr->next;
	while(next_element->next){
		
			count++;
			next_element = next_element->next;
	}
	printf("Returning count:%d \n",count);
	return count;
}

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
uint32_t get_data(NODE* head_ptr,uint32_t index){

	printf("In get_data function \n");
	NODE *next_element;
	INFO *node_info;

	if(index == LINKED_LIST_NUM_ZERO){
		
		printf("Invalid position \n");
		return LINKED_LIST_NUM_ZERO;
	} 
	if(head_ptr->next == NULL){
		
		printf("size ==0 \n");
		return LINKED_LIST_NUM_ZERO;
	}	

	next_element = head_ptr->next;
	for(int count =LINKED_LIST_NUM_ONE; count<index; count++){
		next_element =next_element->next;
	}

	node_info = GET_LIST_CONTAINER(next_element,struct info,list);
	
	return(node_info->data);
}

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
NODE* insert_at_position(NODE* head_ptr,uint32_t info,uint32_t index){
	
	printf("In insert_at_position function \n");

	if(index == LINKED_LIST_NUM_ZERO){
		
		printf("Not inserting any item, since index is zero");
		return head_ptr; 
	}
	
	/* Creating a new node */
	INFO *new_node = (INFO *)malloc(sizeof(INFO));
	NODE *next_element;
	if(new_node == NULL){
		
			printf("Error in malloc\n");
			return NULL;
	}
	
	/* Check for empty linked list */
	if(head_ptr->next == NULL){
		
		printf("Linked list is empty, so entering data in first node \n");
		new_node->data = info;
		(new_node->list).prev = NULL;
		(new_node->list).next = NULL;
		head_ptr->next = &(new_node->list);
		return head_ptr;
	}
	else{
			int list_size = size(head_ptr);
			if(index > list_size){
				
				printf("Entered position is greater than list size, so creating end node \n");
				insert_at_end(head_ptr,info);
				return head_ptr;
			}
			else{
				
				printf("Creating node at required position \n");
				if(index == LINKED_LIST_NUM_ONE){
					
					insert_at_beginning(head_ptr,info);
				}
				else{
					
					next_element = head_ptr->next;
					for(int count =LINKED_LIST_NUM_ONE; count<index; count++){
						next_element =next_element->next;
					}
				
					new_node->data = info;
					(new_node->list).next = next_element;
					(new_node->list).prev = next_element->prev;
				
					next_element->prev->next = &(new_node->list);
					next_element->prev = &(new_node->list);
				}	
				return head_ptr;				
			}	
	}	
}

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
uint32_t print_list(NODE* head_ptr){
	
	printf("In print_list function \n");

	if(head_ptr->next == NULL){
		
		printf("head_ptr == NULL \n");
		return LINKED_LIST_NUM_ZERO;
	}
	
	NODE *next_element;
	INFO *node_info;
	next_element = head_ptr->next;
	while(next_element->next){
		
			node_info = GET_LIST_CONTAINER(next_element,struct info,list);
			printf("Node data is:%d\n",node_info->data);
			next_element = next_element->next;
	}
	node_info = GET_LIST_CONTAINER(next_element,struct info,list);
	printf("Node data is:%d\n",node_info->data);
	return LINKED_LIST_NUM_ZERO;		

}

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
NODE* delete_at_beginning(NODE* head_ptr){
	
	printf("In delete_at_beginning function\n");
	NODE *next_element;
	INFO *node_info;
	if(head_ptr->next == NULL){
		
		printf("Not deleting any item, since head pointer is NULL");
		return head_ptr;
	}
	else{
		
		int list_size = size(head_ptr);
		if(list_size == LINKED_LIST_NUM_ZERO){
			
			printf("Not deleting any item, since list size is zero");
			return head_ptr;
		}
		else if(list_size == LINKED_LIST_NUM_ONE){
	
			printf("In list_size==1\n");
			next_element = head_ptr->next;
			node_info = GET_LIST_CONTAINER(next_element,struct info,list);
			free(node_info);
			head_ptr->next=NULL;
			return head_ptr;		
		}
		else{
	
			printf("In list_size >1 \n");
			next_element = head_ptr->next;
			next_element->next->prev = NULL;
			head_ptr->next = next_element->next;
			node_info = GET_LIST_CONTAINER(next_element,struct info,list);
			free(node_info);
		
			return head_ptr;
		}
	}
}

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
NODE* delete_at_end(NODE* head_ptr){

	printf("In delete_at_end function\n");
	NODE *next_element;
	INFO *node_info;
	NODE *final_element;
	if(head_ptr->next == NULL){
		
		printf("Not deleting any item, since head pointer is NULL");
		return head_ptr;
	}
	else{
		
		int list_size = size(head_ptr);
		if(list_size == LINKED_LIST_NUM_ZERO){
			printf("Not deleting any item, since list size is zero");
			return head_ptr;
		}
		else if(list_size == LINKED_LIST_NUM_ONE){
	
			printf("In list_size==1\n");
			next_element = head_ptr->next;
			node_info = GET_LIST_CONTAINER(next_element,struct info,list);
			free(node_info);
			head_ptr->next=NULL;
			return head_ptr;		
		}
		else{
		
			next_element = head_ptr->next;
			while(next_element->next){
					next_element =next_element->next;
			}
			final_element = next_element->prev;
			final_element->next = NULL;

			node_info = GET_LIST_CONTAINER(next_element,struct info,list);
			free(node_info);
		
			return head_ptr;
		}
	}
}

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
NODE* delete_at_position(NODE* head_ptr, uint32_t index){

	printf("In delete_at_position function \n");
	NODE *next_element;
	INFO *node_info;

	if(index == LINKED_LIST_NUM_ZERO){
		
		printf("Not deleting any item, since index is zero");
		return head_ptr; 
	}
	if(head_ptr->next == NULL){
		
		printf("Not deleting any item, since head pointer is NULL");
		return head_ptr;
	}
	else{
		
		int list_size = size(head_ptr);
		if(list_size == LINKED_LIST_NUM_ZERO || index > list_size){
			printf("Not deleting any item, since list size is zero");
			return head_ptr;
		}
		else if(list_size == LINKED_LIST_NUM_ONE){
	
			printf("In list_size==1\n");
			next_element = head_ptr->next;
			node_info = GET_LIST_CONTAINER(next_element,struct info,list);
			free(node_info);
			head_ptr->next=NULL;
			return head_ptr;	
		}
		else{
			printf("In list_size>1\n");
			if(index == LINKED_LIST_NUM_ONE){
				delete_at_beginning(head_ptr);
			}
			else{
				if(list_size == index){
					delete_at_end(head_ptr);
				}
				else{
					next_element = head_ptr->next;
					for(int count =LINKED_LIST_NUM_ONE; count<index; count++){
						next_element =next_element->next;
					}
	
	
					next_element->prev->next = next_element->next;
					next_element->next->prev = next_element->prev;
					node_info = GET_LIST_CONTAINER(next_element,struct info,list);
					free(node_info);
				}
			}
			return head_ptr;
		}
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
	NODE *next_element;
	INFO *node_info;
	next_element = head_ptr->next;
	while(next_element->next){
		
			node_info = GET_LIST_CONTAINER(next_element,struct info,list);
			free(node_info);
			next_element = next_element->next;
	}
	node_info = GET_LIST_CONTAINER(next_element,struct info,list);
	free(node_info);
	head_ptr->next = NULL;
	return head_ptr;
	
}

/* Main function definition */
int main(void ){
	
	/* Creating a head node */
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	int status = LINKED_LIST_NUM_ZERO;
	int node_data,node_position;
	
	/* Menu for the doubly linked list */
	while(LINKED_LIST_NUM_ONE){
		
		printf("\nMenu for doubly linked list:\n");
		printf("Enter 1 for inserting node at beginning\n");
		printf("Enter 2 for inserting node at end\n");
		printf("Enter 3 for inserting node at any position\n");
		printf("Enter 4 for deleting node at beginning\n");
		printf("Enter 5 for deleting node at end\n");
		printf("Enter 6 for deleting node at any position\n");
		printf("Enter 7 for size of the linked list\n");
		printf("Enter 8 for printing the nodes\n");
		printf("Enter 9 for destroying all the nodes\n");
		printf("Enter 10 for getting data of respective node\n");
		printf("Enter 11 for exit\n");
		printf("\nEnter the input:\n");
		scanf("%d",&status);
		
		if(status>LINKED_LIST_NUM_ZERO  && status<LINKED_LIST_NUM_TWELVE){
			if(status == LINKED_LIST_NUM_ONE){
					printf("Please enter the node data you want to store:\n");
					scanf("%d",&node_data);
					insert_at_beginning(head,node_data);
			}
			else if(status == LINKED_LIST_NUM_TWO){
					printf("Please enter the node data you want to store:\n");
					scanf("%d",&node_data);
					insert_at_end(head,node_data);
			}
			else if(status == LINKED_LIST_NUM_THREE){
					printf("Please enter the node data you want to store:\n");
					scanf("%d",&node_data);
					printf("Please enter the position of node you want to store:\n");
					scanf("%d",&node_position);
					insert_at_position(head,node_data,node_position);
			}
			else if(status == LINKED_LIST_NUM_FOUR){
					delete_at_beginning(head);
			}
			else if(status == LINKED_LIST_NUM_FIVE){
					delete_at_end(head);
			}
			else if(status == LINKED_LIST_NUM_SIX){
					printf("Please enter the position of node you want to delete:\n");
					scanf("%d",&node_position);
					delete_at_position(head,node_position);
			}
			else if(status == LINKED_LIST_NUM_SEVEN){
					int size_linked_list = size(head);
					printf("Size of the linked list is:%d \n", size_linked_list);
			}
			else if(status == LINKED_LIST_NUM_EIGHT){
					print_list(head);
			}
			else if(status == LINKED_LIST_NUM_NINE){
				destroy(head);
			}
			else if(status == LINKED_LIST_NUM_TEN){
				printf("Please enter the position of node you want to store:\n");
				scanf("%d",&node_position);
				uint32_t return_value = get_data(head, node_position);
				printf("Node value is:%d \n",return_value);
			}
			else{
				exit(LINKED_LIST_NUM_ZERO);
			}
		}
		else{	
			printf("Please enter valid input\n");
		}
	}
	return LINKED_LIST_NUM_ZERO;
}

