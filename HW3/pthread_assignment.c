#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

typedef enum{
	child_one = 0,
	child_two = 1
	
}child_enum;

typedef struct{
	
	char * file_name;
	child_enum child_info;
	
}thread_info;

NODE* char_occurrence(NODE* head_ptr){
	
	printf("\nIn char_occurrence function \n");
	
	if(head_ptr == NULL){
		
		printf("Linked list is empty \n");
	}
	else{
		
		NODE *current = head_ptr;
		while (current != NULL){
			
			if(current->details.count > 3){
				
				printf("Character \"%c\" exceeded three times\n",current->details.alphabet);
			}
		   current = current->next;
		}
	}
	return head_ptr;
	
}

void *thread_function(void *info)
{
	thread_info *child_thread_information = (thread_info*)info;

	if(child_thread_information->child_info ==  child_one)
	{
		printf("In first child thread \n"); 
		
		FILE *new_fp;
		new_fp = fopen("Valentinesday.txt","r");
		
		if(new_fp == NULL){
			
			printf("Error in reading file \n"); 
			exit(0);
		}
		
		char temp;
		NODE *head = (NODE *)malloc(sizeof(NODE));
		
		while ((temp = fgetc(new_fp)) != EOF){
        
			if((temp>='A' && temp<='Z') || (temp>='a' && temp<='z')){
				traverse(head,temp);
			}			
		}
		char_occurrence(head);
		destroy(head);
		fclose(new_fp);
		
	}
	else if(child_thread_information->child_info ==  child_two)
	{
		printf("In second child thread \n"); 
	}	
	else
	{
		printf("Inavlid thread id \n");
	}	
}

int main(int argc, char *argv[])
{
	int status;
	pthread_t first_child_thread, second_child_thread;
	char output_file_name[100];
	
	thread_info *first_child = malloc(sizeof(thread_info));
	thread_info *second_child = malloc(sizeof(thread_info));
	
	if(argc > 1)
	{
		printf("%s",argv[1]);
		strncpy(output_file_name, argv[1],strlen(argv[1]));
	}
	else
	{
		exit(1);
	}	
	
	printf("output file name is:%s\n", output_file_name);
	/* Writing information to structure */
	first_child->file_name =  output_file_name;
	first_child->child_info = child_one;
	
	second_child->file_name = output_file_name;
	second_child->child_info = child_two;

	printf("Started creating threads\n");
	
	/* Creating first child thread */
	status = pthread_create(&first_child_thread, NULL, thread_function, (void *) first_child);
	if (status)
	{
		printf("ERROR; pthread_create() for first child thread with status is %d\n", status);
		perror(NULL); 
		exit(-1);
	}
	
	/* Creating second child thread */
	status = pthread_create(&second_child_thread, NULL, thread_function, (void *) second_child);
    	if (status)
	{
		printf("ERROR; pthread_create() for second child thread with status is %d\n", status);
		perror(NULL); 
		exit(-1);
	}
	
	/* Blocking the main master thread till all the threads complete its execution */
	pthread_join(first_child_thread, NULL);
	pthread_join(second_child_thread, NULL);
	
	exit(1);
	
}
