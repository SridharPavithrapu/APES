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

sem_t mutex;

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
	
	char send_buffer[BUFFER_SIZE] = {0}; 
	mqd_t mq2;
	
	mq2 = mq_open(QUEUE_NAME,O_RDWR | O_CREAT, QUEUE_PERMISSIONS, NULL);
	if(mq2 == -1) {
		
		printf("Error in opening message_queue\n");
		exit(1);
	}
	
	sem_wait(&mutex);
	strncpy((char *)&receive_message, (char *)ptr, sizeof(receive_message));
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
	sprintf(sm_ptr, "%s", &sent_message);
	sem_post(&mutex);

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
	
	sem_wait(&mutex);
	sprintf(sm_ptr, "%s", &sample_message);
	sem_post(&mutex);
	
	message receive_message;

	sem_wait(&mutex);
	strncpy((char *)&receive_message, (char *)ptr, sizeof(receive_message));
	sem_post(&mutex);
	
	char output_buffer[BUFFER_SIZE] = {0};
	strncpy(output_buffer, receive_message.info.string, receive_message.info.string_length);
	printf("\nString received from child process:%s\n",output_buffer);
	printf("String length received from child process:%d\n",receive_message.info.string_length);
	printf("Switch status received from child process:%d\n\n",receive_message.switch_status);

	
	
	printf("End of the parent process \n");
}

int  main(void)
{
	pid_t  pid;
	
	/* create, initialize semaphore */
	if( sem_init(&mutex,1,1) < 0){
		
	  perror("semaphore initilization");
	  exit(0);
	}

	pid = fork();
	if (pid != 0) 
	  child_process();
	else 
	  parent_process();
  
	sem_destroy(&mutex);
	return 0;
}



