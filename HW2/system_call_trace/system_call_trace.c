/*************************************************************************************
*
* FileName        :    system_call_trace.c
* Description     :    This file contains necessary systemcalls for demo of tracing
					   system calls.
* File Author Name:    Sridhar Pavithrapu 
* Tools used      :    gcc, gedit
* References      :    None
*
***************************************************************************************/

/* Headers section */
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

/* Macros section */
#define BUFFER (100)

/**
​ * ​ ​ @brief​ : Main function for valid system calls and performing necessary actions
 *            to perform demo on tracing. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ integer 0 on success.
​ */
int main(void)
{
	char file_path[BUFFER] = "new_file.txt";

	/* Printing interested string on the standard output */
	printf("This is an Introduction to APES. \n");
	
	/* Creating a new file */
	FILE *new_fp;
	
	/* Opening the file for writing */
	new_fp = fopen(file_path,"w");
	
	/* Modifying the permissions of the file to be read/write */
    
    if (chmod (file_path,S_IRWXU) < 0)
    {
        fprintf(stderr, "Error in chmod \n");
        exit(1);
    }
	
	
	
	/* Writing a character to a file */
	if(new_fp != NULL)
	{
		putc('S', new_fp);
	}
	else
	{
		/* Error opening the file */
		fprintf(stderr, "Error opening the file \n");
        exit(1);
	}
	
	putc('\n', new_fp);
	/* Closing the file */
	fclose(new_fp);
	
	/* Opening the file for appending */
	new_fp = fopen(file_path,"a");
	
	/* Allocating memory for a sample string */
	char *new_string;
	new_string = malloc(BUFFER);
	
	/* Reading input of the string from the command line */
	printf("Enter the input string: \n");
	scanf("%s",new_string);
	fputs(new_string,new_fp);
	
	/* Flush file output */
	fflush(stdin);

	/* Closing the file */
	fclose(new_fp);
	
	/* Opening the file for writing */
	new_fp = fopen(file_path,"r");
	
	/* Writing a character to a file */
	if(new_fp != NULL)
	{
		int single_character;
		/* Reading a single character from file */ 
		single_character = getc(new_fp);
		printf("Character read is :%d",single_character);
		
		char string_buffer[BUFFER];
		/* Reading a string from the file */
		fgets(string_buffer, BUFFER, new_fp);
	}
	else
	{
		/* Error opening the file */
		fprintf(stderr, "Error opening the file \n");
        exit(1);
	}
	
	/* Freeing the allocated memory */
	free(new_string);
	
	/* Closing the file */
	fclose(new_fp);	

	exit(0);
}
