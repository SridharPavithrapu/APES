/**************************************************************************************
*
* FileName : sort_array_test.c
* Description : This file contains different test scenarios for random_sort system call
* (Sycall No.334).                       
* File Author Name: Sridhar Pavithrapu
* Tools used : gcc, gedit
* References : None
*
***************************************************************************************/

/* Headers section */
#include<unistd.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include <sys/time.h> 
#include <unistd.h> 
#include <assert.h>


/* Macros section */
#define SYSCALL_NO 334
#define VALID_INPUT_SIZE 256
#define INVALID_INPUT_SIZE 200
#define NUM_ZERO (0)
#define NUM_THOUSAND (1000)
#define NUM_TEN_LAKHS (1000000)


/**
​ * ​ ​ @brief​ : Function to convert time in naoseconds. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ timeval structure
​ *
​ * ​ ​ @return​ ​ returns input time in nanoseconds
​ */
long nano_seconds(struct timeval t){
	
	/* Calculate nanoseconds in a timeval structure */
	return((t.tv_sec*NUM_TEN_LAKHS + t.tv_usec) * NUM_THOUSAND); 
}

/**
​ * ​ ​ @brief​ : Test function for valid system call scenario.
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ None
​ */
void valid_test_case(void){
	
	printf("Valid test case scenario \n");
	long status = NUM_ZERO, response = NUM_ZERO;
	int32_t *input_buffer = malloc(sizeof(int32_t)*VALID_INPUT_SIZE);
	int32_t *output_buffer = malloc(sizeof(int32_t)*VALID_INPUT_SIZE);
	struct timeval start_time, stop_time;
	float average_time;
	
	/* Creating input buffer */
	for (int index=NUM_ZERO; index<VALID_INPUT_SIZE; index++){
		
		*(input_buffer+index) = rand()%VALID_INPUT_SIZE; 
	}
	
	printf("Input_Buffer: \n");
	for (int count=NUM_ZERO; count<VALID_INPUT_SIZE; count++){
		
			printf("%d ",*(input_buffer+count));
			
	}  
	printf("\n");
	
	/* Find average time for System call */ 
	response = gettimeofday(&start_time,NULL); 
	assert( response == NUM_ZERO); 

	status = syscall(SYSCALL_NO,input_buffer,VALID_INPUT_SIZE,output_buffer);
	
	if(!status){
		
		response = gettimeofday(&stop_time,NULL);   
		assert(response == NUM_ZERO); 
		average_time = (nano_seconds(stop_time) - nano_seconds(start_time));
		printf("\n\nAverage time for system call is nanoseconds:%f \n\n",average_time);
  
		printf("Sorted_Buffer: \n");
		for (int sort_index=NUM_ZERO; sort_index<VALID_INPUT_SIZE; sort_index++){
		
			printf("%d ",*(output_buffer+sort_index)); 
		}
	}
	else{
		
		printf("Error in syscall with Error ID : %ld \n\n",status);
	}
	free(input_buffer);
	free(output_buffer);
	printf("\n");
}


/**
​ * ​ ​ @brief​ : Function to check invalid input to system call.
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ None
​ */

void invalid_input_test_case(void){
	
	long status = NUM_ZERO;

	printf("\nChecking for invalid input to system call \n");
	status = syscall(SYSCALL_NO,NULL,VALID_INPUT_SIZE,NULL);
	if(!status){
		
		printf("In valid case \n");

	}
	else{
		
		printf("Systemcall error : : %ld \n",status);
	}
	printf("\n");
}

/**
​ * ​ ​ @brief​ : Function to check invalid input size error check.
​ * ​ ​ No Returns. 
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ None
​ */
void inputsize_error_test_case(void){
	
	long status = NUM_ZERO;
	int32_t *input_buffer = malloc(sizeof(int32_t)*INVALID_INPUT_SIZE);
	int32_t *output_buffer = malloc(sizeof(int32_t)*INVALID_INPUT_SIZE);
	
	/* Generating rand input array buffer */
	for (int index=NUM_ZERO; index<INVALID_INPUT_SIZE; index++){
		
		*(input_buffer+index) = rand()%INVALID_INPUT_SIZE; 
	}
	
	printf("Checking for invalid input with buffer size less than 256: \n");
	status = syscall(SYSCALL_NO,input_buffer,INVALID_INPUT_SIZE,output_buffer);
	if(!status){
		
		printf("Sorted_Buffer: \n");
		for (int count=NUM_ZERO; count<INVALID_INPUT_SIZE; count++){
			printf("%d ",*(output_buffer+count));
			
		}
	}
	else{
		
		printf("Systemcall error : %ld \n",status);
	}
	free(input_buffer);
	free(output_buffer);
	printf("\n");
}


/**
​ * ​ ​ @brief​ : Main function for calling different test case scenarios.
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ None
​ *
​ * ​ ​ @return​ ​ Returns 0 on success
​ */
int main(void ){
	
	/* Calling respective valid and invalid test scenarios */
	valid_test_case();
	invalid_input_test_case();
	inputsize_error_test_case();
	
	return NUM_ZERO;
}
