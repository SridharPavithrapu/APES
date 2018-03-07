/***************************************************************************** 
* Copyright (C) 2018 by Sridhar Pavithrapu 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about kernel timers.
* Sridhar Pavithrapu and the University of Colorado are not liable for 
* any misuse of this material.  
*****************************************************************************/ 


/** 
* @file pipes.c 
* @brief  Includes function declarations for understanding pipes.
* @author Sridhar Pavithrapu 
* @date March 6 2018 
**/

/* Headers Section */
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

/* Macros declaration */
#define BUFFER_SIZE 1024

/* Global structures */
/* Structure for storing string and its length */
typedef struct{
        char string[BUFFER_SIZE];
        unsigned int string_length;
}string_info;

/* Structure for storing the string and switch status */
typedef struct message
{
        string_info string_message;
        bool switch_status;
}message;

/* Global variables */
int parent_to_child_pipefd[2]; 
int child_to_parent_pipefd[2];


/*** Function Definitions ***/

/**
​ * ​ ​ @brief​ : process function for child process.
 *
 * ​ ​ @param​ ​: None 
​ *
​ * ​ ​ @return​ : None
​**/

void  child_process(void)
{
	printf("Start of the child process \n");
	
	message receive_message;
	message sent_message;
	int return_value;
	char send_buffer[BUFFER_SIZE] = {0}; 

	close(child_to_parent_pipefd[0]);
	close(parent_to_child_pipefd[1]);

	return_value = read(parent_to_child_pipefd[0], &receive_message, sizeof(receive_message));
	if(return_value > 0 )
	{
		char output_buffer[BUFFER_SIZE] = {0};
		strncpy(output_buffer, receive_message.string_message.string, receive_message.string_message.string_length);
		printf("\nString received from parent process:%s\n",output_buffer);
		printf("String length received from parent process:%d\n",receive_message.string_message.string_length);
		printf("Switch status received from parent process:%d\n\n",receive_message.switch_status);
		fflush(stdout);
		
		
		/* Sending acknowledgment to parent process */
		sprintf(send_buffer, "Switch status changed to %d",receive_message.switch_status);
		strncpy(sent_message.string_message.string , send_buffer, strlen(send_buffer));
		sent_message.string_message.string_length = strlen(send_buffer);
		sent_message.switch_status = receive_message.switch_status;
		
		return_value = write(child_to_parent_pipefd[1],  &sent_message, sizeof(sent_message));
	}

	close(child_to_parent_pipefd[1]);
	close(parent_to_child_pipefd[0]);
	
	
}

/**
​ * ​ ​ @brief​ : process function for parent process.
 *
 * ​ ​ @param​ ​: None 
​ *
​ * ​ ​ @return​ : None
​**/

void  parent_process(void)
{
	printf("Start of the parent process \n"); 
	
	close(child_to_parent_pipefd[1]);
	close(parent_to_child_pipefd[0]);
	int return_value;
	
	message sample_message;
	message receive_message;
	char send_buffer[BUFFER_SIZE] = {0};

	bzero(&sample_message, sizeof(sample_message));
	strncpy(send_buffer, "Sending message for switch status", strlen("Sending message for switch status"));
	strncpy(sample_message.string_message.string , send_buffer, strlen(send_buffer));
	sample_message.string_message.string_length = strlen(send_buffer);
	sample_message.switch_status = true;

	return_value = write(parent_to_child_pipefd[1],  &sample_message, sizeof(sample_message));
	if(return_value > 0)
	{
		bzero(&receive_message, sizeof(receive_message));
		return_value = read(child_to_parent_pipefd[0], &receive_message, sizeof(receive_message));
		if(return_value>0)
		{
			char output_buffer[BUFFER_SIZE] = {0};
			strncpy(output_buffer, receive_message.string_message.string, receive_message.string_message.string_length);
			printf("\nString received from child process:%s\n",output_buffer);
			printf("String length received from child process:%d\n",receive_message.string_message.string_length);
			printf("Switch status received from child process:%d\n\n",receive_message.switch_status);
			fflush(stdout);
		}
	}
	close(child_to_parent_pipefd[0]);
	close(parent_to_child_pipefd[1]);
}

/**
​ * ​ ​ @brief​ : Main function for spawning  processes.
 *
 * ​ ​ @param​ ​: None 
​ *
​ * ​ ​ @return​ : int (status)
​**/

int  main(void)
{
	int status; 
	pid_t  pid;

	/* Creating pipe communication */
	status = pipe(child_to_parent_pipefd);
	if(status)
	{
		perror("Child to parent pipe failure \n");
		exit(1);
	}
	status = pipe(parent_to_child_pipefd);
	if(status)
	{
		perror("Parent to child pipe failure \n");
		close(child_to_parent_pipefd[0]);
		close(child_to_parent_pipefd[1]);
		exit(1);
	}
	
	/* Creating the processes */
	pid = fork();
	if (pid != 0) 
	  child_process();
	else 
	  parent_process();
	
	return 0;
}

