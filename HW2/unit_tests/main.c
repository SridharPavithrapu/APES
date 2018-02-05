#include <stdio.h>
#include <stdlibh>
#include "doublyLinkedList.h"


int main(void ){
	
	NODE *head = (NODE *)malloc(sizeof(NODE));
	head->prev = NULL;
	head->next = NULL;
	int status = 0;
	int node_data,node_position;
	
	while(1){
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
		
		if(status>0  && status<12){
			if(status == 1){
					printf("Please enter the node data you want to store:\n");
					scanf("%d",&node_data);
					insert_at_beginning(head,node_data);
			}
			else if(status == 2){
					printf("Please enter the node data you want to store:\n");
					scanf("%d",&node_data);
					insert_at_end(head,node_data);
			}
			else if(status == 3){
					printf("Please enter the node data you want to store:\n");
					scanf("%d",&node_data);
					printf("Please enter the position of node you want to store:\n");
					scanf("%d",&node_position);
					insert_at_position(head,node_data,node_position);
			}
			else if(status == 4){
					delete_at_beginning(head);
			}
			else if(status == 5){
					delete_at_end(head);
			}
			else if(status == 6){
					printf("Please enter the position of node you want to delete:\n");
					scanf("%d",&node_position);
					delete_at_position(head,node_position);
			}
			else if(status == 7){
					int size_linked_list = size(head);
					printf("Size of the linked list is:%d \n", size_linked_list);
			}
			else if(status == 8){
					print_list(head);
			}
			else if(status == 9){
				destroy(head);
			}
			else if(status == 10){
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
