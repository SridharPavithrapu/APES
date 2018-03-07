/***************************************************************************** 
* Copyright (C) 2018 by Sridhar Pavithrapu 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about kernel timers.
* Sridhar Pavithrapu and the University of Colorado are not liable for 
* any misuse of this material.  
*****************************************************************************/ 


/** 
* @file shared_memory.c 
* @brief  Includes function declarations for understanding shared memory.
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
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>           
#include <sys/stat.h>        
#include <mqueue.h>
#include <errno.h>


/* Macros declaration */
#define SHARED_MEMORY_PERMISSIONS 0666
#define BUFFER_SIZE 1024

/* Global structures */
/* Structure for storing string and its length */
typedef struct {
	char string[BUFFER_SIZE];
    	int string_length;
} string_info;

/* Structure for storing the string and switch status */
typedef struct {
	string_info info;
    	bool switch_status;
} message;

/* Declaring semaphore */
sem_t mutex;

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
	
	/* Name of the shared memory object */
	const char *sm_name = "SHARED_MEM";
	
	/* Shared memory file descriptor */
	int shm_fd;
	
	/* Pointer to the shared memory object */
	void *sm_ptr;
	
	/* Creating shared memory object */
	shm_fd = shm_open(sm_name, O_CREAT | O_RDWR, SHARED_MEMORY_PERMISSIONS);
	
	/* Memory mapping the shared memory object */
	sm_ptr = mmap(0, sizeof(receive_message), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	sem_wait(&mutex);
	/* Receiving message on shared memory */
	memcpy((char *)&receive_message, sm_ptr, sizeof(receive_message));
	msync(sm_ptr,sizeof(receive_message),MS_SYNC);
	sem_post(&mutex);
	

	char output_buffer[BUFFER_SIZE] = {0};
	strncpy(output_buffer, receive_message.info.string, receive_message.info.string_length);
	printf("\nString received from parent process:%s\n",output_buffer);
	printf("String length received from parent process:%d\n",receive_message.info.string_length);
	printf("Switch status received from parent process:%d\n\n",receive_message.switch_status);
	
	message sent_message;
	char send_buffer[BUFFER_SIZE] = {0}; 
	
	/* Sending acknowledgment to parent process */ 
	sprintf(send_buffer, "Switch status changed to %d",receive_message.switch_status);
	strncpy(sent_message.info.string , send_buffer, strlen(send_buffer));
	sent_message.info.string_length = strlen(send_buffer);
	sent_message.switch_status = receive_message.switch_status;

	sem_wait(&mutex);
	/* Sending message on shared memory */
	memcpy(sm_ptr, (char *)&sent_message , sizeof(sent_message));
	msync(sm_ptr,sizeof(sent_message),MS_SYNC);
	sem_post(&mutex);

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
	
	message sample_message;
	
	/* Name of the shared memory object */
	const char *sm_name = "SHARED_MEM";
	
	/* Shared memory file descriptor */
	int shm_fd;
	
	/* Pointer to the shared memory object */
	void *sm_ptr;
	
	/* Creating shared memory object */
	shm_fd = shm_open(sm_name, O_CREAT | O_RDWR, SHARED_MEMORY_PERMISSIONS);
	
	/* Configuring size of shared memory object */
	ftruncate(shm_fd, sizeof(sample_message));
	
	/* Memory mapping the shared memory object */
	sm_ptr = mmap(0, sizeof(sample_message), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	char send_buffer[BUFFER_SIZE] ={0};
	strncpy(send_buffer, "Sending message for switch status", strlen("Sending message for switch status"));

	strncpy(sample_message.info.string , send_buffer, strlen(send_buffer));
	sample_message.info.string_length = strlen(send_buffer);
	sample_message.switch_status = true;	
	
	sem_wait(&mutex);
	/* Sending message on shared memory */
	memcpy(sm_ptr, (char *)&sample_message, sizeof(sample_message));
	msync(sm_ptr,sizeof(sample_message),MS_SYNC);
	sem_post(&mutex);
	sleep(0.5);
	message receive_message;

	sem_wait(&mutex);
	/* Receiving message on shared memory */
	memcpy((char *)&receive_message,sm_ptr, sizeof(receive_message));
	msync(sm_ptr,sizeof(receive_message),MS_SYNC);
	sem_post(&mutex);
	
	char output_buffer[BUFFER_SIZE] = {0};
	strncpy(output_buffer, receive_message.info.string, receive_message.info.string_length);
	printf("\nString received from child process:%s\n",output_buffer);
	printf("String length received from child process:%d\n",receive_message.info.string_length);
	printf("Switch status received from child process:%d\n\n",receive_message.switch_status);

	
	shm_unlink(sm_name);
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
	
	/* create and  initialize semaphore */
	if( sem_init(&mutex,1,1) < 0){
		
	  perror("semaphore initilization");
	  exit(0);
	}

	/* Creating the processes */
	pid = fork();
	if (pid != 0) 
	  child_process();
	else 
	  parent_process();
  
	/* Destroying the semaphore */
	sem_destroy(&mutex);
	return 0;
}



