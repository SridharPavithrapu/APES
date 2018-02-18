/*************************************************************************************
*
* FileName        :    pthread_assignment.c
* Description     :    This file contains necessary function for creating pthreads 
*						and handling signal handlers for the threads created. 
*					   
* File Author Name:    Sridhar Pavithrapu 
* Tools used      :    gcc, gedit
* References      :    None
*
***************************************************************************************/

/* Headers Section */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <signal.h>
#include "linked_list.h"

/* Macros section */
#define PTHREAD_NUM_ZERO (0)
#define PTHREAD_NUM_ONE (1)
#define PTHREAD_NUM_TWO (2)
#define PTHREAD_NUM_THREE (3)
#define PTHREAD_BUFFER (100)
#define PTHREAD_BUFFER_MAX (2000)
#define PTHREAD_TIME_PERIOD (100000)
#define PTHREAD_YEAR (1900)


/***Global enums ***/

/*
​* ​ ​ @brief   ​ : Enum to store log type
*   
​*/
typedef enum{
	
	Info = PTHREAD_NUM_ZERO,
	Debug = PTHREAD_NUM_ONE,
	Error = PTHREAD_NUM_TWO,
	Warning = PTHREAD_NUM_THREE
	
}log_type;

/*
​* ​ ​ @brief   ​ : Enum to determine child number
*   
​*/
typedef enum{
	child_one = PTHREAD_NUM_ZERO,
	child_two = PTHREAD_NUM_ONE
	
}child_enum;

/***Global Structures ***/

/*
​* ​ ​ @brief   ​ : Structure for the thread info
​*  ​ @contents : file_name -> input file name
*               child_info -> child number   
​*/
typedef struct{
	
	char * file_name;
	child_enum child_info;
	
}thread_info;



/* Global variables */

/* Mutex variable */
pthread_mutex_t rsrc_thread;
/* Variables to determine posix thread id and kernel thread id */
int posix_thread_id_master, kernel_thread_id_master;
int posix_thread_id_first_child, kernel_thread_id_first_child;
int posix_thread_id_second_child, kernel_thread_id_second_child;
pthread_t first_child_thread, second_child_thread;
/* File pointers for each thread to open input file */
FILE *first_child_fp;
FILE *second_child_fp;
FILE *master_fp;
/* Head pointer of linked list */
NODE *head = NULL;

/*** Function Definitions ***/

/**
​* ​ ​ @brief​ : Stores logs in the file
​* ​ ​
​*
​* ​ ​ @param​ ​ file_pointer  ​ A pointer to the input file
*	@param​ ​ type  ​log type
*	@param​ ​ posix_thread_id  ​ posix thread id
*	@param​ ​ kernel_thread_id  ​ kerenel thread id 
*	@param​ ​ message  ​ A pointer to the message
*	@param​ ​ thread_name  ​ Name of the thread
​*
​* ​ ​ @return​ ​Node pointing to head
​*/
void logger(FILE* file_pointer, log_type type, int posix_thread_id, int kernel_thread_id, char * message, char * thread_name){
	
	char log_type[PTHREAD_BUFFER];
	time_t Time= time(NULL);
    struct  tm tm = *localtime(&Time);
	char buffer[PTHREAD_BUFFER_MAX];
	memset(buffer, PTHREAD_NUM_ZERO , sizeof(buffer));
	memset(log_type, PTHREAD_NUM_ZERO , sizeof(log_type));
	
	/* Checking log type */
	if(type == PTHREAD_NUM_ZERO){
		strncpy(log_type, "Info", strlen("Info"));
	}
	else if(type == PTHREAD_NUM_ONE){
		strncpy(log_type, "Debug", strlen("Debug"));
	}
	else if(type == PTHREAD_NUM_TWO){
		strncpy(log_type, "Error", strlen("Error"));
	}
	else{
		strncpy(log_type, "Warning", strlen("Warning"));
	}
	
	sprintf(buffer, "Date:%02d/%02d/%04d Time:%02d:%02d:%02d Log_Type:%s Thread_Name:%s TID:%u Posix_ID:%u Message:%s \n", tm.tm_mday, tm.tm_mon+PTHREAD_NUM_ONE, tm.tm_year+PTHREAD_YEAR, tm.tm_hour, tm.tm_min, tm.tm_sec, log_type, thread_name, kernel_thread_id, posix_thread_id, message); 
	
	/* Storing message into the file */	
	fwrite(buffer , PTHREAD_NUM_ONE, strlen(buffer), file_pointer);		
	
}

/**
​* ​ ​ @brief​ : Checking the character occurrence in the linked list
​* ​ ​
​* ​ ​ Returns a node pointing to head
​*
*	@param​ ​ head_ptr  ​ A pointer to the head of the Linked List
​*
​* ​ ​ @return​ ​Node pointing to head
​*/
NODE* char_occurrence(NODE* head_ptr){
	
	printf("\nIn char_occurrence function \n");
	
	/* Check for head pointer */
	if(head_ptr == NULL){
		
		printf("Linked list is empty \n");
	}
	else{
		
		NODE *current = head_ptr;
		/* Check if any character occurred thrice in the linked list */
		while (current->next != NULL){
			
			if(current->details.count == PTHREAD_NUM_THREE){
				
				printf("Character \"%c\" has occurred thrice\n",current->details.alphabet);
			}
		   current = current->next;
		}
		if(current->details.count == PTHREAD_NUM_THREE){
				
				printf("Character \"%c\" has occurred thrice\n",current->details.alphabet);
			}
	}
	return head_ptr;
	
}

/**
​* ​ ​ @brief​ : Signal handler for second child thread
​* ​ ​
​* ​ ​ Returns N/A
​*
*	@param​ ​ signum  ​ Signal number
​*
​* ​ ​ @return​ ​N/A
​*/
void second_child_signal_handler(int signum)
{
	FILE *fp;
	char * line = NULL;
	size_t len = PTHREAD_NUM_ZERO;
    ssize_t read;
	
	/* Check for signal type */
	if(signum == SIGVTALRM){
	 
		fp = fopen("/proc/stat","r");
		if (fp == NULL){
			printf("Error opening file\n");
		}
		/* Logging CPU utilization */
		while ((read = getline(&line, &len, fp)) != -PTHREAD_NUM_ONE) {
			pthread_mutex_lock(&rsrc_thread);
			logger(second_child_fp, Info, posix_thread_id_second_child, kernel_thread_id_second_child, line, "second_child_thread");
			pthread_mutex_unlock(&rsrc_thread);
		}

		fclose(fp);
		if (line){
			free(line);
		}
	}
	else if(signum == SIGUSR1 || signum == SIGUSR2 || signum == SIGINT){
		printf (" Received usr1/usr2/sigint signal for second child thread \n");
		
		pthread_mutex_lock(&rsrc_thread);
		logger(second_child_fp, Info, posix_thread_id_second_child, kernel_thread_id_second_child, "Second child thread exited", "second_child_thread");
		pthread_mutex_unlock(&rsrc_thread);
		fclose(second_child_fp);
		
		pthread_cancel(second_child_thread);
	}
}


/**
​* ​ ​ @brief​ : Signal handler for first child thread
​* ​ ​
​* ​ ​ Returns N/A
​*
*	@param​ ​ signum  ​ Signal number
​*
​* ​ ​ @return​ ​N/A
​*/
void first_child_signal_handler(int signum)
{
	/* Check for signal type */
	if(signum == SIGUSR1 || signum == SIGUSR2 || signum == SIGINT){
		printf (" Received usr1/usr2/sigint signal for first child thread \n");
		/* Check for head pointer of linked list */
		if(head != NULL){

			destroy(head);
		}

		pthread_mutex_lock(&rsrc_thread);
		logger(first_child_fp, Info, posix_thread_id_first_child, kernel_thread_id_first_child, "First child thread exited", "first_child_thread");
		pthread_mutex_unlock(&rsrc_thread);
		fclose(first_child_fp);
		
		pthread_cancel(first_child_thread);
	}
}

/**
​* ​ ​ @brief​ : Thread functional handler
​* ​ ​
​* ​ ​ Returns a pointer 
​*
*	@param​ ​ info  ​ Structure for thread information
​*
​* ​ ​ @return​ ​Void pointer
​*/
void *thread_function(void *info){
	
	thread_info *child_thread_information = (thread_info*)info;

	/* Check for thread number */
	if(child_thread_information->child_info ==  child_one){
		
		printf("In first child thread \n"); 
		
		/* Getting posix id and kernel thread id of first child thread */		
		posix_thread_id_first_child = pthread_self();
		kernel_thread_id_first_child = syscall( __NR_gettid );
		
		struct sigaction sa_child_one;
		
		 /* Registering signal actions for first child thread */
		 memset (&sa_child_one, PTHREAD_NUM_ZERO, sizeof (sa_child_one));
		 sa_child_one.sa_handler = &first_child_signal_handler ;
		 sigaction (SIGUSR1, &sa_child_one, NULL);
		 sigaction (SIGUSR2, &sa_child_one, NULL);
		 sigaction (SIGINT, &sa_child_one, NULL);
		
		/* Open the input file for logging */
		first_child_fp = fopen( child_thread_information-> file_name, "a" );
		
		pthread_mutex_lock(&rsrc_thread);
		logger(first_child_fp, Info, posix_thread_id_first_child, kernel_thread_id_first_child, "First child thread started", "first_child_thread");
		pthread_mutex_unlock(&rsrc_thread);
		
		/* Reading the text file for finding character occurrence with three */
		FILE *text_file_fp;
		text_file_fp = fopen("Valentinesday.txt","r");
		
		if(text_file_fp == NULL){
			
			printf("Error in reading file \n");
			pthread_mutex_lock(&rsrc_thread);
			logger(first_child_fp, Info, posix_thread_id_first_child, kernel_thread_id_first_child, "Error in reading file", "first_child_thread");
			pthread_mutex_unlock(&rsrc_thread);
			
			exit(PTHREAD_NUM_ZERO);
		}
		
		char temp;
		/* Creating linked list and check for occurrence */
		while ((temp = fgetc(text_file_fp)) != EOF){
        		printf("read character:%c \n", temp);
			if((temp>='A' && temp<='Z') || (temp>='a' && temp<='z')){
				head = traverse(head,temp);
			}			
		}
		head = char_occurrence(head);
		head = destroy(head);
		
		pthread_mutex_lock(&rsrc_thread);
		logger(first_child_fp, Info, posix_thread_id_first_child, kernel_thread_id_first_child, "First child thread exited", "first_child_thread");
		pthread_mutex_unlock(&rsrc_thread);
		
		fclose(text_file_fp);
		fclose(first_child_fp);

		pthread_exit(NULL);
		
	}
	else if(child_thread_information->child_info ==  child_two){
		
		printf("In second child thread \n"); 
		
		/* Getting posix id and kernel thread id of second child thread */	
		posix_thread_id_second_child = pthread_self();
		kernel_thread_id_second_child = syscall( __NR_gettid );
		
		/* Open the input file for logging */
		second_child_fp = fopen( child_thread_information-> file_name, "a" );
		
		pthread_mutex_lock(&rsrc_thread);
		logger(second_child_fp, Info, posix_thread_id_second_child, kernel_thread_id_second_child, "Second child thread started", "second_child_thread");
		pthread_mutex_unlock(&rsrc_thread);

		struct sigaction sa;
		struct itimerval timer;
		
		/* Install periodic_task  as the signal handler for SIGVTALRM, and registering other signals. */
		memset (&sa, PTHREAD_NUM_ZERO, sizeof (sa));
		sa.sa_handler = &second_child_signal_handler ;
		sigaction (SIGVTALRM, &sa, NULL);
		sigaction (SIGUSR1, &sa, NULL);
		sigaction (SIGUSR2, &sa, NULL);
		sigaction (SIGINT, &sa, NULL);

		/* Configure the timer to expire after 100 mses */
		timer.it_value.tv_sec = PTHREAD_NUM_ZERO;
		timer.it_value.tv_usec = PTHREAD_TIME_PERIOD;

		/* And every 100 msec after that */
		timer.it_interval.tv_sec = PTHREAD_NUM_ZERO;
		timer.it_interval.tv_usec = PTHREAD_TIME_PERIOD;

		/* Starting virtual timer */
		setitimer (ITIMER_VIRTUAL, &timer, NULL);

		/* Continuous loop */
		while (PTHREAD_NUM_ONE);
		
		pthread_mutex_lock(&rsrc_thread);
		logger(second_child_fp, Info, posix_thread_id_second_child, kernel_thread_id_second_child, "Second child thread exited", "second_child_thread");
		pthread_mutex_unlock(&rsrc_thread);
	
		fclose(second_child_fp);

		pthread_exit(NULL);
	}	
	else{
		
		printf("Invalid thread id \n");
		return NULL;
	}	
	
}

/* Main function definition */
int main(int argc, char *argv[])
{
	int8_t status;
	
	char output_file_name[PTHREAD_BUFFER];
	
	/* Set default protocol for mutex */
  	pthread_mutex_init(&rsrc_thread, NULL);
	
	/* Creating thread info structure variables */
	thread_info first_child_info;
	thread_info second_child_info;
	
	if(argc > PTHREAD_NUM_ONE)
	{
		printf("%s",argv[PTHREAD_NUM_ONE]);
		strncpy(output_file_name, argv[PTHREAD_NUM_ONE],strlen(argv[PTHREAD_NUM_ONE]));
	}
	else
	{
		exit(PTHREAD_NUM_ONE);
	}	
	
	printf("output file name is:%s\n", output_file_name);
	
	
	master_fp = fopen( output_file_name , "a" );
	
	/* Getting posix id and kernel thread id of the master thread */
	posix_thread_id_master = pthread_self();
	kernel_thread_id_master = syscall( __NR_gettid ); 
	
	pthread_mutex_lock(&rsrc_thread);
	logger(master_fp, Info, posix_thread_id_master, kernel_thread_id_master, "Master thread started", "master_thread");
	logger(master_fp, Info, posix_thread_id_master, kernel_thread_id_master, "Master thread creating child threads", "master_thread");
	pthread_mutex_unlock(&rsrc_thread);
	
	
	/* Writing information to structure */
	first_child_info.file_name =  output_file_name;
	first_child_info.child_info = child_one;
	
	second_child_info.file_name = output_file_name;
	second_child_info.child_info = child_two;

	printf("Started creating threads\n");
	
	/* Creating first child thread */
	status = pthread_create(&first_child_thread, NULL, thread_function, (void *) &first_child_info);
	if (status)
	{
		printf("ERROR; pthread_create() for first child thread with status is %d\n", status);
		perror(NULL); 
		exit(PTHREAD_NUM_ONE);
	}
	
	/* Creating second child thread */
	status = pthread_create(&second_child_thread, NULL, thread_function, (void *) &second_child_info);
    	if (status)
	{
		printf("ERROR; pthread_create() for second child thread with status is %d\n", status);
		perror(NULL); 
		exit(PTHREAD_NUM_ONE);
	}
	
	/* Blocking the main master thread till all the threads complete its execution */
	pthread_join(first_child_thread, NULL);
	pthread_join(second_child_thread, NULL);
	

	pthread_mutex_lock(&rsrc_thread);
	logger(master_fp, Info, posix_thread_id_master, kernel_thread_id_master, "Master thread exited", "master_thread");
	pthread_mutex_unlock(&rsrc_thread);

	if(pthread_mutex_destroy(&rsrc_thread) != PTHREAD_NUM_ZERO)
		perror("Error in mutex destroy\n");

	fclose(master_fp);
	
	/* Exit the main function */
	exit(PTHREAD_NUM_ONE);
	
}
