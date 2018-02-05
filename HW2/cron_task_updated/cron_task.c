/*************************************************************************************
*
* FileName        :    cron_task.c
* Description     :    This file contains necessary systemcalls for demo of cron jobs.
* File Author Name:    Sridhar Pavithrapu 
* Tools used      :    gcc, gedit
* References      :    None
*
***************************************************************************************/


/* Headers section */
#include <stdio.h>
#include <string.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <strings.h>

/* Macro's section */
#define BUFFER (100)
#define SORT_BUFFER (256)
#define CRON_NUM_ZERO (0)
#define SYS_CALL_NUMBER (334)

/**
​ * ​ ​ @brief​ : Main function for valid system calls and printing the output to a file. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ integer 0 on success.
​ */
int main(void)
{  
	
	printf("%s", "\n *****START CRON TASK*****\n");
	
	int process_id,user_id;
	time_t current_time;	
	struct tm * time_info; 
	
	/* Getting the current process id */ 
	process_id = getpid();
	printf("The current process id is: %d \n",process_id);

	/* Getting the current user id */ 
	user_id = getuid();
	printf("The current user id is: %d \n",user_id);

	/* Getting the current date and time */ 
	time(&current_time);
	time_info = localtime(&current_time);
	printf("The current date and time is: %s \n",asctime(time_info));

	/* Calling the systemcall*/
	printf("%s \n","The unsorted array is:");
	int sort_buffer[SORT_BUFFER]={};
	int sort_output[SORT_BUFFER]={};	
	for(int count=CRON_NUM_ZERO; count<SORT_BUFFER; count++){

		sort_buffer[count]= (rand()%SORT_BUFFER);
		printf("%d ", sort_buffer[count]);
	}
	/* Calling sortArray system_call, with system call number 334 */	
	long int return_status = syscall(SYS_CALL_NUMBER,sort_buffer,SORT_BUFFER,sort_output); 
         
	if(return_status == CRON_NUM_ZERO) {
         
		printf("\n %s \n","The sorted array output is:");

		for(int index=CRON_NUM_ZERO; index<SORT_BUFFER; index++)
		{
			printf("%d ", sort_output[index]);
		}
    	}
    	else{ 
		printf("\n %s \n","System call-'sortArray' did not execute as expected");
        }

	printf("%s", "\n *****END*****\n");
	
    return CRON_NUM_ZERO;
}
