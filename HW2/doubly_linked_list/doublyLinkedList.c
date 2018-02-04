#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "doublyLinkedList.h"




Error_code insert_at_beginning(NODE* head_ptr, uint32_t info){

	printf("In insert_at_beginning function \n");
	
	INFO *new_node = (INFO *)malloc(sizeof(INFO));
	NODE *next_element;
	if(new_node == NULL){
		
			printf("Error in malloc\n");
			return MALLOC_ERROR;
	}
	printf("No error in malloc\n");
	/* Check for empty linked list */
	if(head_ptr->next == NULL){
		
		printf("Linked list is empty, so entering data in first node \n");
		new_node->data = info;
		(new_node->list).prev = NULL;
		(new_node->list).next = NULL;
		head_ptr->next = &(new_node->list);
		return SUCCESS;
	}
	else{
		printf("Inserting node at the end\n");
		new_node->data = info;
		(new_node->list).next = head_ptr->next;
		head_ptr->next = &(new_node->list);
		next_element = (new_node->list).next;
		next_element->prev = &(new_node->list);
		return SUCCESS;
	}

}

Error_code insert_at_end(NODE* head_ptr, uint32_t info){
	
	printf("In insert_at_end function \n");	
	
	INFO *new_node = (INFO *)malloc(sizeof(INFO));
	NODE *next_element;
	if(new_node == NULL){
		
			printf("Error in malloc\n");
			return MALLOC_ERROR;
	}
	
	/* Check for empty linked list */
	if(head_ptr->next == NULL){
		printf("Linked list is empty, so entering data in first node \n");
		new_node->data = info;
		(new_node->list).prev = NULL;
		(new_node->list).next = NULL;
		head_ptr->next = &(new_node->list);
		return SUCCESS;
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
		return SUCCESS;
	}

}


uint32_t size(NODE* head_ptr){

	printf("In size function \n");

	if(head_ptr->next == NULL){
		printf("size ==0 \n");
		return 0;
	}	
	
	uint32_t count = 1;
	NODE *next_element;
	next_element = head_ptr->next;
	while(next_element->next){
			count++;
			next_element = next_element->next;
	}
	printf("Returning count:%d \n",count);
	return count;
}

Error_code insert_at_position(NODE* head_ptr,uint32_t info,uint32_t index){
	
	printf("In insert_at_position function \n");

	if(index == 0){
		return INVALID_POS;
	}
		
	INFO *new_node = (INFO *)malloc(sizeof(INFO));
	NODE *next_element;
	if(new_node == NULL){
		
			printf("Error in malloc\n");
			return MALLOC_ERROR;
	}
	
	/* Check for empty linked list */
	if(head_ptr->next == NULL){
		printf("Linked list is empty, so entering data in first node \n");
		new_node->data = info;
		(new_node->list).prev = NULL;
		(new_node->list).next = NULL;
		head_ptr->next = &(new_node->list);
		return SUCCESS;
	}
	else{
			int list_size = size(head_ptr);
			if(index > list_size){
				printf("Entered position is greater than list size, so creating end node \n");
				insert_at_end(head_ptr,info);
				return SUCCESS;
			}
			else{
				printf("Creating node at required position \n");
				if(index == 1){
					insert_at_beginning(head_ptr,info);
				}
				else{
					next_element = head_ptr->next;
					for(int count =1; count<index; count++){
						next_element =next_element->next;
					}
				
					new_node->data = info;
					(new_node->list).next = next_element;
					(new_node->list).prev = next_element->prev;
				
					next_element->prev->next = &(new_node->list);
					next_element->prev = &(new_node->list);
				}	
				return SUCCESS;				
			}	
	}	
}

Error_code print_list(NODE* head_ptr){
	
	printf("In print_list function \n");

	if(head_ptr->next == NULL){
		printf("head_ptr == NULL \n");
		return SUCCESS;
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
	return SUCCESS;		

}

Error_code delete_at_beginning(NODE* head_ptr){
	
	printf("In delete_at_beginning function\n");
	NODE *next_element;
	INFO *node_info;
	
	int list_size = size(head_ptr);
	if(list_size == 0){
		return DELETE_ERROR;
	}
	else if(list_size == 1){
	
		printf("In list_size==1\n");
		next_element = head_ptr->next;
		node_info = GET_LIST_CONTAINER(next_element,struct info,list);
		free(node_info);
		head_ptr->next=NULL;
		return SUCCESS;		
	}
	else{
	
		printf("In list_size >1 \n");
		next_element = head_ptr->next;
		next_element->next->prev = NULL;
		head_ptr->next = next_element->next;
		node_info = GET_LIST_CONTAINER(next_element,struct info,list);
		free(node_info);
		
		return SUCCESS;
	}
}

Error_code delete_at_end(NODE* head_ptr){

	printf("In delete_at_end function\n");
	NODE *next_element;
	INFO *node_info;
	NODE *final_element;
	
	int list_size = size(head_ptr);
	if(list_size == 0){
		return DELETE_ERROR;
	}
	else if(list_size == 1){
	
		printf("In list_size==1\n");
		next_element = head_ptr->next;
		node_info = GET_LIST_CONTAINER(next_element,struct info,list);
		free(node_info);
		head_ptr->next=NULL;
		return SUCCESS;		
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
		
		return SUCCESS;
	}
}

Error_code delete_at_position(NODE* head_ptr, uint32_t index){

	printf("In delete_at_position function \n");
	NODE *next_element;
	INFO *node_info;

	if(index == 0){
		return INVALID_POS;
	}
		
	int list_size = size(head_ptr);
	if(list_size == 0 || index > list_size){
		return DELETE_ERROR;
	}
	else if(list_size == 1){
	
		printf("In list_size==1\n");
		next_element = head_ptr->next;
		node_info = GET_LIST_CONTAINER(next_element,struct info,list);
		free(node_info);
		head_ptr->next=NULL;
		return SUCCESS;	
	}
	else{
		printf("In list_size>1\n");
		if(index == 1){
			delete_at_beginning(head_ptr);
		}
		else{
			if(list_size == index){
				delete_at_end(head_ptr);
			}
			else{
				next_element = head_ptr->next;
				for(int count =1; count<index; count++){
					next_element =next_element->next;
				}
	
	
				next_element->prev->next = next_element->next;
				next_element->next->prev = next_element->prev;
				node_info = GET_LIST_CONTAINER(next_element,struct info,list);
				free(node_info);
			}
		}
		return SUCCESS;
	}
}

Error_code destroy(NODE* head_ptr){
	
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
	return SUCCESS;
	
}

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
		printf("Enter 10 for exit\n");
		printf("\nEnter the input:\n");
		scanf("%d",&status);
		
		if(status>0  && status<11){
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
