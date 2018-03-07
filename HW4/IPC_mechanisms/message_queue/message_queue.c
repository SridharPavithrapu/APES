/***************************************************************************** 
* Copyright (C) 2018 by Sridhar Pavithrapu 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about kernel timers.
* Sridhar Pavithrapu and the University of Colorado are not liable for 
* any misuse of this material.  
*****************************************************************************/ 


/** 
* @file message_queue.c 
* @brief  Includes function declarations for understanding message queue.
* @author Sridhar Pavithrapu 
* @date March 6 2018 
**/

/* Headers Section */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>
#include <errno.h>

/* Macros declaration */
#define QUEUE_NAME "/example_mq"
#define QUEUE_PERMISSIONS 0666
#define BUFFER_SIZE 1024

/* Global structures */
/* Structure for storing string and its length */
typedef struct {
	char string[BUFFER_SIZE];
    unsigned int string_length;
} string_info;

/* Structure for storing the string and switch status */
typedef struct {
	string_info info;
    bool switch_status;
} message;

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
	
	char send_buffer[BUFFER_SIZE] = {0}; 
	mqd_t mq2;
	message receive_message;
	message sent_message;
	struct mq_attr *attr1;
	mq_getattr(mq2,attr1);
	
	mq2 = mq_open(QUEUE_NAME,O_RDWR | O_CREAT, QUEUE_PERMISSIONS, NULL);
	if(mq2 == -1) {
		
		printf("Error in opening message_queue\n");
		exit(1);
	}
	
	attr1 = malloc(sizeof(struct mq_attr));
	
	/* Receiving message on message queue */
	if( mq_receive(mq2,(char *)&receive_message,attr1->mq_msgsize,NULL) == -1){
		
		printf("Error in receiving message on message_queue with erro:%s\n",strerror(errno));
			
	}
	else{
		char output_buffer[BUFFER_SIZE] = {0};
		strncpy(output_buffer, receive_message.info.string, receive_message.info.string_length);
		printf("\nString received from parent process:%s\n",output_buffer);
		printf("String length received from parent process:%d\n",receive_message.info.string_length);
		printf("Switch status received from parent process:%d\n\n",receive_message.switch_status);
	}

	/* Sending acknowledgment to parent process */
	sprintf(send_buffer, "Switch status changed to %d",receive_message.switch_status);
	strncpy(sent_message.info.string , send_buffer, strlen(send_buffer));
	sent_message.info.string_length = strlen(send_buffer);
	sent_message.switch_status = receive_message.switch_status;

	/* Sending message on message queue */
	if( mq_send(mq2,(char *)&sent_message,sizeof(sent_message),1)== -1){

		printf("Error in sending message on message_queue with erro:%s\n",strerror(errno));
	}
	

	mq_close(mq2);
	mq_unlink(QUEUE_NAME);

	printf("End of the child process \n");
	
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
	
	mqd_t mq1;
	message sample_message;
	message receive_message;
	struct mq_attr *attr1;
	
	
	char send_buffer[BUFFER_SIZE] ={0};
	strncpy(send_buffer, "Sending message for switch status", strlen("Sending message for switch status"));

	strncpy(sample_message.info.string , send_buffer, strlen(send_buffer));
	sample_message.info.string_length = strlen(send_buffer);
	sample_message.switch_status = true;	
	
	mq1 = mq_open(QUEUE_NAME,O_RDWR | O_CREAT, QUEUE_PERMISSIONS, NULL);
	if(mq1 == -1) {
		
		printf("Error in opening message_queue\n");
		exit(1);
	}

	/* Sending message on message queue */
	if( mq_send(mq1,(char *)&sample_message,sizeof(sample_message),1)== -1){
		printf("Error in sending message on message_queue\n");
	}

	
	attr1 = malloc(sizeof(struct mq_attr));
	mq_getattr(mq1,attr1);

	/* Receiving message on message queue */
	if( mq_receive(mq1,(char *)&receive_message,attr1->mq_msgsize,NULL) == -1){
		
		printf("Error in receiving message on message_queue with erro:%s\n",strerror(errno));
			
	}
	else{
		char output_buffer[BUFFER_SIZE] = {0};
		strncpy(output_buffer, receive_message.info.string, receive_message.info.string_length);
		printf("\nString received from child process:%s\n",output_buffer);
		printf("String length received from child process:%d\n",receive_message.info.string_length);
		printf("Switch status received from child process:%d\n\n",receive_message.switch_status);
	}

	mq_close(mq1);
	mq_unlink(QUEUE_NAME);
	
	printf("End of the parent process \n");
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
	
	pid_t  pid;

	/* Creating the processes */
	pid = fork();
	if (pid != 0) 
	  child_process();
	else 
	  parent_process();
	return 0;
}



