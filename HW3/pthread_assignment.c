#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef enum{
	child_one = 0,
	child_two = 1
	
}child_enum;

typedef struct{
	
	char * file_name;
	child_enum child_info;
	
}thread_info;

void *thread_function(void *info)
{
	thread_info *child_thread_information = (thread_info*)info;

	if(child_thread_information->child_info ==  child_one)
	{
		printf("In first child thread \n"); 
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
	char *output_file_name;
	
	thread_info *first_child;
	thread_info *second_child;
	
	if(argc > 1)
	{
		strncpy(output_file_name, argv[1],strlen(argv[1]));
	}
	else
	{
		exit(1);
	}	
	
	/* Writing information to structure */
	strncpy(first_child->file_name, output_file_name, strlen(output_file_name));
	first_child->child_info = child_one;
	
	strncpy(second_child->file_name, output_file_name, strlen(output_file_name));
	second_child->child_info = child_two;
	
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
	
	
}