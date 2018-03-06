#include "fcntl.h"           /* For O_* constants */
#include "sys/stat.h"        /* For mode constants */
#include "mqueue.h"
#include <stdio.h>
#include <string.h>

#define QUEUE_NAME   "/example_mq"
#define QUEUE_PERMISSIONS 0660

typedef struct {
	char *string;
    long int string_length;
} string_info;

typedef struct {
	string_info info;
    bool switch_satus;
} message;

void  child_process(void)
{
	printf("Start of the child process \n");
	
	mqd_t mq2;
	
	mq2 = mq_open(QUEUE_NAME,O_RDWR | O_CREAT, QUEUE_PERMISSIONS, NULL);
	if(mq2 == -1) {
		
		printf("Error in opening message_queue");
		exit(1);
	}
	
	message *sample_message = (message *)malloc(sizeof(message));
	
	if( mq_receive(mq1,sample_message,sizeof(*sample_message),NULL) == -1){
		
		printf("Error in receiving message on message_queue");
	}
	
	printf("End of the child process \n");
}

void  parent_process(void)
{
    printf("Start of the parent process \n"); 
	
	mqd_t mq1;
	
	message *sample_message = (message *)malloc(sizeof(message));
	
	sample_message->info.string = "Sending message for switch status";
	sample_message->info.string_length = strlen("Sending message for switch status");
	sample_message->info.switch_satus = True;	
	
	mq1 = mq_open(QUEUE_NAME,O_RDWR | O_CREAT, QUEUE_PERMISSIONS, NULL);
	if(mq1 == -1) {
		
		printf("Error in opening message_queue");
		exit(1);
	}
	if( mq_send(mq1,sample_message,sizeof(*sample_message),1)== -1){
		printf("Error in sending message on message_queue");
	}
	printf("End of the parent process \n");
}

int  main(void)
{
	pid_t  pid;

	pid = fork();
	if (pid == 0) 
	  child_process();
	else 
	  parent_process();
	return 0;
}



