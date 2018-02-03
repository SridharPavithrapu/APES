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
	/* File for storing the output */
	FILE *new_fp = fopen("output.txt","a+");
	
	int process_id,user_id;
	time_t current_time;	
	struct tm * time_info; 
	
	/* Getting the current process id and printing in the above opened file */ 
	process_id = getpid();
	fprintf(new_fp, "The current process id is: %d \n",process_id);

	/* Getting the current user id and printing in the above opened file */ 
	user_id = getuid();
	fprintf(new_fp, "The current user id is: %d \n",user_id);

	/* Getting the current date and time and printing in the above opened file */ 
	time(&current_time);
	time_info = localtime(&current_time);
	fprintf(new_fp, "The current date and time is: %s \n",asctime(time_info));

	/* Calling the systemcall and printing the output in the above opened file */
	fprintf(new_fp, "%s \n","The unsorted array is:");
	int sort_buffer[SORT_BUFFER]={};
	int sort_output[SORT_BUFFER]={};	
	for(int count=0;count<SORT_BUFFER; count++){

		sort_buffer[count]= (rand()%SORT_BUFFER);
		fprintf(new_fp, "%d ", sort_buffer[count]);
	}
	/* Calling sortArray system_call, with system call number 334 */	
	long int return_status = syscall(334,sort_buffer,SORT_BUFFER,sort_output); 
         
	if(return_status == 0) {
         
		fprintf(new_fp, "\n %s \n","The sorted array output is:");

		for(int index=0;index<SORT_BUFFER;index++)
		{
			fprintf(new_fp, "%d ", sort_output[index]);
		}
    	}
    	else{ 
		fprintf(new_fp, "\n %s \n","System call-'sortArray' did not execute as expected");
        }

	fprintf(new_fp, "%s", "\n *****END*****\n");
	/* Closing the file */	
	fclose(new_fp);
     	return 0;
}
