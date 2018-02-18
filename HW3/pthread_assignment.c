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

pthread_mutex_t rsrc_thread;
unsigned int posix_thread_id_master, kernel_thread_id_master;
unsigned int posix_thread_id_first_child, kernel_thread_id_first_child;
unsigned int posix_thread_id_second_child, kernel_thread_id_second_child;

FILE *first_child_fp;
FILE *second_child_fp;
FILE *master_fp;

typedef enum{
	child_one = 0,
	child_two = 1
	
}child_enum;

typedef struct{
	
	char * file_name;
	child_enum child_info;
	
}thread_info;

typedef enum{
	
	Info = 0,
	Debug = 1,
	Error = 2,
	Warning = 3
	
}log_type;

void logger(FILE* file_pointer, log_type type, unsigned int posix_thread_id, unsigned int kernel_thread_id, char * message, char * thread_name){
	
	char log_type[100];
	time_t Time= time(NULL);
    struct  tm tm = *localtime(&Time);
	char buffer[500];
	memset(buffer, 0 , sizeof(buffer));
	
	if(type == 0){
		strncpy(log_type, "Info", strlen("Info"));
	}
	else if(type == 1){
		strncpy(log_type, "Debug", strlen("Debug"));
	}
	else if(type == 2){
		strncpy(log_type, "Error", strlen("Error"));
	}
	else{
		strncpy(log_type, "Warning", strlen("Warning"));
	}
	
	sprintf(buffer, "Date:%02d/%02d/%04d Time:%02d:%02d:%02d Log_Type:%s Thread_Name:%s TID:%u Posix_ID:%u Message:%s \n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec, log_type, thread_name, kernel_thread_id, posix_thread_id, message); 
						
	fwrite(buffer , 1, strlen(buffer), file_pointer);		
	
}

NODE* char_occurrence(NODE* head_ptr){
	
	printf("\nIn char_occurrence function \n");
	
	if(head_ptr == NULL){
		
		printf("Linked list is empty \n");
	}
	else{
		
		NODE *current = head_ptr;
		while (current->next != NULL){
			
			if(current->details.count == 3){
				
				printf("Character \"%c\" exceeded three times\n",current->details.alphabet);
			}
		   current = current->next;
		}
		if(current->details.count == 3){
				
				printf("Character \"%c\" exceeded three times\n",current->details.alphabet);
			}
	}
	return head_ptr;
	
}


void second_child_signal_handler(int signum)
{
	static int count = 0;
	FILE *fp;
	char * line = NULL;
	size_t len = 0;
    ssize_t read;
	if(signum == SIGVTALRM){
	 
		printf (" periodic task in C++ timer %d \n", ++count);
		fp = fopen("/proc/stat","r");
		if (fp == NULL){
			printf("Error opening file\n");
		}
		while ((read = getline(&line, &len, fp)) != -1) {
			printf("%s\n", line);
		}

		fclose(fp);
		if (line)
			free(line);
		
	}
	else if(signum == SIGUSR1 || signum == SIGUSR2){
		printf (" Received usr1 or usr2 signal for second child thread \n");
		pthread_mutex_lock(&rsrc_thread);
		logger(second_child_fp, Info, posix_thread_id_second_child, kernel_thread_id_second_child, "Second child thread exited", "second_child_thread");
		pthread_mutex_unlock(&rsrc_thread);
		fclose(second_child_fp);
	}
}

void master_signal_handler(int signum)
{
	if(signum == SIGUSR1 || signum == SIGUSR2){
		printf (" Received usr1 or usr2 signal for main thread \n");
		pthread_mutex_lock(&rsrc_thread);
		logger(master_fp, Info, posix_thread_id_master, kernel_thread_id_master, "Master thread exited", "master_thread");
		pthread_mutex_unlock(&rsrc_thread);
		fclose(master_fp);
	}
}

void first_child_signal_handler(int signum)
{
	if(signum == SIGUSR1 || signum == SIGUSR2){
		printf (" Received usr1 or usr2 signal for first child thread \n");
		pthread_mutex_lock(&rsrc_thread);
		logger(first_child_fp, Info, posix_thread_id_first_child, kernel_thread_id_first_child, "First child thread exited", "first_child_thread");
		pthread_mutex_unlock(&rsrc_thread);
		fclose(first_child_fp);
	}
}

void *thread_function(void *info)
{
	thread_info *child_thread_information = (thread_info*)info;

	if(child_thread_information->child_info ==  child_one)
	{
		printf("In first child thread \n"); 
		 
		posix_thread_id = pthread_self();
		kernel_thread_id = syscall( __NR_gettid );
		
		struct sigaction sa_child_one;
		
		 /* Install periodic_task  as the signal handler for SIGVTALRM. */
		 memset (&sa_child_one, 0, sizeof (sa_child_one));
		 sa_child_one.sa_handler = &first_child_signal_handler ;
		 sigaction (SIGUSR1, &sa_child_one, NULL);
		 sigaction (SIGUSR2, &sa_child_one, NULL);
		 sigaction (SIGINT, &sa_child_one, NULL);
		
		
		first_child_fp = fopen( child_thread_information-> file_name, "a" );
		
		pthread_mutex_lock(&rsrc_thread);
		logger(first_child_fp, Info, posix_thread_id_first_child, kernel_thread_id_first_child, "First child thread started", "first_child_thread");
		pthread_mutex_unlock(&rsrc_thread);
		
		FILE *new_fp;
		new_fp = fopen("sample.txt","r");
		
		if(new_fp == NULL){
			
			printf("Error in reading file \n"); 
			exit(0);
		}
		
		char temp;
		NODE *head = NULL;
		while ((temp = fgetc(new_fp)) != EOF){
        		printf("read character:%c \n", temp);
			if((temp>='A' && temp<='Z') || (temp>='a' && temp<='z')){
				head = traverse(head,temp);
			}			
		}
		char_occurrence(head);
		destroy(head);
		fclose(new_fp);

		return NULL;
		
	}
	else if(child_thread_information->child_info ==  child_two)
	{
		printf("In second child thread \n"); 
		 
		posix_thread_id = pthread_self();
		kernel_thread_id = syscall( __NR_gettid );
		
		
		second_child_fp = fopen( child_thread_information-> file_name, "a" );
		
		pthread_mutex_lock(&rsrc_thread);
		logger(second_child_fp, Info, posix_thread_id_second_child, kernel_thread_id_second_child, "Second child thread started", "second_child_thread");
		pthread_mutex_unlock(&rsrc_thread);
		
		struct sigaction sa;
		struct itimerval timer;
		
		/* Install periodic_task  as the signal handler for SIGVTALRM. */
		memset (&sa, 0, sizeof (sa));
		sa.sa_handler = &second_child_signal_handler ;
		sigaction (SIGVTALRM, &sa, NULL);
		sigaction (SIGUSR1, &sa, NULL);
		sigaction (SIGUSR2, &sa, NULL);
		sigaction (SIGINT, &sa, NULL);

		/* Configure the timer to expire after 100 msec... */
		timer.it_value.tv_sec = 0;
		timer.it_value.tv_usec = 100000;

		/* ... and every 100 msec after that. */
		timer.it_interval.tv_sec = 0;
		timer.it_interval.tv_usec = 100000;

		/* Start a virtual timer. It counts down whenever this process is    executing. */
		setitimer (ITIMER_VIRTUAL, &timer, NULL);

		/* Do busy work. */
		while (1);
		
		

		return NULL;
	}	
	else
	{
		printf("Inavlid thread id \n");
		return NULL;
	}	
	
}

int main(int argc, char *argv[])
{
	int8_t status;
	pthread_t first_child_thread, second_child_thread;
	char output_file_name[100];
	
	/* Set default protocol for mutex */
  	pthread_mutex_init(&rsrc_thread, NULL);
	
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
	
	
	master_fp = fopen( output_file_name , "a" );
	
	posix_thread_id = pthread_self();
	kernel_thread_id = syscall( __NR_gettid ); 
	
	pthread_mutex_lock(&rsrc_thread);
	logger(master_fp, Info, posix_thread_id_master, kernel_thread_id_master, "Master thread started", "master_thread");
	logger(master_fp, Info, posix_thread_id_master, kernel_thread_id_master, "Master thread creating child threads", "master_thread");
	pthread_mutex_unlock(&rsrc_thread);
	
	struct sigaction sa_master;
		
	/* Install periodic_task  as the signal handler for SIGVTALRM. */
	memset (&sa_master, 0, sizeof (sa_master));
	sa_master.sa_handler = &first_child_signal_handler ;
	sigaction (SIGUSR1, &sa_master, NULL);
	sigaction (SIGUSR2, &sa_master, NULL);
	sigaction (SIGINT, &sa_master, NULL);
	
	
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
	
	if(pthread_mutex_destroy(&rsrc_thread) != 0)
		perror("Error in mutex destroy\n");
	
	exit(1);
	
}
