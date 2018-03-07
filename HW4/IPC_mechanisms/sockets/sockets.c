/***************************************************************************** 
* Copyright (C) 2018 by Sridhar Pavithrapu 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are 
* permitted to modify this and use it to learn about kernel timers.
* Sridhar Pavithrapu and the University of Colorado are not liable for 
* any misuse of this material.  
*****************************************************************************/ 


/** 
* @file sockets.c 
* @brief  Includes function declarations for understanding sockets.
* @author Sridhar Pavithrapu 
* @date March 6 2018 
**/

/* Headers Section */
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

#define SOCKET_PATH "./IPC_Socket"
#define BUFFER_SIZE 1024

typedef struct {
        char string[BUFFER_SIZE];
        unsigned int string_length;
}string_info;

typedef struct {
        string_info string_message;
        bool switch_status;
}message;

/* Global variables */
int sockfd, sockfd_child, sockfd_parent;
struct sockaddr_un server, client;

  
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
	message receive_message;
	message sent_message;
	int return_value;

	bzero(&receive_message, sizeof(receive_message));

	socklen_t sockaddr_size = sizeof(struct sockaddr_un);
	sockfd_child = accept(sockfd, (struct sockaddr *)&client, &sockaddr_size);
	if(sockfd_child<0)
	{
		close(sockfd);
		exit(1);
	}
	
	return_value = read(sockfd_child, &receive_message, sizeof(receive_message));
	if(return_value > 0 )
	{
		char output_buffer[BUFFER_SIZE] = {0};
		strncpy(output_buffer, receive_message.info.string, receive_message.info.string_length);
		printf("\nString received from parent process:%s\n",output_buffer);
		printf("String length received from parent process:%d\n",receive_message.info.string_length);
		printf("Switch status received from parent process:%d\n\n",receive_message.switch_status);
		fflush(stdout);
		
		bzero(&sent_message, sizeof(sent_message));
		
		/* Sending acknowledgment to parent process */
		sprintf(send_buffer, "Switch status changed to %d",receive_message.switch_status);
		strncpy(sent_message.info.string , send_buffer, strlen(send_buffer));
		sent_message.info.string_length = strlen(send_buffer);
		sent_message.switch_status = receive_message.switch_status;
		
		return_value = write(sockfd_child,  &sent_message, sizeof(sent_message));
	}
	
	/* Closing sockets */
	close(sockfd);
	close(sockfd_child);
	
	
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
	message sample_message;
	message receive_message;
	char send_buffer[BUFFER_SIZE] ={0};
	int return_value;

	bzero(&sample_message, sizeof(sample_message));
	bzero(buffer, sizeof(buffer));

	sockfd_parent = socket(AF_UNIX, SOCK_STREAM, 0);          
	if (sockfd_parent < 0)
	{
		perror("Error opening socket \n");
		close(sockfd);
		close(sockfd_parent);
		exit(1);
	}

	socklen_t sockaddr_size = sizeof(struct sockaddr_un);
	return_value = connect(sockfd_parent, (struct sockaddr *)&server, sockaddr_size);    
	perror("Return value:%d \n",return_value);

	strncpy(send_buffer, "Sending message for switch status", strlen("Sending message for switch status"));

	strncpy(sample_message.info.string , send_buffer, strlen(send_buffer));
	sample_message.info.string_length = strlen(send_buffer);
	sample_message.switch_status = true;
	
	/* Check for connection */
	if(return_value == 0)
	{
		return_value = write(sockfd_parent,  &sample_message, sizeof(sample_message));        
		if(return_value > 0)
		{
			bzero(&receive_message, sizeof(receive_message));
			return_value = read(sockfd_parent, &receive_message, STRUCT_SIZE);
			if(return_value>0)
			{
				char output_buffer[BUFFER_SIZE] = {0};
				strncpy(output_buffer, receive_message.info.string, receive_message.info.string_length);
				printf("\nString received from child process:%s\n",output_buffer);
				printf("String length received from child process:%d\n",receive_message.info.string_length);
				printf("Switch status received from child process:%d\n\n",receive_message.switch_status);
				fflush(stdout);
			}
		}
	}

	/* Closing sockets */
	close(sockfd);
	close(sockfd_parent);
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

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);          
	if (sockfd < 0) 
	{
		perror("Error in opening socket \n");
		exit(1);
	}
	server.sun_family = AF_UNIX;			
	strcpy(server.sun_path, SOCKET_PATH);			
	unlink(SOCKET_PATH);

	if (bind(sockfd, (struct sockaddr *) &server, sizeof(struct sockaddr_un))) 
	{
		perror("Error in binding the Socket\n");
		exit(1);
	}
	printf("Socket name %s\n", server.sun_path);
	
	/* Listening for maximum of 10 connections */
	listen(sockfd, 10);				

	/* Creating the processes */
	pid = fork();
	if(pid < 0){
		perror("Error creating a child process");
		close(sockfd);
		exit(1);
	}
	else if(pid == 0){ 
	  parent_process();
	}
	else{
	  child_process();
	}
	
	
	unlink(SOCKET_PATH);
	return 0;
}
