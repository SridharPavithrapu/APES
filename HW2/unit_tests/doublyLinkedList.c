
#include "doublyLinkedList.h"




NODE* insert_at_beginning(NODE* head_ptr, uint32_t info){

	printf("In insert_at_beginning function \n");
	
	INFO *new_node = (INFO *)malloc(sizeof(INFO));
	NODE *next_element;
	if(new_node == NULL){
		
			printf("Error in malloc\n");
			return NULL;
	}
	printf("No error in malloc\n");
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

NODE* insert_at_end(NODE* head_ptr, uint32_t info){
	
	printf("In insert_at_end function \n");	
	
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

uint32_t get_data(NODE* head_ptr,uint32_t index){

	printf("In get_data function \n");
	NODE *next_element;
	INFO *node_info;

	if(index == 0){
		printf("Invalid position \n");
		return 0;
	} 
	if(head_ptr->next == NULL){
		printf("size ==0 \n");
		return 0;
	}	

	next_element = head_ptr->next;
	for(int count =1; count<index; count++){
		next_element =next_element->next;
	}

	node_info = GET_LIST_CONTAINER(next_element,struct info,list);
	
	return(node_info->data);
}

NODE* insert_at_position(NODE* head_ptr,uint32_t info,uint32_t index){
	
	printf("In insert_at_position function \n");

	if(index == 0){
		printf("Not inserting any item, since index is zero");
		return head_ptr; 
	}
		
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
				return head_ptr;				
			}	
	}	
}

uint32_t print_list(NODE* head_ptr){
	
	printf("In print_list function \n");

	if(head_ptr->next == NULL){
		printf("head_ptr == NULL \n");
		return 0;
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
	return 0;		

}

NODE* delete_at_beginning(NODE* head_ptr){
	
	printf("In delete_at_beginning function\n");
	NODE *next_element;
	INFO *node_info;
	if(head_ptr->next == NULL)
	{
		printf("Not deleting any item, since head pointer is NULL");
		return head_ptr;
	}
	else{
		int list_size = size(head_ptr);
		if(list_size == 0){
			printf("Not deleting any item, since list size is zero");
			return head_ptr;
		}
		else if(list_size == 1){
	
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

NODE* delete_at_end(NODE* head_ptr){

	printf("In delete_at_end function\n");
	NODE *next_element;
	INFO *node_info;
	NODE *final_element;
	if(head_ptr->next == NULL)
	{
		printf("Not deleting any item, since head pointer is NULL");
		return head_ptr;
	}
	else{
		int list_size = size(head_ptr);
		if(list_size == 0){
			printf("Not deleting any item, since list size is zero");
			return head_ptr;
		}
		else if(list_size == 1){
	
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

NODE* delete_at_position(NODE* head_ptr, uint32_t index){

	printf("In delete_at_position function \n");
	NODE *next_element;
	INFO *node_info;

	if(index == 0){
		printf("Not deleting any item, since index is zero");
		return head_ptr; 
	}
	if(head_ptr->next == NULL)
	{
		printf("Not deleting any item, since head pointer is NULL");
		return head_ptr;
	}
	else{
		
		int list_size = size(head_ptr);
		if(list_size == 0 || index > list_size){
			printf("Not deleting any item, since list size is zero");
			return head_ptr;
		}
		else if(list_size == 1){
	
			printf("In list_size==1\n");
			next_element = head_ptr->next;
			node_info = GET_LIST_CONTAINER(next_element,struct info,list);
			free(node_info);
			head_ptr->next=NULL;
			return head_ptr;	
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
			return head_ptr;
		}
	}
}

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


