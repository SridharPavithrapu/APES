#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/syscalls.h>
#include<linux/err.h>
#include<uapi/asm-generic/errno-base.h>
#include<linux/slab.h>
#include<linux/gfp.h>

#include "sort_array.h"
#define NUMBER_ONE 1
#define NUMBER_ZERO 0

void sort_function(int32_t * kernel_input_buffer, int32_t input_size){

	int32_t outer_loop=0, inner_loop=0;
	int32_t temp;

	for(outer_loop =0; outer_loop<input_size; outer_loop++){
     		
		for(inner_loop = outer_loop+1; inner_loop<input_size; inner_loop++){

       			if(*(kernel_input_buffer+outer_loop) < *(kernel_input_buffer+inner_loop)){ 
	 			
				temp = *(kernel_input_buffer+outer_loop);
				*(kernel_input_buffer + outer_loop) = *(kernel_input_buffer + inner_loop); 
				*(kernel_input_buffer + inner_loop) = temp;
       			}
      		}
	}

}

SYSCALL_DEFINE3(sortArray, int32_t *, input_buffer, int32_t, buffer_size, int32_t *, output_buffer){

	printk(KERN_INFO "Entering the sort_array system call\n");
	printk(KERN_INFO "Validation of sort_array input arguments\n");
	/* Check for input arguments */
	if(input_buffer == NULL || output_buffer == NULL || buffer_size<256){

		printk(KERN_WARNING "Invalid input arguments\n");
		return EINVAL;
		printk(KERN_ALERT "Exiting the system call\n");
	}

	/* Allocating memory in kernel space for the user space buffer */
	int32_t *kernel_buffer = kmalloc(sizeof(int32_t) * buffer_size,GFP_KERNEL);
	if(kernel_buffer == NULL){
	
		printk(KERN_WARNING "Error in allocating kernel space memory\n");
		return ENOMEM;
		printk(KERN_ALERT "Exiting the system call\n");
	}

	/* Copying data from user space to kernel space */
	unsigned long status = copy_from_user(kernel_buffer,input_buffer,(sizeof(int32_t)*buffer_size));
	if(status != 0){

		printk(KERN_WARNING "Error in copying buffer from user space to kernel space\n");
		return EFAULT;
		printk(KERN_ALERT "Exiting the system call\n");
	
	}	

	printk(KERN_INFO "Calling sort function to sort kernel space buffer\n");
	/* Calling the sort function to perform sort of kernel space buffer */
	sort_function(kernel_buffer,buffer_size);
	printk(KERN_INFO "Exiting the sort function\n");

	/* Copying sorted buffer from kernel space to user space */
	status = copy_to_user(output_buffer,kernel_buffer,(sizeof(int32_t)*buffer_size));
	
	if(status != 0){

		printk(KERN_WARNING "Error in copying buffer from kernel space to user space\n");
		return EFAULT;
		printk(KERN_ALERT "Exiting the system call\n");
	
	}

  	printk(KERN_INFO "Exiting sort_array system call");
  	return 0;
}

