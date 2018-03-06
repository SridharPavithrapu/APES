#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <errno.h>


#define SHARED_MEMORY_PERMISSIONS 0666
#define BUFFER_SIZE 1024

typedef struct {
	char string[BUFFER_SIZE];
    	int string_length;
} string_info;

typedef struct {
	string_info info;
    	bool switch_status;
} message;

void  child_process(void)
{
	printf("Start of the child process \n");
	
	char send_buffer[BUFFER_SIZE] = {0}; 
	mqd_t mq2;
	
	mq2 = mq_open(QUEUE_NAME,O_RDWR | O_CREAT, QUEUE_PERMISSIONS, NULL);
	if(mq2 == -1) {
		
		printf("Error in opening message_queue\n");
		exit(1);
	}
	
	message receive_message;
	message sent_message;
	struct mq_attr *attr1;
	attr1 = malloc(sizeof(struct mq_attr));
	mq_getattr(mq2,attr1);

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

	if( mq_send(mq2,(char *)&sent_message,sizeof(sent_message),1)== -1){

		printf("Error in sending message on message_queue with erro:%s\n",strerror(errno));
	}
	

	mq_close(mq2);
	mq_unlink(QUEUE_NAME);

	printf("End of the child process \n");
	
}

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
	
	sprintf(sm_ptr, "%s", &sample_message);

	message receive_message;
	struct mq_attr *attr1;
	attr1 = malloc(sizeof(struct mq_attr));
	mq_getattr(mq1,attr1);

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

int  main(void)
{
	pid_t  pid;

	pid = fork();
	if (pid != 0) 
	  child_process();
	else 
	  parent_process();
	return 0;
}


