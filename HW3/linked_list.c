#include "linked_list.h"


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
		
		//printf("Linked list is empty, so entering data in first node \n");
		if(data>='A' && data<='Z'){
			new_node->details.alphabet = data + 32;
		}
		else{
			new_node->details.alphabet = data;
		}
		new_node->details.count = 1;
		new_node->next = NULL;
		head_ptr = new_node;
		return head_ptr;
	}
	else{
		
		//printf("Inserting node at the first\n");
		if(data>='A' && data<='Z'){
			new_node->details.alphabet = data + 32;
		}
		else{
			new_node->details.alphabet = data;
		}
		new_node->details.count = 1;
		new_node->next = head_ptr;
		head_ptr = new_node;
		return head_ptr;
	}

}

NODE* destroy(NODE* head_ptr){
	
	printf("In destroy function \n");
	NODE *current = head_ptr;
	NODE *next_element;
	if(head_ptr == NULL){
		
		printf("Not deleting any item, since head pointer is NULL");
		return NULL;
	}
	else{
		
		while (current->next != NULL) {
			
		   next_element = current->next;
		   free(current);
		   current = next_element;
		}
		head_ptr = NULL;
		return head_ptr;
	}
	
}

NODE* traverse(NODE* head_ptr,char data){
	
	printf("\nIn traverse function \n");
	
	int flag = 0;
	
	if(data>='A' && data<='Z'){
		data = data + 32;
	}

	if(head_ptr == NULL){
		//printf("In traverse head pointer null\n");
		head_ptr = insert_at_beginning(head_ptr, data);
	}
	else{
		//printf("In traverse head pointer is not null\n");
		NODE *current = head_ptr;
		while (current != NULL) {	
			printf("current->details.alphabet:%c, data:%c\n",current->details.alphabet,data);
			if(current->details.alphabet == data){
				
				current->details.count++;	
				flag = 1;
				break;
			}
		   current = current->next;
		}
		
		if(flag == 0){
			
			//printf("Inside flag 0 case\n");
			head_ptr = insert_at_beginning(head_ptr, data);
		}
	}
	return head_ptr;
}

