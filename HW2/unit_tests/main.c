/*************************************************************************************
*
* FileName        :    main.c
* Description     :    This file contains necessary function for double linked list
					   
* File Author Name:    Sridhar Pavithrapu 
* Tools used      :    gcc, gedit
* References      :    None
*
***************************************************************************************/

/* Headers Section */
#include <stdio.h>
#include <stdlibh>
#include "doublyLinkedList.h"


/* Macros section */
#define MAIN_NUM_ZERO (0)
#define MAIN_LIST_NUM_ONE (1)
#define MAIN_LIST_NUM_TWO (2)
#define MAIN_NUM_THREE (3)
#define MAIN_NUM_FOUR (4)
#define MAIN_NUM_FIVE (5)
#define MAIN_NUM_SIX (6)
#define MAIN_NUM_SEVEN (7)
#define MAIN_NUM_EIGHT (8)
#define MAIN_NUM_NINE (9)
#define MAIN_NUM_TEN (10)
#define MAIN_NUM_ELEVEN (11)
#define MAIN_NUM_TWELVE (12)

/* Main function definition */
int main(void ){
	
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	int status = MAIN_NUM_ZERO;
	int node_data,node_position;
	
	while(MAIN_NUM_ONE){
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
		
		if(status>MAIN_NUM_ZERO  && status<MAIN_NUM_TWELVE){
			if(status == MAIN_NUM_ONE){
					printf("Please enter the node data you want to store:\n");
					scanf("%d",&node_data);
					insert_at_beginning(head,node_data);
			}
			else if(status == MAIN_NUM_TWO){
					printf("Please enter the node data you want to store:\n");
					scanf("%d",&node_data);
					insert_at_end(head,node_data);
			}
			else if(status == MAIN_NUM_THREE){
					printf("Please enter the node data you want to store:\n");
					scanf("%d",&node_data);
					printf("Please enter the position of node you want to store:\n");
					scanf("%d",&node_position);
					insert_at_position(head,node_data,node_position);
			}
			else if(status == MAIN_NUM_FOUR){
					delete_at_beginning(head);
			}
			else if(status == MAIN_NUM_FIVE){
					delete_at_end(head);
			}
			else if(status == MAIN_NUM_SIX){
					printf("Please enter the position of node you want to delete:\n");
					scanf("%d",&node_position);
					delete_at_position(head,node_position);
			}
			else if(status == MAIN_NUM_SEVEN){
					int size_linked_list = size(head);
					printf("Size of the linked list is:%d \n", size_linked_list);
			}
			else if(status == MAIN_NUM_EIGHT){
					print_list(head);
			}
			else if(status == MAIN_NUM_NINE){
				destroy(head);
			}
			else if(status == MAIN_NUM_TEN){
				printf("Please enter the position of node you want to store:\n");
				scanf("%d",&node_position);
				uint32_t return_value = get_data(head, node_position);
				printf("Node value is:%d \n",return_value);
			}
			else{
				exit(0);
			}
		}
		else{	
			printf("Please enter valid input\n");
		}
	}
	return SUCCESS;
}
